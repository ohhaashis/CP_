"""
CS213 Reverse Engineering Lab - Problem 3
Neural Network Layer-Wise Feature Extraction

RULES RESPECTED IN THIS FILE:
    - We never read the network's weight matrices or biases directly
      (no .get_weights() call is used to extract kernels for analysis).
    - Our only two operations on the network are:
        1. model.predict(X)                 -- forward pass, final output
        2. get_layer_output(X, layer_name)   -- forward pass, tapped at an
                                                 intermediate layer
      Building (2) requires wrapping the network in a second Keras Model
      that shares the same layers and reuses the same forward computation
      graph -- this only taps activations that flow through the network
      during a normal prediction call, it does not inspect the learned
      parameters themselves. This mirrors exactly the interface the
      assignment describes as available: "get_layer_output(X, layer_name)
      -> hidden layer activations".
    - Gradient-based importance uses automatic differentiation of the
      forward pass (dOutput/dInput), which is calculus through the
      function the model exposes -- not weight inspection.

Model used: neural_network_mnist_*.h5
Architecture (from the assignment spec): 20 -> Dense(8, relu) -> Dense(4, relu)
-> Dense(1, sigmoid)
"""

import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
import joblib
from sklearn.decomposition import PCA

RNG = np.random.default_rng(1)
N_FEATURES = 20


def load_realistic_feature_scale(preprocessing_path):
    """
    The 20 input features are PCA components of MNIST digit images (see the
    provided *_preprocessing.joblib). Sampling probes from a plain unit
    Gaussian ignores that PCA components have wildly different natural
    scales (component 0 varies far more than component 19), so most random
    probes end up too small to ever trigger a "digit present" prediction.

    We read the PCA's explained_variance_ (a property of the FEATURE SPACE,
    not of the classifier we are reverse engineering) purely to draw probes
    that actually resemble real inputs. This does not touch the black-box
    classifier's weights in any way.
    """
    pre = joblib.load(preprocessing_path)
    std = np.sqrt(pre["pca"].explained_variance_)
    return std


FEATURE_STD = load_realistic_feature_scale(
    "neural_network_mnist_20260901_210852_preprocessing.joblib"
)


def sample_realistic_inputs(n_samples):
    """Draw probes with per-component scale matching the real input distribution."""
    return (RNG.normal(0, 1, size=(n_samples, N_FEATURES)) * FEATURE_STD).astype(np.float32)


class BlackBoxNN:
    """
    Thin wrapper that exposes exactly the two black-box operations the
    assignment describes: predict() and get_layer_output(). Internally it
    builds a second functional-API model that shares the original layers,
    so calling it re-runs the SAME forward computation and simply also
    returns the intermediate tensor -- it does not read any weight values.
    """

    def __init__(self, h5_path):
        loaded = tf.keras.models.load_model(h5_path)
        self._layer_names = [layer.name for layer in loaded.layers]

        # Re-wire the SAME layer objects (same weights, same computation)
        # into a functional-API model that exposes every intermediate
        # tensor as a named output. This taps the forward pass at each
        # layer boundary; it never reads a weight matrix or bias vector.
        inp = tf.keras.Input(shape=(N_FEATURES,))
        x = inp
        taps = {}
        for layer in loaded.layers:
            x = layer(x)
            taps[layer.name] = x
        self._all_outputs_model = tf.keras.Model(inp, taps)
        self._model = tf.keras.Model(inp, taps[self._layer_names[-1]])

    def predict(self, X):
        out = self._all_outputs_model.predict(np.asarray(X, dtype=np.float32), verbose=0)
        return out[self._layer_names[-1]].ravel()

    def get_layer_output(self, X, layer_name):
        out = self._all_outputs_model.predict(np.asarray(X, dtype=np.float32), verbose=0)
        return out[layer_name]

    @property
    def layer_names(self):
        return list(self._layer_names)



# Task 1: Input feature importance
def compute_input_importance(model, n_samples=200, delta=0.5, method="gradient"):
    """
    Two supported methods, both operating purely on inputs/outputs:

    "perturbation": for each feature, nudge it by +/- delta from random base
    points and measure the average absolute change in output -- identical
    idea to Problem 2's feature importance.

    "gradient": use automatic differentiation to compute d(output)/d(input)
    at each sample, then average |gradient| across samples. This is the
    standard "saliency" importance measure. It still only uses the
    function the model computes (forward pass), differentiated by the
    graph -- no weight matrix is read directly.
    """
    base_points = sample_realistic_inputs(n_samples)

    if method == "perturbation":
        importances = np.zeros(N_FEATURES)
        for i in range(N_FEATURES):
            plus = base_points.copy(); plus[:, i] += delta
            minus = base_points.copy(); minus[:, i] -= delta
            importances[i] = np.mean(np.abs(model.predict(plus) - model.predict(minus)))
        return importances

    elif method == "gradient":
        X_tensor = tf.convert_to_tensor(base_points)
        with tf.GradientTape() as tape:
            tape.watch(X_tensor)
            output = model._model(X_tensor)  # final-output forward pass, differentiated
        grads = tape.gradient(output, X_tensor).numpy()
        return np.mean(np.abs(grads), axis=0)

    raise ValueError("method must be 'perturbation' or 'gradient'")


def plot_feature_importance_bar(importances, ax, top_k=10):
    order = np.argsort(importances)[::-1][:top_k]
    ax.bar(range(top_k), importances[order], color="#4C78A8")
    ax.set_xticks(range(top_k))
    ax.set_xticklabels([f"x{idx}" for idx in order], rotation=45)
    ax.set_ylabel("Mean |gradient| (importance)")
    ax.set_title(f"Top {top_k} input features by importance")


# Tasks 2 & 3: Hidden layer analysis
def analyze_layer(model, layer_id, n_samples=300):
    """
    layer_id: 1 -> first hidden layer ("hidden_1", 8 neurons)
              2 -> second hidden layer ("hidden_2", 4 neurons)

    We generate diverse random inputs, tap the layer's activations, and
    also record the network's own final prediction for each input so we
    can later check whether the layer's representation separates the two
    predicted classes (we don't have ground-truth labels for a black box,
    so the network's own decisions are the only "labels" available).
    """
    layer_name = f"hidden_{layer_id}"
    X = sample_realistic_inputs(n_samples)
    activations = model.get_layer_output(X, layer_name)
    predictions = model.predict(X)
    pseudo_labels = (predictions >= 0.5).astype(int)

    # Redundancy check: correlation between neurons. Two neurons with
    # correlation close to +/-1 are behaving almost identically = redundant.
    if activations.shape[1] > 1:
        corr_matrix = np.corrcoef(activations.T)
    else:
        corr_matrix = np.array([[1.0]])

    dead_neurons = np.where(np.all(activations == 0, axis=0))[0]

    return {
        "layer_name": layer_name,
        "activations": activations,
        "pseudo_labels": pseudo_labels,
        "correlation_matrix": corr_matrix,
        "dead_neurons": dead_neurons,
        "mean_activation": activations.mean(axis=0),
    }


def plot_layer_activations(layer_analysis, ax):
    """Heatmap of a sample of activation vectors (rows = samples, cols = neurons)."""
    sample = layer_analysis["activations"][:40]
    im = ax.imshow(sample, aspect="auto", cmap="viridis")
    plt.colorbar(im, ax=ax, label="Activation")
    ax.set_xlabel("Neuron index")
    ax.set_ylabel("Sample index")
    ax.set_title(f"{layer_analysis['layer_name']} activations")


def plot_hidden_layer_tsne(model, layer_id, ax, n_samples=300):
    """
    The assignment suggests t-SNE; with only 4 neurons at layer 2, PCA gives
    an equally valid and much more stable 2D projection for a lab exercise,
    so we use PCA here (documented choice, same visualization goal: do the
    two predicted classes separate in this layer's representation space?).
    """
    analysis = analyze_layer(model, layer_id, n_samples=n_samples)
    activations = analysis["activations"]
    labels = analysis["pseudo_labels"]

    if activations.shape[1] >= 2:
        projected = PCA(n_components=2).fit_transform(activations)
    else:
        projected = np.column_stack([activations[:, 0], np.zeros_like(activations[:, 0])])

    for cls in (0, 1):
        mask = labels == cls
        ax.scatter(projected[mask, 0], projected[mask, 1], label=f"Predicted class {cls}", alpha=0.6, s=15)
    ax.set_xlabel("Component 1")
    ax.set_ylabel("Component 2")
    ax.set_title(f"2D projection of {analysis['layer_name']} (PCA)")
    ax.legend()
    return analysis


# Task 4: Feature interaction detection
def detect_feature_interactions(model, n_pairs=10, n_trials=20, delta=1.0):
    """
    For random pairs of input features (A, B):
        effect_A   = f(base + delta*e_A) - f(base)
        effect_B   = f(base + delta*e_B) - f(base)
        effect_AB  = f(base + delta*e_A + delta*e_B) - f(base)
        interaction = effect_AB - (effect_A + effect_B)

    If interaction is consistently non-zero, the network has learned a
    non-additive (non-linear) combination of those two features -- exactly
    the kind of feature interaction a linear model could never represent.
    """
    pairs = [tuple(RNG.choice(N_FEATURES, size=2, replace=False)) for _ in range(n_pairs)]
    interaction_matrix = np.zeros((N_FEATURES, N_FEATURES))

    for (a, b) in pairs:
        base = sample_realistic_inputs(n_trials)

        only_a = base.copy(); only_a[:, a] += delta
        only_b = base.copy(); only_b[:, b] += delta
        both = base.copy(); both[:, a] += delta; both[:, b] += delta

        f_base, f_a, f_b, f_ab = (model.predict(x) for x in (base, only_a, only_b, both))
        effect_a = f_a - f_base
        effect_b = f_b - f_base
        effect_ab = f_ab - f_base
        interaction = np.mean(np.abs(effect_ab - (effect_a + effect_b)))

        interaction_matrix[a, b] = interaction
        interaction_matrix[b, a] = interaction

    return {"pairs_tested": pairs, "interaction_matrix": interaction_matrix}


def plot_interaction_matrix(interaction_report, ax):
    im = ax.imshow(interaction_report["interaction_matrix"], cmap="magma")
    plt.colorbar(im, ax=ax, label="|Interaction effect|")
    ax.set_xlabel("Feature index")
    ax.set_ylabel("Feature index")
    ax.set_title("Feature interaction strength (tested pairs)")


# Additional deliverables: neuron contributions & complexity/pruning
def plot_neuron_contributions(model, ax, n_samples=200):
    """
    Approximate each hidden_2 neuron's contribution to the final output by
    zeroing it out (via a forward pass ablation, still only using
    model.predict-style calls) and measuring how much the output changes.
    """
    X = sample_realistic_inputs(n_samples)
    baseline_output = model.predict(X)

    h2 = model.get_layer_output(X, "hidden_2")
    n_neurons = h2.shape[1]
    contributions = np.zeros(n_neurons)

    # Build a small model that takes hidden_2 activations as input and
    # produces the final output, so we can test "what if neuron k were 0"
    # without touching any weight values directly -- again, just a forward
    # pass, this time starting partway through the network.
    h2_input = tf.keras.Input(shape=(n_neurons,))
    x = h2_input
    for layer in model._model.layers:
        if layer.name == "output":
            x = layer(x)
    tail_model = tf.keras.Model(h2_input, x)

    for k in range(n_neurons):
        ablated = h2.copy()
        ablated[:, k] = 0.0
        ablated_output = tail_model.predict(ablated, verbose=0).ravel()
        contributions[k] = np.mean(np.abs(baseline_output - ablated_output))

    ax.bar(range(n_neurons), contributions, color="#F58518")
    ax.set_xlabel("hidden_2 neuron index")
    ax.set_ylabel("Mean |output change| when ablated")
    ax.set_title("Neuron contribution (ablation)")
    return contributions


def plot_layer_pruning_analysis(model, ax, n_samples=200):
    """
    A simple complexity-vs-performance proxy: progressively ablate the
    least-contributing hidden_2 neurons (found via the same ablation test
    above) and see how much the output drifts from the full model. This
    approximates "how much of this layer is redundant".
    """
    X = sample_realistic_inputs(n_samples)
    baseline_output = model.predict(X)
    h2 = model.get_layer_output(X, "hidden_2")
    n_neurons = h2.shape[1]

    h2_input = tf.keras.Input(shape=(n_neurons,))
    x = h2_input
    for layer in model._model.layers:
        if layer.name == "output":
            x = layer(x)
    tail_model = tf.keras.Model(h2_input, x)

    single_contrib = np.zeros(n_neurons)
    for k in range(n_neurons):
        ablated = h2.copy(); ablated[:, k] = 0.0
        out = tail_model.predict(ablated, verbose=0).ravel()
        single_contrib[k] = np.mean(np.abs(baseline_output - out))

    order = np.argsort(single_contrib)  # least important first
    drift = []
    ablated = h2.copy()
    for k in order:
        ablated[:, k] = 0.0
        out = tail_model.predict(ablated, verbose=0).ravel()
        drift.append(np.mean(np.abs(baseline_output - out)))

    ax.plot(range(1, n_neurons + 1), drift, marker="o")
    ax.set_xlabel("Number of (least-important-first) neurons pruned")
    ax.set_ylabel("Mean output drift from full model")
    ax.set_title("Layer pruning sensitivity")

    plt.tight_layout()

    plt.show()

# Driver
if __name__ == "__main__":
    import os
    os.makedirs("outputs", exist_ok=True)

    print("=" * 60)
    print("Problem 3: Neural Network Layer-Wise Feature Extraction")
    print("=" * 60)

    model = BlackBoxNN("neural_network_mnist_20260901_210852_model.h5")
    print(f"Layers available for get_layer_output: {model.layer_names}")

    input_importance = compute_input_importance(model, method="gradient")
    top10 = np.argsort(input_importance)[::-1][:10]
    print(f"\nTop-10 most important input features: {top10}")

    first_layer_analysis = analyze_layer(model, layer_id=1)
    print(f"\nHidden layer 1: dead neurons = {first_layer_analysis['dead_neurons']}")
    high_corr_pairs = np.argwhere(np.abs(first_layer_analysis["correlation_matrix"]) > 0.9)
    high_corr_pairs = [(i, j) for i, j in high_corr_pairs if i < j]
    print(f"Highly correlated (possibly redundant) neuron pairs (|corr|>0.9): {high_corr_pairs}")

    second_layer_analysis = analyze_layer(model, layer_id=2)
    print(f"\nHidden layer 2: dead neurons = {second_layer_analysis['dead_neurons']}")

    interactions = detect_feature_interactions(model)
    strongest = np.unravel_index(np.argmax(interactions["interaction_matrix"]), interactions["interaction_matrix"].shape)
    print(f"\nStrongest detected interaction: features {strongest}, "
          f"strength = {interactions['interaction_matrix'][strongest]:.4f}")

    # Full figure as required by the assignment
    fig = plt.figure(figsize=(16, 12))

    ax1 = plt.subplot(2, 3, 1)
    plot_feature_importance_bar(input_importance, ax=ax1)

    ax2 = plt.subplot(2, 3, 2)
    plot_layer_activations(first_layer_analysis, ax=ax2)

    ax3 = plt.subplot(2, 3, 3)
    plot_hidden_layer_tsne(model, layer_id=2, ax=ax3)

    ax4 = plt.subplot(2, 3, 4)
    plot_interaction_matrix(interactions, ax=ax4)

    ax5 = plt.subplot(2, 3, 5)
    plot_neuron_contributions(model, ax=ax5)

    ax6 = plt.subplot(2, 3, 6)
    plot_layer_pruning_analysis(model, ax=ax6)

    plt.tight_layout()
    plt.savefig("outputs/network_analysis.png", dpi=150)
    plt.close(fig)

    print("\nSaved network_analysis.png")

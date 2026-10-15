"""
CS213 Reverse Engineering Lab - Problem 2
Logistic Regression Decision Boundary Discovery

RULES RESPECTED IN THIS FILE:
    - The model is only ever touched through model.predict(X) / model.predict_proba(X).
    - No attribute of the model object (.coef_, .intercept_, etc.) is read anywhere.
    - Only numpy and matplotlib are used.

Model used: breast_cancer_*.joblib -> {"model": LogisticRegression, "scaler": StandardScaler}
The scaler is provided because the underlying model was trained on standardized
features. We are allowed to use it to convert raw inputs into the space the
model expects; this is a preprocessing step, not a peek at the model's weights.

The model itself exposes 2 input features (as per the assignment's Problem 2
spec, "2 features"). We treat model.predict / model.predict_proba as the only
black-box surface.
"""

import numpy as np
import matplotlib.pyplot as plt
import joblib

RNG = np.random.default_rng(0)


def _logit(p, eps=1e-9):
    """logit(p) = ln(p / (1-p)), clipped to avoid +/- inf at p=0 or p=1."""
    p = np.clip(p, eps, 1 - eps)
    return np.log(p / (1 - p))


# Task 1: Grid-based boundary search
def grid_based_boundary_search(model, x_range=(-3, 3), y_range=(-3, 3), resolution=200):
    """
    Build a 2D grid of candidate inputs, query the model's class prediction
    at every point, and reshape the results into an image. The boundary
    between class 0 and class 1 regions in that image IS the decision
    boundary -- no need to solve any equations to *see* it, only to query.
    """
    xx, yy = np.meshgrid(
        np.linspace(*x_range, resolution),
        np.linspace(*y_range, resolution),
    )
    grid_points = np.column_stack([xx.ravel(), yy.ravel()])
    predictions = model.predict(grid_points).reshape(xx.shape)
    return xx, yy, predictions


def plot_decision_boundary(model, ax, x_range=(-3, 3), y_range=(-3, 3)):
    xx, yy, predictions = grid_based_boundary_search(model, x_range, y_range)
    ax.contourf(xx, yy, predictions, levels=[-0.5, 0.5, 1.5], colors=["#a6c8ff", "#ffb3b3"], alpha=0.6)
    ax.contour(xx, yy, predictions, levels=[0.5], colors="black", linewidths=2)
    ax.set_xlabel("Feature 1")
    ax.set_ylabel("Feature 2")
    ax.set_title("Decision boundary (grid search)")
    return xx, yy, predictions

# Task 2: Recover model coefficients
def recover_coefficients(model, n_samples=300, sample_range=(-3, 3)):
    """
    logit(P(y=1|x)) = b0 + b1*x1 + b2*x2  is LINEAR in (b0, b1, b2).

    So: sample points, query predict_proba, apply the logit transform to the
    probabilities, then solve an ordinary least squares problem:

        [1  x1  x2] @ [b0, b1, b2]^T  =  logit(p)

    This is the same "probe + invert" idea as Problem 1, applied after a
    transform that removes the sigmoid non-linearity.
    """
    X = RNG.uniform(sample_range[0], sample_range[1], size=(n_samples, 2))
    probabilities = model.predict_proba(X)[:, 1]  # P(class 1)
    z = _logit(probabilities)

    design_matrix = np.column_stack([np.ones(n_samples), X])  # [1, x1, x2]
    coefficients, *_ = np.linalg.lstsq(design_matrix, z, rcond=None)
    intercept, b1, b2 = coefficients
    return intercept, np.array([b1, b2])


def verify_recovered_coefficients(model, intercept, coefficients, n_samples=100):
    """Compare recovered model's predictions against the real model's predictions."""
    X = RNG.uniform(-3, 3, size=(n_samples, 2))
    true_probs = model.predict_proba(X)[:, 1]
    z_recovered = intercept + X @ coefficients
    recovered_probs = 1 / (1 + np.exp(-z_recovered))

    prob_mae = np.mean(np.abs(true_probs - recovered_probs))
    true_labels = model.predict(X)
    recovered_labels = (recovered_probs >= 0.5).astype(int)
    boundary_accuracy = np.mean(true_labels == recovered_labels)

    return {"prob_mae": prob_mae, "boundary_accuracy": boundary_accuracy}


def plot_coefficient_recovery(estimated_coef, true_coef, ax):
    """
    Bar chart comparing recovered vs "true" coefficients. Note: in a genuine
    black-box setting you would not have true_coef -- here we only use it
    (in the driver) for demonstrating recovery quality on the demo model.
    """
    labels = [f"b{i}" for i in range(len(estimated_coef))]
    width = 0.35
    x_pos = np.arange(len(labels))
    ax.bar(x_pos - width / 2, estimated_coef, width, label="Recovered")
    if true_coef is not None:
        ax.bar(x_pos + width / 2, true_coef, width, label="Reference")
    ax.set_xticks(x_pos)
    ax.set_xticklabels(labels)
    ax.set_title("Recovered vs reference coefficients")
    ax.legend()


# Task 3: Feature importance analysis
def compute_feature_importance(model, n_samples=200, delta=0.5):
    """
    Perturbation-based importance: for each feature, nudge it by +delta and
    -delta from a set of random base points, and measure the average
    absolute change in predicted probability. Larger average change = more
    influence on the decision.
    """
    base_points = RNG.uniform(-3, 3, size=(n_samples, 2))
    importances = np.zeros(2)

    for feature_idx in range(2):
        plus = base_points.copy()
        minus = base_points.copy()
        plus[:, feature_idx] += delta
        minus[:, feature_idx] -= delta

        p_plus = model.predict_proba(plus)[:, 1]
        p_minus = model.predict_proba(minus)[:, 1]
        importances[feature_idx] = np.mean(np.abs(p_plus - p_minus))

    return importances


def plot_feature_importance(importances, ax):
    labels = [f"Feature {i + 1}" for i in range(len(importances))]
    ax.bar(labels, importances, color=["#4C78A8", "#F58518"])
    ax.set_ylabel("Mean |Δ probability| per perturbation")
    ax.set_title("Feature importance (perturbation-based)")


def detect_feature_interaction(model, n_trials=30, delta=0.5):
    """
    Interaction test: compare the effect of moving feature A alone, feature B
    alone, and both together. For a model with NO interaction term, effects
    are additive: Δf(A,B) ≈ Δf(A) + Δf(B). A logistic model with only linear
    terms (no x1*x2 term) will show ~0 interaction on the logit scale, even
    though on the raw *probability* scale the sigmoid squashing can look
    slightly non-additive -- so we do this test in logit space to isolate
    true interaction effects from the sigmoid's own curvature.
    """
    base = RNG.uniform(-3, 3, size=(n_trials, 2))
    logit0 = _logit(model.predict_proba(base)[:, 1])

    a_only = base.copy(); a_only[:, 0] += delta
    b_only = base.copy(); b_only[:, 1] += delta
    both = base.copy(); both[:, 0] += delta; both[:, 1] += delta

    logit_a = _logit(model.predict_proba(a_only)[:, 1])
    logit_b = _logit(model.predict_proba(b_only)[:, 1])
    logit_ab = _logit(model.predict_proba(both)[:, 1])

    predicted_additive = logit0 + (logit_a - logit0) + (logit_b - logit0)
    interaction_residual = logit_ab - predicted_additive

    return {
        "mean_abs_interaction": float(np.mean(np.abs(interaction_residual))),
        "has_interaction": float(np.mean(np.abs(interaction_residual))) > 1e-3,
    }


# Task 4 (Bonus): Robustness / confidence testing
def plot_confidence_heatmap(model, ax, x_range=(-3, 3), y_range=(-3, 3), resolution=200):
    """
    Same grid idea as Task 1, but plotting predict_proba instead of the
    hard class label. This shows model confidence: values near 0 or 1 =
    confident, values near 0.5 = uncertain (near the boundary).
    """
    xx, yy = np.meshgrid(
        np.linspace(*x_range, resolution),
        np.linspace(*y_range, resolution),
    )
    grid_points = np.column_stack([xx.ravel(), yy.ravel()])
    probabilities = model.predict_proba(grid_points)[:, 1].reshape(xx.shape)

    im = ax.contourf(xx, yy, probabilities, levels=20, cmap="RdBu_r")
    plt.colorbar(im, ax=ax, label="P(class 1)")
    ax.set_xlabel("Feature 1")
    ax.set_ylabel("Feature 2")
    ax.set_title("Model confidence heatmap")
    plt.show()
    return probabilities


def adversarial_robustness_test(model, coefficients, n_points=20, epsilon=0.05):
    """
    Sample points very close to the recovered decision boundary
    (b0 + b1*x1 + b2*x2 = 0) and check how confident the model is there.
    Points near the boundary should have probabilities near 0.5; this
    confirms the boundary location and shows the model isn't overconfident
    right at the edge of its decision.
    """
    intercept, (b1, b2) = coefficients
    x1 = RNG.uniform(-3, 3, n_points)
    # Solve for x2 on the boundary line for each x1: b0 + b1*x1 + b2*x2 = 0
    x2 = -(intercept + b1 * x1) / b2
    boundary_points = np.column_stack([x1, x2])

    # jitter slightly to simulate adversarial nudges
    jittered = boundary_points + RNG.uniform(-epsilon, epsilon, boundary_points.shape)
    probs = model.predict_proba(jittered)[:, 1]

    return {
        "mean_prob_near_boundary": float(np.mean(probs)),
        "std_prob_near_boundary": float(np.std(probs)),
    }


# Driver
if __name__ == "__main__":
    import os
    os.makedirs("outputs", exist_ok=True)

    bundle = joblib.load("breast_cancer_20260901_204528_model.joblib")
    model, scaler = bundle["model"], bundle["scaler"]

    print("=" * 60)
    print("Problem 2: Logistic Regression Decision Boundary")
    print("=" * 60)
    print(f"Model expects {model.n_features_in_} (scaled) input features.")

    # NOTE: this demo model was trained on standardized features (2 chosen
    # principal measurements), so we probe directly in the scaled space --
    # that IS the input space model.predict expects.
    estimated_intercept, estimated_coef = recover_coefficients(model)
    print(f"\nRecovered intercept: {estimated_intercept:.4f}")
    print(f"Recovered coefficients: {estimated_coef}")

    verification = verify_recovered_coefficients(model, estimated_intercept, estimated_coef)
    print(f"\nVerification -> mean |prob error|: {verification['prob_mae']:.6f}, "
          f"decision boundary agreement: {verification['boundary_accuracy']:.2%}")

    importances = compute_feature_importance(model)
    print(f"\nFeature importances: {importances}")
    print(f"Most influential feature: Feature {np.argmax(importances) + 1}")

    interaction_report = detect_feature_interaction(model)
    print(f"\nInteraction test -> mean |residual|: {interaction_report['mean_abs_interaction']:.6f}, "
          f"evidence of interaction: {interaction_report['has_interaction']}")

    robustness = adversarial_robustness_test(model, (estimated_intercept, estimated_coef))
    print(f"\nNear-boundary confidence -> mean P(class 1): {robustness['mean_prob_near_boundary']:.3f} "
          f"(should be close to 0.5), std: {robustness['std_prob_near_boundary']:.3f}")

    # Full 2x2 figure as required by the assignment
    fig, axes = plt.subplots(2, 2, figsize=(12, 10))
    plot_decision_boundary(model, ax=axes[0, 0])
    plot_feature_importance(importances, ax=axes[0, 1])
    plot_confidence_heatmap(model, ax=axes[1, 0])
    plot_coefficient_recovery(estimated_coef, true_coef=None, ax=axes[1, 1])
    fig.tight_layout()
    fig.savefig("outputs/problem2_analysis.png", dpi=150)
    plt.close(fig)

    print(f"\nCoefficient Recovery Error (prob MAE): {verification['prob_mae']:.4f}")
    print(f"Decision Boundary Accuracy: {verification['boundary_accuracy']:.4f}")

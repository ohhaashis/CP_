"""
CS213 Reverse Engineering Lab - Problem 1
Linear Regression Model Recovery

Models used: boston_housing_*.joblib, concrete_strength_*.joblib
Both are 3-feature -> 1 continuous output black boxes.
"""

import numpy as np
import matplotlib.pyplot as plt
import joblib

N_FEATURES = 3
RNG = np.random.default_rng(42)



# Task 1: Recover the intercept
def recover_intercept(model):
    """
    A linear model computes y = b0 + b1*x1 + b2*x2 + b3*x3.
    If we query the all-zero input, every b_i * x_i term becomes b_i * 0 = 0,
    so whatever comes back IS the intercept. This costs exactly 1 API call.
    """
    zero_input = np.zeros((1, N_FEATURES))
    intercept = model.predict(zero_input)[0]
    return intercept


# Task 2: Recover individual coefficients
def recover_coefficients(model, step=1.0, n_repeats=5):
    """
    For feature i, hold all other features at 0 and query two points that
    differ ONLY in feature i by a known step size h:

        f(h * e_i) - f(0) = b0 + b_i*h - b0 = b_i * h
        => b_i = [f(h * e_i) - f(0)] / h

    This is exactly the definition of a partial derivative, and because the
    function is linear the "derivative" is a constant, so a single pair of
    probes is mathematically sufficient. We repeat with different step sizes
    and average, purely to guard against floating point noise -- not because
    the underlying model actually needs it.
    """
    baseline = model.predict(np.zeros((1, N_FEATURES)))[0]
    coefficients = np.zeros(N_FEATURES)

    for i in range(N_FEATURES):
        estimates = []
        for _ in range(n_repeats):
            h = step * (1 + RNG.random())  # vary step size a bit each time
            probe = np.zeros((1, N_FEATURES))
            probe[0, i] = h
            output = model.predict(probe)[0]
            estimates.append((output - baseline) / h)
        coefficients[i] = np.mean(estimates)

    return coefficients


# Task 3: Estimate model error / bias-variance character
def estimate_model_error(model, intercept, coefficients, n_samples=50, feature_range=(-3, 3)):
    """
    We don't have access to the true training data or labels (that's the
    point of a black box), so a literal "training MSE" is not obtainable.
    What we CAN legitimately measure:

    1. Recovery error: build our own linear function from the recovered
       (intercept, coefficients) and compare its predictions to the real
       model's predictions on fresh random points. This tells us how
       faithfully we reverse-engineered the model (should be ~0 for a
       true linear model).
    2. Prediction variance across random inputs, which tells us how
       sensitive the model's output is to its inputs.

    High recovery error + high prediction variance would suggest either a
    noisy/non-deterministic model or a mis-specified recovery (wrong
    functional form). Since linear regression predict() is deterministic,
    a near-zero recovery error confirms both correctness AND that the
    model is exactly linear (low "variance" from our recovered model's
    point of view, i.e. it generalizes perfectly because it IS the model).
    """
    X_test = RNG.uniform(feature_range[0], feature_range[1], size=(n_samples, N_FEATURES))

    true_preds = model.predict(X_test)
    recovered_preds = intercept + X_test @ coefficients

    recovery_mse = np.mean((true_preds - recovered_preds) ** 2)
    prediction_variance = np.var(true_preds)

    return {
        "recovery_mse": recovery_mse,
        "prediction_variance": prediction_variance,
        "interpretation": (
            "Recovery MSE ~ 0 confirms the black box is (to numerical precision) "
            "an exact linear function of its 3 inputs, matching our recovered "
            "coefficients. Prediction variance reflects how much the output "
            "naturally swings across the sampled input range -- this is a "
            "property of the coefficients' magnitudes and the input range, "
            "not of bias/variance in the ML sense (there's no fitting step here)."
        ),
    }


# Task 4 (Bonus): Detect non-linearity
def detect_nonlinearity(model, n_trials=20):
    """
    Linearity implies superposition: f(a) + f(b) - f(0) should equal f(a+b).
    (Because f(x) = b0 + w.x is affine: f(a+b) = b0 + w.(a+b)
     = [b0 + w.a] + [b0 + w.b] - b0 = f(a) + f(b) - f(0).)

    We test this identity on random pairs of points. If the residual is
    ~0 everywhere, there's no evidence of learned interactions or
    non-linear terms. Large, systematic residuals would indicate the
    model captures interactions (e.g. cross terms like x1*x2) or
    non-linear transforms.
    """
    f0 = model.predict(np.zeros((1, N_FEATURES)))[0]
    max_residual = 0.0
    residuals = []

    for _ in range(n_trials):
        a = RNG.uniform(-3, 3, size=(1, N_FEATURES))
        b = RNG.uniform(-3, 3, size=(1, N_FEATURES))
        fa = model.predict(a)[0]
        fb = model.predict(b)[0]
        fab = model.predict(a + b)[0]

        predicted_by_superposition = fa + fb - f0
        residual = abs(fab - predicted_by_superposition)
        residuals.append(residual)
        max_residual = max(max_residual, residual)

    return {
        "max_residual": max_residual,
        "mean_residual": float(np.mean(residuals)),
        "is_linear": max_residual < 1e-6,
    }


# Visualization
def plot_model_behavior(model, model_name="model", save_path=None):
    """
    Since we can't plot a 3-D input space directly, we vary one feature at a
    time (holding the other two at their midpoint of the probing range) and
    plot the resulting 1-D response curve for each feature. A straight line
    on each subplot IS the visual proof of linearity.
    """
    fig, axes = plt.subplots(1, N_FEATURES, figsize=(15, 4))
    x_vals = np.linspace(-5, 5, 50)

    for i in range(N_FEATURES):
        X_probe = np.zeros((50, N_FEATURES))
        X_probe[:, i] = x_vals
        y_vals = model.predict(X_probe)

        axes[i].plot(x_vals, y_vals, marker="o", markersize=3, linewidth=1)
        axes[i].set_xlabel(f"Feature {i + 1} value")
        axes[i].set_ylabel("Predicted output")
        axes[i].set_title(f"Response to feature {i + 1}\n(others held at 0)")
        axes[i].grid(alpha=0.3)

    fig.suptitle(f"Model behavior: {model_name}")
    fig.tight_layout()
    if save_path:
        fig.savefig(save_path, dpi=150)
    plt.show()
    return fig


# Driver
def run_full_analysis(model_path, model_name):
    print(f"\n{'=' * 60}\nAnalyzing: {model_name}\n{'=' * 60}")
    model = joblib.load(model_path)

    intercept = recover_intercept(model)
    print(f"Recovered intercept (b0): {intercept:.6f}")

    coefficients = recover_coefficients(model)
    print(f"Recovered coefficients (b1, b2, b3): {coefficients}")

    error_report = estimate_model_error(model, intercept, coefficients)
    print(f"Recovery MSE: {error_report['recovery_mse']:.2e}")
    print(f"Prediction variance: {error_report['prediction_variance']:.4f}")

    nonlinearity_report = detect_nonlinearity(model)
    print(f"Non-linearity check -> max residual: {nonlinearity_report['max_residual']:.2e}, "
          f"model appears linear: {nonlinearity_report['is_linear']}")

    fig = plot_model_behavior(model, model_name, save_path=f"outputs/{model_name}_behavior.png")
    plt.close(fig)

    return {
        "intercept": intercept,
        "coefficients": coefficients,
        "error_report": error_report,
        "nonlinearity_report": nonlinearity_report,
    }


if __name__ == "__main__":
    import os
    os.makedirs("outputs", exist_ok=True)

    results = {}
    results["boston_housing"] = run_full_analysis(
        "boston_housing_20260901_164311_model.joblib", "boston_housing"
    )
    results["concrete_strength"] = run_full_analysis(
        "concrete_strength_20260901_164159_model.joblib", "concrete_strength"
    )

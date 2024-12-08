#include "NumericalSolver.h"
#include <cmath>
#include <algorithm>
#include <iostream>

// Construction des matrices tridiagonales A et B pour Cranck–Nicolson
void NumericalSolver::construireMatrices(double dt, double dx, double r, double sigma) {
    size_t M = grilleSpots_.size();
    lowerDiag_.resize(M - 1);
    mainDiag_.resize(M);
    upperDiag_.resize(M - 1);

    for (size_t i = 1; i < M - 1; ++i) {
        double S = grilleSpots_[i];
        double alpha = 0.5 * dt * (sigma * sigma * S * S / (dx * dx) - r * S / dx);
        double beta = 1.0 + dt * (sigma * sigma * S * S / (dx * dx) + r);
        double gamma = 0.5 * dt * (sigma * sigma * S * S / (dx * dx) + r * S / dx);

        lowerDiag_[i - 1] = -alpha;
        mainDiag_[i] = beta;
        upperDiag_[i - 1] = -gamma;
    }

    // Conditions aux limites
    mainDiag_[0] = mainDiag_[M - 1] = 1.0;
    lowerDiag_[0] = upperDiag_[M - 2] = 0.0;
}

// Résolution de l'EDP avec Cranck–Nicolson
std::vector<double> NumericalSolver::resoudreEDP(double K, double r, double sigma, double T) {
    size_t M = grilleSpots_.size();
    size_t N = grilleTemps_.size();
    std::vector<double> V(M, 0.0);         // Valeurs actuelles
    std::vector<double> V_next(M, 0.0);    // Valeurs à la prochaine itération

    // Condition initiale (Payoff pour une option européenne CALL)
    for (size_t i = 0; i < M; ++i) {
        double S = grilleSpots_[i];
        V[i] = std::max(S - K, 0.0);
    }

    double dt = grilleTemps_[1] - grilleTemps_[0];
    double dx = grilleSpots_[1] - grilleSpots_[0];

    construireMatrices(dt, dx, r, sigma);

    // Backward in time (itérations temporelles)
    for (int n = N - 2; n >= 0; --n) {
        // Formule Cranck–Nicolson
        std::vector<double> rhs(M, 0.0);
        for (size_t i = 1; i < M - 1; ++i) {
            rhs[i] = 0.5 * (lowerDiag_[i - 1] * V[i - 1] +
                            mainDiag_[i] * V[i] +
                            upperDiag_[i - 1] * V[i + 1]);
        }

        // Gestion des conditions aux bords
        rhs[0] = 0.0; // Option CALL : Pas de valeur si S=0
        rhs[M - 1] = grilleSpots_[M - 1] - K;

        // Résolution du système tridiagonal
        resoudreMatriceTridiagonale(lowerDiag_, mainDiag_, upperDiag_, rhs);

        // Mise à jour
        V = rhs;
    }

    return V;
}

// Résolution d'un système tridiagonal
void NumericalSolver::resoudreMatriceTridiagonale(const std::vector<double>& lowerDiag,
                                                  const std::vector<double>& mainDiag,
                                                  const std::vector<double>& upperDiag,
                                                  std::vector<double>& rhs) {
    size_t n = mainDiag.size();
    std::vector<double> gamma(n);

    // Forward substitution
    gamma[0] = mainDiag[0];
    rhs[0] /= gamma[0];
    for (size_t i = 1; i < n; ++i) {
        double m = lowerDiag[i - 1] / gamma[i - 1];
        gamma[i] = mainDiag[i] - m * upperDiag[i - 1];
        rhs[i] -= m * rhs[i - 1];
    }

    // Backward substitution
    for (int i = n - 2; i >= 0; --i) {
        rhs[i] -= upperDiag[i] * rhs[i + 1] / gamma[i];
    }
}

// Affichage des diagonales pour débogage
void NumericalSolver::afficherDiagonales() const {
    std::cout << "Diagonale inférieure : ";
    for (const auto& val : lowerDiag_) std::cout << val << " ";
    std::cout << "\n";

    std::cout << "Diagonale principale : ";
    for (const auto& val : mainDiag_) std::cout << val << " ";
    std::cout << "\n";

    std::cout << "Diagonale supérieure : ";
    for (const auto& val : upperDiag_) std::cout << val << " ";
    std::cout << "\n";
}

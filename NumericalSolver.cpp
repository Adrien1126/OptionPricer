#include "NumericalSolver.h"
#include <cmath>
#include <algorithm>
#include <iostream>

// Construction des matrices tridiagonales A et B pour Crank–Nicolson
void NumericalSolver::construireMatrices(double dt, double dx, double r, double sigma) {
    size_t M = grilleSpots_.size();
    lowerDiagA_.resize(M - 1);
    mainDiagA_.resize(M);
    upperDiagA_.resize(M - 1);
    lowerDiagB_.resize(M - 1);
    mainDiagB_.resize(M);
    upperDiagB_.resize(M - 1);

    for (size_t i = 1; i < M - 1; ++i) {
        double S = grilleSpots_[i];

        // Coefficients de la matrice A
        double alphaA = -0.25 * (sigma * sigma * S * S / (dx * dx) - r * S / dx);
        double betaA = 1 / dt - 0.5 * (sigma * sigma * S * S / (dx * dx) + r);
        double gammaA = -0.25 * (sigma * sigma * S * S / (dx * dx) + r * S / dx);

        // Coefficients de la matrice B
        double alphaB = 0.25 * (sigma * sigma * S * S / (dx * dx) - r * S / dx);
        double betaB = 1 / dt + 0.5 * (sigma * sigma * S * S / (dx * dx) + r);
        double gammaB = 0.25 * (sigma * sigma * S * S / (dx * dx) + r * S / dx);

        lowerDiagA_[i - 1] = alphaA;
        mainDiagA_[i] = betaA;
        upperDiagA_[i - 1] = gammaA;

        lowerDiagB_[i - 1] = alphaB;
        mainDiagB_[i] = betaB;
        upperDiagB_[i - 1] = gammaB;

        std::cout << "i: " << i
          << ", alpha_A: " << alphaA
          << ", beta_A: " << betaA
          << ", gamma_A: " << gammaA
          << ", alpha_B: " << alphaB
          << ", beta_B: " << betaB
          << ", gamma_B: " << gammaB << std::endl;
    }

    // Conditions aux limites
    mainDiagA_[0] = mainDiagA_[M - 1] = 1.0;
    lowerDiagA_[0] = upperDiagA_[M - 2] = 0.0;

    mainDiagB_[0] = mainDiagB_[M - 1] = 1.0;
    lowerDiagB_[0] = upperDiagB_[M - 2] = 0.0;
}

// Résolution de l'EDP avec Crank–Nicolson
std::vector<double> NumericalSolver::resoudreEDP(double K, double r, double sigma, double T) {
    size_t M = grilleSpots_.size();
    size_t N = grilleTemps_.size();
    std::vector<double> V(M, 0.0);  // Valeurs actuelles
    std::vector<double> rhs(M, 0.0);

    // Initialisation : Payoff à l'échéance (option CALL)
    for (size_t i = 0; i < M; ++i) {
        V[i] = std::max(grilleSpots_[i] - K, 0.0);
    }

    double dt = grilleTemps_[1] - grilleTemps_[0];
    double dx = grilleSpots_[1] - grilleSpots_[0];

    construireMatrices(dt, dx, r, sigma);

    for (int n = N - 2; n >= 0; --n) {
        for (size_t i = 1; i < M - 1; ++i) {
            rhs[i] = lowerDiagB_[i - 1] * V[i - 1] +
                     mainDiagB_[i] * V[i] +
                     upperDiagB_[i - 1] * V[i + 1];
        }

        // Vérification des bornes
        rhs[0] = 0.0;
        rhs[M - 1] = grilleSpots_[M - 1] - K;

        // Imprimer RHS pour vérification
        for (size_t i = 0; i < M; ++i) {
            std::cout << "RHS[" << i << "] = " << rhs[i] << "\n";
        }

        resoudreMatriceTridiagonale(lowerDiagA_, mainDiagA_, upperDiagA_, rhs);
        V = rhs;

        // Vérification des résultats
        for (size_t i = 0; i < M; ++i) {
            if (std::abs(V[i]) > 1e10) {
                std::cerr << "Erreur numérique détectée à V[" << i << "] = " << V[i] << "\n";
                exit(1);
            }
        }

        std::cout << "Itération temporelle n=" << n << ", V:\n";
        for (size_t i = 0; i < M; ++i) {
            std::cout << V[i] << " ";
        }
        std::cout << "\n";
            
    }
    return V;
}


// Résolution d'un système tridiagonal
void NumericalSolver::resoudreMatriceTridiagonale(const std::vector<double>& lowerDiag,
                                                  const std::vector<double>& mainDiag,
                                                  const std::vector<double>& upperDiag,
                                                  std::vector<double>& rhs) {
    size_t n = mainDiag.size();
    std::vector<double> gamma(n);  // Pour stocker la diagonale principale modifiée

    // Forward substitution
    gamma[0] = mainDiag[0];       // Initialisation de la première diagonale principale
    rhs[0] /= gamma[0];           // Mise à jour du premier élément du vecteur RHS
    for (size_t i = 1; i < n; ++i) {
        double m = lowerDiag[i - 1] / gamma[i - 1];  // Coefficient multiplicatif
        gamma[i] = mainDiag[i] - m * upperDiag[i - 1];  // Mise à jour de la diagonale principale
        rhs[i] -= m * rhs[i - 1];  // Mise à jour du RHS
    }

    // Backward substitution
    for (int i = n - 2; i >= 0; --i) {
        rhs[i] -= upperDiag[i] * rhs[i + 1] / gamma[i + 1];  // Mise à jour du RHS pour l'élément supérieur
    }
}


// Affichage des diagonales pour débogage
void NumericalSolver::afficherDiagonales() const {
    std::cout << "Diagonale inférieure : ";
    for (const auto& val : lowerDiagA_) std::cout << val << " ";
    std::cout << "\n";

    std::cout << "Diagonale principale : ";
    for (const auto& val : mainDiagA_) std::cout << val << " ";
    std::cout << "\n";

    std::cout << "Diagonale supérieure : ";
    for (const auto& val : upperDiagA_) std::cout << val << " ";
    std::cout << "\n";
}

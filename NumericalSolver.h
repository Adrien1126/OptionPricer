#ifndef __NUMERICALSOLVER_H__
#define __NUMERICALSOLVER_H__

#include <vector>
#include <iostream>

class NumericalSolver {
private:
    const std::vector<double>& grilleTemps_; // Référence à la grille de temps
    const std::vector<double>& grilleSpots_; // Référence à la grille de spots

    std::vector<double> lowerDiagA_; // Diagonale inférieure de la matrice
    std::vector<double> mainDiagA_;  // Diagonale principale de la matrice
    std::vector<double> upperDiagA_; // Diagonale supérieure de la matrice
    std::vector<double> lowerDiagB_; // Diagonale inférieure de la matrice
    std::vector<double> mainDiagB_;  // Diagonale principale de la matrice
    std::vector<double> upperDiagB_; // Diagonale supérieure de la matrice
public:
    // Constructeur
    NumericalSolver(const std::vector<double>& grilleTemps, const std::vector<double>& grilleSpots)
        : grilleTemps_(grilleTemps), grilleSpots_(grilleSpots) {}

    // Méthodes pour construire les matrices A et B pour Cranck–Nicolson
    void construireMatrices(double dt, double dx, double r, double sigma);

    // Méthode pour résoudre l'EDP
    std::vector<double> resoudreEDP(double K, double r, double sigma, double T);

    // Résolution d'un système tridiagonal
    void resoudreMatriceTridiagonale(const std::vector<double>& lowerDiag,
                                     const std::vector<double>& mainDiag,
                                     const std::vector<double>& upperDiag,
                                     std::vector<double>& rhs);

    // Afficher les matrices tridiagonales pour débogage
    void afficherDiagonales() const;
};

#endif // __NUMERICALSOLVER_H__

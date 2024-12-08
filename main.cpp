#include "Discretisation.h"
#include "NumericalSolver.h"
#include <iostream>

int main() {
    // Grilles de discrétisation
    Discretisation discretisation;
    discretisation.generateTimeGrid(0.01, 1.0);  // Pas de temps 0.01 jusqu'à T=1.0
    discretisation.generateSpotGrid(5.0, 100.0);  // Pas de spot 5 jusqu'à Smax=100

    // Instanciation du solveur
    NumericalSolver solver(discretisation.getTimeGrid(), discretisation.getSpotGrid());

    // Résolution de l'EDP (Option Européenne CALL)
    double K = 50.0;     // Strike
    double r = 0.05;     // Taux sans risque
    double sigma = 0.2;  // Volatilité
    double T = 1.0;      // Maturité

    std::vector<double> result = solver.resoudreEDP(K, r, sigma, T);

    // Affichage des résultats
    std::cout << "Prix de l'option (grille finale) :\n";
    for (size_t i = 0; i < discretisation.getSpotGrid().size(); ++i) {
        std::cout << "Spot: " << discretisation.getSpotGrid()[i]
                  << ", Prix: " << result[i] << "\n";
    }

    return 0;
}

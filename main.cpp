#include "Discretisation.h"
#include "NumericalSolver.h"
#include <iostream>

int main() {
    Discretisation discretisation;
    discretisation.generateTimeGrid(100, 1.0);  // 100 pas temporels, T = 1.0
    discretisation.generateSpotGrid(10, 100.0); // 10 pas spatiaux, Smax = 100.0

    NumericalSolver solver(discretisation.getTimeGrid(), discretisation.getSpotGrid());

    double K = 50.0;     // Strike
    double r = 0.05;     // Taux sans risque
    double sigma = 0.2;  // Volatilité
    double T = 1.0;      // Maturité

    std::vector<double> result = solver.resoudreEDP(K, r, sigma, T);

    std::cout << "Prix de l'option (grille finale) :\n";
    for (size_t i = 0; i < discretisation.getSpotGrid().size(); ++i) {
        std::cout << "Spot: " << discretisation.getSpotGrid()[i]
                  << ", Prix: " << result[i] << "\n";
    }

    return 0;
}

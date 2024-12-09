#include "Discretisation.h"
#include <iostream>
#include <stdexcept>

void Discretisation::generateTimeGrid(int N, double T)
{
    if (N <= 0 || T <= 0.0) {
        throw std::invalid_argument("N doit être strictement positif et T doit être positif.");
    }

    timeGrid_.clear();
    double dt = T / N; // Calcul du pas de temps à partir du nombre de pas
    for (int i = 0; i <= N; ++i) {
        timeGrid_.push_back(i * dt);
    }
}

void Discretisation::generateSpotGrid(int M, double Smax)
{
    if (M <= 0 || Smax <= 0.0) {
        throw std::invalid_argument("M doit être strictement positif et Smax doit être positif.");
    }

    spotGrid_.clear();
    double dS = Smax / M; // Calcul du pas spatial à partir du nombre de pas
    for (int i = 0; i <= M; ++i) {
        spotGrid_.push_back(i * dS);
    }
}

void Discretisation::afficherGrid() const
{
    std::cout << "=== Grille de discrétisation ===" << std::endl;

    std::cout << "Grille de temps : ";
    for (const auto& t : timeGrid_) {
        std::cout << t << " ";
    }
    std::cout << std::endl;

    std::cout << "Grille de prix : ";
    for (const auto& s : spotGrid_) {
        std::cout << s << " ";
    }
    std::cout << std::endl;

    std::cout << "===============================" << std::endl;
}

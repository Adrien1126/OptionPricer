#include "Discretisation.h"
#include <iostream>

void Discretisation::generateTimeGrid(double dt, double T)
{
    if (dt <= 0.0 || T <= 0.0) {
        throw std::invalid_argument("dt et T doivent être positifs.");
    }

    timeGrid_.clear();
    for (double t = 0.0; t <= T; t += dt)
    {
        timeGrid_.push_back(t);
    }
}

void Discretisation::generateSpotGrid(double dS, double Smax)
{
    if (dS <= 0.0 || Smax <= 0.0) {
        throw std::invalid_argument("dS et Smax doivent être positifs.");
    }

    spotGrid_.clear();
    for (double s = 0.0; s <= Smax; s += dS)
    {
        spotGrid_.push_back(s);
    }
}

void Discretisation::afficherGrid() const
{
    std::cout << "=== Grille de discrétisation ===" << std::endl;
    std::cout << "Grille de temps : ";
    for (const auto& t : timeGrid_)
    {
        std::cout << t << " ";
    }
    std::cout << std::endl;

    std::cout << "Grille de prix : ";
    for (const auto& s : spotGrid_)
    {
        std::cout << s << " ";
    }
    std::cout << std::endl;
    std::cout << "===============================" << std::endl;
}

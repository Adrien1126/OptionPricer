#include "marche.h"
#include <iostream>

double marche::interpolationLineaire(double t) const
{
    if (riskFreeRate_.size() < 2)
    {
        throw std::runtime_error("Il faut au moins 2 points pour l'interpolation linéaire");
    }
    
    for (size_t i = 0; i < riskFreeRate_.size()-1; i++)
    {
        double tk = riskFreeRate_[i].first;
        double rtk = riskFreeRate_[i].second;
        double tk1 = riskFreeRate_[i + 1].first;
        double rtk1 = riskFreeRate_[i + 1].second;

        if (t >= tk && t < tk1) {
            // Interpolation linéaire
            return rtk + (rtk1 - rtk) * (t - tk) / (tk1 - tk);
        }
    }

    // Si t est hors de la plage, retourner le dernier taux
    if (t >= riskFreeRate_.back().first) {
        return riskFreeRate_.back().second;
    }

    // Si t est avant le premier point, retourner le premier taux
    return riskFreeRate_.front().second;
}

void marche::afficherMarche() const
{
    std::cout << "=== Marché ===" << std::endl;
    std::cout << "S0 : " << S0_ << std::endl;
    std::cout << "Taux sans risque : " << std::endl;
    for (const auto& rate : riskFreeRate_)
    {
        std::cout << "  Temps " << rate.first << ", Taux " << rate.second << std::endl;
    }
    std::cout << "================" << std::endl;
}

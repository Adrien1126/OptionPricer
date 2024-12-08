#include "Option.h"
#include "EuropeanOption.h"
#include "AmericanOption.h"
#include <iostream>

int main() {
    // Données pour les options
    std::string contractType = "CALL";
    std::string exerciseTypeEuropeenne = "EUROPEAN";
    std::string exerciseTypeAmericaine = "AMERICAN";
    double maturity = 2.0; // 2 ans
    double strike = 100.0; // Prix d'exercice
    double volatility = 0.25; // 25% volatilité

    // Instanciation des options
    EuropeanOption europeenne(contractType, exerciseTypeEuropeenne, maturity, strike, volatility);
    AmericanOption americaine(contractType, exerciseTypeAmericaine, maturity, strike, volatility);

    // Appel des méthodes
    std::cout << "=== Option Européenne ===" << std::endl;
    europeenne.afficherDetails();
    std::cout << "Prix de l'option : " << europeenne.calculPrix() << std::endl;

    std::cout << "\n=== Option Américaine ===" << std::endl;
    americaine.afficherDetails();
    std::cout << "Prix de l'option : " << americaine.calculPrix() << std::endl;

    return 0;
}

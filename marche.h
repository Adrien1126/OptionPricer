#ifndef _MARCHE_H_
#define _MARCHE_H_

#include <vector>
#include <utility>

class marche
{
private:
    double S0_;
    std::vector<std::pair<double, double>> riskFreeRate_;
public:
    marche(double S0, std::vector<std::pair<double, double>> riskFreeRate): S0_(S0), riskFreeRate_(riskFreeRate) {};
    double interpolationLineaire(double t) const;
    void afficherMarche() const;
};

#endif // _MARCHE_H_
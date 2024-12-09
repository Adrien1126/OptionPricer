#ifndef _DISCRETISATION_H_
#define _DISCRETISATION_H_

#include <vector>

class Discretisation
{
private:
    std::vector<double> timeGrid_;
    std::vector<double> spotGrid_;
public:
    void generateTimeGrid(int N, double T);
    void generateSpotGrid(int M, double Smax); 
    void afficherGrid() const;

    // Getters pour accéder aux grilles (utile pour les tests ou intégration)
    const std::vector<double>& getTimeGrid() const { return timeGrid_; }
    const std::vector<double>& getSpotGrid() const { return spotGrid_; }
};





#endif // _DISCRETISATION_H_    
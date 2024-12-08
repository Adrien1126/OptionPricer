#ifndef __OPTION_H__
#define __OPTION_H__

#include <string>
#include <iostream>

class Option
{
protected:
    std::string ContractType_;
    std::string ExerciseType_;
    double Maturity_;
    double Strike_;
    double Volatility_;
public:
    Option(std::string& ContractType, std::string& ExerciseType, double Maturity, double Strike, double Volatility): ContractType_(ContractType), ExerciseType_(ExerciseType), Maturity_(Maturity), Strike_(Strike), Volatility_(Volatility) {};
    virtual double calculPrix() = 0;

    // Getters
    std::string getContractType() const { return ContractType_; }
    std::string getExerciseType() const { return ExerciseType_; }
    double getMaturity() const { return Maturity_; }
    double getStrike() const { return Strike_; }
    double getVolatility() const { return Volatility_; }

    // Setters
    void setMaturity(double maturity) { Maturity_ = maturity; }
    void setStrike(double strike) { Strike_ = strike; }
    void setVolatility(double volatility) { Volatility_ = volatility; }

    // Fonction afficher détails
    void afficherDetails() const;
};




#endif // __OPTION_H__
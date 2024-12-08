#ifndef __EUROPEAN_OPTION_H__
#define __EUROPEAN_OPTION_H__

#include <string>
#include "Option.h"

class EuropeanOption : public Option {
public:
    EuropeanOption(std::string& ContractType, std::string& ExerciseType, double Maturity, double Strike, double Volatility): Option(ContractType, ExerciseType, Maturity, Strike, Volatility) {};
    double calculPrix() override;
};

#endif // __EUROPEAN_OPTION_H__
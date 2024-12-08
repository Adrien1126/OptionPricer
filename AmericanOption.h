#ifndef _AMERICAN_OPTION_H_
#define _AMERICAN_OPTION_H_

#include <string>
#include "Option.h"

class AmericanOption : public Option {
public:
    AmericanOption(std::string& ContractType, std::string& ExerciseType, double Maturity, double Strike, double Volatility): Option(ContractType, ExerciseType, Maturity, Strike, Volatility) {};
    double calculPrix() override;
};

#endif // _AMERICAN_OPTION_H_


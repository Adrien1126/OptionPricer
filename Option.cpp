#include "Option.h"

void Option::afficherDetails() const {
    std::cout << "=== Option Details ===" << std::endl;
    std::cout << "Contract Type  : " << ContractType_ << std::endl;
    std::cout << "Exercise Type  : " << ExerciseType_ << std::endl;
    std::cout << "Maturity       : " << Maturity_ << std::endl;
    std::cout << "Strike         : " << Strike_ << std::endl;
    std::cout << "Volatility     : " << Volatility_ << std::endl;
    std::cout << "=======================" << std::endl;
}

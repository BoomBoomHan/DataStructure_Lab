#include "Individual.h"

FIndividual::FIndividual(const double coef, const double expo)
    :Coefficient(coef),
    Exponent(expo)
{
    
}

FIndividual::~FIndividual()
{
    Coefficient = 0;
    Exponent = 0;
}

std::string FIndividual::ToString(bool isSignedIfPositive, char inDisplayChar) const
{
    if (!Coefficient)
    {
        return "";
    }
    char symbol = (isSignedIfPositive) ? '+' : '\0';
    const std::string coefStr = (Coefficient != 1 ? std::to_string(Coefficient) : "");
    const std::string expoStr = (Exponent != 1 ? '^' + std::to_string(Exponent) : "");
    return (symbol + coefStr + inDisplayChar + expoStr);
}
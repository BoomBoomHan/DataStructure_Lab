#include "Individual.h"
#include "FunctionLibrarys/DataHandleStatics.h"

FIndividual::FIndividual(const double coef, const int expo)
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
    const std::string coefStr = UDataHandleStatics::PurifyDecimal(Coefficient != 1 ? std::to_string(Coefficient) : "");
    const std::string expoStr = (Exponent != 1 ? '^' + std::to_string(Exponent) : "");
    return (symbol + coefStr + inDisplayChar + expoStr);
}

bool FIndividual::IsExponentEqualTo(const FIndividual& another) const
{
    return (Exponent == another.Exponent);
}

bool FIndividual::IsExponentEqualTo(FIndividual&& another) const
{
    const FIndividual& indi = another;
    return IsExponentEqualTo(indi);
}

bool FIndividual::IsExponentLargerThan(const FIndividual& another) const
{
    return (Exponent > another.Exponent);
}

bool FIndividual::IsExponentLargerThan(FIndividual&& another) const
{
    const FIndividual& indi = another;
    return IsExponentLargerThan(indi);
}

bool FIndividual::IsExponentSmallerThan(const FIndividual& another) const
{
    return (Exponent < another.Exponent);
}

bool FIndividual::IsExponentSmallerThan(FIndividual&& another) const
{
    const FIndividual& indi = another;
    return IsExponentSmallerThan(indi);
}

bool FIndividual::operator==(const FIndividual& another)
{
    return (UDataHandleStatics::IsNearlyEqual(Coefficient, another.Coefficient) && IsExponentEqualTo(another));
}

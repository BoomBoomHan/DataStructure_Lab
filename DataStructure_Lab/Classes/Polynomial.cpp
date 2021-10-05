#include "Polynomial.h"
#include <iostream>

UPolynomial::UPolynomial(const FIndiArray& inArray, bool shouldSort)
    :individualsArray(inArray)
{
    if (shouldSort)
    {
        Sort();
    }
}

UPolynomial::UPolynomial(FIndiArray&& inArray, bool shouldSort)
    :individualsArray(inArray)
{
    if (shouldSort)
    {
        Sort();
    }
}

void UPolynomial::Sort()
{
    
}

void UPolynomial::PrintF(ETraversalMethod inMethod, char inDisplayChar)
{
    int index = 0;
    individualsArray.ForEach([&](TArrayIterator<FIndividual> it)->void
    {
        std::cout << (*it).ToString((index ? true : false), inDisplayChar);
        index++;
    }, inMethod);
    std::cout << std::endl;
}

void UPolynomial::AddIndividual(const FIndividual& inIndividual)
{
    individualsArray.Add(inIndividual);
}

void UPolynomial::AddIndividual(FIndividual&& inIndividual)
{
    const FIndividual& indi = inIndividual;
    AddIndividual(indi);
}

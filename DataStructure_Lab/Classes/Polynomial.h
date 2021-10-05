#pragma once
#include "Structs/Array.h"
#include "Structs/Individual.h"

#define C_PROTECTED(variable); protected:\
                                variable;\
                             private:\

#define C_PUBLIC(variable); public:\
                              variable;\
                          private:\

class UPolynomial
{
private:

    typedef TArray<FIndividual> FIndiArray;

    /**
     *单项式数组
     */
    FIndiArray individualsArray;

    /**
     *最高项数的指数
     */
    int maxExponent;


    
public:

    
    UPolynomial(const FIndiArray& inArray, bool shouldSort = true);


    UPolynomial(FIndiArray&& inArray, bool shouldSort = true);


    void PrintF(ETraversalMethod inMethod = Sequential, char inDisplayChar = 'x');

    
    void AddIndividual(const FIndividual& inIndividual);


    void AddIndividual(FIndividual&& inIndividual);

private:

    void Sort();
};

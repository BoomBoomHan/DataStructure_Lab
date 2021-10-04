#include "Structs/Array.h"
#include <iostream>
using namespace std;

/*
double RandomProperFraction();

template<typename ReturnType, typename ParamType>
ReturnType RandomNumberInRange(ParamType inMin, ParamType inMax);*/

/**
 * @ brief 生成一个在一定区间内的随机数。
 * @ param inMin 区间最小值
 * @ param inMax 区间最大值
 * @ return 基于最小值、最大值之间的随机数(任意类型)
 * @ note min,max不得超过-10^9~10^9范围。
 */ 
/*template<typename ReturnType, typename ParamType>
ReturnType RandomNumberInRange(ParamType inMin, ParamType inMax)
{
    return ReturnType(inMin + (inMax - inMin) * RandomProperFraction());
    
}*/

/**
 * @ brief 生成一个0至1间的小数
 */
/*double RandomProperFraction()
{
    const int randMax = 1000;
    auto Random = [randMax]()->double
    {
        return rand() % randMax;
    };
    return (Random() / randMax + Random() / randMax / randMax);
}*/






int main()
{
    TArray<int> arr(1, 2);
    arr.Add(3);
    arr.Add(-1);
    bool addUniqueSuccess;
    int val = 888;
    arr.Add(val);
    arr.RemoveByIndex(arr.FindIndex(2));
    arr.AddUnique(val, addUniqueSuccess);
    int sum = 0;
    arr.ForEach([&](TArrayIterator<int> it)->void
    {
        sum += *it;
    });
    /*arr.PrintF();
    cin.get();
    bool removeSuccess;
    arr.Remove(2, removeSuccess);
    arr.PrintF();*/
    //int twoIndex;
    cout << sum << endl;
    return 0;
}

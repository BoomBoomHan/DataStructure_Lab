#include "DataHandleStatics.h"

std::string UDataHandleStatics::PurifyDecimal(const std::string& inDecimal)
{
    int position = int(inDecimal.size() - 1);
    while (position--)
    {
        const char cur = inDecimal[position];
        if (cur == '0') continue;
        else if (isdigit(cur)) return inDecimal.substr(0, position + 1);
        else if (cur == '.') return inDecimal.substr(0, position);
        return inDecimal;
    }
    return inDecimal;
}

bool UDataHandleStatics::IsNearlyEqual(const float& a, const float& b)
{
    return (fabs(a - b) < 1e-5);
}

bool UDataHandleStatics::IsNearlyEqual(const double& a, const double& b)
{
    return (fabs(a - b) < 1e-7);
}

std::string UDataHandleStatics::ToString(const bool& inBool)
{
    return (inBool ? "Yes" : "No");
}

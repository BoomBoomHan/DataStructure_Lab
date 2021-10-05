#pragma once
#include <string>
#include <cmath>

class UDataHandleStatics
{
public:
    /**
     *@brief 纯化小数字符串，使其后缀省略不必要的0和小数点。
     *@param inDecimal 输入的字符串对象引用
     *@return 纯化后的小数字符串
     *@note 如果此字符串还由除了数字和小数点以外的字符构成，那么会返回它本身。
     */
    static std::string PurifyDecimal(const std::string& inDecimal);

    static bool IsNearlyEqual(const float& a, const float& b);

    static bool IsNearlyEqual(const double& a, const double& b);

    static std::string ToString(const bool& inBool);
};

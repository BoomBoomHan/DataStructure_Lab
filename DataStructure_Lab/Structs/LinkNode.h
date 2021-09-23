#pragma once
#include "Enums/EnumLibrary.h"
#include <iostream>


/**
 *@brief 模板结构体：节点
 */
template<typename T>
struct TLinkNode
{
    /**
     *数据域
     */
    T Element;

    /**
     *Last指针域
     */
    TLinkNode* Last;

    /**
     *Next指针域
     */
    TLinkNode* Next;

    /**
     *@brief 构造函数，构造一个有元素值，两个指针域的节点
     *@param inValue 输入元素值
     *@param lastPtr Last指针
     *@param nextPtr Next指针
     */
    TLinkNode(T inValue = T(0), TLinkNode* lastPtr = nullptr, TLinkNode* nextPtr = nullptr)
    :Element(inValue),
    Last(lastPtr),
    Next(nextPtr)
    {

    }

    /**
     *@brief 拷贝构造函数
     *@param copy 被拷贝节点对象引用
     */
    TLinkNode(const TLinkNode& copy)
    :Element(copy.Element),
    Last(copy.Last),
    Next(copy.Next)
    {

    }

    /**
     *@brief 运算符=(对于另一个节点)
     *@param another 另一个节点对象引用
     *@return 自身对象引用
     */
    TLinkNode& operator =(const TLinkNode& another)
    {
        Element = another.Element;
        Last = another.Last;
        Next = another.Next;
        return *this;
    }

    /**
     *@brief 运算符=(对于元素值)
     *@param elem 赋值的元素值
     *@return 自身对象引用
     */
    TLinkNode& operator =(T& elem)
    {
        Element = elem;
        return *this;
    }

    /**
     *@brief 运算符==(对于另一个节点)
     *@param another 另一个节点对象引用
     *@return 两者数据域，指针域完全相同返回真，否则返回假
     *@note 此运算符限制极强，若不想要那么强的限制，请调用IsEqualTo函数。
     *@note 若模板元素类型是struct或class，则必须重载运算符==，否则无法调用!!!!!!
     */
    bool operator ==(const TLinkNode& another)
    {
        return IsEqualTo(another, ValueRequired, LastPtrRequired, NextPtrRequired);
    }

    /**
     *@brief 运算符==(对于某元素值)
     *@param elem 输入元素值
     *@return 若此节点数据域与输入值相同则返回真，否则返回假
     *@note 若模板元素类型是struct或class，则必须重载运算符==，否则无法调用!!!!!!
     */
    bool operator ==(T& elem)
    {
        return (Element == elem);
    }

    /**
     *@brief 此节点是否与另一节点相等
     *@param another 另一个节点对象引用
     *@param require 要求(枚举值)
     *@param requires 更多要求
     *@return 若满足所有要求则返回真，否则返回假
     *@note 要求的个数不做限制。
     */
    template<typename T0, typename ... Ts>
    bool IsEqualTo(const TLinkNode& another, T0 require = ValueRequired, Ts ... requires)
    {
        return IsEqualTo(another, require) * IsEqualTo(another, requires ...);
    }

    /**
     *@brief 此节点是否与另一节点相等
     *@param another 另一个节点对象引用
     *@param require 要求(枚举值)
     *@return 若满足该单一要求则返回真，否则返回假
     *@note 此重载版本只能有一个要求。
     */
    bool IsEqualTo(const TLinkNode& another, ELinkNodeEqual require)
    {
        switch (require)
        {
        case LastPtrRequired:
            return (Last == another.Last);
        case NextPtrRequired:
            return (Next == another.Next);
        case ValueRequired:
        default:
            return (Element == another.Element);
        }
    }

    /**
     *@brief 重载输出运算符
     */
    friend std::ostream& operator << (std::ostream& cout, TLinkNode* inLinkNode)
    {
        if (inLinkNode)
        {
            cout << inLinkNode->Element;
        }
        else
        {
            cout << "空指针!";
        }
        return cout;
    }
};

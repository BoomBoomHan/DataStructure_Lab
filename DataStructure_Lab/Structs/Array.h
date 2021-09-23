#pragma once
#include "LinkNode.h"
#include "Enums/EnumLibrary.h"
#include <iostream>

#define PRIVATE(variable) private:\
                            variable;\
                          public:\
                          
/**
 *@brief 模板结构体：数组(链表)
 *@note 尚未完工
 */
template<typename T>
struct TArray
{
    typedef TLinkNode<T> FNode;
    typedef FNode* (TArray::*Compare)(FNode*);
    
    /**
     *头结点
     */
    FNode* Head;

    /**
     *尾结点
     */
    FNode* Tair;

    /**
     *链表
     */
    FNode LinkNode;

    /**
     *链表元素个数(私有成员!)
     */
    PRIVATE(int size);

    /**
     *@brief 构造函数，生成若干个相同值的元素
     *@param inSize 构造的元素个数
     *@param inValue 每个元素的值
     */
    TArray(int inSize = 1, T inValue = T(0))
    :Head(&LinkNode),
    Tair(Head),
    LinkNode(FNode(inValue)),
    size(1)
    {
        for (; inSize > 1; inSize--)
        {
            AddCall(inValue);
        }
        Tair->Next = nullptr;
    }

    /**
     *@brief 输出函数，将每个元素打印在屏幕上
     *@param inMethod 打印的方式：顺序打印Sequential，倒叙打印Inverted
     *@note 要输出的模板类型T如果是struct或class，必须重载运算符<<，否则无法调用!!!!!!
     */
    void PrintF(ETraversalMethod inMethod = Sequential)
    {
        FNode* beginNode = GetBeginNodeWithMethod(inMethod);
        do
        {
            std::cout << beginNode << std::endl;
            beginNode = ToTargetPointer(beginNode, inMethod);
        }while (beginNode);
    }

    /**
     *@brief 在数组的末尾添加元素
     *@param inValue 添加的元素值
     */
    virtual void Add(T inValue)
    {
        FNode* newNode = new FNode(inValue, Tair);
        Tair->Next = newNode;
        Tair = newNode;
        size++;
    }

    /**
    *@brief 在数组的末尾添加元素
    *@param inValue 添加的元素值
    *@param outStatus 是否添加成功
    *@note 这个重载版本还能输出添加成功与否，如不需要获取这个值，调用另一个重载版本。
    */
    void Add(T inValue, bool& outStatus)
    {
        Add(inValue);
        outStatus = true;
    }

    /**
    *@brief 在数组的末尾添加值唯一的元素
    *@param inValue 添加的元素值
    *@param outStatus 是否添加成功
    *@note 如果数组中已有此元素，则会添加失败。
    */
    void AddUnique(T inValue, bool& outStatus)
    {
        for (int index = 0; index < size; index++)
        {
            T& element = (*this)[index];
            if (element == inValue)
            {
                outStatus = false;
                return ;
            }
        }
        Add(inValue, outStatus);
    }

    /**
     *@brief 获取数组大小
     *@return 数组的元素个数
     */
    int GetSize() const
    {
        return size;
    }

    /**
     *@brief 获取数组指定索引节点
     *@param index 目标索引
     *@return 获取的节点对象引用
     *@note 如果输入索引存在越界现象，则会将其对数组大小size求余后运算。
     */
    FNode& At(int index)
    {
        index %= size;
        ETraversalMethod method;
        int traversalTimes;
        GetTraverseDatas(index, method, traversalTimes);
        FNode* beginNode = GetBeginNodeWithMethod(method);
        for (; traversalTimes; traversalTimes--)
        {
            beginNode = ToTargetPointer(beginNode, method);
        }
        return *beginNode;
    }

    /**
     *@brief 得到数组指定索引的值
     *@param index 目标索引
     *@return 获取的模板类型对象引用
     *@note 如果输入索引存在越界现象，则会将其对数组大小size求余后运算。
     */
    T& operator [](int index)
    {
        return At(index).Element;
    }

    /**
     *析构函数
     */
    virtual ~TArray()
    {
        delete Head;
        delete Tair;
        size = 0;
    }

#pragma region PrivateFunctions

private:

    /**
     *@brief 根据不同方式得到下一个节点
     *@param inNode 输入的节点
     *@param inMethod 目标遍历方式
     *@return 如果是顺序遍历则返回Next节点，否则返回Last节点
     */
    FNode* ToTargetPointer(FNode* inNode, ETraversalMethod inMethod = Sequential)
    {
        Compare To;
        To = (inMethod == Sequential) ? &TArray::ToNext : &TArray::ToLast;
        return (this->*To)(inNode);
    }

    /**
     *@brief 获取Last节点
     *@param inNode 输入节点
     *@return inNode->Last
     */
    FNode* ToLast(FNode* inNode)
    {
        return inNode->Last;
    }

    /**
     *@brief 获取Next节点
     *@param inNode 输入节点
     *@return inNode->Next
     */
    FNode* ToNext(FNode* inNode)
    {
        return inNode->Next;
    }

    /**
     *@brief 根据遍历方式获得遍历开始的节点
     *@param inMethod 目标遍历方式
     *@return 若顺序遍历则返回头结点，否则返回尾结点
     */
    FNode* GetBeginNodeWithMethod(ETraversalMethod inMethod)
    {
        return (inMethod == Sequential) ? Head : Tair;
    }

    /**
     *@brief 根据不同的索引，依照就近原则获得遍历数据
     *@param index 目标索引
     *@param outMethod 输出遍历方式
     *@param outTraversalTimes 输出遍历次数
     */
    void GetTraverseDatas(int index, ETraversalMethod& outMethod, int& outTraversalTimes)
    {
        bool fromHead = (index < size / 2);
        outMethod = fromHead ? Sequential : Inverted;
        outTraversalTimes = fromHead ? index : size - index - 1;
    }

    /**
     *@brief 调用虚函数Add
     *@note 只在构造函数中调用
     */
    void AddCall(T inValue)
    {
        Add(inValue);
    }

#pragma endregion PrivateFunctions
};

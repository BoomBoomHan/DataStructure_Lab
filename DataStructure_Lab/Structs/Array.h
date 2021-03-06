#pragma once
#include "LinkNode.h"
#include "Enums/EnumLibrary.h"

#define S_PRIVATE(variable); private:\
                                variable;\
                          public:\

#define S_PROTECTED(variable); protected:\
                                variable;\
                            public:

/**
 *@brief 模板结构体：数组(链表)
 */
template<typename T>
struct TArray
{
    typedef TLinkNode<T> FNode;
    typedef FNode* (TArray::*Compare)(FNode*);
    
    template<typename T1>
    friend struct TArrayIterator;

    typedef TArrayIterator<T> FIterator;
    
    /**
     *头结点(私有成员!)
     */
    S_PRIVATE(FNode* Head);

    /**
     *尾结点(私有成员!)
     */
    S_PRIVATE(FNode* Tair);

    /**
     *链表
     */
    FNode LinkNode;

    /**
     *链表元素个数(保护成员!)
     */
    S_PROTECTED(int size);

    /**
     *@brief 构造函数，生成若干个相同值的元素
     *@param inSize 构造的元素个数
     *@param inValue 每个元素的值右值引用
     */
    TArray(T&& inValue, int inSize = 1)
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

    TArray()
    :Head(nullptr),
    Tair(nullptr),
    LinkNode(FNode()),
    size(0)
    {
        
    }

    /**
     *@brief 输出函数，将每个元素打印在屏幕上
     *@param inMethod 打印的方式：顺序打印Sequential，倒叙打印Inverted
     *@note 要输出的模板类型T如果是struct或class，必须重载运算符<<，否则无法调用!!!!!!
     */
    void PrintF(ETraversalMethod inMethod = Sequential)
    {
        ForEach([](FIterator it)->void
        {
            std::cout << it.ToRawNode() << std::endl;
        }, inMethod);
    }

    /**
     *@brief 在数组的末尾添加元素
     *@param inValue 添加的元素值对象引用
     */
    virtual void Add(const T& inValue)
    {
        if (!size)
        {
            LinkNode.Element = inValue;
            Head = &LinkNode;
            Tair = Head;
        }
        else
        {
            FNode* newNode = new FNode(inValue, Tair);
            Tair->Next = newNode;
            Tair = newNode;
        }
        size++;
    }

    /*
     *@brief 在数组的末尾添加元素
     *@param inValue 添加的元素右值引用
     */
    /*void Add(T&& inValue)
    {
        T& val = inValue;
        Add(val);
    }*/

    /**
     *@brief 在数组的末尾添加元素
     *@param inValue 添加的元素值对象引用
     *@param outStatus 是否添加成功
     *@note 这个重载版本还能输出添加成功与否，如不需要获取这个值，调用另一个重载版本。
     */
    void Add(const T& inValue, bool& outStatus)
    {
        outStatus = false;
        Add(inValue);
        outStatus = true;
    }

    /*
     *@brief 在数组的末尾添加元素
     *@param inValue 添加的元素右值引用
     *@param outStatus 是否添加成功
     *@note 这个重载版本还能输出添加成功与否，如不需要获取这个值，调用另一个重载版本。
     */
    /*void Add(T&& inValue, bool& outStatus)
    {
        outStatus = false;
        Add(inValue);
        outStatus = true;
    }*/

    /**
     *@brief 在数组的末尾添加值唯一的元素
     *@param inValue 添加的元素值对象引用
     *@param outStatus 是否添加成功
     *@note 如果数组中已有此元素，则会添加失败。
     */
    void AddUnique(const T& inValue, bool& outStatus)
    {
        outStatus = !Contains(inValue);
        if (outStatus)
        {
            Add(inValue, outStatus);
        }
    }

    /*
     *@brief 在数组的末尾添加值唯一的元素
     *@param inValue 添加的元素右值引用
     *@param outStatus 是否添加成功
     *@note 如果数组中已有此元素，则会添加失败。
     */
    /*void AddUnique(T&& inValue, bool& outStatus)
    {
        T& val = inValue;
        AddUnique(val, outStatus);
    }*/

    virtual void Insert(const T& inValue, const FIterator& inIt)
    {
        if (!size) return;
        FNode* newNode = new FNode(inValue);
        FNode* itNode = const_cast<FIterator&>(inIt).ToRawNode();
        if (IsHead(itNode))
        {
            AddOnHead(newNode);
        }
        else
        {
            FNode* lastNode = itNode->Last;
            InsertNodes(lastNode, newNode, itNode);
        }
        size++;
    }
    
    /**
     *@brief 是否包括某个值
     *@param inElement 输入的元素对象引用
     *@return 如果包括该值则返回真，否则返回假。
     */
    bool Contains(const T& inElement)
    {
        return (FindIndex(inElement) != -1);
    }

    /*
     *@brief 是否包括某个值
     *@param inElement 输入的元素右值引用
     *@return 如果包括该值则返回真，否则返回假。
     */
    /*bool Contains(T&& inElement)
    {
        T& ele = inElement;
        return Contains(ele);
    }*/

    /**
     *@brief 查找某个元素的索引
     *@param inElement 输入的元素对象引用
     *@return 若找到则返回其索引，否则返回-1。
     *@note 如果包括多个该值，输出第一个出现该值的索引。
     */
    int FindIndex(const T& inElement)
    {
        int outIndex = 0;
        for (FIterator it = CreateIterator(); it.IsValid(); ++it, outIndex++)
        {
            if (inElement == *it)
            {
                return outIndex;
            }
        }
        return -1;
    }

    /*
     *@brief 查找某个元素的索引
     *@param inElement 输入的元素右值引用
     *@return 若找到则返回其索引，否则返回-1。
     *@note 如果包括多个该值，输出第一个出现该值的索引。
     */
    /*int FindIndex(T&& inElement)
    {
        T& ele = inElement;
        return FindIndex(ele);
    }*/

    /**
     *@brief 按索引移除某个元素
     *@param inIndex 索引值
     *@note 如果输入索引存在越界现象，则会将其对数组大小size求余后运算。
     */
    void RemoveByIndex(int inIndex)
    {
        try
        {
            FNode& targetNode = At(inIndex);
        }
        catch (int)
        {
            std::cout << "ERROR!" << std::endl;
            return;
        }
        FNode& targetNode = At(inIndex);
        HandleInRemove(&targetNode);
        size--;
    }

    /**
     *@brief 按索引移除某个元素
     *@param inIndex 索引值
     *@param outStatus 移除是否成功
     *@note 此重载版本还能输出移除是否成功，如不需要这个值，请调用上一个版本。如果输入索引存在越界现象，则会将其对数组大小size求余后运算。
     */
    void RemoveByIndex(int inIndex, bool& outStatus)
    {
        outStatus = false;
        RemoveByIndex(inIndex);
        outStatus = true;
    }

    /**
     *@brief 按值移除某个元素
     *@param inElement 指定的元素对象引用
     *@param outStatus 移除是否成功
     *@note 此重载版本能按值移除元素。如果数组不包含此值，则不会发生任何事。
     */
    void Remove(const T& inElement, bool& outStatus)
    {
        const int targetIndex = FindIndex(inElement);
        if (targetIndex != -1)
        {
            RemoveByIndex(targetIndex, outStatus);
        }
    }

    /*
     *@brief 按值移除某个元素
     *@param inElement 指定的元素右值引用
     *@param outStatus 移除是否成功
     *@note 此重载版本能按值移除元素。如果数组不包含此值，则不会发生任何事。
     */
    /*void Remove(T&& inElement, bool& outStatus)
    {
        T& ele = inElement;
        Remove(ele, outStatus);
    }*/

    /**
     *@brief 获取数组大小
     *@return 数组的元素个数
     */
    int GetSize() const
    {
        return size;
    }

    /**
     *@brief 创建一个迭代器以供迭代。
     *@param inMethod 遍历方式
     *@return 如果是顺序遍历则返回一个从头节点开始的迭代器，否则返回从尾开始的迭代器
     */
    FIterator CreateIterator(ETraversalMethod inMethod = Sequential)
    {
        return FIterator(*this, inMethod);
    }

    /**
     *@brief 形成一个ForEach遍历。
     *@param inFunction 传入的函数指针
     *@param inMethod 遍历方式
     *@note 传入的函数指针必须是任意返回类型的、参数列表仅有TArrayIterator的函数。
     */
    template<typename FunctionType>
    void ForEach(FunctionType inFunction, ETraversalMethod inMethod = Sequential)
    {
        for (FIterator it = CreateIterator(inMethod); it.IsValid(); it.MoveIterator())
        {
            inFunction(it);
        }
    }

    /**
     *@brief 获取数组指定索引节点
     *@param index 目标索引
     *@return 获取的节点对象引用
     *@note 如果输入索引存在越界现象，则会将其对数组大小size求余后运算。
     */
    FNode& At(int index)
    {
        if (!size)
        {
            throw size;
        }
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
        ForEach([this](FIterator it)->void
        {
            Free(it.ToRawNode());
        });
    }

#pragma region InnerFunctions

protected:

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
    FNode* GetBeginNodeWithMethod(ETraversalMethod inMethod) const
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
    void AddCall(T&& inValue)
    {
        Add(inValue);
    }

    /**
     *@brief 调用虚函数Add
     *@note 只在构造函数中调用
     */
    void AddCall(const T& inValue)
    {
        Add(inValue);
    }

    void BindNodes(FNode* inFormerNode, FNode* inLatterNode)
    {
        inFormerNode->Next = inLatterNode;
        inLatterNode->Last = inFormerNode;
    }

    void InsertNodes(FNode* inFormerNode, FNode* inTargetNode, FNode* inLatterNode)
    {
        BindNodes(inFormerNode, inTargetNode);
        BindNodes(inTargetNode, inLatterNode);
    }

    void AddOnHead(FNode* inNewNode)
    {
        BindNodes(inNewNode, Head);
        Head = inNewNode;
    }

    /**
     *@brief 在移除节点时处理其相邻节点
     */
    void HandleInRemove(FNode* inTargetNode)
    {
        if (size == 1)
        {
            HandleSingle(inTargetNode);
        }
        else
        {
            HandleDuo(inTargetNode);
        }
        
        Free(inTargetNode);
    }

    /**
     *@brief 当只剩一个节点时的调用
     */
    void HandleSingle(FNode* inTargetNode)
    {
        Head = nullptr;
        Tair = nullptr;
    }

    /**
     *@brief 当还有超过一个节点时的调用
     */
    void HandleDuo(FNode* inTargetNode)
    {
        FNode*& lastNode = inTargetNode->Last;
        FNode*& nextNode = inTargetNode->Next;
        if (IsHead(inTargetNode))
        {
            //std::cout << "头" << std::endl;
            Head = nextNode;
            Head->Last = nullptr;
        }
        else if (IsTair(inTargetNode))
        {
            //std::cout << "尾" << std::endl;
            Tair = lastNode;
            Tair->Next = nullptr;
        }
        else
        {
            //std::cout << "飞头飞卫" << std::endl;
            lastNode->Next = nextNode;
            nextNode->Last = lastNode;
        }
    }

    bool IsEqualNodes(FNode* inNode, FNode* targetNode) const
    {
        if ((!inNode) || (!targetNode))
        {
            return false;
        }
        return inNode->IsEqualTo(*targetNode, ValueRequired, LastPtrRequired, NextPtrRequired);
    }

    bool IsHead(FNode* inNode) const
    {
        return IsEqualNodes(inNode, Head);
    }

    bool IsTair(FNode* inNode) const
    {
        return IsEqualNodes(inNode, Tair);
    }

    /**
     *@brief 释放节点指针
     *@param inNode 目标节点
     */
    void Free(FNode* inNode)
    {
        if (!inNode)
        {
            return;
        }
        inNode->Element = T(0);
        inNode->Last = nullptr;
        inNode->Next = nullptr;
    }

#pragma endregion InnerFunctions
    
};

/**
 *@brief 模板结构体：链表迭代器
 */
template<typename T>
struct TArrayIterator
{
    typedef TLinkNode<T> FNode;

    /**
    *当前的指向节点
    */
    FNode* CurrentNode;

    /**
     *@brief 构造函数。
     *@param inArray 输入的链表
     *@param inMethod 迭代的方式
     *@note 迭代方式的不同会导致构造不同的迭代器。顺序遍历则迭代器在Head，否则在Tair。
     */
    TArrayIterator(const TArray<T>& inArray, ETraversalMethod inMethod = Sequential)
        :CurrentNode(inArray.GetBeginNodeWithMethod(inMethod))
    {
        
    }

    /**
     *@brief 转换为原始的节点。
     *@return 当前指向的节点
     */
    FNode*& ToRawNode()
    {
        return CurrentNode;
    }

    /**
     *@brief 迭代器是否有效。
     *@return 当前的节点是否为空指针
     */
    bool IsValid() const
    {
        return (CurrentNode != nullptr);
    }

    /**
     *@brief 根据遍历方式不同移动一次。
     *@param inMethod 迭代方式
     */
    void MoveIterator(ETraversalMethod inMethod = Sequential)
    {
        if (inMethod == Sequential)
        {
            ++(*this);
        }
        else
        {
            --(*this);
        }
    }

    /**
     *@brief 迭代器向后移动一定单位
     *@param inNum 向后移动的单位数量
     */
    TArrayIterator& operator +(unsigned int inNum)
    {
        while (inNum--)
        {
            ++(*this);
        }
        return (*this);
    }

    /**
     *@brief 迭代器向前移动一定单位
     *@param inNum 向前移动的单位数量
     */
    TArrayIterator& operator -(unsigned int inNum)
    {
        while (inNum--)
        {
            --(*this);
        }
        return (*this);
    }

    /**
     *@brief 迭代器向后移动一定单位
     *@param inNum 向后移动的单位数量
     */
    TArrayIterator& operator += (unsigned int inNum)
    {
        (*this) = (*this) + inNum;
        return (*this);
    }

    /**
     *@brief 迭代器向前移动一定单位
     *@param inNum 向前移动的单位数量
     */
    TArrayIterator& operator -=(unsigned int inNum)
    {
        (*this) = (*this) - inNum;
        return (*this);
    }

    /**
     *@brief 迭代器向后移动。
     *@return 指向的节点的Next节点
     */
    TArrayIterator& operator ++()
    {
        CurrentNode = CurrentNode->Next;
        return (*this);
    }

    /**
     *@brief 迭代器向前移动。
     *@return 指向的节点的Last节点
     */
    TArrayIterator& operator --()
    {
        CurrentNode = CurrentNode->Last;
        return (*this);
    }

    /**
     *@brief 解指针(实际上解的是节点的指针)。
     *@return 当前的元素对象引用
     */
    T& operator *()
    {
        return CurrentNode->Element;
    }

    /**
     *@brief 箭头操作符，有解指针操作。
     *@warning 有效性待定!
     */
    T& operator ->()
    {
        return CurrentNode->Element;
    }
};
#include "Structs/LinkNode.h"
#include "Structs/Array.h"
#include <iostream>

int main()
{
    /*TLinkNode<int> node1(8);
    TLinkNode<int> node2(8, &node1);
    TLinkNode<int> node3(8, &node1, &node2);
    std::cout << (node3.IsEqualTo(node2, ValueRequired, LastPtrRequired));*/
    TArray<int> arr1(6, 10);
    bool success;
    arr1.AddUnique(5, success);
    arr1[0] = 666;
    arr1.At(1).Element = 9999;
    arr1.PrintF();
    //std::cout << success << std::endl;
    return 0;
}

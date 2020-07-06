#include <iostream>
#include <list>

#include "List.h"

template<class T>
void Print(List<T>&& list)
{
    for(auto i = 0; i < list.Size(); ++i)
        std::cout << list[i] << " ";
}

int main()
{
    List<int> list{1, 3, 4, 5, 6, 7, 8, 9};
    list.AddFront(0);
    list.AddBack(10);
    list.Add(2,2);

    list.Remove(0);
    list.Remove(9);

    list.Reverse();

    list.Print();
    list.PrintReverse();
}

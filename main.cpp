#include <iostream>

#include "List.h"

template<class T>
void Print(List<T>&& list)
{
    for(auto i = 0; i < list.Size(); ++i)
        std::cout << list[i] << " ";
}

int main()
{
    List<int> list;
    list.AddFront(3);
    list.AddFront(2);
    list.AddBack(5);
    list.AddBack(6);
    list.Add(2,4);

    list.RemoveFront();
    list.RemoveBack();

    list.Print();
    list.PrintReverse();

    std::cout << list.Size() << std::endl;
    Print(std::move(list));
}

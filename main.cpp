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
    list.AddFront(new int(3));
    list.AddFront(new int(2));
    list.AddBack(new int(5));
    list.AddBack(new int(6));
    list.Add(2,new int(4));

    list.RemoveFront();
    list.RemoveBack();
    list.Remove(1);

    list.Print();
    list.PrintReverse();

    list.Reverse();

    list.Print();
    list.PrintReverse();

    std::cout << list.Size() << std::endl;
    Print(std::move(list));
}

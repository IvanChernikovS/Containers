//
// Created by Ivan Chernikov on 23.06.2020.
//

#pragma once

#include <iostream>

template<class T>
class List
{
private:
    struct Node
    {
        explicit Node(T _data = T(),
                      Node* _nextPtr = nullptr,
                      Node* _prevPtr = nullptr)
        :Data(_data), nextPtr(_nextPtr), prevPtr(_prevPtr)
        {}

        ~Node() noexcept
        {
            nextPtr = nullptr;
            prevPtr = nullptr;
        }

        T Data;

        Node* nextPtr   = nullptr;
        Node* prevPtr   = nullptr;
    };

public:
    explicit List()                         = default;
    List(std::initializer_list<T> _il);
    ~List() noexcept                        { Clear(); }

    List(const List&)                       = delete;
    List(List&&)                noexcept    = delete;

    List& operator= (const List&)           = delete;
    List& operator= (List&&)    noexcept    = delete;

    T& operator[] (int index)   const;

    void Print()                const;
    void PrintReverse()         const;

    int          Size()         const { return size; }
    bool         IsEmpty()      const { return size == 0; }

    void         Clear();

    void AddFront(T _data);
    void AddBack(T _data);
    void Add(int _pos, T _data);

    void RemoveFront();
    void RemoveBack();
    void Remove(int _pos);

    void Reverse();
    //void Unique();
    //void Remove_if();
    //void Merge();
    //void Sort();
    //void Swap();

private:
    int size    = 0;
    Node* head  = nullptr;
};

template<class T>
List<T>::List(std::initializer_list<T> _il)
{
    for(typename std::initializer_list<T>::const_iterator it = _il.begin(); it != _il.end(); ++it)
    {
        AddBack(*it);
    }
}

template<class T>
inline T& List<T>::operator[] (int index) const
{
    int counter = 0;
    Node* current = head;

    while(current)
    {
        if(counter == index)
        {
            return current->Data;
        }
        current = current->nextPtr;
        ++counter;
    }
}

template<class T>
void List<T>::Print() const
{
    if(!head)
        return;

    for(auto it = head; it != nullptr; it = it->nextPtr)
    {
        std::cout << it->Data << " ";
    }
    std::cout << std::endl;
}

template<class T>
void List<T>::PrintReverse() const
{
    if(!head)
        return;

    Node* current = head;
    while(current->nextPtr)
    {
        current = current->nextPtr;
    }

    for(auto it = current; it != nullptr; it = it->prevPtr)
    {
        std::cout << it->Data << " ";
    }
    std::cout << std::endl;
}

template<class T>
void List<T>::Clear()
{
    while(size)
    {
        RemoveFront();
    }
}

template<class T>
void List<T>::AddFront(T _data)
{
    if(!head && size == 0)
    {
        head = new Node(_data);
    }
    else
    {
        head = new Node(_data, head, nullptr);
        head->nextPtr->prevPtr = head;
    }
    ++size;
}

template<class T>
void List<T>::AddBack(T _data)
{
    if(!head)
    {
        head = new Node(_data);
    }
    else
    {
        Node* current = head;

        while(current->nextPtr)
        {
            current = current->nextPtr;
        }

        current->nextPtr = new Node(_data, nullptr, current);
    }
    ++size;
}

template<class T>
void List<T>::Add(int _pos, T _data)
{
    if(!head)
    {
        head = new Node(_data);
    }
    else
    {
        if(_pos == 0)
        {
            AddFront(_data);
        }
        else
        {
            Node* current = head;

            for(auto i = 0; i < _pos; ++i)
            {
                current = current->nextPtr;
            }

            Node* newNode = new Node(_data, current, current->prevPtr);
            current->prevPtr->nextPtr = newNode;
            current->prevPtr = newNode;
        }
    }
    ++size;
}

template<class T>
void List<T>::RemoveFront()
{
    if(!head)
        return;

    if(size == 1)
    {
        delete head;
    }
    else
    {
        Node* tmp = head;
        head = head->nextPtr;
        head->prevPtr = nullptr;

        delete tmp;
    }
    --size;
}

template<class T>
void List<T>::RemoveBack()
{
    if(!head)
        return;

    if(size == 1)
    {
        delete head;
    }
    else
    {
        Node* current = head;

        while(current->nextPtr)
        {
            current = current->nextPtr;
        }
        current->prevPtr->nextPtr = nullptr;

        delete current;
    }
    --size;
}

template<class T>
void List<T>::Remove(int _pos)
{
    if(!head)
        return;

    if(_pos == 0)
    {
        RemoveFront();
    }
    else if(_pos == Size() - 1)
    {
        RemoveBack();
    }
    else
    {
        if(size == 1)
        {
            delete head;
        }
        else
        {
            Node* current = head;

            for(auto i = 0; i < _pos; ++i)
            {
                current = current->nextPtr;
            }

            current->prevPtr->nextPtr = current->nextPtr;
            current->nextPtr->prevPtr = current->prevPtr;

            delete current;
        }
        --size;
    }
}

template<class T>
void List<T>::Reverse()
{
    if(!head || size == 1)
        return;

    Node* tempHead = head;
    Node* current = tempHead->nextPtr;
    tempHead->nextPtr = nullptr;
    tempHead->prevPtr = current;

    while(current)
    {
        Node* tmp = current->nextPtr;
        current->nextPtr = tempHead;
        current->prevPtr = tmp;
        tempHead = current;
        current = tmp;
    }
    head = tempHead;
}
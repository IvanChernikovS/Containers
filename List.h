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
        explicit Node(T* _data = nullptr,
                      Node* _nextPtr = nullptr,
                      Node* _prevPtr = nullptr)
        :Data(_data), nextPtr(_nextPtr), prevPtr(_prevPtr)
        {}

        ~Node() noexcept
        {
            Data    = nullptr;

            nextPtr = nullptr;
            prevPtr = nullptr;
        }

        T* Data         = nullptr;

        Node* nextPtr   = nullptr;
        Node* prevPtr   = nullptr;
    };

public:
    explicit List()                         = default;
    virtual ~List();

    List(const List&)                       = delete;
    List(List&&)                noexcept    = delete;

    List& operator= (const List&)           = delete;
    List& operator= (List&&)    noexcept    = delete;

    T& operator[] (int index)   const;

    virtual void Print()        const;
    virtual void PrintReverse() const;

    int          Size()         const { return size; }
    bool         Empty()        const { return size == 0; }

    void         Clear();

    virtual void AddFront(T* _data);
    virtual void AddBack(T* _data);
    virtual void Add(int _pos, T* _data);

    virtual void RemoveFront();
    virtual void RemoveBack();
    virtual void Remove(int _pos);

    virtual void Reverse();

private:
    int size    = 0;
    Node* head  = nullptr;
};

template<class T>
List<T>::~List()
{
    Clear();
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
            return *current->Data;
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
        std::cout << *it->Data << " ";
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
        std::cout << *it->Data << " ";
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
void List<T>::AddFront(T* _data)
{
    if(!head)
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
void List<T>::AddBack(T* _data)
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
void List<T>::Add(int _pos, T* _data)
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

    Node* tmp = head;
    head = head->nextPtr;
    head->prevPtr = nullptr;

    delete tmp;
    --size;
}

template<class T>
void List<T>::RemoveBack()
{
    if(!head)
        return;

    Node* current = head;

    while(current->nextPtr)
    {
        current = current->nextPtr;
    }
    current->prevPtr->nextPtr = nullptr;

    delete current;
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
        --size;
    }
}

template<class T>
void List<T>::Reverse()
{
    if(!head)
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
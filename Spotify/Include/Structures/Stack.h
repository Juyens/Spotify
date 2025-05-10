#pragma once

#include "Node.h"

template <typename T>
class Stack
{
private:
    Node<T>* top;
    uint size;

public:
    Stack() : top(nullptr), size(0) {}

    ~Stack()
    {
        while (!isEmpty()) pop();
    }

    void push(T elem)
    {
        Node<T>* newNode = new Node<T>(elem);
        newNode->setNext(top);
        top = newNode;
        ++size;
    }

    void pop()
    {
        if (isEmpty()) return;
        Node<T>* temp = top;
        top = top->getNext();
        delete temp;
        --size;
    }

    T peek() const
    {
        if (isEmpty()) throw std::runtime_error("Stack is empty");
        return top->getElement();
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    uint getSize() const
    {
        return size;
    }
};

#pragma once

#include "Node.h"

template <typename T>
class Queue
{
private:
    Node<T>* front;
    Node<T>* rear;
    uint size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue()
    {
        while (!isEmpty()) dequeue();
    }

    void enqueue(T elem)
    {
        Node<T>* newNode = new Node<T>(elem);
        if (rear == nullptr)
        {
            front = rear = newNode;
        }
        else
        {
            rear->setNext(newNode);
            rear = newNode;
        }
        ++size;
    }

    T dequeue()
    {
        if (isEmpty()) throw std::runtime_error("Queue is empty");

        Node<T>* temp = front;
        T data = front->getElement();
        front = front->getNext();

        if (front == nullptr) rear = nullptr;

        delete temp;
        --size;
        return data;
    }

    T peek() const
    {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        return front->getElement();
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

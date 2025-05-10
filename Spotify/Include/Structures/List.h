#pragma once

#include "Node.h"

#include <functional>
#include <stdexcept>

template<class T>
class List
{
private:
    typedef std::function<int(T, T)> Compare;
    Compare compare;
    Node<T>* head;
    uint length;

public:
    List()
        : head(nullptr), length(0), compare(nullptr)
    {
    }

    List(Compare cmp)
        : head(nullptr), length(0), compare(cmp)
    {
    }

    List(Node<T>* pNode, Compare cmp)
        : head(pNode), compare(cmp), length(0)
    {
    }

    ~List()
    {
        Node<T>* aux = head;
        while (aux != nullptr)
        {
            Node<T>* temp = aux;
            aux = aux->getNext();
            delete temp;
        }
    }

    List<T>& operator=(const List<T>& other);

    uint size();
    bool isEmpty();
    void addFirst(T elem);
    void addAtPosition(T elem, uint pos);
    void addLast(T elem);
    void updateFirst(T elem);
    void updateAtPosition(T elem, uint pos);
    void updateLast(T elem);
    void removeFirst();
    void removeAtPosition(uint pos);
    void removeLast();
    T getFirst();
    T getAtPosition(uint pos);
    T getLast();
    T find(T elem);
    void swap(uint index1, uint index2);
    void clear();
};

template<class T>
inline List<T>& List<T>::operator=(const List<T>& other)
{
    if (this == &other)
    {
        return *this;
    }

    this->clear();

    Node<T>* aux = other.head;
    while (aux != nullptr)
    {
        this->addLast(aux->getElement());
        aux = aux->getNext();
    }

    return *this;
}

template <class T>
uint List<T>::size()
{
    return length;
}

template <class T>
bool List<T>::isEmpty()
{
    return length == 0;
}

template <class T>
void List<T>::addFirst(T elem)
{
    Node<T>* newNode = new Node<T>(elem);
    newNode->setNext(head);
    head = newNode;
    length++;
}

template <class T>
T List<T>::find(T elem)
{
    if (!compare)
    {
        throw std::invalid_argument("Compare function is null");
    }

    Node<T>* aux = head;
    while (aux != nullptr)
    {
        if (compare(aux->getElement(), elem) == 0)
        {
            return aux->getElement();
        }
        aux = aux->getNext();
    }

    throw std::runtime_error("Element not found");
}

template<class T>
void List<T>::swap(uint index1, uint index2)
{
    if (index1 >= length || index2 >= length)
    {
        throw std::out_of_range("Position out of range in swap");
    }

    Node<T>* node1 = head;
    Node<T>* node2 = head;

    for (uint i = 0; i < index1; ++i)
    {
        node1 = node1->getNext();
    }

    for (uint i = 0; i < index2; ++i)
    {
        node2 = node2->getNext();
    }

    T temp = node1->getElement();
    node1->setElement(node2->getElement());
    node2->setElement(temp);
}

template <class T>
void List<T>::addAtPosition(T elem, uint pos)
{
    if (pos > length) return;

    if (pos == 0)
    {
        addFirst(elem);
    }
    else
    {
        Node<T>* aux = head;
        for (uint i = 1; i < pos; i++)
        {
            aux = aux->getNext();
        }
        Node<T>* newNode = new Node<T>(elem);
        newNode->setNext(aux->getNext());
        aux->setNext(newNode);
        length++;
    }
}

template <class T>
void List<T>::addLast(T elem)
{
    Node<T>* newNode = new Node<T>(elem);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node<T>* aux = head;
        while (aux->getNext() != nullptr)
        {
            aux = aux->getNext();
        }
        aux->setNext(newNode);
    }
    length++;
}

template <class T>
void List<T>::removeFirst()
{
    if (length > 0)
    {
        Node<T>* aux = head;
        head = head->getNext();
        delete aux;
        length--;
    }
}

template <class T>
void List<T>::removeAtPosition(uint pos)
{
    if (pos < length)
    {
        if (pos == 0)
        {
            removeFirst();
        }
        else
        {
            Node<T>* aux = head;
            for (uint i = 1; i < pos; i++)
            {
                aux = aux->getNext();
            }
            Node<T>* temp = aux->getNext();
            aux->setNext(temp->getNext());
            delete temp;
            length--;
        }
    }
}

template <class T>
void List<T>::removeLast()
{
    removeAtPosition(length - 1);
}

template <class T>
void List<T>::updateFirst(T elem)
{
    if (length > 0)
    {
        head->setElement(elem);
    }
}

template <class T>
void List<T>::updateAtPosition(T elem, uint pos)
{
    if (pos < length)
    {
        Node<T>* aux = head;
        for (uint i = 0; i < pos; i++)
        {
            aux = aux->getNext();
        }
        aux->setElement(elem);
    }
}

template <class T>
void List<T>::updateLast(T elem)
{
    updateAtPosition(elem, length - 1);
}

template <class T>
T List<T>::getFirst()
{
    if (isEmpty())
    {
        throw std::out_of_range("List is empty");
    }

    return getAtPosition(0);
}

template <class T>
T List<T>::getAtPosition(uint pos)
{
    if (pos >= length)
    {
        throw std::out_of_range("Position out of range");
    }

    Node<T>* aux = head;
    for (uint i = 0; i < pos; i++)
    {
        aux = aux->getNext();
    }
    return aux->getElement();
}

template <class T>
T List<T>::getLast()
{
    return getAtPosition(length - 1);
}

template <class T>
void List<T>::clear()
{
    Node<T>* current = head;
    Node<T>* next = nullptr;

    while (current != nullptr)
    {
        next = current->getNext();
        delete current;
        current = next;
    }

    head = nullptr;
    length = 0;
}
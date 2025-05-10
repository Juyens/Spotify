#pragma once

typedef unsigned int uint;

template<class T>
class Node
{
private:
	T m_Element;
	Node<T>* m_Next;

public:
	Node() : m_Next(nullptr) {}

	Node(T element)
		: m_Element(element), m_Next(nullptr)
	{
	}

	void setElement(T element) { m_Element = element; }
	T getElement() { return m_Element; }

	void setNext(Node<T>* next) { m_Next = next; }
	Node<T>* getNext() { return m_Next; }

	bool isEmpty() { return !m_Next; }
};
/*************************************************
* Author:          Jaden Prante
* File Name:       DoublyLinkedList.h
* Date Created:    Apr 6th 2025
* Modifications:   Currently same date
* 
* 
**************************************************/

#pragma once
#include <iostream>
#include "Node.h"
#include "Exception.h"

using std::cout;
using std::endl;

/************************************************************************
* Class: DoublyLinkedList
*
* Purpose: This class strings nodes together
*
* Manager functions:
*	DoublyLinkedList();
*	~DoublyLinkedList();
*	DoublyLinkedList(const DoublyLinkedList<T>& other);
*	DoublyLinkedList(DoublyLinkedList<T>&& other)noexcept;
*	DoublyLinkedList& operator =(const DoublyLinkedList<T>& rhs);
*	DoublyLinkedList& operator =(DoublyLinkedList<T>&& rhs)noexcept;
*
* Methods:
*	bool isEmpty();
*	const T& First();
*	const T& Last();
*	void Prepend(T data);
*	void Append(T data);
*	void Purge();
*	void Extract(T value);
*	void InsertAfter(T newItem, T existingItem);
*	void InsertBefore(T newItem, T existingItem);
*	void PrintFowards();
*	void PrintBackwards();
*
*************************************************************************/

template <typename T>
class DoublyLinkedList
{
public:
	DoublyLinkedList();
	~DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList<T>& other);
	DoublyLinkedList(DoublyLinkedList<T>&& other)noexcept;
	DoublyLinkedList& operator =(const DoublyLinkedList<T>& rhs);
	DoublyLinkedList& operator =(DoublyLinkedList<T>&& rhs)noexcept;
	Node<T>* getHead();
	Node<T>* getTail();
	void setHead(Node<T>* head);
	void setTail(Node<T>* tail);
	bool isEmpty();
	const T& First();
	const T& Last();
	void Prepend(T data);
	void Append(T data);
	void Purge();
	void Extract(T value);
	void InsertAfter(T newItem, T existingItem);
	void InsertBefore(T newItem, T existingItem);
	void PrintFowards();
	void PrintBackwards();
	T GetTailData() const;
private:
	Node<T>* m_head;
	Node<T>* m_tail;
};



// Default Constructor
/**********************************************************************
* Purpose: Creates default object
*
* Precondition:
*		Calls a new blank object
*
* Postcondition:
*		New object is created
*
************************************************************************/
template<typename T>
inline DoublyLinkedList<T>::DoublyLinkedList() : m_head(nullptr), m_tail(nullptr)
{
}

// Destructor
/**********************************************************************
* Purpose: Destroys an object
*
* Precondition:
*			End of function or program
*
* Postcondition:
*			Memort leaks are avoided, objects are gone.
*
************************************************************************/
template<typename T>
inline DoublyLinkedList<T>::~DoublyLinkedList()
{
	Purge();
}



// Copy Constructor
/**********************************************************************
* Purpose: Copies one object into antother objcet
*
* Precondition:
*		2 objects with an equal sign between them
*
* Postcondition:
*		2 objects with the same values
*
************************************************************************/
template<typename T>
inline DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : m_head(nullptr), m_tail(nullptr)
{
	if (other.m_head)
	{
		Node<T>* current = other.m_head;
		while (current != nullptr)
		{
			Append(current->m_data);
			current = current->m_next;
		}
	}
}


// Move Constructor
/**********************************************************************
* Purpose:	to move information form one object to another
*
* Precondition:
*		a call for a new object with anther object being passed in
*
* Postcondition:
*		the new object having the data of the other object. While the other object is now a nullptr
*
************************************************************************/
template<typename T>
inline DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& other) noexcept : m_head(other.m_head), m_tail(other.m_tail)
{
	other.m_head = nullptr;
	other.m_tail = nullptr;
}



// Copy Assignment Operator
template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& rhs)
{
	if (rhs.m_head != nullptr)
	{
		Purge();
		Node<T>* current = rhs.m_head;
		while (current != nullptr)
		{
			Append(current->m_data);
			current = current->m_next;
		}
	}
	return *this;
}

// Move Assignment Operator
template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& rhs)noexcept
{
	if (rhs.m_head != nullptr)
	{
		m_head = rhs.m_head;
		m_tail = rhs.m_tail;
		rhs.m_head = nullptr;
		rhs.m_tail = nullptr;
	}
	return *this;
}

// Getter Functions
/**********************************************************************
* Purpose: Head - to return the current Head to the client
*		   tail - to return the Tail to the client
*
* Precondition: Head - a getHead() call on an object is called
*				Tail - a getTail() call on an object is called
*
* Postcondition: Head - m_head is given to the client
*				 Tail - m_tail is given to the client
*
************************************************************************/
template<typename T>
inline Node<T>* DoublyLinkedList<T>::getHead()
{
	return m_head;
}

template<typename T>
inline Node<T>* DoublyLinkedList<T>::getTail()
{
	return m_tail;
}


// Setter Functions
/**********************************************************************
* Purpose: Head - The change m_head
*		   Tail - The change m_tail
*
* Precondition: Head - Calls setHead() with a message for m_head
*				Tail - Calls setTail()  with a message for m_tail
*
* Postcondition: Head - m_head is changed
*				 Tail - m_tail is changed
*
************************************************************************/
template<typename T>
inline void DoublyLinkedList<T>::setHead(Node<T>* head)
{
	m_head = head;
}

template<typename T>
inline void DoublyLinkedList<T>::setTail(Node<T>* tail)
{
	m_tail = tail;
}

// isEmpty Function
/**********************************************************************
* Purpose: Checks if the LinkedList is empty
*
* Precondition:
*			Calls the isEmpty functions
*
* Postcondition:
*		Returns a true/false statement
*
************************************************************************/
template<typename T>
inline bool DoublyLinkedList<T>::isEmpty()
{
	return m_head == nullptr;
}

// First Functions
/**********************************************************************
* Purpose: Returns first node data
*
* Precondition:
*			Calls first node
*
* Postcondition:
*			Returns the data in first node
*
************************************************************************/
template<typename T>
inline const T& DoublyLinkedList<T>::First()
{
	if (m_head != nullptr)
		return m_head->m_data;
	else
		throw Exception("List has no contents");
}

// Last Functions
/**********************************************************************
* Purpose: Returns last node data
*
* Precondition:
*			Calls last node
*
* Postcondition:
*			Returns the data in last node
************************************************************************/
template<typename T>
inline const T& DoublyLinkedList<T>::Last()
{
	if (m_tail != nullptr)
		return m_tail->m_data;
	else
		throw Exception("List has no contents");
}

// Prepend Function
/**********************************************************************
* Purpose: Adds a node to the front of the list
*
* Precondition:
*		Calls prepend with new data being passed in
*
* Postcondition:
*		Adds a new object at the front of the list
************************************************************************/
template<typename T>
inline void DoublyLinkedList<T>::Prepend(T data)
{
	Node<T>* newNode = new Node<T>;
	newNode->m_data = data;
	if (m_head == nullptr)
	{
		m_head = newNode;
		m_tail = newNode;
	}
	else if (m_head != nullptr)
	{
		m_head->m_prev = newNode;
		newNode->m_next = m_head;
		m_head = newNode;
	}
}

// Append Function
/**********************************************************************
* Purpose: Adds a node to the back of the list
*
* Precondition:
*		Calls prepend with new data being passed in
*
* Postcondition:
*		Adds a new object at the back of the list
* 
************************************************************************/
template<typename T>
inline void DoublyLinkedList<T>::Append(T data)
{
	Node<T>* newNode = new Node<T>;
	newNode->m_data = data;
	if (m_head == nullptr)
	{
		m_head = newNode;
		m_tail = newNode;
	}
	else if (m_head != nullptr)
	{
		m_tail->m_next = newNode;
		newNode->m_prev = m_tail;
		m_tail = newNode;
	}
}

// Purge Function
/**********************************************************************
* Purpose: Removes the list
*
* Precondition:
*			Calls for the purge
*
* Postcondition:
*			the list is removed
*
************************************************************************/
template<typename T>
inline void DoublyLinkedList<T>::Purge()
{
	if (m_head != nullptr)
	{
		Node<T>* current = m_head;
		while (current != nullptr)
		{
			current = current->m_next;
			delete m_head;
			m_head = current;
		}
		m_tail = nullptr;
	}
}

// Extract Function
/**********************************************************************
* Purpose: Removes specfic element in the array
*
* Precondition:
*			Calls to extract a value
*
* Postcondition:
*			Node is removed from the list
*
************************************************************************/
template<typename T>
inline void DoublyLinkedList<T>::Extract(T value)
{
	if (m_head != nullptr)
	{
		bool move = true;
		Node<T>* current = m_head;
		Node<T>* prev = nullptr;
		while (current != nullptr && move)
		{
			if (current->m_data == value)
			{
				move = false;
				if (current == m_head)
				{
					if (m_head->m_next != nullptr)
					{
						current = current->m_next;
						delete m_head;
						m_head = current;
						m_head->m_prev = nullptr;
					}
					else
					{
						delete m_head;
						m_head = nullptr;
						m_tail = nullptr;
					}
				}
				else if (current == m_tail)
				{
					current = current->m_prev;
					delete m_tail;
					m_tail = current;
					m_tail->m_next = nullptr;
				}
				else
				{
					prev->m_next = prev->m_next->m_next;
					prev = prev->m_next;
					prev->m_prev = prev->m_prev->m_prev; //
					delete current;
				}

			}
			else
			{
				prev = current;
				current = current->m_next;
			}
		}
		if (move)
		{
			throw Exception("Data is not availaibe");
		}
	}
	else
	{
		throw Exception("List is empty");
	}

}

// InsertAfter Function
/**********************************************************************
* Purpose: Adds node after another node
*
* Precondition:
*			Calls InsertAfter, with some information being passed in
*
* Postcondition:
*			New obejct to list is added
*
************************************************************************/

template<typename T>
inline void DoublyLinkedList<T>::InsertAfter(T newItem, T existingItem)
{
	if (m_head != nullptr)
	{
		bool move = true;
		Node<T>* current = m_head;
		while (current != nullptr && move)
		{
			if (current->m_data == existingItem)
			{
				Node<T>* newNode = new Node<T>;
				newNode->m_data = newItem;
				move = false;
				if (current == m_tail)
				{
					m_tail->m_next = newNode;
					newNode->m_prev = m_tail;
					m_tail = newNode;
				}
				else if (current == m_head)
				{
					newNode->m_prev = current;
					current = current->m_next;
					newNode->m_next = current;
					current->m_prev = newNode;
					m_head->m_next = newNode;
				}
				else
				{
					current = current->m_next;
					newNode->m_next = current;
					current = current->m_prev;
					newNode->m_prev = current;
					current->m_next = newNode;
				}
			}
			else
			{
				current = current->m_next;
			}
		}
		if (move)
		{
			throw Exception("Data is not availaibe");
		}
	}
	else
	{
		throw Exception("List is Empty");
	}
}

// InsertBefore Function
/**********************************************************************
* Purpose: Adds node before another node
*
* Precondition:
*			Calls insertBefore, with some information being passed in
*
* Postcondition:
*			New object is added to the list
*
************************************************************************/

template<typename T>
inline void DoublyLinkedList<T>::InsertBefore(T newItem, T existingItem)
{
	if (m_head != nullptr)
	{
		bool move = true;
		Node<T>* current = m_head;
		while (current != nullptr && move)
		{
			if (current->m_data == existingItem)
			{
				Node<T>* newNode = new Node<T>;
				newNode->m_data = newItem;
				move = false;
				if (current == m_head)
				{
					m_head->m_prev = newNode;
					newNode->m_next = m_head;
					m_head = newNode;
				}
				else if (current == m_tail)
				{
					newNode->m_next = current;
					current = current->m_prev;
					newNode->m_prev = current;
					current->m_next = newNode;
					m_tail->m_prev = newNode;
				}
				else
				{
					current = current->m_next;
					newNode->m_next = current;
					current = current->m_prev;
					newNode->m_prev = current;
					current->m_next = newNode;
				}

			}
			else
			{
				current = current->m_next;
			}
		}
		if (move)
		{
			throw Exception("Data is not availaibe");
		}
	}
	else
	{
		throw Exception("List is Empty");
	}
}

// PrintForward Function
/**********************************************************************
* Purpose: Prints list from front to back
*
* Precondition:
*			Calls the PrintForward
*
* Postcondition:
*			the list is printed
*
************************************************************************/

template<typename T>
inline void DoublyLinkedList<T>::PrintFowards()
{
	if (m_head != nullptr)
	{
		Node<T>* current = m_head;
		while (current != nullptr)
		{
			cout << " <- " << current->m_data << " -> " << endl;
			current = current->m_next;

		}
	}
}

// Printbackward Function
/**********************************************************************
* Purpose: Prints list front back to fromt
*
* Precondition:
*			Calls the PrintForward
*
* Postcondition:
*			the list is printed
*
************************************************************************/
template<typename T>
inline void DoublyLinkedList<T>::PrintBackwards()
{
	if (m_head != nullptr)
	{
		Node<T>* current = m_tail;
		while (current != nullptr)
		{
			cout << " <- " << current->m_data << " -> " << endl;
			current = current->m_prev;

		}
	}
}

template<typename T>
inline T DoublyLinkedList<T>::GetTailData() const
{
	if (m_tail == nullptr) {
		throw Exception("List is empty.");
	}
	return m_tail->m_data; // Assuming tail is of type Node<T>* and holds data.return T();
}

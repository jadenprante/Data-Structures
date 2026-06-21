/*************************************************
* Author:          Jaden Prante
* File Name:       List.h
* Date Created:    Apr 6th 2025
* Modifications:   currently Same date
* 
* 
**************************************************/
#pragma once
#include <iostream>

/************************************************************************
* Class: Node
*
* Purpose: This class handles node creation
*
* Manager functions:
* 	 Node();
*	~Node();
*	Node(const Node<T>& other);
*	Node(Node<T>&& other)noexcept;
*	Node<T>& operator =(const Node<T>& rhs);
*	Node<T>& operator =(Node<T>&& rhs)noexcept;
*
* Methods:
*	T getData();
*	Node<T>* getNextNodePtr();
*   Node<T>* getPreviousNodePtr();
*   void setData(T data);
*	void setNext(Node<T>* next);
*	void setPrevious(Node<T>* next);
*
*************************************************************************/

template <typename T>
class DoublyLinkedList;

template <typename T>
class Node
{
public:
	// Manager Functions and Operators
	Node();  
	~Node(); 
	Node(const Node<T>& other); 
	Node(Node<T>&& other)noexcept; 
	Node<T>& operator =(const Node<T>& rhs); 
	Node<T>& operator =(Node<T>&& rhs)noexcept; 

	// Getters
	T getData(); 
	Node<T>* getNext(); 
	Node<T>* getPrevious(); 

	// Setters
	void setData(T data); 
	void setNext(Node<T>* next);
	void setPrevious(Node<T>* next);

private:
	friend class DoublyLinkedList<T>;
	T m_data;
	Node<T>* m_next;
	Node<T>* m_prev;
};

// Default Constructor
/**********************************************************************
* Purpose: creates a default object
*
* Precondition:
*		a call for a new blank object
*
* Postcondition:
*		A new blank object is created
*
************************************************************************/
template<typename T>
inline Node<T>::Node() : m_data(), m_next(nullptr), m_prev(nullptr)
{}

// Deconstrutor
/**********************************************************************
* Purpose: destroys an object
*
* Precondition:
*			end of function or program
*
* Postcondition:
*			memory leaks are avoided and objects are gone.
*
************************************************************************/
template<typename T>
inline Node<T>::~Node()
{
	m_next = nullptr;
	m_prev = nullptr;
}

// Copy Constructor
/**********************************************************************
* Purpose: to create an object that is a copy of another object
*
* Precondition:
*			a call for a new object with anther object being passed in
*
* Postcondition:
*			two objects witht the same data are created
*
************************************************************************/

template<typename T>
inline Node<T>::Node(const Node<T>& other) : m_data(other.m_data), m_next(other.m_next), m_prev(other.m_prev)
{}

// Move Construtor
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
inline Node<T>::Node(Node<T>&& other) noexcept : m_data(std::move(other.m_data)), m_next(std::move(other.m_next)), m_prev(std::move(other.m_prev))
{}

// Copy Assignment Operator
/**********************************************************************
* Purpose: to copy one object into antother objcet
*
* Precondition:
*		two objects with an equal sign between them
*
* Postcondition:
*		two objects with the same values
*
************************************************************************/
template<typename T>
inline Node<T>& Node<T>::operator=(const Node<T>& rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_next = rhs.m_next;
		m_prev = rhs.m_prev;
	}
	return *this;
}

// Move Assignment Operator
/**********************************************************************
* Purpose: to move information in one object to another
*
* Precondition:
*		two objects with an equal sign between them with the rhs having an std::move
*
* Postcondition:
*		one ojbect with the information of the rhs object
*
************************************************************************/
template<typename T>
inline Node<T>& Node<T>::operator=(Node<T>&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_next = rhs.m_next;
		m_prev = rhs.m_prev;
		rhs.m_next = nullptr;
		rhs.m_prev = nullptr;
	}
	return *this;
}

// Getter Functions
/**********************************************************************
* Purpose: Data - Returns  data to the client
*		   Next - Returns next pointer to the client
*		   Previous - Returns previous pointer to the client
*
* Precondition: Data - Calls an object
*				Next - Returns m_nect to the client
*				Previous - Calls getPrevious() on an object
*
* Postcondition: Data - m_data is given to the client
*				 Next - m_next is given to the client
*				 Previous - m_prev is given to the client

*
************************************************************************/

template<typename T>
inline T Node<T>::getData()
{
	return m_data;
}

template<typename T>
inline Node<T>* Node<T>::getNext()
{
	return m_next;
}

template<typename T>
inline Node<T>* Node<T>::getPrevious()
{
	return m_prev;
}

// Setter Functions
/**********************************************************************
* Purpose: Data - Holds m_data change
*		   Nest - Holds m_nect change
*		   Previous Holds m_prev change
* 
*
* Precondition: Data - called with a message for m_data
*				 Next - Calls setNext() with a message for m_next
*				 Previous - Calls setPrevious() with a message for m_prev
*
*
* Postcondition: Data - m_data is changed
* *				 Next - m_next is changed
*				 Previous - m_prev is changed

*
************************************************************************/
template<typename T>
inline void Node<T>::setData(T data)
{
	m_data = data;
}

template<typename T>
inline void Node<T>::setNext(Node<T>* next)
{
	m_next = next->m_next;
}

template<typename T>
inline void Node<T>::setPrevious(Node<T>* next)
{
	m_prev = next->m_prev;
}


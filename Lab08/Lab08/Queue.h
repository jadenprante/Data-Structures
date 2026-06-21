/*************************************************
* Author:          Jaden Prante
* File Name:       Queue.h
* Date Created:    Apr 21st 2025
* Modifications:   Currenrly same date
*
* Class: Stack
*
* Purpose: This class creates a dynamic one-dimensional array that can be
*          started at any base.
*
* Manager Functions:
*       Stack() - Default Constructor
*       Stack(int size) - Constructor with parameters
*       Stack(const Stack<T>& other) - Copy Constructor
*       Stack(Stack<T>&& other) noexcept - Move Constructor
*       Stack& operator=(const Stack<T>& other) - Copy Assignment Operator
*       Stack& operator=(Stack<T>&& other) noexcept - Move Assignment Operator
*       ~Stack - Deconstructor
*
* Methods:
*       void Push(T data);
*       T Pop();
*       T Peek() const;
*       int getNumElements() const;
*       int getSize() const;
*       void setSize(int new_size);
*       bool isEmpty() const;
*       bool isFull() const;
**************************************************/

#pragma once
#include <iostream>
#include "Node.h"
#include "DoublyLinkedList.h"
#include "Exception.h"

template <typename T>
class Queue
{
public:
	Queue();
	Queue(const Queue& other);
	Queue(Queue&& othert) noexcept;
	Queue& operator= (const Queue& other);
	Queue& operator= (Queue&& othert) noexcept;
	~Queue();
	void Enqueue(T data);
	T Dequeue();
	T Peek();
	int getNumElements() const;
	bool isEmpty() const;
private:
	int m_num_elements;
	DoublyLinkedList<T> m_queue;
};

// Defaul Constructor
/*************************************************
*Purpose : Initialize queue
*
*Precondition : NA
*
*Postcondistion : NA
*
**************************************************/
template<typename T>
inline Queue<T>::Queue() : m_num_elements(0) {}

// Copy Constructor
/*************************************************
*Purpose : Creates a copy of a queue object
*
*Precondition : Called when a class object is created based on another object value
*
*Postcondistion : New object would be created based on another object value
*
**************************************************/
template<typename T>
inline Queue<T>::Queue(const Queue& other) : m_num_elements(other.m_num_elements), m_queue(other.m_queue) {}

// Move Constructor
/*************************************************
Purpose : Makes a shallow copy of the object
*
*Precondition : Called when a class object is created based on another object value on the right hand side
*
*Postcondistion : New object would be created based on another object value
*
**************************************************/
template<typename T>
inline Queue<T>::Queue(Queue&& other) noexcept : m_num_elements(other.m_num_elements), m_queue(std::move(other.m_queue))
{
    other.m_num_elements = 0;
}

// Copy Assignment Operator
/*************************************************
*Purpose : Makes a deep copy of the object and assigns it to another object
*
*Precondition : Called when a class is set equal to another object of the class and sets values of two objects to be equal
*
*Postcondistion : Value is set equal to another object that it passes into
*
**************************************************/
template<typename T>
inline Queue<T>& Queue<T>::operator=(const Queue& other)
{
    if (this != &other)
    {
        m_queue = other.m_queue;
        m_num_elements = other.m_num_elements;
    }
    return *this;
}

// Move Assignment Operator
/*************************************************
*Purpose : Makes a shallow copy of the object and sets the value of this to the same value on the right hand side
*
*Precondition : Called when a class object is set equal to another object value by the right hand reference
*
*Postcondistion : Value is set equal to another object that it passes into
*
*
**************************************************/
template<typename T>
inline Queue<T>& Queue<T>::operator=(Queue&& other) noexcept
{
    if (this != &other) 
    {
        m_queue = std::move(other.m_queue);
        m_num_elements = other.m_num_elements;
        other.m_num_elements = 0;
    }
    return *this;
}

// Destructor
/*************************************************
*Purpose : Frees dynamically allocated memory for the queue and resets the internal state
*
*Precondition : m_queue must point to valid memory or be nullptr
*
*Postcondistion : Memory is deallocated, and the queue's attributes are reset
*
**************************************************/
template<typename T>
inline Queue<T>::~Queue()
{
    m_queue.Purge();
}

// Enqueue function
template<typename T>
inline void Queue<T>::Enqueue(T data)
{
    m_queue.Append(data); 
    m_num_elements++;
}

// Dequeue function
template<typename T>
inline T Queue<T>::Dequeue()
{
    if (isEmpty()) 
    {
        throw Exception("Queue is empty");
    }
    T frontValue = m_queue.First(); 
    m_queue.Extract(frontValue); 
    m_num_elements--;
    return frontValue;
}

// Peek function
/*************************************************
*Purpose : returns value, doesn't permit top
*
*Precondition : NA
*
*Postcondistion : private members are set
*
**************************************************/
template<typename T>
inline T Queue<T>::Peek() 
{
    if (isEmpty()) 
    {
        throw Exception("Queue is empty");
    }
    return m_queue.First();
}

// getNumElements function
/*************************************************
*Purpose : gets number of elements
*
*Precondition : data members
*
*Postcondistion :   returns m_num_elements
*
**************************************************/
template<typename T>
inline int Queue<T>::getNumElements() const
{
    return m_num_elements;
}

// isEmpty function
/*************************************************
*Purpose : checks if the queue is empty
*
*Precondition : queue contents
*
*Postcondistion : empties m_top
*
**************************************************/
template<typename T>
inline bool Queue<T>::isEmpty() const
{
    return m_num_elements == 0;               
}

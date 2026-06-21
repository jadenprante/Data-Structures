/*************************************************
* Author:          Jaden Prante
* File Name:       Stack.h
* Date Created:    Apr 21st 2025
* Modifications:   Currenrly same date
*
* Class: Stack
*
* Purpose: This class creates a dynamic one-dimensional array that can be
*          started at any base.
*
* Manager Functions:
*       CircularQueue() - Default Constructor
*       CircularQueue(int size) - Constructor with parameters
*       CircularQueue(const CircularQueue& other) - Copy Constructor
*       CircularQueue(CircularQueue&& other) noexcept - Move Constructor
*       CircularQueue& operator=(const CircularQueue& other) - Copy Assignment Operator
*       CircularQueue& operator=(CircularQueue&& other) noexcept - Move Assignment Operator
*       ~CircularQueue() - Deconstructor
*
* Methods:
*       void Enqueue(T data);
*	    T Dequeue();
*	    T Peek() const;
*	    int getSize() const;
*	    bool isEmpty() const;
*	    bool isFull() const;
**************************************************/

#pragma once

#include <iostream>
#include "Array.h"
#include "Exception.h"

template <typename T>
class CircularQueue
{
public:
	CircularQueue();
	CircularQueue(int size);
	CircularQueue(const CircularQueue& other);
	CircularQueue(CircularQueue&& other) noexcept;
	CircularQueue& operator=(const CircularQueue& other);
	CircularQueue& operator=(CircularQueue&& other) noexcept;
	~CircularQueue();
	void Enqueue(T data);
	T Dequeue();
	T Peek() const;
	int getSize() const;
	bool isEmpty() const;
	bool isFull() const;
private:
	Array<T> m_queue;
	int m_size;
	int m_head;
	int m_tail;
};

// Default Constructor
/*************************************************
*Purpose : Initialize circular queue
*
*Precondition : NA
*
*Postcondistion : NA
*
**************************************************/
template<typename T>
inline CircularQueue<T>::CircularQueue() : m_size(0), m_head(-1), m_tail(-1), m_queue(0) {}

// Constructor with parameters
/*************************************************
*Purpose : Initialize private members of circular queue
*
*Precondition : NA
*
*Postcondistion : private members are set
*
**************************************************/
template<typename T>
inline CircularQueue<T>::CircularQueue(int size) : m_size(size), m_head(-1), m_tail(-1), m_queue(size)
{}

// Copy Constructor
/*************************************************
*Purpose : Creates a copy of a circular queue
*
*Precondition : Called when a class object is created based on another object value
*
*Postcondistion : New object would be created based on another object value
*
**************************************************/
template<typename T>
inline CircularQueue<T>::CircularQueue(const CircularQueue& other) :  m_size(other.m_size), m_head(other.m_head), m_tail(other.m_tail) 
{
    m_queue = Array<T>(m_size); 
    for (int i = 0; i < m_size; ++i)
    {
        m_queue[i] = other.m_queue[i]; 
    }
}

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
inline CircularQueue<T>::CircularQueue(CircularQueue&& other) noexcept : m_queue(std::move(other.m_queue)), m_size(other.m_size), m_head(other.m_head), m_tail(other.m_tail)
{
    other.m_size = 0;
    other.m_head = 0;
    other.m_tail = 0;
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
inline CircularQueue<T>& CircularQueue<T>::operator=(const CircularQueue& other)
{
    if (this != &other)
    {
        m_queue = other.m_queue;
        m_size = other.m_size;
        m_head = other.m_head;
        m_tail = other.m_tail;
    }
    return *this;
}

//Move Assignment Operator
/*************************************************
*Purpose : Makes a shallow copy of the object and sets the value of this to the same value on the right hand side
*
*Precondition : Called when a class object is set equal to another object value by the right hand reference
*
*Postcondistion : Value is set equal to another object that it passes into
*
**************************************************/
template<typename T>
inline CircularQueue<T>& CircularQueue<T>::operator=(CircularQueue&& other) noexcept
{
    if (this != &other)
    {
        m_queue = std::move(other.m_queue);
        m_size = other.m_size;
        m_head = other.m_head;
        m_tail = other.m_tail;
        other.m_size = 0;
        other.m_head = 0;
        other.m_tail = 0;
    }
    return *this;
}

// Destructor
/*************************************************
*Purpose : Frees dynamically allocated memory for the circular queue and resets the internal state
*
*Precondition : m_queue must point to valid memory or be nullptr
*
*Postcondistion : Memory is deallocated, and the circular queue's attributes are reset
*
**************************************************/
template<typename T>
inline CircularQueue<T>::~CircularQueue() 
{
    m_size = 0;
    m_head = -1;
    m_tail = -1;
}

// Push Function
/*************************************************
*Purpose : pushes data of queue to top
*
*Precondition : NA
*
*Postcondistion : adds data members
*
**************************************************/
template<typename T>
inline void CircularQueue<T>::Enqueue(T data)
{
    if (isFull())
    {
        throw Exception("Queue is full");
    }
    if (m_head == -1)
    {
        m_head = 0;
    }
    m_tail = (m_tail + 1) % m_size;
    m_queue[m_tail] = data;
}

// Pop function
/*************************************************
*Purpose : removes data from bottom of queue
*
*Precondition : NA
*
*Postcondistion : removes data members
*
**************************************************/
template<typename T>
inline T CircularQueue<T>::Dequeue()
{
    if (isEmpty())
    {
        throw Exception("Queue is empty");
    }
    T data = m_queue[m_head];
    if (m_head == m_tail) 
    {
        m_head = m_tail = -1;
    }
    else
    {
        m_head = (m_head + 1) % m_size;
    }
    return data;
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
inline T CircularQueue<T>::Peek() const
{
    if (isEmpty())
    {
        throw Exception("Queue is empty");
    }
    return m_queue[m_head];
}

// getSize function
/*************************************************
*Purpose : gets size of queue
*
*Precondition : data members
*
*Postcondistion :   returns m_size
*
**************************************************/
template<typename T>
inline int CircularQueue<T>::getSize() const
{
    return m_size;
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
inline bool CircularQueue<T>::isEmpty() const
{
    return ((m_head == -1) && (m_tail == -1));
}

// isFull function
/*************************************************
*Purpose : checks if the queue is full
*
*Precondition : queue contents
*
*Postcondistion : returns full queue
*
**************************************************/
template<typename T>
inline bool CircularQueue<T>::isFull() const
{
    bool full = false;
    if (m_head == -1 && m_tail == m_size -1)
    {
        full = true;
    }
    if ((m_tail + 1) % m_size == m_head)
    {
        full = true;
    }
    return full;
}

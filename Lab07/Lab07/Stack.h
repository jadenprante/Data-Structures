/*************************************************
* Author:          Jaden Prante
* File Name:       Stack.h
* Date Created:    Apr 19th 2025
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

template <typename T>
class Stack 
{
public:
    Stack();
    Stack(const Stack<T>& other);
    Stack(Stack<T>&& other) noexcept;
    Stack& operator=(const Stack<T>& other);
    Stack& operator=(Stack<T>&& other) noexcept;
    ~Stack();
	void Push(T data);
	T Pop();
	T Peek() const;
	int getNumElements() const;
	bool isEmpty() const;
private:
	DoublyLinkedList<T> m_stack;
	int num_elements;
};

// Default Constructor
/*************************************************
*Purpose : Initialize stack
*
*Precondition : NA
*
*Postcondistion : NA
*
**************************************************/
template<typename T>
inline Stack<T>::Stack() : num_elements(0) {}

// Copy Constructor
/*************************************************
*Purpose : Creates a copy of a stack object
*
*Precondition : Called when a class object is created based on another object value
*
*Postcondistion : New object would be created based on another object value
*
**************************************************/
template<typename T>
inline Stack<T>::Stack(const Stack<T>& other) : m_stack(other.m_stack), num_elements(other.num_elements) {}


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
inline Stack<T>::Stack(Stack<T>&& other) noexcept : m_stack(std::move(other.m_stack)), num_elements(other.num_elements)
{
    other.num_elements = 0;  // Reset the other stack's element count
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
inline Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    if (this != &other)  // Self-assignment check
    {
        m_stack = other.m_stack;  // Copy the stack
        num_elements = other.num_elements;
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
*
**************************************************/
template<typename T>
inline Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept
{
    if (this != &other)  // Self-assignment check
    {
        m_stack = std::move(other.m_stack);  // Move the stack
        num_elements = other.num_elements;
        other.num_elements = 0;  // Reset the other stack's element count
    }
    return *this;
}

// Destructor
/*************************************************
*Purpose : Frees dynamically allocated memory for the stack and resets the internal state
*
*Precondition : m_stack must point to valid memory or be nullptr
*
*Postcondistion : Memory is deallocated, and the stacks's attributes are reset
*
**************************************************/
template<typename T>
inline Stack<T>::~Stack()
{
    num_elements = 0;
}


// Push Function
/*************************************************
*Purpose : pushes data of stack
*
*Precondition : NA
*
*Postcondistion : adds data members
*
**************************************************/
template <typename T>
inline void Stack<T>::Push(T data)
{
    m_stack.Append(data);
    num_elements++;
}

// Pop Function
/*************************************************
*Purpose : pops data from stack
*
*Precondition : NA
*
*Postcondistion : removes data members
*
**************************************************/
template <typename T>
inline T Stack<T>::Pop()
{
    if (isEmpty()) {
        throw Exception("Stack Underflow!");
    }
    T data = m_stack.Last(); 
    m_stack.Extract(data);
    num_elements--;
    return data;
}

// Peek Function
/*************************************************
*Purpose : returns value, doesn't permit top
*
*Precondition : NA
*
*Postcondistion : private members are set
*
**************************************************/
template <typename T>
inline T Stack<T>::Peek() const
{
    if (isEmpty()) {
        throw Exception("Stack is empty! Cannot peek.");
    }
    return m_stack.GetTailData();
}

// getNumElements Function
/*************************************************
*Purpose : gets number of elements
*
*Precondition : data members
*
*Postcondistion : NumElements - m_top + 1
*
**************************************************/
template <typename T>
inline int Stack<T>::getNumElements() const
{
    return num_elements;
}

// isEmpty Function
/*************************************************
*Purpose : checks if the stack is empty
*
*Precondition : stack contents
*
*Postcondistion : empties m_top
*
**************************************************/

template <typename T>
bool Stack<T>::isEmpty() const
{
    return num_elements == 0;  // If no elements, return true
}


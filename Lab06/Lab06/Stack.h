/*************************************************
* Author:          Jaden Prante
* File Name:       Stack.h
* Date Created:    Apr 19th 2025
* Modifications:   Apr 30th 2025
*                  Added getTop function to test setSize
*                  May 2st 2025
*                  Removed getTop and reworked getSize
*                  Reworked Peek, isEmpty and setSize functions
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
#include "Array.h"

template <typename T>
class Stack
{
public:
    Stack();
    Stack(int size);  
    Stack(const Stack<T>& other);
    Stack(Stack<T>&& other) noexcept;
    Stack& operator=(const Stack<T>& other);
    Stack& operator=(Stack<T>&& other) noexcept;
    ~Stack();
    void Push(T data);
    T Pop();
    T Peek() const;
    int getNumElements() const;
    int getSize() const;
    void setSize(int new_size);
    bool isEmpty() const;
    bool isFull() const;
private:
    Array<T> m_stack;  
    int m_size;
    int m_top;
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
inline Stack<T>::Stack() : m_size(0), m_top(0), m_stack(0)
{}

// Constructor with parameters
/*************************************************
*Purpose : Initialize private members of stack
*
*Precondition : NA
*
*Postcondistion : private members are set
*
**************************************************/
template <typename T>
Stack<T>::Stack(int size) : m_size(size), m_top(-1), m_stack(size) {}

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
inline Stack<T>::Stack(const Stack<T>& other) : m_size(other.m_size), m_top(other.m_top), m_stack(other.m_stack)
{}


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
inline Stack<T>::Stack(Stack<T> && other) noexcept : m_stack(std::move(other.m_stack)), m_top(other.m_top), m_size(other.m_size)
{ }

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
    if (this != &other)
    {
        m_top = other.m_top;
        m_size = other.m_size;
        m_stack = other.m_stack;
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
    if (this != other)
    {
        m_stack = std::move(other.m_stack);
        m_top = other.m_top;
        m_size = other.m_size;
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
    m_size = 0;
    m_top = 0;
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
void Stack<T>::Push(T data)
{
    if (isFull())
    {
        throw Exception("Overflow in stack");
    }
    m_stack[m_top] = data;
    m_top++;
}

// Pop function
/*************************************************
*Purpose : pops data from stack
*
*Precondition : NA
*
*Postcondistion : removes data members
*
**************************************************/
template <typename T>
T Stack<T>::Pop()
{
    if (isEmpty()) 
    {
        throw Exception("Underflow in stack");
    }
    m_top--;
    return m_stack[m_top];
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
template <typename T>
T Stack<T>::Peek() const
{
    if (isEmpty())
    {
        throw Exception("Underflow in stack");
    }
    return m_stack[m_top - 1];  
}

// Getter functions
/*************************************************
*Purpose : NumElements - gets number of elements
*          Size - gets the size of stack
*
*Precondition : NumElements - data members
*               Size - stack
*
*Postcondistion : NumElements - m_top + 1
*                 Size - m_size
*
**************************************************/
template <typename T>
int Stack<T>::getNumElements() const
{
    return m_top + 1;  
}

template <typename T>
int Stack<T>::getSize() const
{
    return m_top; 
}

// setSize function
/*************************************************
*Purpose : set size of stack
*
*Precondition : stack
*
*Postcondistion : size is set
*
**************************************************/
template <typename T>
void Stack<T>::setSize(int new_size)
{
    if (new_size < m_top + 1) 
    {
        throw Exception("New size is smaller than the current number of elements");
    }
    m_stack.SetLength(new_size); 
    m_size = new_size;  
    if (m_top > new_size)
    {
        m_top = new_size;
    }
}

// isEmpty function
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
    bool state = false;
    if (m_top == 0)
    {
       state = true;
    }
    return state;  
}

// isFull function
/*************************************************
*Purpose : checks is the stack is full
*
*Precondition : stack contents
*
*Postcondistion : m_top is the size - 1
*
**************************************************/
template <typename T>
bool Stack<T>::isFull() const
{
    return m_top == m_size;  
}



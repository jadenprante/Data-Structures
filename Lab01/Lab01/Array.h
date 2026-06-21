/*************************************************
* Author:          Jaden Prante
* File Name:       Array.h
* Date Created:    Apr 1st 2025
* Modifications:   Currenrly same date
*
* Class: Array
*
* Purpose: This class creates a dynamic one-dimensional array that can be 
*          started at any base.
*
* Manager Functions: 
*       Array() - The default size is zero and the base is zero.
*       Array(int length, int start_index = 0) - Creates an appropriate sized array with the starting index either zero or the supplied starting value.        
*       Array(const Array & copy) - Copies data in array class
*       Array(Array<T>&& other) - Moves data in aray class
*       Array& operator=(const Array & copy) - operator for copy constructor
*       Array& operator=(Array<T>&& other) - operator for move constructor
*       ~Array() - Deletes data in array class
*
* Methods:
*       operator [] (int index)
*       getStartIndex() 
*       getLength() 
*       setStartIndex() 
*       setLength(int length) 
**************************************************/

#pragma once
#include <iostream>
#include "Exception.h"

template <typename T> 
class Array 
{
private:
    T* m_array;
    int m_start_index;
    int m_length;
public:
    Array();
    Array(int length, int start_index = 0 );
    Array(const Array<T>& other);
    Array(Array<T>&& other) noexcept ;
    Array& operator=(const Array<T>& other);
    Array& operator=(Array<T>&& other) noexcept;
    ~Array();
    T& operator[] (int index);
    const T& operator[] (int index) const;
    int GetStartIndex() const;
    int GetLength() const;
    void SetStartIndex(int start_index);
    void SetLength(int length);
};

// Default constructor function
/*************************************************
*Purpose : Sets the values of class variables
*
*Precondition : Called when object of a class is created
*
*Postcondistion : All variables are set to zero and/or null
*
**************************************************/
template <typename T>
Array<T>::Array() : m_array(nullptr), m_start_index(0), m_length(0) 
{}


// Parameterized constructor function
/*************************************************
*Purpose : Allows client to set m_length vales and set a start indez
*
*Precondition : Calls array object and passes into two ints as parameters
*
*Postcondistion : m_length and m_start_index values are set to new values based on the client passed values
*
**************************************************/
template <typename T>
Array<T>::Array(int length, int start_index) :  m_length(length), m_start_index(start_index), m_array(nullptr)
{
    if (length > 0)
    {
        m_array = new T[length];
    }
    else 
    {
       throw  Exception("Length is not accurate");
    }
}


// Copy constructor function
/*************************************************
*Purpose : Creates a copy of an array object with a copy of m_array
*
*Precondition : Called when a class object is created based on another object value
*
*Postcondistion : New object would be created based on another object value
*
**************************************************/
template <typename T>
Array<T>::Array(const Array<T>& other) : m_array(new T[other.m_length]), m_start_index(other.m_start_index), m_length(other.m_length) 
{
    m_array = new T[other.m_length];
    for (int i = 0; i < m_length; ++i) 
    {
        m_array[i] = other.m_array[i];
    }
}

// Move constructor function
/*************************************************
*Purpose : Makes a shallow copy of the object
*
*Precondition : Called when a class object is created based on another object value on the right hand side 
*
*Postcondistion : New object would be created based on another object value
*
**************************************************/
template <typename T>
Array<T>::Array(Array<T>&& other) noexcept : m_array(other.m_array), m_start_index(other.m_start_index), m_length(other.m_length) 
{
    other.m_array = nullptr;
    other.m_length = 0;
    other.m_start_index = 0;
}

// Copy assignment function
/*************************************************
*Purpose : Makes a deep copy of the object and assigns it to another object
*
*Precondition : Called when a class is set equal to another object of the class and sets values of two objects to be equal
*
*Postcondistion : Value is set equal to another object that it passes into
*
**************************************************/
template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) 
{
    if (this != &other) 
    {
        delete[] m_array;
        m_array = new T[other.m_length];
        m_start_index = other.m_start_index;
        m_length = other.m_length;
        for (int i = 0; i < m_length; ++i) 
        {
            m_array[i] = other.m_array[i];
        }
    }
    return *this;
}

// Move assignment function
/*************************************************
*Purpose : Makes a shallow copy of the object and sets the value of this to the same value on the right hand side
*
*Precondition : Called when a class object is set equal to another object value by the right hand reference
*
*Postcondistion : Value is set equal to another object that it passes into
*
**************************************************/
template <typename T>
Array<T>& Array<T>::operator=(Array<T>&& other) noexcept
{
    if (this != &other) 
    {
        delete[] m_array;
        m_array = other.m_array;
        m_start_index = other.m_start_index;
        m_length = other.m_length;
        other.m_array = nullptr;
        other.m_length = 0;
        other.m_start_index = 0;
    }
    return *this;
}

// Destructor function
/*************************************************
*Purpose : Frees  dynamically allocated memory for the array and resets the internal state
* 
*Precondition : m_array must point to valid memory or be nullptr
*
*Postcondistion : Memory is deallocated, and the array's attributes are reset
* 
**************************************************/
template <typename T>
Array<T>::~Array() 
{
    delete[] m_array;
    m_length = 0;
    m_start_index = 0;
    m_array = nullptr;
}

// Subscript operator
/*************************************************
*Purpose : Accesses the element at the given index, taking the starting index into account
*
*Precondition : The array must not be nullptr. The index must be within bounds
*
*Postcondistion : Returns a reference to the array element at the specified index
*
**************************************************/
template <typename T>
T& Array<T>::operator[](int index) 
{
    if (m_array == nullptr) 
    {
        throw Exception("Array is never null");
    } 
    int actual_index = index - m_start_index;
    if (actual_index < 0 || actual_index > m_length - 1) 
    {
        throw Exception("Index out of bounds");
    }
    return m_array[index - m_start_index];
}

template <typename T>
inline const T& Array<T>::operator[](int index) const
{
    if (m_array == nullptr)
    {
        throw Exception("Array is never null");
    }
    int actual_index = index - m_start_index;
    if (actual_index < 0 || actual_index > m_length - 1)
    {
        throw Exception("Index out of bounds");
    }
    return m_array[index - m_start_index];
}

// Getter Functions
/*************************************************
*Purpose : for Length - Returns the current length of the array
*          for StartIndex - Returns the current starting index of the array
* 
*Precondition : for Length - NA
*               for StartIndex - NA
*
*
*Postcondistion : for Length - Returns the value of m_length
*                 for StartIndex - Returns the value of m_start_index
*
*
**************************************************/
template <typename T>
int Array<T>::GetStartIndex() const 
{
    return m_start_index;
}

template <typename T>
int Array<T>::GetLength() const 
{
    return m_length;
}

// Setter functions
/*************************************************
*Purpose : for Length - Resizes the array to the new length, adjusting memory allocation as needed
*          for StartIndex - Updates the starting index of the array
*
*Precondition : for Length - length must be greater than zero
*               for StartIndex - The new starting index must be a valid integer
*
*
*Postcondistion : for Length - Allocates new arrat memory, up to the minimum of the old and new lengths of data are preserved 
*                 for StartIndex - m_start_index to the specified value
*
*
**************************************************/
template <typename T>
void Array<T>::SetStartIndex(int start_index) 
{
    m_start_index = start_index;
}

template <typename T>
void Array<T>::SetLength(int length) 
{
    if (length > 0)
    {
        if (length < m_length) 
        {
            T* temp = new T[length];
            for (int i = 0; i < length; i++) 
            {
                temp[i] = m_array[i];
            }
            delete[] m_array;
            m_array = new T[length];
            for (int i = 0; i < length; i++)
            {
                m_array[i] = temp[i];
            }
            delete[] temp;
        }
        else if (length > m_length)
        {
            T* temp = new T[m_length];
            for (int i = 0; i < m_length; i++)
            {
                temp[i] = m_array[i];
            }
            delete[] m_array;
            m_array = new T[length];
            for (int i = 0; i < m_length; i++)
            {
                m_array[i] = temp[i];
            }
            delete[] temp;
        }
        m_length = length;
    }
    else
    {
        throw Exception("Length not in bounds");
    }
}

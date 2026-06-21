/*************************************************
* Author:          Jaden Prante
* File Name:       Row.h
* Date Created:    Jan 12th 2025
* Modifications:   Jan 13th - Jan 14th 2025
*				   Getters and Setters work accordingly
*				   Select function also has a const cast
*
* Class: Row
*
* Purpose: This handles row properties within a 2D array.
*
* Manager Functions:
*		Row(Array2D<T>& array2D, int row)
*
* Methods:
*       T& operator[] (int column);
*		const T& operator[] (int column) const;
**************************************************/
#pragma once
#include <iostream>
#include "Exception.h"

template <typename T>
class Array2D;

template <typename T>
class Row
{
public:
	Row(Array2D<T>& array2D, int row);
	T& operator[] (int column) const;
	//const T& operator[] (int column) const;
private:
	friend class Array2D<T>;
	Array2D<T>& m_array2D;
	int m_row;
};

// Constructor with parameters
/*************************************************
*Purpose : Initializes a Row object that represents a specific row in a 2D array
*
*Precondition : array2D is a valid Array2D<T> object
*				row must be a valid row index within bounds of 2D array
*
*Postcondistion : A Row<T> object is created that references the specified row in the Array2D<T> object
*
**************************************************/
template<typename T>
inline Row<T>::Row(Array2D<T>& array2D, int row) : m_array2D(array2D), m_row(row)
{ }

// Subscript Operator 
/*************************************************
*Purpose : Provides access to the element in the specified row and given column index in the 2D array
*
*Precondition :column must be within the valid column range
*			   m_row must be a valid row index within the bounds of the 2D array
*
*Postcondistion : Returns a reference to the element located at the specified column in the row of the 2D array
*
* const version sets them as a cosnt reference
**************************************************/
template<typename T>
inline T& Row<T>::operator[](int column) const
{
	if (column < 0)
	{
		throw Exception("Unable to access negative element");
	}
	return const_cast<T&>(m_array2D.Select(m_row, column));
}

/*template<typename T>
inline const T& Row<T>::operator[](int column) const
{
	if (column < 0)
	{
		throw Exception("Unable to access negative element");
	}
	return m_array2D.Select(m_row, column);
}*/


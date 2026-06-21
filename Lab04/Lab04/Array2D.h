/*************************************************
* Author:          Jaden Prante
* File Name:       Array2D.h
* Date Created:    Apr 10th 2025
* Modifications:   Currently same date
* 
*
* Class: Array2D
*
* Purpose: This class creates a dynamic one-dimensional array that can be
*          started at any base.
*
* Manager Functions:
*       Array2D(int row, int column) - Creates an appropriate sized array with the starting index either zero or the supplied starting value.
*       Array2D(const Array & copy) - Copies data in array class
*       Array2D& operator=(const Array & copy) - operator for copy constructor
*       ~Array2D() - Deletes data in array class
*
* Methods:
*       int getRows() const;
*		int getColumns() const;
*		void setRows(int rows);
*		void setColumns(int columns);
*		Row<T> operator[] (int row);
*		const Row<T> operator[] (int row) const;
*		T& Select(int desired_row, int desired_column) const;
*		const T& Select(int desired_row, int desired_column) const;
**************************************************/
#pragma once

#include "Row.h"
#include "Exception.h"
#include <iostream>

template <typename T>
class Array2D
{
public:
	Array2D();
	Array2D(int row, int column);
	Array2D(const Array2D<T>& other);
	Array2D(Array2D<T>&& other);
	Array2D<T>& operator =(const Array2D<T>& rhs);
	Array2D<T>& operator =(Array2D<T>&& rhs);
	~Array2D();
	int getRow() const;
	int getColumns() const;
	void setRows(int rows);
	void setColumns(int columns);
	Row<T> operator[] (int row);
	const Row<T> operator[] (int row) const;
	T& Select(int desired_row, int desired_column);
	const T& Select(int desired_row, int desired_column) const;
private:
	T** m_array;
	int m_rows;
	int m_columns;
};

// Default Constructor
/*************************************************
*Purpose: Initializes an empty 2D array with zero rows and zero columns
*
*Precondition: NA
*
*Postcondition: An empty Array2D object is created with m_rows = 0 and m_columns = 0
*
**************************************************/
template<typename T>
inline Array2D<T>::Array2D() : m_rows(0), m_columns(0)
{}

// Constructor with parameters
/*************************************************
*Purpose: Initializes a 2D array with the specified number of rows and columns
*
*Precondition: row and column must be non-negative integers
*
*Postcondition: A 2D array with the specified dimensions is created with m_rows = row and m_columns = column
*
**************************************************/
template<typename T>
inline Array2D<T>::Array2D(int row, int column) : m_rows(row), m_columns(column), m_array(nullptr)
{
	m_array = new T * [m_rows];
	for (int i = 0; i < m_rows; i++)
	{
		m_array[i] = new T[m_columns];
	}
}

// Copy Constructor
/*************************************************
*Purpose: Creates a new Array2D object that is a copy of another Array2D object
*
*Precondition: other is a valid Array2D object
*
*Postcondition: A new Array2D object is created with the same size and contents as the other array
*
**************************************************/
template<typename T>
inline Array2D<T>::Array2D(const Array2D<T>& other) : m_columns(other.m_columns), m_rows(other.m_rows)
{
	m_array = new T * [m_rows];
	for (int i = 0; i < m_rows; i++)
	{
		m_array[i] = new T[m_columns];
	}
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j< m_columns; j++)
		{
			m_array[i][j] = other.m_array[i][j];
		}
	}
}

// Move Constructor
/*************************************************
*Purpose : Makes a shallow copy of the object
*
*Precondition : Called when a class object is created based on another object value on the right hand side
*
*Postcondistion : New object would be created based on another object value
*
**************************************************/
template<typename T>
inline Array2D<T>::Array2D(Array2D<T>&& other)
{
	other.m_array = nullptr;
	other.m_rows = 0;
	other.m_columns = 0;
}

// Copy Assignment Operator
/*************************************************
*Purpose: Assigns the contents of one Array2D object (rhs) to another Array2D object
*
*Precondition: rhs is a valid Array2D object
*
*Postcondition: The current object is updated to have the same size and contents as the rhs object
*
**************************************************/
template<typename T>
inline Array2D<T>& Array2D<T>::operator=(const Array2D<T>& rhs)
{
	if (this != &rhs)
	{
		m_rows = rhs.m_rows;
		m_columns = rhs.m_columns;
		m_array = new T * [m_rows];
		for (int i = 0; i < m_rows; i++)
		{
			m_array[i] = new T[m_columns];
		}
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_columns; j++)
			{
				m_array[i][j] = rhs.m_array[i][j];
			}
		}
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
**************************************************/
template<typename T>
inline Array2D<T>& Array2D<T>::operator=(Array2D<T>&& rhs)
{
	if (this != &rhs)
	{
		m_array = rhs.m_array;
		rhs.m_array = nullptr;
		m_rows = rhs.m_rows;
		m_columns = rhs.m_columns;
	}
	return *this;
}

// Deconstructor
/*************************************************
*Purpose: Destroys the Array2D object and cleans up any resources
*
*Precondition: The object must be initialized
*
*Postcondition: The Array2D object is destroyed
*
**************************************************/
template<typename T>
inline Array2D<T>::~Array2D()
{
	for (int i = 0; i < m_rows; i++)
	{
		delete[] m_array[i];
		m_array[i] = nullptr;
	}
	delete[] m_array;
	m_array = nullptr;
	m_rows = 0;
	m_columns = 0;
}

// Getter Functions
/*************************************************
*Purpose : Row - Returns the number of rows in the 2D array
*		   Column - Returns the number of columns in the 2D array
*
*Precondition : Row - The Array2D object must be initialized
*		        Column - The Array2D object must be initialized
*
*
*Postcondistion : Row - Returns the value of m_rows
*		          Column - Returns the value of m_columns
*
**************************************************/
template<typename T>
inline int Array2D<T>::getRow() const
{
	return m_rows;
}

template<typename T>
inline int Array2D<T>::getColumns() const
{
	return m_columns;
}

// Setter Functions
/*************************************************
*Purpose : Row - Sets number of rows in the 2D array
*		   Column - Sets the number of columns in the 2D array
*
*Precondition : Row - rows must be a non-negative integer.
*		        Column - columns must be a non-negative integer
*
*
*Postcondistion : Row - The number of rows is updated to rows.
*		          Column - The number of columns is updated to columns.
*
**************************************************/
template<typename T>
inline void Array2D<T>::setRows(int rows)
{
	if (rows < 0)
	{
		throw Exception("Incorrect number of rows!");
	}
	Array2D<T> temp(rows, m_columns);
	for (int i = 0; i < m_rows && i < rows; i++) 
	{
		for (int j = 0; j < m_columns; j++)
		{
			temp[i][j] = this->Select(i, j);
		}
	}
	for (int i = 0; i < m_rows; i++)
	{
		delete[] m_array[i];
	}
	delete[] m_array;
	m_rows = rows;
	m_array = new T * [m_rows];
	for (int i = 0; i < m_rows; i++)
	{
		m_array[i] = new T[m_columns];  
		for (int j = 0; j < m_columns; j++)
		{
			m_array[i][j] = temp[i][j];  
		}
	}
}

template<typename T>
inline void Array2D<T>::setColumns(int columns)
{
	if (columns < 0)
	{
		throw Exception("Incorrect number of columns!");
	}
	if (m_columns < columns)
	{
		Array2D<T>temp(m_rows, columns);
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (j < m_columns)
				{
					temp[i][j] = Select(i, j);
				}
				else
				{
					temp[i][j] = T();
				}
			}
		}
		for (int i = 0; i < m_rows; i++)
		{
			delete[] m_array[i];
		}
		m_columns = columns;
		for (int i = 0; i < m_rows; i++)
		{
			m_array[i] = new T[m_columns];
			for (int j = 0; j < m_columns; j++)
			{
				m_array[i][j] = temp[i][j];
			}
		}
	}
	else if (m_columns > columns)
	{
		Array2D<T>temp(m_rows, columns);
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
					temp[i][j] = Select(i, j);
			}
		}
		m_columns = columns;
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_columns; j++)
			{
				m_array[i][j] = temp[i][j];
			}
		}
	}
}

// Subscript Operators
/*************************************************
*Purpose: Returns a reference to a specific row in the 2D array for modification.
*
*Precondition: row must be within the valid range of rows (0 to m_rows - 1).
*
*Postcondition: Returns a Row<T> object that represents the specified row, allowing modification of that row's elements.
*
*const version of this makes them all const reference
**************************************************/
template<typename T>
inline Row<T> Array2D<T>::operator[](int row)
{
	if (row < 0)
	{
		throw Exception("Unable to access negative elements");
	}
	else if (row > m_rows)
	{
		throw Exception("Gone out of bounds");
	}
	return Row<T>(*this, row);
}

template<typename T>
inline const Row<T> Array2D<T>::operator[](int row) const
{
	if (row < 0)
	{
		throw Exception("Unable to access negative elements");
	}
	else if (row > m_rows)
	{
		throw Exception("Gone out of bounds");
	}
	return Row<T>(const_cast<Array2D<T>&>(*this), row);
}


// Select Functions
/*************************************************
*Purpose: Returns a reference to the element at the specified row and column in the 2D array.
*
*Precondition: desired_row and desired_column must be within the valid bounds of the array.
*
*Postcondition: Returns a reference to the element at the specified position.
*
* const version makes them all const reference
**************************************************/
template<typename T>
inline T& Array2D<T>::Select(int desired_row, int desired_column)
{
	if (desired_row < 0)
	{
		throw Exception("Variable is not in the array");
	}
	if (desired_column < 0)
	{
		throw Exception("Variable is not in the array");
	}
	if (desired_row > m_rows)
	{
		throw Exception("Gone out of bounds");
	}
	if (desired_column > m_columns)
	{
		throw Exception("Gone out of bounds");
	}
	return m_array[desired_row][desired_column];
}

template<typename T>
inline const T& Array2D<T>::Select(int desired_row, int desired_column) const
{
	if (desired_row < 0)
	{
		throw Exception("Variable is not in the array");
	}
	if (desired_column < 0)
	{
		throw Exception("Variable is not in the array");
	}
	if (desired_row > m_rows)
	{
		throw Exception("Gone out of bounds");
	}
	if (desired_column > m_columns)
	{
		throw Exception("Gone out of bounds");
	}
	return m_array[desired_row][desired_column];
}

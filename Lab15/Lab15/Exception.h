/*************************************************
* Author:          Jaden Prante
* File Name:       Exception.h
* Date Created:    Jan 7th 2025
* Modifications:   Currenrly same date
*
* Class: Exception
*
* Purpose: This class will throw exceptions at something when it's called.
*		
* Manager Functions:
*		Exception() - Default Constructor
*		~Exception() - Destructor
*		Exception(const char* msg) - Constructor with parameter
*		Exception(const Exception& other) - Copy Constructor
*		Exception(Exception&& other) - Move Constructor
*		Exception& operator=(const Exception& other) - Copy Assignment Opeerator
*		Exception& operator=(Exception&& other) - Move Assignment Operator
* 
* Methods:
*		getMessage() 
*		setMessage(const char* msg) 
*		operator << (stream ostream&, const Exception& except)
**************************************************/

#pragma once
#include <ostream>
using std::ostream;

class Exception 
{
private:
	char* m_msg;
public:
	Exception();
	~Exception();
	Exception(const char* msg);
	Exception(const Exception& other);
	Exception(Exception&& other) noexcept;
	Exception& operator=(const Exception& other);
	Exception& operator=(Exception&& other) noexcept ;
	const char* getMessage();
	void setMessage(const char* msg);
	friend ostream& operator << (ostream& stream, const Exception& except);
};
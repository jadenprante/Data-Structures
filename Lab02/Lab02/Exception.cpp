/*************************************************
* Author:          Jaden Prante
* File Name:       Exception.cpp
* Date Created:    Apr 1st 2025
* Modifications:   Currenrly same date
**************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "Exception.h"
#include <cstring>        // This is for the strcpy and strlen usages 
#include <iostream>       // THis is for ostream usages

// Default Constructor
/*************************************************
*Purpose : Initialize the exception object without a message
*
*Precondition : NA
*
*Postcondistion : m_msg is set to nullptr
*
**************************************************/
Exception::Exception() : m_msg(nullptr) 
{}


// Destructor 
/*************************************************
*Purpose : Clean up dynamically allocated memory for the message
*
*Precondition : m_msg must point to valid memory or be nullptr
*
*Postcondistion : Memory allocated for m_msg is released
*
**************************************************/
Exception::~Exception() 
{
	delete[] m_msg;
}

// Constructor with parameters
/*************************************************
*Purpose : Initialize the exception object with a given message
*
*Precondition : msg is a valid C-string or nullptr
*
*Postcondistion : m_msg points to a copy of the provided message or is set to nullptr
*
**************************************************/
Exception::Exception(const char* msg) : m_msg(nullptr)
{
	if (msg) 
	{
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
	else 
	{
		m_msg = nullptr;
	}
}


// Copy Constructor
/*************************************************
*Purpose : Create a new exception object as a deep copy of another
*
*Precondition : The source exception must have valid state
*
*Postcondistion : The new object contains an independent copy of the source's message
*
**************************************************/
Exception::Exception(const Exception& other) : m_msg(nullptr)
{
	if (other.m_msg) 
	{
		m_msg = new char[strlen(other.m_msg) + 1];
		strcpy(m_msg, other.m_msg);
	}
	else 
	{
		m_msg = nullptr;
	}
}

// Move Constructor
/*************************************************
*Purpose : Transfer ownership of the message from another exception object
*
*Precondition : Source exception must be in a valid state
*
*Postcondistion : Current object takes ownership of the source's message, leaving the source nullified
*
**************************************************/
Exception::Exception(Exception&& other) noexcept : m_msg(other.m_msg)
{
	other.m_msg = nullptr; // This nullifies the source to prevent double deletion
}

// Copy Assignment Operator
/*************************************************
*Purpose : Assign the current object with a deep copy of another
*
*Precondition : Source exception must have valid state
*
*Postcondistion : Current object contains an independent copy of the source's message
*
**************************************************/
Exception& Exception::operator=(const Exception& other) 
{
	if (this != &other) 
	{
		delete[] m_msg; // Free existing memory
		if (other.m_msg) 
		{
			m_msg = new char[strlen(other.m_msg) + 1];
			strcpy(m_msg, other.m_msg);
		}
		else 
		{
			m_msg = nullptr;
		}
	}
	return *this;
}

// Move Assignment Operator 
/*************************************************
*Purpose : Transfer ownership of the message during assignment
*
*Precondition : The source exception must be in a valid state
*
*Postcondistion : The current object takes ownership of the source's message, leaving the source nullified
*
**************************************************/
Exception& Exception::operator=(Exception&& other) noexcept
{
	if (this != &other) 
	{
		delete[] m_msg;         // This frees existing memory
		m_msg = other.m_msg;    // This will transfer ownership 
		other.m_msg = nullptr;  // This nullifies the source to prevent double deletion
	}
	return *this;
}

// Getter message
/*************************************************
*Purpose : Retrieve the current exception message
*
*Precondition : NA
*
*Postcondistion : Returns the current message or nullptr
*
**************************************************/
const char* Exception::getMessage() 
{
	return m_msg;
}

// Setter message
/*************************************************
*Purpose : Update the exception message
*
*Precondition : msg is a valid C-string or nullptr
*
*Postcondistion : The current message is updated with a copy of msg
*
**************************************************/
void Exception::setMessage(const char* msg) 
{
    delete[] m_msg; // This frees existing memory
	if (msg) 
	{
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
	else 
	{
		m_msg = nullptr;
	}
}

// Overloader << operator
/*************************************************
*Purpose : Stream the exception message to an output stream
*
*Precondition : NA
*
*Postcondistion : The message is written to the output stream or "No message" is output if m_msg is nullptr
*
**************************************************/
ostream& operator<<(ostream& stream, const Exception& except) {
	if (except.m_msg) {
		stream << except.m_msg;
	}
	else {
		stream << "No message";
	}
	return stream;
}


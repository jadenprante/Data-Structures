/*************************************************
* Author:          Jaden Prante
* File Name:       Cell.cpp
* Date Created:    Apr 16th 2025
* Modifications:   Created same day
**************************************************/

#include "Cell.h"
#include <Windows.h>
#include "iostream"
using std::cout;

// Default Constructor
/*************************************************
*Purpose : Is Default Constructor
*
*Precondition : NA
*
*Postcondistion : NA
*
**************************************************/
Cell::Cell() :m_adjBomb(0), m_bomb(false), m_covered(true), m_marked(false)
{}

// Copy Constructor
/*************************************************
*Purpose : copies data
*
*Precondition : data members
*
*Postcondistion : data is copied
*
**************************************************/
Cell::Cell(const Cell& copy) :m_adjBomb(copy.m_adjBomb), m_bomb(copy.m_bomb), m_covered(copy.m_covered), m_marked(copy.m_marked)
{}

// Move Constructor
/*************************************************
*Purpose : moves data
*
*Precondition : data members
*
*Postcondistion : data is moved
*
**************************************************/
Cell::Cell(Cell&& rhs) noexcept :m_adjBomb(rhs.m_adjBomb), m_bomb(rhs.m_bomb), m_covered(rhs.m_covered), m_marked(rhs.m_marked)
{
	rhs.m_adjBomb = 0;
	rhs.m_bomb = false;
	rhs.m_covered = true;
	rhs.m_marked = false;
}

// Destructor
/*************************************************
*Purpose : deletes data
*
*Precondition : data members
*
*Postcondistion : data is deleted
*
**************************************************/
Cell::~Cell()
{
	m_adjBomb = 0;
	m_bomb = false;
	m_covered = true;
	m_marked = false;
}

// Copy Assignment Operator
/*************************************************
*Purpose : makes deep copy of data
*
*Precondition : data members
*
*Postcondistion : deep copies data and stores it on
*				  right hand side
*
**************************************************/
Cell& Cell::operator=(const Cell& rhs)
{
	if (this != &rhs)
	{
		m_adjBomb = rhs.m_adjBomb;
		m_bomb = rhs.m_bomb;
		m_covered = rhs.m_covered;
		m_marked = rhs.m_marked;
	}
	return *this;
}

// Move Assignement Operator
/*************************************************
*Purpose : makes deep copy and moves data
*
*Precondition : data members
*
*Postcondistion : deep copies data and moves it on
*				  right hand side
*
**************************************************/
Cell& Cell::operator=(Cell&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_adjBomb = rhs.m_adjBomb;
		rhs.m_adjBomb = 0;
		m_bomb = rhs.m_bomb;
		rhs.m_bomb = false;
		m_covered = rhs.m_covered;
		rhs.m_covered = true;
		m_marked = rhs.m_marked;
		rhs.m_marked = false;
	}
	return *this;
}

// Getters and Setters
/*************************************************
*Purpose : gets and sets bombs (includes adjacent
*		   bombs)
*
*Precondition : cell data
*
*Postcondistion : bomb data is got and set
*
**************************************************/
void Cell::SetBomb(bool hasBomb)
{
	m_bomb = hasBomb;
}

bool Cell::GetBomb() const
{
	return m_bomb;
}

int Cell::GetAdjBomb()
{
	return m_adjBomb;
}

// CheckCovered Function
/*************************************************
*Purpose : Checks covered state of bomb
*
*Precondition : cell data
*
*Postcondistion : cell could be covered
*
**************************************************/
bool Cell::CheckCovered()
{
	return m_covered;
}

// IsMakred Function
/*************************************************
*Purpose : Checks marked state of bomb
*
*Precondition : cell data
*
*Postcondistion : cell could be marked
*
**************************************************/
bool Cell::IsMarked()
{
	return m_marked;
}

// Increment Functiom
/*************************************************
*Purpose : increments bombs to board
*
*Precondition : cell data
*
*Postcondistion : bombs are incremented
*
**************************************************/
void Cell::IncrementAdjVal()
{
	m_adjBomb++;
}

// Uncover Function
/*************************************************
*Purpose : uncovers bomb
*
*Precondition : cell data
*
*Postcondistion : cell is uncovered
*
**************************************************/
void Cell::Uncover()
{
	m_covered = false;
}

// Mark Function
/*************************************************
*Purpose : marks bomb
*
*Precondition : cell data
*
*Postcondistion : cell is marked
*
**************************************************/
void Cell::Mark()
{
	m_marked = true;
}

// Unmark Function
/*************************************************
*Purpose : unmarks bomb
*
*Precondition : cell data
*
*Postcondistion : cell is unmarked
*
**************************************************/
void Cell::Unmark()
{
	m_marked = false;
}

// Display Function
/*************************************************
*Purpose : displays the cells
*
*Precondition : cell data
*
*Postcondistion : cells are displayed
*
**************************************************/
void Cell::Display() const
{
	HANDLE hStdout = 0;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m_marked == true)
	{
		cout << '[';
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << 'F';
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << ']';
	}
	else if (m_covered == true)
	{
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "[O]";
	}
	else if (m_covered == false && m_bomb == true)
	{
		cout << '[';
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << '*';
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << ']';
	}
	else if (m_covered == false && m_adjBomb > 0)
	{
		cout << '[';

		switch (m_adjBomb)
		{
		case 1:
			SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			break;
		case 2:
			SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case 3:
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		case 4:
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			break;
		case 5:
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case 6:
			SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case 7:
			SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case 8:
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		default:
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		cout << m_adjBomb;
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << ']';
	}
	else
	{
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "[ ]";
	}
}
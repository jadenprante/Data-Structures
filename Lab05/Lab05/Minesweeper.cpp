/*************************************************
* Author:          Jaden Prante
* File Name:       Minesweeper.cpp
* Date Created:    Apr 16th 2025
* Modifications:   Created same day
**************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "Minesweeper.h"

// Default Constructor
/*************************************************
*Purpose : Is Default Constructor
*
*Precondition : NA
*
*Postcondistion : NA
*
**************************************************/
Minesweeper::Minesweeper() : m_Board(nullptr)
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
Minesweeper::Minesweeper(const Minesweeper& copy) : m_Board(nullptr)
{
	*m_Board = *copy.m_Board;
}

// Move Constructor
/*************************************************
*Purpose : moves data
*
*Precondition : data members
*
*Postcondistion : data is moved
*
**************************************************/
Minesweeper::Minesweeper(Minesweeper&& rhs) noexcept : m_Board(nullptr)
{
	m_Board = rhs.m_Board;
	rhs.m_Board = nullptr;
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
Minesweeper::~Minesweeper()
{
	delete m_Board;
	m_Board = nullptr;
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
Minesweeper& Minesweeper::operator=(const Minesweeper& rhs)
{
	if (this != &rhs)
	{
		*m_Board = *rhs.m_Board;
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
Minesweeper& Minesweeper::operator=(Minesweeper&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_Board = rhs.m_Board;
		rhs.m_Board = nullptr;
	}
	return *this;
}

// NewGame Function 
/*************************************************
*Purpose : Makes a new game
*
*Precondition : game just ended
*
*Postcondistion : makes new game
*
**************************************************/
void Minesweeper::NewGame(char mode)
{
	int cr;
	int cc;
	int cb;
	if (m_Board != nullptr)
	{
		delete m_Board;
	}
	cin >> mode;
	switch (mode)
	{
	case 'b':
		m_Board = new Board(10, 10, 10);
		break;
	case 'i':
		m_Board = new Board(16, 16, 40);
		break;
	case 'e':
		m_Board = new Board(16, 30, 100);
		break;
	case 'c':
		cin >> cr;
		cin >> cc;
		cin >> cb;
		m_Board = new Board(cr, cc, cb);
		break;
	default:
		cout << "Not a Valid Option, Pick Again\n";
		break;
	}
}


// PlayGame Function
/*************************************************
*Purpose : starts a new game
*
*Precondition : difficulty of game
*
*Postcondistion : game is set and started
*
**************************************************/
void Minesweeper::PlayGame()
{
	char mode = '\0';
	char input[10];
	char* token;
	int coordX = 0;
	int coordY = 0;
	bool gameWon = false;
	bool gameLost = false;
	bool play = true;
	while (play == true)
	{
		if (m_Board == nullptr)
		{
			cout << "Please Select a Gamemode:\nBeginner = b\nIntermediate = i\nExpert = e\n";
			cin >> mode;
			NewGame(mode);
			m_Board->UpdateBoard();
		}
		while (gameWon != true && gameLost != true)
		{
			cin.ignore(cin.rdbuf()->in_avail());
			cin.getline(input, 10);
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			token = strtok(input, " (,)");
			switch (*token)
			{
			case 'm':
				token = strtok(nullptr, "(,)");
				coordX = atoi(token);
				token = strtok(nullptr, "(,)");
				coordY = atoi(token);
				system("cls");
				m_Board->MarkCell(coordX, coordY);
				break;
			case 'u':
				token = strtok(nullptr, "(,)");
				coordX = atoi(token);
				token = strtok(nullptr, "(,)");
				coordY = atoi(token);
				system("cls");
				m_Board->UnmarkCell(coordX, coordY);
				break;
			case 'n':
				cout << "Please Select a Gamemode:\nBeginner = b\nIntermediate = i\nExpert = e\n";
				cin >> mode;
				NewGame(mode);
				system("cls");
				m_Board->UpdateBoard();
				break;
			default:
				coordX = atoi(token);
				token = strtok(nullptr, " (,)");
				coordY = atoi(token);
				system("cls");
				if (coordX >= m_Board->GetRows() || coordY >= m_Board->GetColumns())
				{
					m_Board->UpdateBoard();
					cout << "Out Of Bonds of Game Board\n";
				}
				else
				{
					m_Board->Uncover(coordX, coordY);
				}
				break;
			}
			gameWon = GameWon();
			gameLost = GameLost();
		}
		if (gameWon == true)
		{
			cout << "Congradulations, You Won!";
		}
		else
		{
			cout << "Game Over... You Lost!";
		}
		cout << "\nPlay Again (y/n)";
		cin >> input;
		if (input[0] == 'n' || input[0] == 'N')
		{
			play = false;
		}
		else
		{
			delete m_Board;
			m_Board = nullptr;
			gameWon = false;
			gameLost = false;
		}
	}
}

// GameWon Function
/*************************************************
*Purpose : Win condition for game
*
*Precondition : game running
*
*Postcondistion : you won the game
*
**************************************************/
bool Minesweeper::GameWon()
{
	return m_Board->GetMarkedBombs() == m_Board->GetBombCount() && m_Board->CellsCovered() == m_Board->GetMarkedBombs();
}

// GameWon Function
/*************************************************
*Purpose : Lose condition for game
*
*Precondition : game running
*
*Postcondistion : you lost the game
*
**************************************************/
bool Minesweeper::GameLost()
{
	return m_Board->GetBmbTrig() == true;
}


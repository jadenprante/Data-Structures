/*************************************************
* Author:          Jaden Prante
* File Name:       Board.cpp
* Date Created:    Apr 16th 2025
* Modifications:   Created same day
**************************************************/

#include "Board.h"
#include <Windows.h>

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
Board::Board() :m_Board(Array2D<Cell>()), m_rows(0), m_columns(0), m_bombs(0), m_Marked(0), m_coveredCells(0), m_firstMove(true), m_Triggered(false)
{ }

// Constructor with Parameters
/*************************************************
*Purpose : Sets data members for board
*
*Precondition : data members
*
*Postcondistion : data members are set
*
**************************************************/
Board::Board(int rows, int columns, int bombs) :m_Board(rows, columns), m_rows(rows), m_columns(columns), m_bombs(bombs), m_Marked(0), m_coveredCells(rows* columns), m_firstMove(true), m_Triggered(false)
{ }

// Copy Constructor
/*************************************************
*Purpose : copies data
*
*Precondition : data members
*
*Postcondistion : data is copied
*
**************************************************/
Board::Board(const Board& copy) : m_Board(copy.m_Board), m_rows(copy.m_rows), m_columns(copy.m_columns), m_bombs(copy.m_bombs), m_Marked(copy.m_Marked), m_coveredCells(copy.m_coveredCells), m_firstMove(copy.m_firstMove), m_Triggered(copy.m_Triggered)
{ }

// Move Constructor
/*************************************************
*Purpose : moves data
*
*Precondition : data members
*
*Postcondistion : data is moved
*
**************************************************/
Board::Board(Board&& rhs) noexcept : m_Board(std::move(rhs.m_Board)), m_rows(rhs.m_rows), m_columns(rhs.m_columns), m_bombs(rhs.m_bombs), m_Marked(rhs.m_Marked), m_coveredCells(rhs.m_coveredCells), m_firstMove(rhs.m_firstMove), m_Triggered(rhs.m_Triggered)
{
	rhs.m_rows = 0;
	rhs.m_columns = 0;
	rhs.m_bombs = 0;
	rhs.m_Marked = 0;
	rhs.m_coveredCells = 0;
	rhs.m_firstMove = true;
	rhs.m_Triggered = false;
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
Board::~Board()
{
	m_rows = 0;
	m_columns = 0;
	m_bombs = 0;
	m_Marked = 0;
	m_coveredCells = 0;
	m_firstMove = true;
	m_Triggered = false;
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
Board& Board::operator=(const Board& rhs)
{
	if (this != &rhs)
	{
		m_Board = rhs.m_Board;
		m_rows = rhs.m_rows;
		m_columns = rhs.m_columns;
		m_bombs = rhs.m_bombs;
		m_Marked = rhs.m_Marked;
		m_coveredCells = rhs.m_coveredCells;
		m_firstMove = rhs.m_firstMove;
		m_Triggered = rhs.m_Triggered;
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
Board& Board::operator=(Board&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_Board = std::move(rhs.m_Board);
		m_rows = rhs.m_rows;
		rhs.m_rows = 0;
		m_columns = rhs.m_columns;
		rhs.m_columns = 0;
		m_bombs = rhs.m_bombs;
		rhs.m_bombs = 0;
		m_Marked = rhs.m_Marked;
		rhs.m_Marked = 0;
		m_coveredCells = rhs.m_coveredCells;
		rhs.m_coveredCells = 0;
		m_firstMove = rhs.m_firstMove;
		rhs.m_firstMove = true;
		m_Triggered = rhs.m_Triggered;
		rhs.m_Triggered = false;
	}
	return *this;
}

// Some Bomb Functions
/*************************************************
*Purpose : counts bombs, gets bombs marked and triggered
*		   checks and selects cells
*
*Precondition : cell data
*
*Postcondistion : got triggered and marked bombs, and
*				  cells are either marked selected or counted
*
**************************************************/
int Board::GetMarkedBombs() const
{
	return m_Marked;
}

int Board::GetBombCount() const
{
	return m_bombs;
}

int Board::CellsCovered() const
{
	return m_coveredCells;
}

bool Board::GetBmbTrig() const
{
	return m_Triggered;
}

Cell& Board::SelectCell(int row, int column)
{
	return m_Board[row][column];
}

// UpdateBoard Functions
/*************************************************
*Purpose : will updated bombs on board
*
*Precondition : cell and board data
*
*Postcondistion : board is updated
*
**************************************************/
void Board::UpdateBoard() const
{
	HANDLE hStdout = 0;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursor;
	cursor.X = 0;
	cursor.Y = 0;
	SetConsoleCursorPosition(hStdout, cursor);
	for (int j = 0; j < m_rows; j++)
	{
		for (int i = 0; i < m_columns; i++)
		{
			m_Board[j][i].Display();
		}
		cout << '\n';
	}
	if (m_firstMove == true)
	{
		cout << "Elements start at 0, so first cell is (0,0).\n";
	}
}

// PlaceBombs Functions
/*************************************************
*Purpose : will place bombs on board
*
*Precondition : cell and board data
*
*Postcondistion : bombs are placed on board
*
**************************************************/
void Board::PlaceBombs(int s_row, int s_col)
{
	int bombsPlaced = 0;

	srand((unsigned int)std::time(0));

	while (bombsPlaced != m_bombs)
	{
		int x = rand() % m_rows;
		int y = rand() % m_columns;
		if (y != s_col && x != s_row)
		{
			if (m_Board[x][y].GetBomb() != true)
			{
				m_Board[x][y].SetBomb(true);
				bombsPlaced++;
				if (y - 1 >= 0 && y - 1 < m_columns)
				{
					if (x - 1 >= 0)
					{
						m_Board[x - 1][y - 1].IncrementAdjVal();
					}
					if (x + 1 < m_rows)
					{
						m_Board[x + 1][y - 1].IncrementAdjVal();
					}
					m_Board[x][y - 1].IncrementAdjVal();
				}
				if (y + 1 < m_columns)
				{
					if (x - 1 >= 0)
					{
						m_Board[x - 1][y + 1].IncrementAdjVal();
					}
					if (x + 1 < m_rows)
					{
						m_Board[x + 1][y + 1].IncrementAdjVal();
					}
					m_Board[x][y + 1].IncrementAdjVal();
				}
				if (x - 1 >= 0)
				{
					m_Board[x - 1][y].IncrementAdjVal();
				}
				if (x + 1 < m_rows)
				{
					m_Board[x + 1][y].IncrementAdjVal();
				}
			}
		}
	}
}

// Uncover Function
/*************************************************
*Purpose : uncovers bomb on board
*
*Precondition : cell and board data
*
*Postcondistion : cell is uncovered on board
*
**************************************************/
void Board::Uncover(int x, int y)
{
	if (m_Board[y][x].CheckCovered() == true && m_Board[y][x].IsMarked() != true)
	{
		m_Board[y][x].Uncover();
		m_coveredCells--;
		if (m_firstMove == true)
		{
			PlaceBombs(x, y);
			m_firstMove = false;
		}
		if (m_Board[y][x].GetBomb() == true)
		{
			DisplayAllBombs();
			m_Triggered = true;
		}
		else if (m_Board[y][x].GetAdjBomb() == 0)
		{
			if (y - 1 >= 0)
			{
				if (x - 1 >= 0)
				{
					if (m_Board[y - 1][x - 1].CheckCovered() == true && m_Board[y - 1][x - 1].GetBomb() != true)
					{
						if (m_Board[y - 1][x - 1].GetAdjBomb() > 0)
						{
							m_Board[y - 1][x - 1].Uncover();
							m_coveredCells--;
						}
						else
						{
							Uncover(x - 1, y - 1);
						}
					}
				}
				if (x + 1 < m_rows)
				{
					if (m_Board[y - 1][x + 1].CheckCovered() == true && m_Board[y - 1][x + 1].GetBomb() != true)
					{
						if (m_Board[y - 1][x + 1].GetAdjBomb() > 0)
						{
							m_Board[y - 1][x + 1].Uncover();
							m_coveredCells--;
						}
						else
						{
							Uncover(x + 1, y - 1);
						}
					}
				}
				if (m_Board[y - 1][x].CheckCovered() == true && m_Board[y - 1][x].GetBomb() != true)
				{
					if (m_Board[y - 1][x].GetAdjBomb() > 0)
					{
						m_Board[y - 1][x].Uncover();
						m_coveredCells--;
					}
					else
					{
						Uncover(x, y - 1);
					}
				}
			}
			if (y + 1 < m_columns)
			{
				if (x - 1 >= 0)
				{
					if (m_Board[y + 1][x - 1].CheckCovered() == true && m_Board[y + 1][x - 1].GetBomb() != true)
					{
						if (m_Board[y + 1][x - 1].GetAdjBomb() > 0)
						{
							m_Board[y + 1][x - 1].Uncover();
							m_coveredCells--;
						}
						else
						{
							Uncover(x - 1, y + 1);
						}
					}
				}
				if (x + 1 < m_rows)
				{
					if (m_Board[y + 1][x + 1].CheckCovered() == true && m_Board[y + 1][x + 1].GetBomb() != true)
					{
						if (m_Board[y + 1][x + 1].GetAdjBomb() > 0)
						{
							m_Board[y + 1][x + 1].Uncover();
							m_coveredCells--;
						}
						else
						{
							Uncover(x + 1, y + 1);
						}
					}
				}
				if (m_Board[y + 1][x].CheckCovered() == true && m_Board[y + 1][x].GetBomb() != true)
				{
					if (m_Board[y + 1][x].GetAdjBomb() > 0)
					{
						m_Board[y + 1][x].Uncover();
						m_coveredCells--;
					}
					else
					{
						Uncover(x, y + 1);
					}
				}
			}
			if (x - 1 >= 0)
			{
				if (m_Board[y][x - 1].CheckCovered() == true && m_Board[y][x - 1].GetBomb() != true)
				{
					if (m_Board[y][x - 1].GetAdjBomb() > 0)
					{
						m_Board[y][x - 1].Uncover();
						m_coveredCells--;
					}
					else
					{
						Uncover(x - 1, y);
					}
				}
			}
			if (x + 1 < m_rows)
			{
				if (m_Board[y][x + 1].CheckCovered() == true && m_Board[y][x + 1].GetBomb() != true)
				{
					if (m_Board[y][x + 1].GetAdjBomb() > 0)
					{
						m_Board[y][x + 1].Uncover();
						m_coveredCells--;
					}
					else
					{
						Uncover(x + 1, y);
					}
				}
			}
		}
	}
	UpdateBoard();
}

// Display Function
/*************************************************
*Purpose : displays the cells on board
*
*Precondition : cell data
*
*Postcondistion : cells are displayed
*
**************************************************/
void Board::DisplayAllBombs() const
{
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_columns; j++)
		{	
			if (m_Board[i][j].GetBomb() == true)
			{
				m_Board[i][j].Uncover();
			}
		}
	}
	UpdateBoard();
}

// Cell Makring Functions
/*************************************************
*Purpose : Marks or Unmakrs a cell
*
*Precondition : cell data
*
*Postcondistion : cell is now marked or unmakred
*
**************************************************/
void Board::MarkCell(int x, int y)
{
	if (x >= 0 && x < m_columns && y >= 0 && y < m_rows)
	{
		if (m_Board[y][x].IsMarked() != true && m_Board[y][x].CheckCovered() == true)
		{
			m_Board[y][x].Mark();
			if (m_Board[y][x].GetBomb() == true)
			{
				m_Marked++;
			}
		}
	}
	UpdateBoard();
}

void Board::UnmarkCell(int x, int y)
{
	if (x >= 0 && x < m_columns && y >= 0 && y < m_rows)
	{
		if (m_Board[y][x].IsMarked() == true && m_Board[y][x].CheckCovered() == true)
		{
			m_Board[y][x].Unmark();
			if (m_Board[y][x].GetBomb() == true)
			{
				m_Marked--;
			}
		}
	}
	UpdateBoard();
}

// Getter Functions
/*************************************************
*Purpose : gets rows and columns
*
*Precondition : data members
*
*Postcondistion : now have rows and columns
*
**************************************************/
int Board::GetRows() const
{
	return m_rows;
}

int Board::GetColumns() const
{
	return m_columns;
}

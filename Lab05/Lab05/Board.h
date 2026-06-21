/*************************************************
* Author:          Jaden Prante
* File Name:       Board.h
* Date Created:    Apr 16th 2025
* Modifications:   Currenrly same date
*
* Class: Board
*
* Purpose: This class deals with the board, containing all cells
*
* Manager Functions:
*		Board() - Default Constructor
*       Board(int rows, int cols, int mines) - Constructor with parameters
*		Board(const Board& copy) - Copy Constructor
*		Board(Board&& rhs) noexcept - Move Constructor
*		Board& operator=(const Board& rhs) - Copy Assignment Operator
*		Board& operator=(Board&& rhs) noexcept - Move Assignment Operator
*		~Board() - Destructor
*
* Methods:
*		int GetMarkedBombs() const
*		int GetBombCount() const
*		int CellsCovered() const
*		bool GetBmbTrig() const
*		Cell& SelectCell(int row, int column)
*		void UpdateBoard() const
*		void PlaceBombs(int s_row, int s_col)
*		void Uncover(int x, int y)
*		void DisplayAllBombs() const
*		void MarkCell(int x, int y)
*		void UnmarkCell(int x, int y)
*		int GetRows() const
*		int GetColumns() const
* 
**************************************************/

#pragma once
#include "Array2D.h"
#include "Cell.h"

class Board
{
public:
	Board();
	Board(int rows, int columns, int bombs);
	Board(const Board& copy);
	Board(Board&& rhs) noexcept;
	Board& operator=(const Board& rhs);
	Board& operator=(Board&& rhs) noexcept;
	~Board();
	int GetMarkedBombs() const;
	int GetBombCount() const;
	int CellsCovered() const;
	bool GetBmbTrig() const;
	Cell& SelectCell(int row, int column);
	void UpdateBoard() const;
	void PlaceBombs(int s_row, int s_col);
	void Uncover(int x, int y);
	void DisplayAllBombs() const;
	void MarkCell(int x, int y);
	void UnmarkCell(int x, int y);
	int GetRows() const;
	int GetColumns() const;
private:
	Array2D<Cell> m_Board;
	int m_rows;
	int m_columns;
	int m_bombs;
	int m_Marked;
	int m_coveredCells;
	bool m_firstMove;
	bool m_Triggered;
};
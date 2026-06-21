/*************************************************
* Author:          Jaden Prante
* File Name:       Cell.h
* Date Created:    Apr 16th 2025
* Modifications:   Currenrly same date
*
* Class: Cell
*
* Purpose: This class deals with cells, wether or not they're mines
*
* Manager Functions:
*		Cell() - Default Consturctor
*		Cell(const Cell& copy) - Copy Constructor
*		Cell(Cell&& rhs) noexcept - Move Constructor
*		Cell& operator=(const Cell& rhs) - Copy Assignment Operator
*		Cell& operator=(Cell&& rhs) noexcept - Move Assignment Operator
*		~Cell() - Destructor
*
* Methods:
*		void SetBomb(bool hasBomb)
*		bool GetBomb() const
*		int GetAdjBomb()
*		bool CheckCovered()
*		bool IsMarked()
*		void IncrementAdjVal()
*		void Uncover()
*		void Mark()
*		void Unmark()
*		void Display() const
*
**************************************************/

#pragma once

class Cell
{
public:
	Cell();
	Cell(const Cell& copy);
	Cell(Cell&& rhs) noexcept;
	Cell& operator=(const Cell& rhs);
	Cell& operator=(Cell&& rhs) noexcept;
	~Cell();
	void SetBomb(bool hasBomb);
	bool GetBomb() const;
	int GetAdjBomb();
	bool CheckCovered();
	bool IsMarked();
	void IncrementAdjVal();
	void Uncover();
	void Mark();
	void Unmark();
	void Display() const;
private:
	int m_adjBomb;
	bool m_bomb;
	bool m_covered;
	bool m_marked;
};

/*************************************************
* Author:          Jaden Prante
* File Name:       Minesweeper.h
* Date Created:    Apr 16th 2025
* Modifications:   Currenrly same date
*
* Class: Minesweeper
*
* Purpose: This class deals with minesweeper game mechanics
*
* Manager Functions:
*		Minesweeper() - Default Constructor
*		Minesweeper(const Minesweeper& copy) - Copy Constructor
*		Minesweeper(Minesweeper&& rhs) noexcept - Move Constructor
*		Minesweeper& operator=(const Minesweeper& rhs) - Copy Assignment Operator
*		Minesweeper& operator=(Minesweeper&& rhs) noexcept - Move Assignment Operator
*		~Minesweeper() - Destructor
*
* Methods:
*		void NewGame(char mode)
*		void PlayGame()
*		bool GameWon()
*		bool GameLost()
* 
**************************************************/

#pragma once
#include <stdlib.h>
#include <iostream>
#include "Board.h"
using std::cout;
using std::cin;

class Minesweeper
{
public:
	Minesweeper();
	Minesweeper(const Minesweeper& copy);
	Minesweeper(Minesweeper&& rhs) noexcept;
	~Minesweeper();
	Minesweeper& operator=(const Minesweeper& rhs);
	Minesweeper& operator=(Minesweeper&& rhs) noexcept;
	void NewGame(char mode);
	void PlayGame();
	bool GameWon();
	bool GameLost();
private:
	Board* m_Board;
};
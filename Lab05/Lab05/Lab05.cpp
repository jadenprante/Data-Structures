/*************************************************************
* Author:			Jaden Prante
* Filename:			Lab03.cpp
* Date Created:		Apr 16th 2025
* Modifications:	NA
*
* 
* Lab/Assignment: Lab 5 - Minesweeper
*
* Overview:
* This lab allows you to play minesweeper
* reveal as much of the area without hitting mines to win
*
* Input:
* input either a mark, flag, or uncover, with array coordinatees
* to reveal areas on the board
*
* Output:
* The output will be, a bomb or a blank, or a number telling how
* many bombs are adjacent from the point
* can get either a winning or losing screen
**************************************************************/

#include <crtdbg.h>
#include "Cell.h"
#include <windows.h>
#include <iostream>
#include "Board.h"
#include "Minesweeper.h"

using namespace std;
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Minesweeper minesweeper;
	minesweeper.PlayGame();
	return 0;
}


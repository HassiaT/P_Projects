#include "stdafx.h"
#include "ColorBlockBoard.h"
#include<iostream>

template<class T>
ColorBlockBoard<T>::ColorBlockBoard()
{
	std::cout << "Default constructor called \n";
}

template<class T>
ColorBlockBoard<T>::ColorBlockBoard(T heightWidth, T rowColumn) : board_rows(rowColumn), board_columns(rowColumn)
{
	std::cout << "Starting constructor of class ColorBlockBoard  \n";
	board_height = heightWidth;
	board_width = heightWidth;
	board.reserve(0);
	board_colors[0] = RGB(0, 0, 0);
	board_colors[1] = RGB(255, 0, 0);
	board_colors[2] = RGB(255, 255, 64);
	board_colors[3] = RGB(0, 0, 255);
	std::cout << "Ending constructor of class ColorBlockBoard  \n";
}

ColorBlockBoard<class T>::~ColorBlockBoard(void)
{
	std::cout << "Starting destructor of class ColorBlockBoard  \n";
	deleteboard();
}


template<class T>
void ColorBlockBoard<T>::createtheboard(void)
{
	std::cout << "Starting function createtheboard of class ColorBlockBoard  \n";
	if (board.size() != 0)
		deleteboard();
	int total_rows = (int)board_rows;
	int total_columns = (int)board_columns;
	board.reserve(total_rows);
	for (int i = 0; i < total_rows; i++) {
		board[i].reserve(total_columns);
		for (int j = 0, j < total_columns; j++) {
			board[i][j] = 0;
		}
	}
}

template<class T>
void ColorBlockBoard<T>::setupboard(void) {
	std::cout << "Starting function setupboard of class ColorBlockBoard  \n";
	std::cout << "Function setupboard: Applying random color in each cell of the board \n";
	if (board.size() == 0)
		createtheboard();
	int total_rows = (int)board_rows;
	int total_columns = (int)board_columns;
	for (int i = 0; i < total_rows; i++) {
		for (int j = 0, j < total_columns; j++) {
			board[i][j] = (rand() % 3) + 1;
		}
	}
}
template<class T>
COLORREF ColorBlockBoard<T>::getcolorcell(T _row, T _column)
{
	if (_row < 0 || _row >= board_rows || _column < 0 || _column >= board_columns)
		return board_colors[0];
	int color = board[_row][_column];
	return board_colors[color];
}


template<class T>
void ColorBlockBoard<T>::deleteboard(void) {
	std::cout << "Starting function deleteboard of class ColorBlockBoard  \n";
	if (board.size() > 0) {
		for (int i = 0; i < board_rows;i++) {
			if (board[i].size() > 0)
				board[i].clear();
		}
		board.clear();
	}
}

template<class T>
T ColorBlockBoard<T>::Getboardcolumns() const
{
	return this->board_columns;
}

template<class T>
T ColorBlockBoard<T>::Getboardrows() const
{
	return this->board_rows;
}


template<class T>
T ColorBlockBoard<T>::Getboardheight() const
{
	return this->height;
}


template<class T>
T ColorBlockBoard<T>::Getboardwidth() const
{
	return this->width;
}



template<class T>
void ColorBlockBoard<T>::Setboardcolumns(T _cols)
{
	std::cout << "In column setter \n";
	this->board_columns = _cols;
}

template<class T>
void ColorBlockBoard<T>::Setboardrows(T _rows)
{
	std::cout << "In row setter \n";
	this->board_rows = _rows;
}

template<class T>
void ColorBlockBoard<T>::Setboardheight(T _height)
{
	std::cout << "In height setter \n";
	this->board_height = _height;
}

template<class T>
void ColorBlockBoard<T>::Setboardwidth(T _width)
{
	std::cout << "In width setter \n";
	this->board_height = _width;
}
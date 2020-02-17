#include "stdafx.h"
#include "ColorBlockBoard.h"
#include<iostream>

constexpr auto DIM1 = 15;
constexpr auto DIM2 = 35;
typedef std::vector<int> VBCOLUMS;


ColorBlockBoard::ColorBlockBoard(void) :board_rows(DIM1), board_columns(DIM1), board_height(DIM2), board_width(DIM2)
{
	std::cout << "Default constructor called \n";
	VBCOLUMS vbcolumns(board_columns);
	for (int i = 0; i < board_rows; i++) {
		board.push_back(vbcolumns);
	}
	board_height = DIM2;
	board_width = DIM2;
	board_colors[0] = RGB(224, 224, 224);
	board_colors[1] = RGB(178, 255, 102);
	board_colors[2] = RGB(204, 0, 0);
	board_colors[3] = RGB(0, 0, 255);
	std::cout << "Ending default constructor of class ColorBlockBoard  \n";
}



ColorBlockBoard::ColorBlockBoard(int heightWidth, int rowColumn) : board_rows(rowColumn), board_columns(rowColumn)
{
	std::cout << "Starting constructor of typename ColorBlockBoard  \n";
	VBCOLUMS vbcolumns(board_columns);
	for (int i = 0; i < board_rows; i++) {
		board.push_back(vbcolumns);
	}
	board_height = heightWidth;
	board_width = heightWidth;
	board_colors[0] = RGB(0, 0, 0);
	board_colors[1] = RGB(255, 0, 0);
	board_colors[2] = RGB(255, 255, 64);
	board_colors[3] = RGB(0, 0, 255);
	std::cout << "Ending constructor of typename ColorBlockBoard  \n";
}

ColorBlockBoard::~ColorBlockBoard(void)
{
	std::cout << "Starting destructor of typename ColorBlockBoard  \n";
	deleteboard();
}


void ColorBlockBoard::createtheboard(void)
{
	std::cout << "Starting function createtheboard of typename ColorBlockBoard  \n";
	if (board.size() != 0)
		deleteboard();
	board.reserve(board_rows);
	for (int i = 0; i < board_rows; i++) {
		board[i].reserve(board_columns);
		for (int j = 0; j < board_columns; j++) {
			board[i][j] = 0;
		}
	}
}


void ColorBlockBoard::setuptheboard(void) {
	std::cout << "Starting function setuptheboard of typename ColorBlockBoard  \n";
	std::cout << "Function setuptheboard: Applying random color in each cell of the board \n";
	if (board.size() == 0)
		createtheboard();

	for (int i = 0; i < board_rows; i++) {
		for (int j = 0; j < board_columns; j++) {
			board[i][j] = (rand() % 3) + 1;
		}
	}
}



COLORREF ColorBlockBoard::getcolorcell(int _row, int _column)
{
	if (_row < 0 || _row >= board_rows || _column < 0 || _column >= board_columns)
		return board_colors[0];
	int color = board[_row][_column];
	return board_colors[color];
}



void ColorBlockBoard::deleteboard(void) {
	std::cout << "Starting function deleteboard of typename ColorBlockBoard  \n";
	if (board.size() > 0) {
		for (int i = 0; i < board_rows; i++) {
			if (board[i].size() > 0)
				board[i].clear();
		}
		board.clear();
	}
}


int ColorBlockBoard::Getboardcolumns() const
{
	return this->board_columns;
}


int ColorBlockBoard::Getboardrows() const
{
	return this->board_rows;
}

int ColorBlockBoard::Getboardheight() const
{
	return this->board_height;
}


int ColorBlockBoard::Getboardwidth() const
{
	return this->board_width;
}



void ColorBlockBoard::Setboardcolumns(int _cols)
{
	std::cout << "In column setter \n";
	this->board_columns = _cols;
}


void ColorBlockBoard::Setboardrows(int _rows)
{
	std::cout << "In row setter \n";
	this->board_rows = _rows;
}



void ColorBlockBoard::Setboardheight(int _height)
{
	std::cout << "In height setter \n";
	this->board_height = _height;
}


void ColorBlockBoard::Setboardwidth(int _width)
{
	std::cout << "In width setter \n";
	this->board_height = _width;
}
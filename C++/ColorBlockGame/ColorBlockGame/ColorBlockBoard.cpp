#include "stdafx.h"
#include "ColorBlockBoard.h"
#include<iostream>

constexpr auto DIM1 = 15;
constexpr auto DIM2 = 35;
typedef std::vector<int> VBCOLUMS;

COLORREF ColorBlockBoard::board_colors[MAX_NUMBER_COLORS];



ColorBlockBoard::ColorBlockBoard(void) : NB_colors(3), NB_remaining(0), board_rows(DIM1), board_columns(DIM1), board_height(DIM2), board_width(DIM2)
{
	std::cout << "Default constructor called \n";
	VBCOLUMS vbcolumns(board_columns);
	for (int i = 0; i < board_rows; i++) {
		board.push_back(vbcolumns);
	}
	board_height = DIM2;
	board_width = DIM2;
	board_colors[0] = RGB(0, 0, 0);
	board_colors[1] = RGB(178, 255, 102);
	board_colors[2] = RGB(204, 0, 0);
	board_colors[3] = RGB(0, 0, 255);
	board_colors[4] = RGB(0, 255, 255);
	board_colors[5] = RGB(255, 0, 108);
	board_colors[6] = RGB(0, 64, 0);
	board_colors[7] = RGB(255, 255, 64);

	std::cout << "Ending default constructor of class ColorBlockBoard  \n";
}



ColorBlockBoard::ColorBlockBoard(int heightWidth, int rowColumn) :NB_colors(3), NB_remaining(0), board_rows(rowColumn), board_columns(rowColumn)
{
	std::cout << "Starting constructor of typename ColorBlockBoard  \n";
	VBCOLUMS vbcolumns(board_columns);
	for (int i = 0; i < board_rows; i++) {
		board.push_back(vbcolumns);
	}
	board_height = heightWidth;
	board_width = heightWidth;
	board_colors[0] = RGB(0, 0, 0);
	board_colors[1] = RGB(178, 255, 102);
	board_colors[2] = RGB(204, 0, 0);
	board_colors[3] = RGB(0, 0, 255);
	board_colors[4] = RGB(0, 255, 255);
	board_colors[5] = RGB(255, 0, 108);
	board_colors[6] = RGB(0, 64, 0);
	board_colors[7] = RGB(255, 255, 64);
	std::cout << "Ending constructor of class ColorBlockBoard  \n";
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

int ColorBlockBoard::deleteNeighboringBlocks(int r, int c, int color, DIRECTION D)
{
	if (r < 0 || r >= board_rows || c < 0 || c >= board_columns)
		return  0;
	if (board[r][c] != color) {
		return 0;
	}
	int nCount = 1;
	board[r][c] = 0;
	if (D != DIR_UP)
		nCount += deleteNeighboringBlocks(r - 1, c, color, DIR_DOWN);
	if (D != DIR_DOWN)
		nCount += deleteNeighboringBlocks(r + 1, c, color, DIR_UP);
	if (D != DIR_LEFT)
		nCount += deleteNeighboringBlocks(r, c - 1, color, DIR_RIGHT);
	if (D != DIR_RIGHT)
		nCount += deleteNeighboringBlocks(r, c + 1, color, DIR_LEFT);
	return nCount;
}

void ColorBlockBoard::reduceBoard(void)
{
	for (int c = 0; c < board_columns; c++) {
		int nextBlankRow = board_rows - 1;
		int nextNonBlankRow = nextBlankRow;
		while (nextNonBlankRow >= 0 && nextBlankRow >= 0) {
			while (nextBlankRow >= 0 && board[nextBlankRow][c] != 0) {
				nextBlankRow--;
			}
			if (nextNonBlankRow >= 0) {
				nextNonBlankRow = nextBlankRow - 1;
				while (nextNonBlankRow >= 0 && board[nextNonBlankRow][c] == 0) {
					nextNonBlankRow--;
				}
				if (nextNonBlankRow >= 0) {
					board[nextBlankRow][c] = board[nextNonBlankRow][c];
					board[nextNonBlankRow][c] = 0;
				}
			}
		}
	}

	int nextBlankCol = 0;
	int nextNonBlankCol = nextBlankCol;
	while (nextBlankCol < board_columns && nextNonBlankCol < board_columns) {
		while (nextBlankCol < board_columns && board[board_rows - 1][nextBlankCol] != 0) {
			nextBlankCol++;
		}
		if (nextBlankCol < board_columns) {
			nextNonBlankCol = nextBlankCol + 1;
			while (nextNonBlankCol < board_columns && board[board_rows - 1][nextNonBlankCol] == 0) {
				nextNonBlankCol++;
			}
			if (nextNonBlankCol < board_columns) {
				for (int r = 0; r < board_rows; r++) {
					board[r][nextBlankCol] = board[r][nextNonBlankCol];
					board[r][nextNonBlankCol] = 0;
				}
			}
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
			board[i][j] = (rand() % NB_colors) + 1;
		}
	}
	NB_remaining = board_columns * board_rows;
}



COLORREF ColorBlockBoard::getcolorcell(int _row, int _column)
{
	if (_row < 0 || _row >= board_rows || _column < 0 || _column >= board_columns)
		return board_colors[0];
	int color = board[_row][_column];
	return board_colors[color];
}

bool ColorBlockBoard::isgameOver() const
{
	for (int col = 0; col < board_columns; col++) {
		for (int row = board_rows - 1; row >= 0; row--) {
			int current_color = board[row][col];
			if (current_color == 0)
				break;
			else {
				if (row - 1 >= 0 && board[row - 1][col] == current_color)
					return false;
				else if (col + 1 < board_columns && board[row][col + 1] == current_color)
					return false;
			}
		}
	}
	return true; // Game is truly over as there are no two adjacent cells with same color
}

int ColorBlockBoard::deleteRangeofBlocks(int r, int c)
{

	if (r < 0 || r >= board_rows || c < 0 || c >= board_columns)
		return  -1;
	int current_color = board[r][c];
	if (current_color == 0)
		return -1;
	int nCount = -1;
	if ((r - 1 >= 0 && board[r - 1][c] == current_color) ||
		(r + 1 < board_rows && board[r + 1][c] == current_color) ||
		(c - 1 >= 0 && board[r][c - 1] == current_color) ||
		(c + 1 < board_columns && board[r][c - 1] == current_color)) {
		board[r][c] = 0;
		nCount = 1;
		nCount += deleteNeighboringBlocks(r - 1, c, current_color, DIR_DOWN);
		nCount += deleteNeighboringBlocks(r + 1, c, current_color, DIR_UP);
		nCount += deleteNeighboringBlocks(r, c + 1, current_color, DIR_LEFT);
		nCount += deleteNeighboringBlocks(r, c - 1, current_color, DIR_RIGHT);
		reduceBoard();
		NB_remaining -= nCount;
		//this is the number of deleted cells on the board game:
		return nCount;
	}
}

int ColorBlockBoard::getRemainingBlocks()
{
	return NB_remaining;
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

int ColorBlockBoard::GetNBColors() const
{
	return this->NB_colors;
}

void ColorBlockBoard::SetNBColors(int nbcolors)
{
	this->NB_colors = (nbcolors >= 3 && nbcolors <= 7) ? nbcolors : this->NB_colors;
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
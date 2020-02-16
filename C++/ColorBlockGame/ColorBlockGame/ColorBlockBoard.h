#pragma once
#include<vector>
#include<array>

#define NB_COLORS 4

template <class T> using VBOARD= std::vector<std::vector<T>> VBOARD;


template <class T>
class ColorBlockBoard
{
private:
	T board_columns;
	T board_rows;
	T board_height;
	T board_width;
	VBOARD board;
	void createtheboard(void);
	COLORREF board_colors[NB_COLORS];

public:
	ColorBlockBoard();
	ColorBlockBoard(T, T);
	~ColorBlockBoard();
	T Getboardcolumns() const;
	T Getboardrows() const;
	T Getboardheight() const;
	T Getboardwidth() const;	
	void Setboardcolumns(T);
	void Setboardrows(T);
	void Setboardheight(T);
	void Setboardwidth(T);
	void deleteboard();
	void setupboard();
	COLORREF getcolorcell(T, T);
};


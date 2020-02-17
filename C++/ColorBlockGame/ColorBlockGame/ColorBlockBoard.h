#pragma once
#include<vector>
#include<array>

#define NB_COLORS 4

typedef std::vector<std::vector<int>> VBOARDTYPE;


//intemplainte <intypename int>
class ColorBlockBoard
{
private:
	int board_columns;
	int board_rows;
	int board_height;
	int board_width;
	VBOARDTYPE board;
	void createtheboard(void);
	COLORREF board_colors[NB_COLORS];



public:
	ColorBlockBoard();
	ColorBlockBoard(int, int);
	~ColorBlockBoard();
	int Getboardcolumns() const;
	int Getboardrows() const;
	int Getboardheight() const;
	int Getboardwidth() const;	
	void Setboardcolumns(int);
	void Setboardrows(int);
	void Setboardheight(int);
	void Setboardwidth(int);
	void deleteboard();
	void setuptheboard();
	COLORREF getcolorcell(int, int);
};


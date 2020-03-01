#pragma once
#include<vector>
#include<array>

#define NB_COLORS 4
#define MAX_NUMBER_COLORS 8
#define MIN_HEIGHT 3
#define MIN_WIDTH 5

typedef std::vector<std::vector<int>> VBOARDTYPE;

class ColorBlockBoard
{

private:
	int NB_remaining;
	int NB_colors;
	int board_columns;
	int board_rows;
	int board_height;
	int board_width;
	VBOARDTYPE board;
	
	/* 0 is color for background ---> BLACK ; 1 to 7 are cell colors */
	static COLORREF board_colors[MAX_NUMBER_COLORS];
	
	enum DIRECTION {
		DIR_UP,
		DIR_DOWN,
		DIR_LEFT,
		DIR_RIGHT,
	};

	/* PRIVATE METHODS: */
	void createtheboard(void);
	int deleteNeighboringBlocks(int r, int c, int color, DIRECTION D);
	void reduceBoard(void);

public:
	
	ColorBlockBoard();
	ColorBlockBoard(int, int);
	ColorBlockBoard(const ColorBlockBoard&);
	~ColorBlockBoard();
	int Getboardcolumns() const;
	int Getboardrows() const;
	int Getboardheight() const;
	int Getboardwidth() const;
	int GetNBColors() const;
	void SetNBColors(int);
	void Setboardcolumns(int);
	void Setboardrows(int);
	void Setboardheight(int);
	void Setboardwidth(int);
	void deleteboard();
	void setuptheboard();
	COLORREF getcolorcell(int, int);
	bool isgameOver() const;
	int deleteRangeofBlocks(int, int);
	int getRemainingBlocks();
};


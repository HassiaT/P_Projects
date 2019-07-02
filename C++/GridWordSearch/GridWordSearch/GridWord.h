#pragma once
#include<map>
#include<vector>
#include<list>


using namespace std;
typedef pair<int, int> coordonnees;
typedef pair<string, bool> checkExistence;


enum class Direction { LEFT, RIGHT, DOWN, UP, RIGHTDIAGUP, LEFTDIAGUP, RIGHTDIAGDOWN, LEFTDIAGDOWN };


class GridWord
{

private:
	int rows;
	int cols;
	map<int, vector<char>> grid;
	map<char, list<coordonnees>> charBypositions;
	vector<checkExistence> wordsToSearch;



public:
	GridWord();
	~GridWord();
	int getRows();
	int getCols();
	void setRows(int);
	void setCols(int);
	void initializeGrid(string, string, string);
	map<int, vector<char>> getGrid();
	map<char, list<coordonnees>> getPositions();
	void setGrid(map<int, vector<char>>);
	void setPositions(map<char, list<coordonnees>>);
	bool isNeighborValid(int, int);
	bool searchingAWord(int, int, string, string, Direction, string);
	coordonnees getDirectionalNeighbor(int, int, Direction);
	void search(string&, string);
	bool findingAWord(int, int, string, string, string);
	void searchAllWords(string fileOut);
	bool isTheWordFound(string);



};


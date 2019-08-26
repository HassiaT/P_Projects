#include "pch.h"
#include "GridWord.h"
#include <iostream>
#include <iterator>
#include<fstream>
#include<exception>
#include<algorithm>
#include<string>

using namespace std;

GridWord::GridWord()
{
	cout << "Default constructor GridWord\n";
	rows = 0;
	cols = 0;
}


GridWord::~GridWord()
{
	cout << "Destructor GridWord\n";
	rows = 0;
	cols = 0;
}

int GridWord::getRows()
{
	return rows;
}

int GridWord::getCols()
{
	return cols;
}

void GridWord::setRows(int ro_)
{
	rows = ro_;
}

void GridWord::setCols(int co_)
{
	cols = co_;
}


map<int, vector<char>> GridWord::getGrid()
{
	return grid;
}

map<char, list<coordonnees>> GridWord::getPositions()
{
	return charBypositions;
}

void GridWord::setGrid(map<int, vector<char>>g_)
{
	grid = g_;
}

void GridWord::setPositions(map<char, list<coordonnees>> coord_)
{
	charBypositions = coord_;
}

void GridWord::initializeGrid(string filename, string words, string fileOut)
{
	ifstream fin(filename);
	ifstream fin_words(words);

	/* storing the list of words to search in the grid */
	try
	{
		string line = "first";
		while (!fin_words.eof())
		{
			fin_words >> line;
			checkExistence p(line, false);
			wordsToSearch.push_back(p);
		}
		fin_words.close();
	}
	catch (ios::failure& f)
	{
		ofstream fout(fileOut);
		fout << " Exception found with the input file: " << words << " ; " << f.what() << "\n";
		fout.close();
	}

	/* initializing grid with characters */
	string l_previous = "";
	try {
		string line;
		fin >> line;
		int s_ = line.size();
		if (s_ == 0) throw invalid_argument("Input file does not contain valid grid");
		this->cols = s_;
		do
		{
			l_previous = line;
			this->rows++;
			vector<char> characters;
			int column_position = 0;
			for (char c : line)
			{
				characters.push_back(c);
				coordonnees p(this->rows, column_position);
				charBypositions[c].push_back(p);
				column_position++;
			}
			int key = this->rows;
			grid[key] = characters;
			fin >> line;
		} while (line != l_previous);
	}
	catch (ios::failure& f)
	{
		ofstream fout(fileOut);
		fout << " Exception found with the input file" << f.what() << "\n";
		fout.close();
	}
	fin.close();
}


bool GridWord::isNeighborValid(int i, int j)
{
	return ((i >= 1 && i < rows + 1) && (j >= 0 && j < cols));
}

coordonnees GridWord::getDirectionalNeighbor(int i, int j, Direction d)
{
	coordonnees neighbor(-1, -1);
	switch (d)
	{
	case(Direction::LEFT):
		neighbor.first = i;
		neighbor.second = j - 1;
		break;

	case(Direction::RIGHT):
		neighbor.first = i;
		neighbor.second = j + 1;
		break;


	case(Direction::UP):
		neighbor.first = i - 1;
		neighbor.second = j;
		break;

	case(Direction::DOWN):
		neighbor.first = i + 1;
		neighbor.second = j;
		break;

	case(Direction::RIGHTDIAGUP):
		neighbor.first = i - 1;
		neighbor.second = j + 1;
		break;


	case(Direction::RIGHTDIAGDOWN):
		neighbor.first = i + 1;
		neighbor.second = j + 1;
		break;


	case(Direction::LEFTDIAGDOWN):
		neighbor.first = i + 1;
		neighbor.second = j - 1;
		break;

	case(Direction::LEFTDIAGUP):
		neighbor.first = i - 1;
		neighbor.second = j - 1;
		break;
	}
	return neighbor;
}



bool GridWord::searchingAWord(int i, int j, string current, string the_word, Direction d, string fileOut)
{
	vector<char> characters;
	checkExistence e_New(the_word, true);
	coordonnees neighbor = getDirectionalNeighbor(i, j, d);
	int row_pos = neighbor.first;
	int col_pos = neighbor.second;
	ofstream fout(fileOut, ios::app);


	// the word has already been searched and found:
	if (find(wordsToSearch.begin(), wordsToSearch.end(), e_New) != wordsToSearch.end()) return true;

	if (isNeighborValid(row_pos, col_pos))
	{
		characters = this->grid[row_pos];
		current += characters[col_pos];
		while (the_word.find(current) != string::npos)
		{
			if (current == the_word)
			{
				checkExistence e(the_word, false);
				replace(this->wordsToSearch.begin(), this->wordsToSearch.end(), e, e_New);
				string str = the_word + ": yes" + "\n";
				fout << (str);
				return true;
			}
			else return searchingAWord(row_pos, col_pos, current, the_word, d, fileOut);
		}
	}
	return false;
}

bool GridWord::findingAWord(int i, int j, string current, string the_word, string fileOut)
{
	bool LEFT_FOUND = false;
	bool RIGHT_FOUND = false;
	bool UP_FOUND = false;
	bool DOWN_FOUND = false;
	bool LEFTDIAGUP_FOUND = false;
	bool LEFTDIAGDOWN_FOUND = false;
	bool RIGHTDIAGUP_FOUND = false;
	bool RIGHTDIAGDOWN_FOUND = false;

	if (LEFT_FOUND = searchingAWord(i, j, current, the_word, Direction::LEFT, fileOut))
		return true;

	else if (RIGHT_FOUND = searchingAWord(i, j, current, the_word, Direction::RIGHT, fileOut))
		return true;

	else if (UP_FOUND = searchingAWord(i, j, current, the_word, Direction::UP, fileOut))
		return true;

	else if (DOWN_FOUND = searchingAWord(i, j, current, the_word, Direction::DOWN, fileOut))
		return true;

	else if (LEFTDIAGUP_FOUND = searchingAWord(i, j, current, the_word, Direction::LEFTDIAGUP, fileOut))
		return true;

	else if (LEFTDIAGDOWN_FOUND = searchingAWord(i, j, current, the_word, Direction::LEFTDIAGDOWN, fileOut))
		return true;

	else if (RIGHTDIAGUP_FOUND = searchingAWord(i, j, current, the_word, Direction::RIGHTDIAGUP, fileOut))
		return true;

	else if (RIGHTDIAGDOWN_FOUND = searchingAWord(i, j, current, the_word, Direction::RIGHTDIAGDOWN, fileOut))
		return true;
	return false;
}


void GridWord::search(string& the_word, string fileOut)
{
	ofstream fout(fileOut, ios::app);

	if (the_word != "")
	{
		char first_Letter = the_word[0];
		list<coordonnees> first_Letter_Possibilities = charBypositions[first_Letter];
		list<coordonnees>::iterator itt;
		if (first_Letter_Possibilities.size() == 0)
		{
			ofstream fout(fileOut, ios::app);
			string str = the_word + ": no" + "\n";
			fout << (str);
			fout.close();
		}
		else {

			for (itt = first_Letter_Possibilities.begin(); itt != first_Letter_Possibilities.end(); ++itt)
			{
				int i = itt->first;
				int j = itt->second;
				string current = "";
				current += first_Letter;
				bool found = findingAWord(i, j, current, the_word, fileOut);
				if (found) break;
				if (itt == --first_Letter_Possibilities.end() && !found)
				{
					ofstream fout(fileOut, ios::app);
					string str = the_word + ": no" + "\n";
					fout << (str);
					fout.close();
				}
			}
		}
	}
	fout.close();
}

void GridWord::searchAllWords(string fileOut)
{
	ofstream fout(fileOut);
	fout << "";
	fout.close();
	int n_size = wordsToSearch.size();
	for (int i = 0; i < n_size; i++)
	{
		string the_word = wordsToSearch[i].first;
		search(the_word, fileOut);
	}
}


bool GridWord::isTheWordFound(string word)
{
	checkExistence e(word, true);
	return ((find(this->wordsToSearch.begin(), this->wordsToSearch.end(), e)) != wordsToSearch.end());
}
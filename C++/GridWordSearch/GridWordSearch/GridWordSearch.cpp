//// GridWordSearch.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include "pch.h"
//#include "./GridWord.h"
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <cstdio>
//#include <chrono>
//
//using namespace std;
//using namespace std::chrono;
//
//int main()
//{
//	auto start = high_resolution_clock::now();
//	GridWord *gridWord = new GridWord;
//	string fileIn = "grid.in";
//	string fileWithWords = "words.in";
//	string fileOut = "words.out";
//	gridWord->initializeGrid(fileIn, fileWithWords, fileOut);
//	cout << " ********************* \n";
//	cout << " \n";
//	cout << "Number of lines :" << gridWord->getRows() << "\n";
//	cout << "Number of characters in each line :" << gridWord->getCols() << "\n";
//	gridWord->searchAllWords(fileOut);
//	auto stop = high_resolution_clock::now();
//	auto duration = duration_cast<microseconds>(stop - start);
//	double durat = (double)duration.count() / 1000000;
//	cout << "PROGRAM TAKES " << durat << " seconds" << "\n";
//	int r;
//	cin >> r;
//	return 0;
//}



//// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
//// Debug program: F5 or Debug > Start Debugging menu
//
//// Tips for Getting Started: 
////   1. Use the Solution Explorer window to add/manage files
////   2. Use the Team Explorer window to connect to source control
////   3. Use the Output window to see build output and other messages
////   4. Use the Error List window to view errors
////   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
////   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
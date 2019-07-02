#include "pch.h"
#include "./gtest/gtest.h"
#include "../GridWordSearch/GridWord.h"
#include <chrono>



using namespace std;
using namespace std::chrono;


TEST(searchingTwoWords, searchAllWords) {
	auto start = high_resolution_clock::now();
	GridWord *gridWord = new GridWord;
	string fileIn = "grid.in";
	string fileWithWords = "words.in";
	string fileOut = "words.out";
	gridWord->initializeGrid(fileIn, fileWithWords, fileOut);
	gridWord->searchAllWords(fileOut);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	double durat = (double)duration.count() / 1000000;
	cout << "FUNCTION RESEARCH TAKES :" << durat << " seconds \n";
	bool isFound = gridWord->isTheWordFound("DIVERTIR");
	bool notFound = gridWord->isTheWordFound("TRAVESTIR");
	EXPECT_TRUE(isFound);
	EXPECT_FALSE(notFound);
}

int main(int argc, char*argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	int r;
	cin >> r;
	return 0;
}
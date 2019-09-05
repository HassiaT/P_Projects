#include "pch.h"
#include "gtest/gtest.h"
#include "C:\Users\hassi\source\repos\HardChallenges\HardChallenges\HardChallenges.cpp"

#define GTEST_COUT std::cerr << "[          ] [ INFO ]"


TEST(threeCases, countPaths) {
	int n = 5;
	vector < vector<int>> edges = { {1, 2},{2,4},{2,3},{3,4},{4,5} }; // ANSWER:  2
   //vector<vector<int>> edges = { {1,2},{4,2},{2,3},{3,4},{4,5} }; // ANSWER:  INFINITE PATHS
   //vector<vector<int>> edges = { {4,2},{2,3},{3,4},{4,5} }; // ANSWER:  0 PATHS

   //GTEST_COUT << "0" << std::endl;
   //GTEST_COUT << "INFINITE PATHS" << std::endl;
	GTEST_COUT << "2" << std::endl;

}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	int r;
	cin >> r;
	return EXIT_SUCCESS;
}
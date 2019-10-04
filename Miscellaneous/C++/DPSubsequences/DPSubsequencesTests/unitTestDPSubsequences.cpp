#include "./stdafx.h"
#include "CppUnitTest.h"
#include "C:\Users\hassi\source\repos\DPSubsequences\DPSubsequences\DPSubsequences.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace DPSubsequencesTests
{
	TEST_CLASS(DPSubsequencesTests)
	{

	public:

		TEST_METHOD(checklongestIncreasingSubsequence)
		{
			Logger::WriteMessage("LONGEST INCREASING SUBSEQUENCE TEST :\n");
			vector<int> v = { 6,2,9,5,1,5,7,5,5,5,4,8,3 };
			int length_expected = 4;
			int found = longestIncreasingSubsequence(v);
			Assert::AreEqual(length_expected, found);
		}

		TEST_METHOD(checklongestDecreasingSubsequence)
		{
			Logger::WriteMessage("LONGEST DECREASING SUBSEQUENCE TEST :\n");
			vector<int> v = {};
			int length_expected = -1;
			int found = longestDecreasingSubsequence(v);
			Assert::AreEqual(length_expected, found);
		}

		TEST_METHOD(checklongestNonDecreasingSubsequence)
		{
			Logger::WriteMessage("LONGEST NON DECREASING SUBSEQUENCE TEST :\n");
			vector<int> v = { 1,0,1,2,-5,5,7,6 };
			int length_expected = 5;
			int found = longestNonDecreasingSubsequence(v);
			Assert::AreEqual(length_expected, found);
		}

		TEST_METHOD(checklongestCommonAncestor)
		{
			Logger::WriteMessage("LONGEST COMMON ANCESTOR TEST :\n");
			vector<char> u = { 'A', 'B', 'C', 'B', 'D','A','B' };
			vector<char> v = { 'B','D', 'C', 'A','B','A' };
			int length_expected = 4;
			int found = LCS(u, v);
			Assert::AreEqual(length_expected, found);
		}

		TEST_METHOD(checklongestCommonAncestorBis)
		{
			Logger::WriteMessage("LONGEST COMMON ANCESTOR TEST with integers:\n");
			vector<int> X_test = { 1,0,0,1,0,1,0,1 };
			vector<int> Y_test = { 0,1,0,1,1,0,1,1,0 };
			int length_expected = 4;
			int found = LCS(Y_test, X_test);
			Assert::IsFalse(length_expected==found);
		}
	};
}


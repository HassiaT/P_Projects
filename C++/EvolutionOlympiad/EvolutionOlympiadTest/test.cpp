#include "pch.h"
#include "gtest/gtest.h"
#include "../EvolutionOlympiad/BinaryTree.h"
#include "C:\Users\hassi\source\repos\EvolutionOlympiad\EvolutionOlympiad\EvolutionOlympiad.cpp"



TEST(PreOrderDisplayTreeTest, displayTree) {
	BinaryTree<int>* root = nullptr;
	BinaryTree<int>* rootBis = nullptr;
	root = root->BinaryTree<int>::insert(4);
	root = root->BinaryTree<int>::insert(5);
	root = root->BinaryTree<int>::insert(10);
	root = root->BinaryTree<int>::insert(-1);
	root = root->BinaryTree<int>::insert(-100);
	root = root->BinaryTree<int>::insert(0);
	root = root->BinaryTree<int>::insert(15);
	cout << "SHOW ME THE TREE PRE ORDER :";
	root->preOrderTraversal();
	cout << "\n";
	cout << "SHOW ME THE TREE POST ORDER :";
	root->postOrderTraversal();
	cout << "\n";
	cout << "SHOW ME THE TREE IN ORDER :";
	root->inOrderTraversal();
	cout << "\n";
	bool resultat = root->find(15);
	EXPECT_TRUE(resultat);
	resultat = root->find(100);
	EXPECT_FALSE(resultat);
	resultat = root->find(0);
	EXPECT_TRUE(resultat);
	resultat = root->find(120);
	EXPECT_FALSE(resultat);
	int height = root->height();
	ASSERT_EQ(4, height);
	ASSERT_FALSE(root->isLeaf());
	ASSERT_TRUE(rootBis->isLeaf());
	ASSERT_TRUE(root->isBST());
}
TEST(EvolutionaryTreeTest, buildET) {
	BinaryTree<string> *tree = new BinaryTree<string>;
	string fileIn = "evolution.in";
	string fileOut = "evolution.out";
	EXPECT_FALSE(checkIfProperTree(fileIn, fileOut));
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	int r;
	cin >> r;
	return EXIT_SUCCESS;
}
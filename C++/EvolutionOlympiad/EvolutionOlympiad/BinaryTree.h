#pragma once

#include <string>


template <typename T>
class BinaryTree
{
private:
	T value;
	BinaryTree<T> *children[2];


public:
	BinaryTree();
	BinaryTree(T);
	~BinaryTree();
	T getValue();
	void setValue(T);
	void setChildren(BinaryTree*);
	BinaryTree* getChildren();
	int height();
	void preOrderTraversal();
	void inOrderTraversal();
	void postOrderTraversal();
	BinaryTree* insert(T);
	bool find(T);
	bool isLeaf();
	bool isBST();
};


#include "BinaryTree.hpp"


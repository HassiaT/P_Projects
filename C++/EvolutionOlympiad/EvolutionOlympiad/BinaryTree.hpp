#pragma once
#include "BinaryTree.h"
#include <cctype>

using namespace std;


template<typename T> BinaryTree<T>::BinaryTree() : value(NULL), children(nullptr) {}

template<typename T> BinaryTree<T>::BinaryTree(T val) : value(val)
{
	children[1] = nullptr;
	children[0] = nullptr;
}

template<typename T> BinaryTree<T>::~BinaryTree()
{
	value = NULL;
	if (!children)
	{
		children[1] = nullptr;
		children[0] = nullptr;
	}
}

template<typename T>
inline bool BinaryTree<T>::isLeaf()
{
	if (!this) return true;
	else if (this) return (!children[0] && !children[1]);
}

template <typename T>
inline bool BinaryTree<T>::isBST()
{
	if (!this) return false;
	else
	{
		if (this->isLeaf()) return true;
		else
		{
			if (this)
			{
				{
					if (!children[1] && children[0]) return children[0]->value <= value;
					if (!children[0] && children[1]) return children[1]->value > value;
					return (children[0]->value <= value && children[1]->value > value && children[0]->isBST() && children[1]->isBST());
				}

			}
		}
	}
	return false;
}


template<typename T>
inline T BinaryTree<T>::getValue()
{
	return value;
}

template<typename T>
inline void BinaryTree<T>::setValue(T val)
{
	value = val;

}

template<typename T>
inline void BinaryTree<T>::setChildren(BinaryTree *TwoChildren)
{
	children = TwoChildren;
}

template<typename T>
inline BinaryTree<T>* BinaryTree<T>::getChildren()
{
	return children;
}

template<typename T>
inline int BinaryTree<T>::height()
{
	int totalHeight = 0;
	if (!this) return 0;
	else if (this && !children) return 1;
	return 1 + maximum(children[0]->height(), children[1]->height());
}

template<typename T> T maximum(T a, T b)
{
	return (a > b) ? a : b;
}


template<typename T>
inline void BinaryTree<T>::preOrderTraversal()
{
	if (this != nullptr) {
		cout << value << "  ";

		if (children)
		{
			BinaryTree* leftChild = children[0];
			leftChild->preOrderTraversal();
			BinaryTree* rightChild = children[1];
			rightChild->preOrderTraversal();
		}
	}
}

template<typename T>
inline  void BinaryTree<T>::postOrderTraversal()
{
	if (this != nullptr)
	{
		if (children)
		{
			BinaryTree* left = (children[0]);
			left->postOrderTraversal();
			BinaryTree *right = (children[1]);
			right->postOrderTraversal();
		}
		cout << value << "  ";
	}
}


template<typename T>
inline void BinaryTree<T>::inOrderTraversal()
{
	if (this != nullptr) {

		if (children)
		{
			BinaryTree *leftChild = (children[0]);
			leftChild->inOrderTraversal();
		}
		cout << value << "  ";

		if (children)
		{
			BinaryTree *rightChild = (children[1]);
			rightChild->inOrderTraversal();
		}
	}
}

template<typename T>
inline bool BinaryTree<T>::find(T v)
{
	if (this == nullptr) return false;
	else
	{
		if (value == v) return true;
		if (v <= value)
		{
			if (children)
			{
				BinaryTree* left = children[0];
				return left->find(v);
			}
			else return false;
		}

		else if (v > value)
		{
			if (children != nullptr)
			{
				BinaryTree* right = children[1];
				return right->find(v);
			}
			else return false;
		}
	}
}

template<typename T>
inline BinaryTree<T>*  BinaryTree<T> ::insert(T newValue)
{
	if (!this)
	{
		BinaryTree<T>* newTree = new BinaryTree(newValue);
		return newTree;
	}
	if (newValue <= value)
	{
		BinaryTree<T> * left = children[0];
		left = left->insert(newValue);
		children[0] = left;
	}

	else
	{
		BinaryTree<T> * right = children[1];
		right = right->insert(newValue);
		children[1] = right;
	}
	return this;
}


// template specialization
template <>
class BinaryTree<string>
{
private:
	string value;
	BinaryTree<string> *children[2];

public:
	BinaryTree()
	{
		cout << "Evolutionary tree constructor called \n";
		value = "ROOT";
		children[1] = nullptr;
		children[0] = nullptr;
	}

	BinaryTree(string s)
	{
		cout << "Evolutionary tree constructor with parameter string called \n";
		value = s;
		children[0] = nullptr;
		children[1] = nullptr;
	}

	~BinaryTree()
	{
		cout << "Evolutionary tree destructor called \n";
		if (children)
		{
			if (children[1]) delete children[1];
			if (children[0]) delete children[0];
		}
	}

	bool isEmpty();
	void setValue(string);
	void setChildren(BinaryTree<string>**);
	void preOrderTraversal();
	string getValue();
	BinaryTree<string>** getChildren();
	int height();
};

inline void BinaryTree<string>::preOrderTraversal()
{
	if (this != nullptr) {
		if (value == "") cout << "NSF" << "  ";
		else cout << value << "  ";

		if (children)
		{
			BinaryTree<string>* leftChild = children[0];
			leftChild->preOrderTraversal();

			BinaryTree<string>* rightChild = children[1];
			rightChild->preOrderTraversal();
		}
	}
}

inline void BinaryTree<string>::setChildren(BinaryTree<string>** chi)
{
	children[0] = chi[0];
	children[1] = chi[1];
}

inline int BinaryTree<string>::height()
{
	if (this->isEmpty() || (this->value != "ROOT" && this->children[0] == nullptr)) return 0;
	else if (this && !children[0]) return 1;
	return  1 + maximum(children[0]->height(), children[1]->height());
}

inline void BinaryTree<string>::setValue(string s) {
	value = s;
}

inline string BinaryTree<string>::getValue() {
	return value;
};


inline BinaryTree<string>** BinaryTree<string>::getChildren() {
	return children;
}

inline bool BinaryTree<string>::isEmpty()
{
	if (this == nullptr) return true;
	return (this->value == "ROOT" && this->children[0] == nullptr);
}

inline BinaryTree<string>* insertET(BinaryTree<string> *node, int n_children, string val)
{
	BinaryTree<string> *newNode = node;
	if (node)
	{
		BinaryTree<string> * createChildren[2];
		if (n_children == 2)
		{
			createChildren[0] = new BinaryTree<string>("");
			createChildren[1] = new BinaryTree<string>(val);
			newNode->setChildren(createChildren);
		}

		if (n_children == 1 && val == "")
		{
			createChildren[0] = new BinaryTree<string>(val);
			createChildren[1] = nullptr;
			newNode->setChildren(createChildren);
		}

		if (n_children == 1 && val != "")
		{
			createChildren[0] = new BinaryTree<string>(val);
			createChildren[1] = nullptr;
			newNode->setChildren(createChildren);
		}
	}
	return newNode;
}




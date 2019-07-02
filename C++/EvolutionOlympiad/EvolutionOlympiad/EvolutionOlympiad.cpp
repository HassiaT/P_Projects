// EvolutionOlympiad.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <istream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <list>
#include <exception>
#include <cassert>
#include <typeinfo>
#include "BinaryTree.h"


#define NDEBUG

using namespace std;


vector<pair<string, int>>featuresInOrder(map<string, vector<int>> allfeatures)
{
	map<string, vector<int>>::iterator it;
	vector<pair<string, int>> featuresAscendingOrder;
	for (it = allfeatures.begin(); it != allfeatures.end(); advance(it, 1))
	{
		pair<string, int> toAdd(it->first, it->second.size());
		featuresAscendingOrder.push_back(toAdd);
	}
	sort(featuresAscendingOrder.begin(), featuresAscendingOrder.end(), [](auto & left, auto & right)
	{
		return (left.second > right.second);
	});
	return featuresAscendingOrder;
}


void buildETree(int originalPopulations, vector<pair<string, int>>features, int position, vector<vector<int>> populationBinary, BinaryTree<string>* tree)
{
	int n_population = populationBinary.size();
	int found_zero = 0, found_one = 0;
	vector<vector<int>> zerosBlock, onesBlock;
	if (position >= features.size()) return;
	if (n_population > 0)
	{
		//splitting into two groups
		for (int i = 0; i < n_population; i++)
		{
			vector<int> v = populationBinary[i];
			if (v[position] == 0)
			{
				found_zero++;
				zerosBlock.push_back(v);
			}
			else if (v[position] == 1)
			{
				found_one++;
				onesBlock.push_back(v);
			}
		}
		pair<string, int> oneFeature = features[position];
		string newFeature = oneFeature.first;
		// adding two branches/ children to the current node 
		if (found_zero > 0 && found_one > 0)
		{
			tree = insertET(tree, 2, newFeature); //adding two children
			position++;
			BinaryTree<string> **children = tree->getChildren();
			BinaryTree<string> *childZero = children[0];
			BinaryTree<string> *childOne = children[1];
			buildETree(originalPopulations, features, position, onesBlock, childOne);
			buildETree(originalPopulations, features, position, zerosBlock, childZero);
		}
		else if (found_zero > 0)
		{
			position++;
			buildETree(originalPopulations, features, position, zerosBlock, tree);
		}
		else if (found_one > 0)
		{
			tree = insertET(tree, 1, newFeature);
			BinaryTree<string> **children = tree->getChildren();
			if (children) {
				BinaryTree<string> *childZero = *children;
				position++;
				buildETree(originalPopulations, features, position, onesBlock, childZero);
			}
		}
	}
}


vector<vector<int>> turnIntoBinary(vector<pair<string, int>>features, vector<vector<string>>allPopulations)
{
	int n = allPopulations.size();
	int n_features = features.size();
	vector<vector<int>> binaryPopulations(n - 1);
	vector<pair<string, int>>::iterator it;

	for (int i = 1; i < n; i++)
	{
		vector<string> v = allPopulations[i];
		vector<int> v_Binary;
		for (it = features.begin(); it != features.end(); ++it)
		{
			string s = it->first;
			vector<string>::iterator it_str = find(v.begin(), v.end(), s);
			if (it_str != v.end()) v_Binary.push_back(1);
			else v_Binary.push_back(0);
		}
		binaryPopulations[i - 1] = v_Binary;
	}
	return binaryPopulations;
}


bool properEvolutionaryTree(map<string, vector<int>> allfeatures)
{
	map<string, vector<int>>::iterator it, itPrev;
	itPrev = prev(allfeatures.end());
	for (it = allfeatures.begin(); it != itPrev; advance(it, 1))
	{
		map<string, vector<int>>::iterator itNext = it;
		for (itNext = next(itNext, 1); itNext != allfeatures.end(); advance(itNext, 1))
		{
			vector<int> firstVector = it->second;
			std::sort(firstVector.begin(), firstVector.end());
			vector<int> scdVector = itNext->second;
			std::sort(scdVector.begin(), scdVector.end());
			int n = firstVector.size() + scdVector.size();
			vector<int> intersection(n);
			vector<int> differenceOne(n);
			vector<int> differenceTwo(n);
			vector<int> ::iterator ittVec = set_intersection(firstVector.begin(), firstVector.end(), scdVector.begin(), scdVector.end(), intersection.begin());
			intersection.resize(ittVec - intersection.begin());
			vector<int> ::iterator ittVec2 = set_difference(firstVector.begin(), firstVector.end(), scdVector.begin(), scdVector.end(), differenceOne.begin());
			differenceOne.resize(ittVec2 - differenceOne.begin());
			vector<int> ::iterator ittVec3 = set_difference(scdVector.begin(), scdVector.end(), firstVector.begin(), firstVector.end(), differenceTwo.begin());
			differenceTwo.resize(ittVec3 - differenceTwo.begin());
			if (intersection.size() > 0 && differenceOne.size() > 0 && differenceTwo.size() > 0)
				return false;
		}
	}
	return true;
}


int checkIfProperTree(string filename, string fileOut)
{
	try {
		ifstream fin(filename);
		ofstream fout(fileOut);
		map<string, vector<int>> featurepopulations;
		map<string, vector<int>>::iterator itt;
		vector<pair<string, int>> featuresInAscendingOrder;
		string line;
		int number_populations;
		int popCount = 0, popID = 0;
		fin >> number_populations;
		bool checkPopulation = typeid(number_populations).name() == typeid(popCount).name();
		if (!checkPopulation)
		{
			fout << " Problem with the number of populations read in the file " << filename << "\n";
			return EXIT_FAILURE;
		}
		assert(typeid(number_populations).name() == typeid(popCount).name());
		vector<vector<string>> allPopulations(number_populations + 1);
		vector<vector<int>> binaryPopulations(number_populations + 1);
		while (popCount < number_populations + 1)
		{
			getline(fin, line);
			if (line != "")
			{
				fout << "No population found in the input file " << filename << "\n";
				return EXIT_FAILURE;
			}
			assert(line != "");
			istringstream iss(line);
			vector<string> features{ istream_iterator<string>(iss), {} };
			for (int i = 0; i < features.size(); i++)
			{
				string f = features[i];
				if (f != "")
				{
					if (!isdigit(f[0]))
					{
						featurepopulations[f].push_back(popCount);
						allPopulations[popID].push_back(f);
					}
				}
			}
			if (!allPopulations.empty()) popID++;
			popCount++;
		}
		fin.close();
		bool isProper = properEvolutionaryTree(featurepopulations);
		if (isProper)
		{
			fout << "yes\n";
			fout.close();
			return EXIT_SUCCESS;
		}
		else
		{
			fout << "no\n";
			fout.close();
			return EXIT_FAILURE;
		}
	}

	catch (ifstream::failure e)
	{
		ofstream fout(fileOut);
		fout << "Exception: " << "Opening /reading file " << filename << "\n";
	}
	catch (bad_typeid& bt)
	{
		ofstream fout(fileOut);
		fout << "Exception raised - bad type  :" << bt.what() << "\n";
	}
	catch (exception& e)
	{
		ofstream fout(fileOut);
		fout << "Exception raised :" << e.what() << "\n";
	}
	return EXIT_FAILURE;
}

bool buildingET(vector<vector<string>> allPopulations,bool isProperPossible, BinaryTree<string> *tree, map<string, vector<int>> featurepopulations)
{
	if (isProperPossible)
	{
		int number_populations = allPopulations.size();
		vector<pair<string, int>> featuresInAscendingOrder;
		featuresInAscendingOrder = featuresInOrder(featurepopulations);
		vector<vector<int>> binaryPopulations(number_populations + 1);
		binaryPopulations = turnIntoBinary(featuresInAscendingOrder, allPopulations);
		int originalPopulations = binaryPopulations.size();
		buildETree(originalPopulations, featuresInAscendingOrder, 0, binaryPopulations, tree);
		cout << "SHOW ME THE PROPER TREE IN PRE ORDER :\n ";
		tree->preOrderTraversal();
		cout << " \n ";
		cout << "WHAT IS THE HEIGHT OF THE PROPER TREE ? " << tree->height() << "\n";
		cout << " \n ";
		return EXIT_SUCCESS;
	}
	 return EXIT_FAILURE;
}


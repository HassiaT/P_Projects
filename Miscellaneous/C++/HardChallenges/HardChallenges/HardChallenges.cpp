// HardChallenges.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "pch.h"
#include <iostream>
#include <map>
#include <list>
#include <vector>

using namespace std;

map<int, vector<int>>* findNeighbors(int n, vector<vector<int>> &edges)
{
	map<int, vector<int>> *neighbors = new map<int, vector<int>>;
	while (n > 0)
	{
		list<int> current_neighbors;
		for (int i = 0; i < edges.size(); i++) {
			vector<int> item = edges[i];
			if (item[0] == n)
			{
				(*neighbors)[n].push_back(item[1]);
			}
		}
		n--;
	}
	return neighbors;
}

void print_out(map<int, vector<int>> *neighbors)
{
	if (!neighbors)
		cout << "Null pointer \n";
	else
	{
		map<int, vector<int>>::iterator it;
		for (it = neighbors->begin(); it != neighbors->end(); ++it) {
			cout << "KEY :" << (it->first) << ";";
			vector<int> values = it->second;
			cout << "VALUES :";
			for (vector<int>::iterator itt = values.begin(); itt != values.end(); itt++) {
				cout << *itt << " ";
			}
			cout << endl;
		}

	}
}


void dfs(int source, map<int, vector<int>>*neighbors, int destination,
	int &countPaths, int *marked)
{
	if (source == destination) countPaths++;

	marked[source] = 1; //VISITING

	vector<int> current_neighors = (*neighbors)[source];
	for (int i = 0; i < current_neighors.size(); i++)
	{
		int current_node = current_neighors[i];
		if (marked[current_node] == 0)
		{
			vector<int> next_neighbors = (*neighbors)[current_node];
			for (int v = 0; v < next_neighbors.size(); v++)
			{
				int neigh = next_neighbors[v];
				if (marked[neigh] == 1)   //FINDING A NEIGHBORD THAT IS STILL BEING VISITED
				{
					cout << "INFINITE PATHS" << endl;
					return;
				}
			}
		}
		dfs(current_node, neighbors, destination, countPaths, marked);
	}
	marked[source] = 2;   //COMPLETED
}

void countPaths(int n, vector<vector<int>> edges, int &countPaths) {
	map<int, vector<int>>*allNeighbors = findNeighbors(n, edges);
	int source = 1;
	int destination = 5;
	int*m_marked = new int[n + 1];
	for (int u = 0; u < n; u++)
		m_marked[u] = 0;
	
	dfs(source, allNeighbors, destination, countPaths, m_marked);
	cout << "COUNT PATHS : " << countPaths << endl;
}

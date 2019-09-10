#pragma once
#include "Graph.h"
#include <vector>
#include <queue>


using namespace std;

struct UF
{
	int count; // number of components
	int items;
	vector<int>ids;

	UF(int _items)
	{
		count = _items;
		items = _items;
		for (int u = 0; u < _items + 1; u++)
		{
			ids.push_back(u);
		}		
	}
};

int find(int, UF*);
bool connected(UF *, int, int);
void unionComponents (UF *, int, int);
priority_queue<Edge, vector<Edge>, CompareEdge> gettingPriorityQueue(Graph, UF*);
queue<Edge> KruskalAlgorithm(Graph);
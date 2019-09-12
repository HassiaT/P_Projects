#include "pch.h"
#include "Graph.h"
#include <algorithm>
#include <stack>
#include <functional>
#include <iostream>
#include <string>

using namespace std;



void gettingEdges(Graph graph, DjikstraResults *dji)
{
	int V = graph.getV();
	vector<vector<int>> *edges = graph.getEdges();
	for (int i = 0; i < edges->size(); i++)
	{
		vector<int>oneEdge = (*edges)[i];
		int current = oneEdge[0];
		Edge e(oneEdge[0], oneEdge[1], (double)oneEdge[2]);
		dji->allTheEdges[current].push_back(e);
	}
}

stack<int>getShortestPath(int s, int dest, DjikstraResults *dji)
{
	stack<int> onePath_;
	if (s == dest)
	{
		onePath_.push(s);
		return onePath_;
	}

	for (int currentNode = dest; currentNode != s; currentNode = (dji->parents)[currentNode])
	{
		if (currentNode == -1) break;
		onePath_.push(currentNode);
	}
	onePath_.push(s);
	return onePath_;
}


void allTheShortestPaths(int s, int n, DjikstraResults *dji)
{
	int numberofNodes = n;
	while (numberofNodes > 0)
	{
		stack<int> onePath = getShortestPath(s, numberofNodes, dji);
		dji->edgesTo[numberofNodes] = (onePath);
		numberofNodes--;
	}
}


void printoutshortestPaths(DjikstraResults *dji, int start)
{
	string thepath = "";
	cout << " These are the shortest paths from single source :" << start << endl;
	for (int i = 1; i < dji->edgesTo.size(); i++)
	{
		cout << "PATH BETWEEN " << start << " AND " << i << " IS :";
		stack<int> path = dji->edgesTo[i];
		thepath = "";
		while (!path.empty())
		{
			int current = path.top();
			path.pop();
			cout << current;
			if (!path.empty()) cout << " -> ";
			else cout << fixed << "    :" << dji->distanceTo[i];
		}
		cout << "\n";
	}
}


DjikstraResults djikstraAlgorithm(Graph graph, int start)
{
	double INF = numeric_limits<double>::max();
	int V = graph.getV();
	DjikstraResults *dji = new DjikstraResults(V);
	gettingEdges(graph, dji);
	vector<vector<int>> *edges = graph.getEdges();
	priority_queue<Edge, vector<Edge>, CompareEdge> PQ;

	dji->distanceTo[start] = 0.0;
	Edge e_new(start, start, 0.0);
	dji->marked[start] = true;
	dji->parents[start] = start;
	PQ.push(e_new);
	while (!PQ.empty())
	{
		Edge top = PQ.top();
		int currentNode = top.v;
		PQ.pop();
		dji->marked[currentNode] = false;

		for (int i = 0; i < (dji->allTheEdges)[currentNode].size(); i++)
		{
			Edge i_ = dji->allTheEdges[currentNode][i];
			int destination = i_.v;
			if (dji->distanceTo[destination] > i_.w + dji->distanceTo[currentNode])
			{
				dji->distanceTo[destination] = i_.w + dji->distanceTo[currentNode];
				dji->parents[destination] = currentNode;
				dji->marked[destination] = true;
				Edge ee(currentNode, destination, dji->distanceTo[destination]);
				PQ.push(ee);
			}
		}
	}
	replace(++dji->distanceTo.begin(), dji->distanceTo.end(), INF, -1.0);
	allTheShortestPaths(start, V, dji);
	return (*dji);
}


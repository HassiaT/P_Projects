#pragma once
#include "pch.h"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;
typedef pair<int, double> PAIR_WEIGHT;


struct Compare
{
	bool operator() (const PAIR_WEIGHT p, const PAIR_WEIGHT p2)
	{
		if (p.first == p2.first) return p.second < p2.second;
		else  return p.second < p2.second;
	};
};


struct Edge
{
	int u;
	int v;
	double w;

	Edge(int first, int second, double weight) :u(first), v(second), w(weight) {};
};


struct CompareEdge {
	bool operator() (const Edge&e1, const Edge& e2)
	{
		return e1.w < e2.w;
	};
};




class Graph
{

private:
	int V; /* number of vertices */
	vector<vector<int>> *edges;

public:
	Graph(int, vector<vector<int>>*);
	~Graph();
	int getV();
	void setV(int);
	vector<vector<int>> * getEdges();
	void setV(vector<vector<int>> *);


};

struct DjikstraResults
{
	int v; //number of vertices
	vector<vector<Edge>> allTheEdges;
	vector<stack<int>>edgesTo;
	vector<bool>marked;
	vector<int>parents;
	vector<double>distanceTo;

	/* Constructor */
	DjikstraResults(int _v) :v(_v) {
		vector<Edge> new_Edge;
		stack<int> new_Edge_stack;
		allTheEdges.assign(v + 1, new_Edge);
		edgesTo.assign(v + 1, new_Edge_stack);
		marked.assign(v + 1, false);
		parents.assign(v + 1, -1);
		distanceTo.assign(v + 1, numeric_limits<double>::max());
	};
};


struct DirectedNegativeCycle {
	int v; //number of vertices
	vector<stack<int>> cycles;
	vector<bool>marked;
	vector<int>edgeTo;
	vector<bool> onstack;
	DjikstraResults * results;

	/* Constructor */
	DirectedNegativeCycle(int _v) :v(_v) {
		edgeTo.assign(v + 1, 0);
		marked.assign(v + 1, false);
		onstack.assign(v + 1, false);
		results = new DjikstraResults(v);
	};
};

void gettingEdges(Graph, DjikstraResults *);
stack<int>getShortestPath(int, int, DjikstraResults *);
void allTheShortestPaths(int, int , DjikstraResults *);
void printoutshortestPaths(DjikstraResults *, int);
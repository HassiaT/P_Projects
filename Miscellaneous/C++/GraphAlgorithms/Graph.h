#pragma once
#include "pch.h"
#include <iostream>
#include <vector>
#include <queue>


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
		return e1.w > e2.w;
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


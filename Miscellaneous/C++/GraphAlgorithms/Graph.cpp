#include "pch.h"
#include "Graph.h"


Graph::Graph(int nb_vertices, vector<vector<int>> *all_edges) : V(nb_vertices), edges(all_edges)
{
	cout << "Constructor of the graph with number of edges and vertices \n";
}

Graph::~Graph()
{
	cout << "Destructor called \n";
}

int Graph::getV()
{
	return V;
}


void Graph::setV(int v)
{
	v = v;
}

vector<vector<int>>* Graph::getEdges()
{
	return edges;
}

void Graph::setV(vector<vector<int>> *vectorEdges)
{
	edges->assign(vectorEdges->begin(), vectorEdges->end());
}

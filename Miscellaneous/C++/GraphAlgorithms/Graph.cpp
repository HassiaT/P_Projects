#include "pch.h"
#include "Graph.h"


Graph::Graph(int nb_vertices, vector<vector<int>> *all_edges) : V(nb_vertices), edges(all_edges)
{
	cout << "Constructor of the graph with number of edges and vertices \n";
}

Graph::~Graph()
{
	//cout << "Destructor called \n";
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
		while (!path.empty())
		{
			int current = path.top();
			path.pop();
			cout << current;
			double real_cost = (dji->distanceTo[i] == 0.0) ? -1.0 : dji->distanceTo[i];
			if (!path.empty()) cout << " -> ";
			else cout << fixed << "    :" << real_cost;
		}
		cout << "\n";
	}
}

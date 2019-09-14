#include "pch.h"
#include "BellmanFord.h"
#include <queue>

using namespace std;

double lengthCycle(stack<int> cycle, DjikstraResults *results)
{
	double L = 0.0;
	int previous_Node = -1;
	while (!cycle.empty())
	{
		int top = cycle.top();
		cycle.pop();
		if (previous_Node != -1)
		{
			for (unsigned int i = 0; i < (results->allTheEdges[previous_Node].size()); i++)
			{
				Edge i_ = results->allTheEdges[previous_Node][i];
				if (i_.v == top)
				{
					L += i_.w;
				}
			}
		}
		previous_Node = top;
	}
	return L;
}


void printOutNegativeCycles(DirectedNegativeCycle *r)
{
	if (r->cycles.empty())
	{
		cout << "NO NEGATIVE CYCLE FOUND \n";
		return;
	}
	for (unsigned int i = 0; i < r->cycles.size(); i++)
	{
		stack<int> cycles = r->cycles[i];
		while (!cycles.empty())
		{
			int top = cycles.top();
			cout << top;
			cycles.pop();
			if (cycles.empty()) cout << " ->";
		}
	}
}


void dfsSpecializedCycle(Graph graph, DirectedNegativeCycle *r, int current)
{
	DjikstraResults *results = r->results;
	gettingEdges(graph, results);
	r->onstack[current] = true;
	r->marked[current] = true;
	vector<Edge> current_edges = results->allTheEdges[current];

	for (unsigned int i = 0; i < current_edges.size(); i++)
	{
		int node_from = current_edges[i].u;
		int node_to = current_edges[i].v;
		if (r->cycles.empty()) return;
		else if (!r->marked[node_to])
		{
			r->edgeTo[node_to] = node_from;
			dfsSpecializedCycle(graph, r, node_to);
		}
		//found a new cycle
		else if (r->onstack[node_to])
		{
			stack<int>oneCycle;
			for (int x = current; x != node_to; x = r->edgeTo[x])
			{
				oneCycle.push(x);
			}
			oneCycle.push(node_to);
			oneCycle.push(current);
			stack<int> copy_cycle = oneCycle;
			double L = lengthCycle(copy_cycle, r->results);

			//IS IT A NEGATIVE CYCLE ?
			if (L < 0)
				r->cycles.push_back(oneCycle);
		}
	}
	r->onstack[current] = false;
}

void BellmanFord(Graph graph, int current)
{
	int vertices = graph.getV();
	DirectedNegativeCycle *r = new DirectedNegativeCycle(vertices);
	DjikstraResults *results = r->results;
	gettingEdges(graph, results);
	double INF_POSITIVE = numeric_limits<double>::max();
	vector<double>distanceTo(vertices + 1, INF_POSITIVE);
	vector<bool>onQ(vertices + 1, false);
	queue<int> queueNodes;
	int cost = 0; //number of calls to function relaxEdge
	results->distanceTo[current] = 0.0;
	r->results->parents[current] = current;
	queueNodes.push(current);
	onQ[current] = true;

	while (!queueNodes.empty() && r->cycles.empty())
	{
		int v = queueNodes.front();
		queueNodes.pop();
		onQ[v] = false;
		for (unsigned int i = 0; i < (results->allTheEdges[v].size()); i++)
		{
			Edge i_ = results->allTheEdges[v][i];
			int node_to = i_.v;
			if (results->distanceTo[node_to] > i_.w + results->distanceTo[v])
			{
				results->distanceTo[node_to] = i_.w + results->distanceTo[v];
				r->edgeTo[node_to] = v;
				r->results->parents[node_to] = v;
				if (onQ[node_to] == false)
				{
					queueNodes.push(node_to);
					onQ[node_to] = true;
				}
			}
			if (cost++ %vertices == 0)
			{
				dfsSpecializedCycle(graph, r, current);
			}
		}
	}
	replace(++results->distanceTo.begin(), results->distanceTo.end(), INF_POSITIVE, -1.0);
	allTheShortestPaths(current, vertices, results);
	printOutNegativeCycles(r);
	cout << "BELLMAN-FORD ALGORITHM SHORTEST PATHS : \n";
	printoutshortestPaths(results, current);

}
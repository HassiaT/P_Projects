#pragma once
#include "pch.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <limits>
#include <set>
#include "PrimAlgorithm.h"


using namespace std;
typedef pair<int, double> PAIR_WEIGHT;



map<int, vector<pair<int, int>>>* buildAdjList(vector<vector<int>>& graph)
{
	map<int, vector<pair<int, int>>> *adjList = new map<int, vector<pair<int, int>>>;
	if (graph.size() == 0)
		return nullptr;
	for (int u = 0; u < graph.size(); u++)
	{
		vector<int> item = graph[u];
		PAIR_WEIGHT p = make_pair(item[1], item[2]);
		PAIR_WEIGHT p1 = make_pair(item[0], item[2]);
		(*adjList)[item[0]].push_back(p);
		(*adjList)[item[1]].push_back(p1);
	}
	/* Printing out the adjacency list */
	map<int, vector<pair<int, int>>>::iterator it;
	for (it = adjList->begin(); it != adjList->end(); it++)
	{
		int current = (*it).first;
		cout << "NODE " << current << ": [";
		vector<pair<int, int>> neighbors = (*adjList)[current];
		for (int i = 0; i < neighbors.size(); i++) {
			PAIR_WEIGHT p1 = neighbors[i];
			double weight = (double)(p1.second);
			cout << " (" << p1.first << ";" << fixed << weight << ") ";
		}
		cout << "] \n";
	}
	return adjList;
}


queue<Edge> PrimsAlgorithm(Graph graph, int start)
{
	int vertices = graph.getV();
	vector<vector<int>> *my_edges = graph.getEdges();
	map<int, vector<pair<int, int>>>* listeAdj = buildAdjList(*my_edges);
	map<double, int> *PQ = new map<double, int>;
	queue<Edge> queueEdges;
	PAIR_WEIGHT p;
	int currentNode = 0;
	double cost = 0.0;
	int nodes = listeAdj->size(); //number of nodes in graph
	vector<bool>marked(nodes + 1, false);
	vector<double> distanceTo(nodes + 1, numeric_limits<double>::max());
	vector<int>parent(nodes + 1, false);
	distanceTo[start] = 0.0;
	PQ->insert(make_pair(0.0, start));
	parent[start] = -1;
	int previous_Node = start;


	while (!PQ->empty())
	{
		pair<double, int> p = (*PQ->begin());
		currentNode = p.second;
		cost += p.first;
		marked[currentNode] = true;
		if (parent[currentNode] != -1) {
			Edge e(currentNode, parent[currentNode], p.first);
			queueEdges.push(e);
		}
		PQ->erase(p.first);
		vector<pair<int, int>> current_neighs = (*listeAdj)[currentNode];
		for (int z = 0; z < current_neighs.size(); z++)
		{
			int neigh = current_neighs[z].first;
			if (marked[neigh] == true) continue;
			double weight = (double)(current_neighs[z].second);
			if (weight < distanceTo[neigh] && marked[neigh] == false)
			{
				auto it = std::find_if(PQ->begin(), PQ->end(), [neigh](const std::pair<double, int> & t) -> bool { return t.second == neigh; });
				distanceTo[neigh] = weight;
				parent[neigh] = currentNode;
				if (it != PQ->end()) {
					double key = it->first;
					PQ->erase(key);
					PQ->insert(make_pair(weight, neigh));
				}
				else
				{
					PQ->insert(make_pair(weight, neigh));
				}
			}
		}
	}
	return queueEdges;
}


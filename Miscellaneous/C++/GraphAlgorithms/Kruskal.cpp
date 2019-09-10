#pragma once
#include "pch.h"
#include <vector>
#include <queue>
#include "Kruskal.h"


using namespace std;

int find(int p, UF* _uf)
{
	return _uf->ids[p];
}


bool connected(UF *_uf, int p, int q)
{
	int pRoot = find(p, _uf);
	int qRoot = find(q, _uf);
	return (pRoot == qRoot);
}

void unionComponents(UF*_uf, int p, int q)
{
	int pRoot = find(p, _uf);
	int qRoot = find(q, _uf);
	if (pRoot == qRoot) return;
	_uf->ids[pRoot] = qRoot;
	_uf->count--;
}

priority_queue<Edge, vector<Edge>, CompareEdge> gettingPriorityQueue(Graph graph, UF* _uf)
{
	priority_queue<Edge, vector<Edge>, CompareEdge> mst_prior;
	vector<vector<int>> *edges = graph.getEdges();

	for (int i = 0; i < edges->size(); i++)
	{
		vector<int> one_edge = (*edges)[i];
		Edge e_new(one_edge[0], one_edge[1], (double)one_edge[2]);
		mst_prior.push(e_new);
	}
	return mst_prior;
}


queue<Edge> KruskalAlgorithm(Graph graph)
{
	int number_vertices = graph.getV();
	queue<Edge> mst_edges;
	UF *kruskal_mst = new UF(number_vertices);
	priority_queue<Edge, vector<Edge>, CompareEdge> mst_prior = gettingPriorityQueue(graph, kruskal_mst);
	while (!mst_prior.empty() && mst_edges.size() < number_vertices - 1)
	{
		Edge min_weight = mst_prior.top();
		mst_prior.pop();
		int node1 = min_weight.u;
		int node2 = min_weight.v;
		if (connected(kruskal_mst, node1, node2)) continue;
		unionComponents(kruskal_mst, node1, node2);
		mst_edges.push(min_weight);
	}
	return mst_edges;
}
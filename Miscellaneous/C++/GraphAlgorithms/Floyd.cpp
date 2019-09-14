#include "pch.h"
#include "Floyd.h"

bool existsNegativeCycle(vector<vector<double>>distances)
{
	int vertices = distances.size();
	int count = 0;
	for (int i = 1; i < vertices; i++)
	{
		vector<double> current_node_distances = distances[i];
		if (current_node_distances[i] < 0)
			count++;
	}
	cout << "NUMBER OF NEGATIVE CYCLES FOUND :" << count << endl;
	return (count != 0);
}

void printFloydPaths(int vertices, int source, vector<vector<int>>allPaths, vector<vector<double>> distance)
{
	double real_cost = 0.0;
	for (int u = 1; u < vertices + 1; u++)
	{
		double cost = 0.0;
		stack<int> onePath;
		if (u == source)
		{
			cout << "PATH BETWEEN " << source << " AND " << u << " IS :";
			cout << u << " -> " << u << " : ";
			real_cost = (cost == 0.0) ? -1.0 : cost;
			cout << fixed << "    :" << real_cost;
			cout << "\n";
		}

		else {
			int destination = u;
			onePath.push(destination);
			int current = allPaths[source][destination];

			while (current != -1)
			{
				onePath.push(current);
				cost += distance[current][destination];
				destination = current;
				current = allPaths[source][destination];
			}
			cout << "PATH BETWEEN " << source << " AND " << u << " IS :";
			while (!onePath.empty())
			{
				int current = onePath.top();
				onePath.pop();
				cout << current;
				real_cost = (cost == 0.0) ? -1.0 : cost;
				if (!onePath.empty()) cout << " -> ";
				else cout << fixed << "    :" << real_cost;
			}
			cout << "\n";
		}
	}
}



void floydWarshall(Graph graph, int startPoint)
{
	int vertices = graph.getV();
	double INF = numeric_limits<double>::max();
	vector<double>init_distances(vertices + 1, INF);
	vector<int>init_paths(vertices + 1, -1);
	vector<vector<double>>distances(vertices + 1, init_distances);
	vector<vector<int>>paths(vertices + 1, init_paths);
	vector<vector<int>> *edges = graph.getEdges();

	/* Initialization:  */
	for (int i = 0; i < edges->size(); i++)
	{
		vector<int> ed = (*edges)[i];
		int u = ed[0];
		int v = ed[1];
		double w = (double)ed[2];
		distances[u][v] = w;
		distances[u][u] = 0.0;
		distances[v][v] = 0.0;
		paths[u][v] = u;
	}
	/* FLOYD-WARSHALL algorithm : */
	for (int a = 1; a < vertices + 1; a++)
	{
		for (int b = 1; b < vertices + 1; b++)
		{
			for (int c = 1; c < vertices + 1; c++)
			{
				if (distances[b][c] > distances[b][a] + distances[a][c])
				{
					distances[b][c] = distances[b][a] + distances[a][c];
					paths[b][c] = paths[a][c];
				}
			}
		}
	}
	if (existsNegativeCycle(distances))
		cout << "NEGATIVE CYCLES FOUND \n";
	printFloydPaths(vertices, startPoint, paths, distances);
}
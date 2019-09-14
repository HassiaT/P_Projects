// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "pch.h"
#include "PrimAlgorithm.h"
#include "Kruskal.h"
#include "djikstra.h"
#include "BellmanFord.h"
#include "Floyd.h"

using namespace std;

void displayMST(queue<Edge> mstPrim)
{
	double cost = 0.0;
	if (mstPrim.empty()) {
		cout << "MINIMUM SPANNING TREE IS EMPTY - total weight: " << fixed << cost << "\n";
		return;
	}
	while (!mstPrim.empty())
	{
		Edge e = (Edge)mstPrim.front();
		cout << e.u << "--" << e.v << " : " << e.w << "\n";
		cost += e.w;
		mstPrim.pop();
	}
	cout << "MINIMUM SPANNING TREE - TOTAL WEIGHT : " << fixed << cost << "\n";
}


int main()
{
	cout.precision(2.0);
	int n = 5;
	int start_Point = 1;
	vector<vector<int>> edges = { {1,4,1}, {4,1,15},{4,3,2},{2,3,-2},{1,2,3},{1,3,6} };
	//vector<vector<int>> edges = { {1,2,3}, {1,3,4},{4,2,6},{5,2,2},{2,3,5},{3,5,7} };
	Graph graph(n, &edges);
	int which_algorithm = 0;
	queue<Edge> q_Prim, q_Kruskal;
	DjikstraResults results(0);
	while ((which_algorithm != 5) && (which_algorithm != 4) && (which_algorithm != 3) && (which_algorithm != 2)
		&& (which_algorithm != 1))
	{
		cout << "Choose an algorithm to run \n";
		cout << "  1-- Prim \n";
		cout << "  2-- Kruskal \n";
		cout << "  3-- Djikstra \n";
		cout << "  4-- Bellman-Ford \n";
		cout << "  5-- Floyd-Warshall \n";
		cout << "\n";
		cin >> which_algorithm;
		cout << "Please enter a number between 1 and 5 to choose an algorithm \n";
	}
	switch (which_algorithm)
	{
	case 1:
		q_Prim = PrimsAlgorithm(graph, start_Point);
		cout << "MINIMUM SPANNING TREE WITH PRIMS ALGORITHM :" << "   \n";
		displayMST(q_Prim);
		cout << "\n";
		break;

	case 2:
		q_Kruskal = KruskalAlgorithm(graph);
		cout << "MINIMUM SPANNING TREE WITH KRUSKAL ALGORITHM :" << "   \n";
		displayMST(q_Kruskal);
		cout << "\n";
		break;

	case 3:
		cout << "DJIKSTRA ALGORITHM SHORTEST PATHS FROM SINGLE SOURCE : " << "   \n";
		results = djikstraAlgorithm(graph, start_Point);
		printoutshortestPaths(&results, start_Point);
		cout << "\n";
		break;

	case 4:
		cout << "BELLMAN-FORD ALGORITHM FROM SINGLE SOURCE  : " << "   \n";
		BellmanFord(graph, start_Point);
		cout << "\n";
		break;
	
	case 5:
		floydWarshall(graph, start_Point);
		break;
	
	default:
		cout << "Please enter a number between 1 and 5 to choose an algorithm \n";
		break;
	}
	cout << "\n";
	cout << "\n";
	cout << "PRESS KEYBOARD TO END PROGRAM  \n";
	int r;
	cin >> r;
	return EXIT_SUCCESS;
}


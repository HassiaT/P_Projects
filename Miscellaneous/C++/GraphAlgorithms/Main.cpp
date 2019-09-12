// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include "pch.h"
#include "PrimAlgorithm.h"
#include "Kruskal.h"
#include "djikstra.h"
#include "BellmanFord.h"

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
	int start_Point=1;
	vector<vector<int>> edges = { {1,2,3}, {1,3,4},{4,2,6},{5,2,2},{2,3,5},{3,5,7} };
	Graph graph(n, &edges);
	/*queue<Edge> q_Prim = PrimsAlgorithm(graph, start_Point);
	cout << "MINIMUM SPANNING TREE WITH PRIMS ALGORITHM :" << "   \n";
	displayMST(q_Prim);
	cout << "\n";
	queue<Edge> q_Kruskal = KruskalAlgorithm(graph);
	cout << "\n";
	cout << "\n";
	cout << "MINIMUM SPANNING TREE WITH KRUSKAL ALGORITHM :" << "   \n";
	displayMST(q_Kruskal);
	cout << "\n";
	cout << "\n";
*/

	//cout << "DJIKSTRA ALGORITHM : " << "   \n";
	//DjikstraResults results = djikstraAlgorithm(graph, start_Point);
	//printoutshortestPaths(&results, start_Point);
	cout << "\n";
	cout << "\n";

	BellmanFord(graph, start_Point);



	cout << " PRESS KEYBOARD TO END PROGRAM  \n";
	int r;
	cin >> r;
	return EXIT_SUCCESS;
}


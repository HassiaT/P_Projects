#pragma once
#include "Graph.h"
#include<queue>
#include <map>


using namespace std;

map<int, vector<pair<int, int>>>* buildAdjList(vector<vector<int>>&);
queue<Edge> PrimsAlgorithm(Graph, int);

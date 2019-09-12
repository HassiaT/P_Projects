#pragma once

#include "Graph.h"

stack<int>getShortestPath(int, int, DjikstraResults *);
void allTheShortestPaths(int, int, DjikstraResults *);
void printoutshortestPaths(DjikstraResults *, int);
DjikstraResults djikstraAlgorithm(Graph, int);

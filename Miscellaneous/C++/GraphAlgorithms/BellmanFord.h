#pragma once
#include "Graph.h"

void printOutNegativeCycles(DirectedNegativeCycle *);
void dfsSpecializedCycle(Graph, DirectedNegativeCycle *, int );
void BellmanFord(Graph, int);
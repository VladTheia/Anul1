#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int main() {
	Graph g;

	g = initGraph(7, 0);
	g = insertEdge(g, 0, 3);
	g = insertEdge(g, 0, 4);
	g = insertEdge(g, 0, 7);
	g = insertEdge(g, 5, 3);
	g = insertEdge(g, 2, 6);
	g = insertEdge(g, 3, 1);
	g = insertEdge(g, 2, 4);
	g = insertEdge(g, 3, 6);
	printGraph(g);
	drawGraph(g, "graph.dot");
	g = freeGraph(g);
	return 0;
}
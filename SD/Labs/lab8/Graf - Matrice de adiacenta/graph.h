#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>

#define DIRECTED 1
#define UNDIRECTED 0
#define SIZE 200

typedef int Vertex;

typedef struct graph {
	int V, type;
	Vertex **matrix;
}*Graph;

Graph initGraph(int V, int type);
Graph insertEdge(Graph g, Vertex from, Vertex to);
Graph freeGraph(Graph g);
int inDegree(Graph g, Vertex to);
void printGraph(Graph g);
void drawGraph(Graph g, char *name);

#endif

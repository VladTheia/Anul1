#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "queue.h"
#include "stack.h"

#define SIZE 200

typedef struct graph {
	int V;
	List *adjLists;
	int *visited;
	int *start, *end;
}*Graph;

Graph initGraph(int V);
Graph insertEdge(Graph g, int u, int v, int cost);
Graph deleteVertex(Graph g, int v);
int getInDegree(Graph g, int v);
void printGraph(Graph g);
void drawGraph(Graph g, char *name);
Graph bfs(Graph g, int start);
Graph dfs(Graph g, int start, Stack *stack);
void FloydWarshall(Graph g, int n, int **w);

#endif
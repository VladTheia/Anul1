#include "graph.h"

Graph initGraph(int V, int type)
{
	Graph g;
	int i;

	g = (Graph) malloc(sizeof(struct graph));
	g->V = V;
	g->type = type;
	g->matrix = (int**) malloc(V*sizeof(int*));
	for (i = 0; i < V; i++)
		g->matrix[i] = (int*) calloc(V, sizeof(int));
	return g;
}

Graph insertEdge(Graph g, Vertex from, Vertex to)
{
	if (g == NULL)
		return g;
	if (from >= g->V || to >= g->V)
		return g;
	g->matrix[from][to] = 1;
	if (g->type == UNDIRECTED)
		g->matrix[to][from] = 1;
	return g;
}

Graph freeGraph(Graph g)
{
	int i;

	if (g == NULL)
		return g;
	for (i = 0; i < g->V; i++)
		free(g->matrix[i]);
	free(g->matrix);
	free(g);
	return NULL;
}

int inDegree(Graph g, Vertex to)
{
	int count, i;

	if (g == NULL || to >= g->V)
		return -1;
	for (i = 0; i < g->V; i++)
		if (g->matrix[i][to] == 1)
			count++;
	return count;
}

void printGraph(Graph g)
{
	int i, j;

	if (g == NULL)
		return;
	if (g->type == DIRECTED) {
		for (i = 0; i < g->V; i++)
			for (j = 0; j < g->V; j++)
				if (g->matrix[i][j] != 0)
					printf("%d -> %d\n", i, j);
	} else {
		for (i = 0; i < g->V; i++)
			for (j = 0; j < i; j++)
				if (g->matrix[i][j] != 0)
					printf("%d -> %d\n", i, j);
	}
}

void drawGraph(Graph g, char *name)
{
	int i, j;
	FILE *stream;
	char *buffer;

	if (g == NULL || name == NULL)
		return;
	stream = fopen(name, "w");
	if (g->type == UNDIRECTED)
		fprintf(stream, "graph G {\n");
	else
		fprintf(stream, "digraph G {\n");
	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=blue];\n");
	if (g->type == DIRECTED) {
		for (i = 0; i < g->V; i++)
			for (j = 0; j < g->V; j++)
				if (g->matrix[i][j] != 0)
					fprintf(stream, "    %d -> %d;\n", i, j);
	} else {
		for (i = 0; i < g->V; i++)
			for (j = 0; j < i; j++)
				if (g->matrix[i][j] != 0)
					fprintf(stream, "    %d -- %d;\n", i, j);
	}
	fprintf(stream, "}\n");
	fclose(stream);
	buffer = (char*) malloc(SIZE*sizeof(char));
	sprintf(buffer, "dot %s | neato -n -Tpng -o graph.png", name);
	system(buffer);
	free(buffer);
}
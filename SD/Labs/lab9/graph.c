#include "graph.h"
#include "stack.h"
#include <math.h>
#include <stdio.h>

Graph initGraph(int V) {
	Graph g;
	int i;
	g = (Graph) malloc(sizeof(struct graph));
	g->V = V;
	g->adjLists = (List*) malloc(V * sizeof(List));
	for (i = 0; i < V; i++) {
		g->adjLists[i] = NULL;
	}
	g->visited = calloc(V, sizeof(int));
	g->start = malloc(V * sizeof(int));
	g->end = malloc(V * sizeof(int));
	return g;
}

Graph insertEdge(Graph g, int u, int v, int cost) {
	Pair p;
	p.v = v;
	p.cost = cost;
	g->adjLists[u] = addLast(g->adjLists[u], p);
	return g;
}

Graph bfs(Graph g, int start) {
	int i, j;
	Queue q = NULL;
	List tmp;
	g->visited[start] = 1;
	q = enqueue(q, start);
	while(!isEmptyQueue(q)) {
		i = first(q);
		printf("%d\n", i);
		q = dequeue(q);
		tmp = g->adjLists[i];
		while (tmp != NULL) {
			j = tmp->data.v;
			if (g->visited[j] == 0) {
				q = enqueue(q, j);
				g->visited[j] = 1;
			}
			tmp = tmp->next;
		}
	}
	return g;
}

Graph dfs(Graph g, int start, Stack *stack) {
	int i;
	List tmp;
	g->visited[start] = 1;
	tmp = g->adjLists[start];
	while (tmp != NULL) {
		i = tmp->data.v;
		if (g->visited[i] == 0)
			g = dfs(g, i, stack);
		tmp = tmp->next;
	}
		*stack = push(*stack, start);
	return g;
}

//Functie care va deseneaza graful
void drawGraph(Graph g, char *name)
{
	int i, j;
	FILE *stream;
	char *buffer;
	List tmp;

	if (g == NULL || name == NULL)
		return;
	stream = fopen(name, "w");
	fprintf(stream, "digraph G {\n");
	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n");
	for (i = 0; i < g->V; i++) {
		tmp = g->adjLists[i];
		while (tmp != NULL) {
			fprintf(stream, "    %d -> %d;\n", i, tmp->data.v);
			tmp = tmp->next;
		}
	}
	fprintf(stream, "}\n");
	fclose(stream);
	buffer = (char*) malloc(SIZE*sizeof(char));
	sprintf(buffer, "dot %s | neato -n -Tpng -o graph.png", name);
	system(buffer);
	free(buffer);
}

int min(int a, int b) {
	if (a < b)
		return a;
	return b;
}

void FloydWarshall(Graph g, int n, int **w) {
	int d[n][n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			d[i][j] = w[i][j];
		}
	}

	for (int k = 1; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", d[i][j]);
		}
		printf("\n");
	}
	return;
}
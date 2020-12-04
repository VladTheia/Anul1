#include "graph.h"
#include "list.h"
#include "stack.h"
#include "queue.h"

//TODO - Implementati functiile pentru un graf neorientat

typedef struct graph {
	int V, *dist;
	List *adjLists;
} * Graph;

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
	fprintf(stream, "graph G {\n");
	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n");
	for (i = 0; i < g->V; i++) {
		tmp = g->adjLists[i];
		while (tmp != NULL) {
			if (tmp->data > i)
				fprintf(stream, "    %d -- %d;\n", i, tmp->data);
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

Graph initGraph(int V) {
	int i;
	Graph g = (Graph)malloc(sizeof(struct graph));
	g->V = V;
	g->adjLists = (List*)malloc(V * sizeof(List));
	g->dist = (int*)malloc(V * sizeof(int));
	for (i = 0; i < V; i++) {
		g->adjLists[i] = NULL;
		g->dist[i] = -1;
	}
	return g;
}

Graph insertEdge(Graph g, int u, int v) {
	g->adjLists[u] = addLast(g->adjLists[u], v);
	g->adjLists[v] = addLast(g->adjLists[v], u);
	return g;
}

void printGraph(Graph g) {
	int i;
	List adjList;
	for (i = 0; i < g->V; i++) {
		printf("%d: ", i);
		adjList = g->adjLists[i];
		while (adjList != NULL) {
			printf("%d ", adjList->data);
			adjList = adjList->next;
		}
		printf("\n");
	}
}

void dfs(Graph g, int start) {
	int *viz = (int*)malloc(g->V * sizeof(int));
	for (int i = 0; i < g->V; i++)
		viz[i] = 0; 
	Stack s = NULL;
	s = push(s, start);
	while (!isEmptyStack(s)) {
		int u = top(s);
		s = pop(s);
		if (viz[u] == 0) {
			viz[u] = 1;
			printf("%d\n", u);
			List list = g->adjLists[u];
			while (list != NULL) {
				int v = list->data;
				if (viz[v] == -1) {
					s = push(s, v);
				}
				list = list->next;
			}
		}
	}
}

void recursiveDFS(Graph g, int i, int *viz) {
	List list;
	printf("n%d", i);
	list = g->adjLists[i]
	viz[i] = 1;
	while (list != NULL) {
		i = p->data;
		if(!viz[i]) 
			recursiveDFS(g, i, viz);
		list = list->next;
	}
	return;
}

void bfs(Graph g, int start) {

}

int main() {
	int *viz = (int *)malloc(g->V * sizeof(int));
	for (int i = 0; i < g->V; i++)
		viz[i] = 0;
	Graph g;
	g = initGraph(5);
	insertEdge(g, 0, 1);
	insertEdge(g, 0, 2);
	insertEdge(g, 1, 3);
	insertEdge(g, 2, 4);
	dfs(g, 0);
	recursiveDFS(g, 0, viz);
	printGraph(g);
	return 0;
}
#include <string.h>
#include "graph.h"

#define MAX 100000

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

int isArc(Graph g, int u, int v) {
	List tmp = g->adjLists[u];
	while (tmp != NULL) {
		if (tmp->data.v == v)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

int getCost(Graph g, int u, int v) {
	List tmp = g->adjLists[u];
	while (tmp != NULL) {
		if (tmp->data.v == v)
			return tmp->data.cost;
		tmp = tmp->next;
	}
	return INFINITY;
}

//Functie care va deseneaza graful
void drawGraph(Graph g, char *name)
{
	int i, j;
	FILE *stream;
	char *buffer, *aux;
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
	aux = (char*) malloc(SIZE*sizeof(char));
	strncpy(aux, name, strlen(name) - 4);
	sprintf(buffer, "dot %s.dot | neato -n -Tpng -o %s.png", aux, aux);
	system(buffer);
	free(buffer);
}

void Dijkstra(Graph g, int *parent, int *dist, int source) {
	Heap *h;
	int i;
	int *vizitat = calloc((g->V), sizeof(int));
	int nod;

	h = new_heap(g->V, 0, NULL, MIN_h);
	//TODO 1
	vizitat[source] = 1;
	for (i = 0; i < g->V; i++) {
		if (isArc(g, source, i)) {
			dist[i] = getCost(g, source, i);
			insert(h, i, dist[i]);
			parent[i] = source;
		} else {
			dist[i] = MAX;
			parent[i] = -1;
		}
	}
	while (h->size != 0) {
		int u = h->keys[1];
		int cost = pop(h, 0);
		vizitat[u] = 1;
		List aux = g->adjLists[u];

		while (aux != NULL) {
			if (vizitat[aux->data.v] == 0 && dist[aux->data.v] > dist[u] + getCost(g, u, aux->data.v)) {
				dist[aux->data.v] = dist[u] + getCost(g, u, aux->data.v);
				parent[aux->data.v] = u;
				insert(h, aux->data.v, dist[i]);
			}
			aux = aux->next;
		}
	}
}

int cmp(const void *a, const void *b) {
	Edge m1, m2;
	m1 = *(Edge *) a;
	m2 = *(Edge *) b;
	return m1.cost - m2.cost;
}

int find(int node, int *status) {
	if (status[node] == node) return node;
	return find(status[node], status);
}

Graph Kruskal(Graph g) {
	Graph AMA;
	int *status, i, count, capacity, j, x;
	Edge *edges;
	List tmp;
	j = 0;

	AMA = initGraph(g->V);
	//TODO 2
	for (i = 0; i < g->V; i++) {
		List aux = g->adjLists[i];
		while (aux != NULL) {
			edges[j].u = i;
			edges[j].v = aux->data.v;
			edges[j].cost = aux->data.cost;
			j++;
			aux = aux->next;
		}
	}

	qsort(edges, j - 1, sizeof(edges[0]), cmp);

	capacity = j - 1;
	count = j - 1;
	status = calloc(capacity, sizeof(int));
	for (i = 0; i < j; i++)
		status[i] = i;
	
	for (i = 0; i < j; i++) {
		if (find(edges[i].u, status) != find(edges[i].v, status)) {
			status[edges[i].v] = status[edges[i].u];
			insertEdge(AMA, edges[i].u, edges[i].v, edges[i].cost);
			count--;
		}
		if(count == 0) break;
	}

	return AMA;
}

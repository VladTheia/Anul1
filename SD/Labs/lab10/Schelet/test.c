#include "graph.h"

int main(int argc, char **argv) {
	FILE *f;
	int i, n, m, x, y, cost, nod;
	int *prev, *dist;
	Graph AMA, g;

	if (argc < 2) {
		printf("./graph file.txt\n");
		return 1;
	}
	f = fopen(argv[1], "r");
	fscanf(f, "%d %d", &n, &m);
	g = initGraph(n+1);
	for (i = 0; i < m; i++) {
		fscanf(f, "%d %d %d", &x, &y, &cost);
		g = insertEdge(g, x, y, cost);
	}
	drawGraph(g, "graph.dot");
	prev = (int*) malloc(g->V * sizeof(int));
	dist = (int*) malloc(g->V * sizeof(int));
	Dijkstra(g, prev, dist, 1);
	for (i = 2; i < g->V; i++) {
		printf("%d - dist = %d si prev = %d\n", i, dist[i], prev[i]);
		nod = prev[i];
		while (nod != -1) {
			printf("%d ", nod);
			nod = prev[nod];
		}
		printf("\n");
	}
	AMA = Kruskal(g);
	drawGraph(AMA, "ama.dot");
	return 0;
}


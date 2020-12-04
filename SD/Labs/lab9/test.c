#include "graph.h"

int main(int argc, char **argv) {
	FILE *f;
	Stack stack = NULL;
	int i, n, m, x, y, cost;
	Graph g;
	if (argc < 2) {
		printf("./graph file.txt\n");
		return 1;
	}
	f = fopen(argv[1], "r");
	fscanf(f, "%d %d", &n, &m);
	g = initGraph(n);
	int w[m][m];
	for (i = 0; i < m; i++) {
		fscanf(f, "%d %d %d", &x, &y, &cost);
		for (int j = 0; j < m; j++) {
			w[x][y] = cost;
			w[y][x] = cost;
		}
		g = insertEdge(g, x, y, cost);
	}
	drawGraph(g, "graph.dot");

	for (int i = 0; i < n; i++) {
		if (g->visited[i] == 0) {
			g = dfs(g, i, &stack);
			g->visited[i] = 1;
		}
	}
	printStack(stack);

	FloydWarshall(g, m, w);
	return 0;
}
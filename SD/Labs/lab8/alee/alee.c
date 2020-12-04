#include "queue.h"

Point applyDirection(Point point, Point direction) {
    point.x += direction.x;
    point.y += direction.y;
    return point;
}

int checkPoint(Point point, int width) {
    if (point.x <= 0 || point.y <= 0)
        return 0;
    if (point.x > width || point.y > width)
        return 0;
    return 1;
}

void Lee(Queue queue, int **map, int width, Point directions[], Point end) {
    Point point, next_point;
    int i;

    while (!isEmpty(queue) && map[end.x][end.y] == 0) {
        point = first(queue);
        queue = dequeue(queue);

        for (i = 0; i < 4; i++) {
            next_point = applyDirection(point, directions[i]);
            if (!checkPoint(next_point, width)) {
                continue;
            }
            if (map[next_point.x][next_point.y] == 0) {
                map[next_point.x][next_point.y] = map[point.x][point.y] + 1;
                queue = enqueue(queue, next_point);
            }
        }
    }
}


int main (int argc, char **argv) {
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
    int **labirint;
    int n, m, i, j, x, y;
    Point start, end;
    Point directions[4];
    directions[0].x = -1;
    directions[0].y = 0;
    directions[1].x = 0;
    directions[1].y = 1;
    directions[2].x = 1;
    directions[2].y = 0;
    directions[3].x = 0;
    directions[3].y = -1;

    scanf("%d %d", &n, &m);
    labirint = (int**) malloc(n * sizeof(int*));
    for(i = 1; i <= n; i++) {
        labirint[i] = (int*) malloc(n * sizeof(int));
        for(j = 1; j <= n; j++) {
            //initial, marchez toate pozitiile libere
            labirint[i][j] = 0;
        }
    }
    for(i = 1; i <= m; i++) {
        scanf("%d %d", &x, &y);
        //marchez ca fiind un copac
        labirint[x][y] = -1;
    }
    scanf("%d %d %d %d", &start.x, &start.y, &end.x, &end.y);
    //Initial, coada este vida
    Queue coada = initQueue(SIZE);
    coada = enqueue(coada, start);
    //Setez 1 pentru pozitia de inceput
    labirint[start.x][start.y] = 1;
    //Aplic algoritmul lui Lee pentru a determina solutia
    Lee(coada, labirint, n, directions, end);
    //Solutia o voi avea in pozitia de final
    printf("%d\n", labirint[end.x][end.y]);
    for (i = 0; i < n; i++) {
        free(labirint[i]);
    }
    free(labirint);
    coada = freeQueue(coada);
    return 0;
}
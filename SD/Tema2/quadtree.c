#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

typedef struct QuadtreeNode {
	unsigned char blue, green, red;
	uint32_t area;
	int32_t top_left, top_right;
	int32_t bottom_left, bottom_right;
} __attribute__ ((packed)) QuadtreeNode;

typedef struct quadTree {
	unsigned char red, green, blue;
	uint32_t area;
	int index;
	struct quadTree *copil1, *copil2, *copil3, *copil4;
}* quadTree;

/*Pentru a usura procesul am folosit o structura pixel ce contine
cele 3 culori.*/
typedef struct Pixel {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} Pixel;

quadTree initNode (Pixel pixel, int size) {
	quadTree node;
	node = (quadTree)calloc(1, sizeof(struct quadTree));
	node->blue = pixel.blue;
	node->green = pixel.green;
	node->red = pixel.red;
	node->area = size * size;
	node->copil1 = NULL;
	node->copil2 = NULL;
	node->copil3 = NULL;
	node->copil4 = NULL;
	return node;
}

/*Functie pentru realizarea mediei culorilor dintr-o 
matrice de pixeli.*/
Pixel makeAverage(Pixel **grid, int size, int x, int y) {
    int i,j;
    Pixel avgPix;

    long long avgRed = 0;
    long long avgGreen = 0;
    long long avgBlue = 0;

    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++) {
            avgRed += grid[i][j].red;
            avgGreen += grid[i][j].green;
            avgBlue += grid[i][j].blue;
        }

    avgPix.red = avgRed / (size * size);
    avgPix.green = avgGreen / (size * size);
    avgPix.blue = avgBlue / (size * size);
    
    return avgPix;
}

/*Verifica daca un element este frunza, prin compararea mean-ului
cu pragul oferit.*/
int isLeaf(Pixel **grid, Pixel avgPix, int size, int prag, int x, int y) {
    long long mean = 0;
    int i, j;
    
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++) {
            mean += pow((avgPix.red - grid[i][j].red), 2) +
                    pow((avgPix.green - grid[i][j].green), 2) +
                    pow((avgPix.blue - grid[i][j].blue), 2);
        }
        
    mean = mean / (3 * size * size);
    if (mean <= prag)
        return 1;
    return 0;
}

/*Functie recursiva pentru obtinerea arborelui: daca este frunza se
intoarce nodul, altfel creaza 4 copii.*/
quadTree makeTree(Pixel **grid, int size, int x, int y, int prag) {
    Pixel avgPix = makeAverage(grid, size, x, y);
    quadTree node = initNode(avgPix, size);
    if (isLeaf(grid, avgPix, size, prag, x, y)) {
        return node;
    } else {
        /*x si y sunt coordonate de care ne vom folosi pentru
        a imparti un element in 4 sferturi egale*/
        node->copil1 = makeTree(grid, size / 2, x, y, prag);
        node->copil2 = makeTree(grid, size / 2, x, y + size / 2, prag);
        node->copil3 = makeTree(grid, size / 2, x + size / 2, y + size / 2, prag);
        node->copil4 = makeTree(grid, size / 2, x + size / 2, y, prag);
    }
    
    return node;
}

//Indexare utila pentru vectorul de tip QuadtreeNode
void indexTree(quadTree *tree, int *index) {
    if ((*tree) != NULL) {
        (*tree)->index = *index;
        (*index)++;
        indexTree(&(*tree)->copil1, index);
        indexTree(&(*tree)->copil2, index);
        indexTree(&(*tree)->copil3, index);
        indexTree(&(*tree)->copil4, index);
    }
}

//Initierea elementelor pentru vector
QuadtreeNode initQTN(quadTree node) {
    QuadtreeNode QTN;
    QTN.blue = node->blue;
    QTN.green = node->green;
    QTN.red = node->red;
    QTN.area = node->area;
    
    if (node->copil1 == NULL) {
        QTN.top_left = -1;
        QTN.top_right = -1;
        QTN.bottom_left = -1;
        QTN.bottom_right = -1;
    } else {
        QTN.top_left = node->copil1->index;
        QTN.top_right = node->copil2->index;
        QTN.bottom_right = node->copil3->index;
        QTN.bottom_left = node->copil4->index;
    }

    return QTN;
}

//Functie recursiva pentru crearea vectorului
QuadtreeNode* makeVector(QuadtreeNode *v, quadTree node) {
    QuadtreeNode aux;

    if (node != NULL) {
        aux = initQTN(node);
        v[node->index] = aux;
        v = makeVector(v, node->copil1);
        v = makeVector(v, node->copil2);
        v = makeVector(v, node->copil3);
        v = makeVector(v, node->copil4);
    }

    return v;
}

void preorder(quadTree tree) {
    if (tree != NULL) {
        printf("%d %d-%d-%d\n", tree->index, tree->red, tree->green, tree->blue);
        preorder(tree->copil1);
        preorder(tree->copil2);
        preorder(tree->copil3);
        preorder(tree->copil4);
    }
}

//Functie recursiva pentru eliberarea memoriei ocupata de arbore
void freeTree(quadTree tree) {
    if (tree != NULL) {
        freeTree(tree->copil1);
        freeTree(tree->copil2);
        freeTree(tree->copil3);
        freeTree(tree->copil4);
        free(tree);
    }
}

//Functie principala pentru rezolvarea task-ului 1
void compression(char* factor, char* input, char* output) {
    Pixel **grid;
    int prag = atoi(factor);
    char ftype[3];
    char c;
    int height, width, max, i;
    
    //Citirea header-ului
    FILE* f;
    f = fopen(input, "r");
    fscanf(f, "%s\n%d %d\n%d%c", ftype, &height, &width, &max, &c);
    int size = height;

    /*Citirea culorilor intr-o matrice de pixeli alocata dinamic*/
    grid = calloc(size, sizeof(Pixel*));
    for (i = 0; i < size; i++) {
        grid[i] = calloc(size, sizeof(Pixel));
        fread(grid[i], sizeof(Pixel), size, f);
    }
    fclose(f);
    

    int x = 0, y = 0;
    quadTree tree = makeTree(grid, size, x, y, prag);
    
    int index = 0;
    indexTree(&tree, &index);

    QuadtreeNode *array = calloc(index, sizeof(QuadtreeNode));
    array = makeVector(array, tree);

    int leafNumber = 0;
    for (i = 0; i < index; i++) {
        if (array[i].top_left == -1)
            leafNumber++;
    }

    /*Scrierea in format binar a numarului de frunze, a numarului de 
    elemente si a vectorului.*/
    f = fopen(output, "wb");
    fwrite(&leafNumber, sizeof(int), 1, f);
    fwrite(&index, sizeof(int), 1, f);
    fwrite(array, sizeof(QuadtreeNode), index, f);
    fclose(f);

    //Eliberarea de memorie
    free(array);
    freeTree(tree);
    for (i = 0; i < size; i++)
        free(grid[i]);
    free(grid);
    return;
}

/*Functie recursiva pentru obtinerea arborelui de decompresie, pe baza
vectorului de compresie.*/
quadTree makeTree2(Pixel *pixArray, QuadtreeNode *array, int size, int i) {
    quadTree node = initNode(pixArray[i], size);
    
    if (array[i].top_left == -1) {
        return node;
    } else {
        node->copil1 = makeTree2(pixArray, array, size / 2, array[i].top_left);
        node->copil2 = makeTree2(pixArray, array, size / 2, array[i].top_right);
        node->copil3 = makeTree2(pixArray, array, size / 2, array[i].bottom_right);
        node->copil4 = makeTree2(pixArray, array, size / 2, array[i].bottom_left);
    }

    return node;
}

/*Dupa obtinerea arborelui, pe baza lui vom crea matricea de pixeli.
Ne vom ajuta si de coordonatele x si y pentru a distinge zona ficarui
copil.*/
Pixel **pixMatrix(Pixel **grid, quadTree tree, int size, int x, int y) {
    int i, j;
    if (tree->copil1 != NULL) {
        grid = pixMatrix(grid, tree->copil1, size / 2, x, y);
        grid = pixMatrix(grid, tree->copil2, size / 2, x, y + size / 2);
        grid = pixMatrix(grid, tree->copil3, size / 2, x + size / 2, y + size / 2);
        grid = pixMatrix(grid, tree->copil4, size / 2, x + size / 2, y);
    } else {
        for (i = x; i < x + size; i++)
            for (j = y; j < y + size; j++) {
                grid[i][j].red = tree->red;
                grid[i][j].green = tree->green;
                grid[i][j].blue = tree->blue;
            }
    }
    
    return grid;
}

/*Functia principala pentru rezolvarea task-ului 2*/
void decompression(char* input, char* output) {
    int leafNumber, index, i, j;
    int max = 255;
    
    //Citirea fisierului comprimat
    FILE* f;
    f = fopen(input, "rb");
    fread(&leafNumber, sizeof(int), 1, f);
    fread(&index, sizeof(int), 1, f);
    QuadtreeNode *array = calloc(index, sizeof(QuadtreeNode));
    fread(array, sizeof(QuadtreeNode), index, f);
    fclose(f);

    int size = sqrt(array[0].area);
    Pixel *pixArray = calloc(index, sizeof(Pixel));
    //Crearea unui vector de pixeli pe baza vectorului QuadNodeTree
    for (i = 0; i < index; i++) {
        pixArray[i].red = array[i].red;
        pixArray[i].green = array[i].green;
        pixArray[i].blue = array[i].blue;
    }

    quadTree tree = makeTree2(pixArray, array, size, 0);

    Pixel **grid;
    grid = calloc(size, sizeof(Pixel *));
    for (i = 0; i < size; i++) {
        grid[i] = calloc(size, sizeof(Pixel));
    }
    grid = pixMatrix(grid, tree, size, 0, 0);
    
    //Scrierea header-ului specific fisierelor PPM
    f = fopen(output, "w");
    fprintf(f, "%s\n%d %d\n%d\n", "P6", size, size, max);

    //Scrierea datelor utile(a culorilor) pe baza matricei de pixeli
    for (i = 0; i < size; i++)
        for(j = 0; j < size; j++)
        fprintf(f, "%c%c%c", grid[i][j].red, grid[i][j].green, grid[i][j].blue);
    fclose(f);

    //Eliberarea de memorie
    for (i = 0; i < size; i++)
        free(grid[i]);
    free(grid);
    freeTree(tree);
    free(pixArray);
    free(array);
    return;
}

/*Functia pentru obtinerea arborelui de oglindire. Este identica cu
cea de la compresie, doar ca ordinea copiilor este schimbata in functie
de tipul oglindirii.*/
quadTree makeTree3(Pixel **grid, int size, int x, int y, int prag, char type) {
    Pixel avgPix = makeAverage(grid, size, x, y);
    quadTree node = initNode(avgPix, size);
    if (isLeaf(grid, avgPix, size, prag, x, y)) {
        return node;
    }
    else {
        if (type == 'v') {
            node->copil4 = makeTree3(grid, size / 2, x, y, prag, type);
            node->copil3 = makeTree3(grid, size / 2, x, y + size / 2, prag, type);
            node->copil2 = makeTree3(grid, size / 2, x + size / 2, y + size / 2, prag, type);
            node->copil1 = makeTree3(grid, size / 2, x + size / 2, y, prag, type);
        } else {
            node->copil2 = makeTree3(grid, size / 2, x, y, prag, type);
            node->copil1 = makeTree3(grid, size / 2, x, y + size / 2, prag, type);
            node->copil4 = makeTree3(grid, size / 2, x + size / 2, y + size / 2, prag, type);
            node->copil3 = makeTree3(grid, size / 2, x + size / 2, y, prag, type);
        }
    }

    return node;
}

/*Functie principala pentru rezolvarea task-ului 3. Combina elemente
din primele 2 task-uri. */
void mirroring(char type, char* factor, char* input, char* output) {
    Pixel **grid;
    int prag = atoi(factor);
    char ftype[3];
    char c;
    int height, width, max, i, j;

    //Citirea header-ului
    FILE *f;
    f = fopen(input, "r");
    fscanf(f, "%s\n%d %d\n%d%c", ftype, &height, &width, &max, &c);
    int size = height;

    //Alocarea si citirea matricei de pixeli
    grid = calloc(size, sizeof(Pixel *));
    for (i = 0; i < size; i++) {
        grid[i] = calloc(size, sizeof(Pixel));
        fread(grid[i], sizeof(Pixel), size, f);
    }
    fclose(f);
    int x = 0, y = 0;
    quadTree tree = makeTree3(grid, size, x, y, prag, type);

    int index = 0;
    indexTree(&tree, &index);

    //Crearea unei matrice de pixeli pe baza arborelui
    Pixel **grid2;
    grid2 = calloc(size, sizeof(Pixel *));
    for (i = 0; i < size; i++) {
        grid2[i] = calloc(size, sizeof(Pixel));
    }
    grid2 = pixMatrix(grid2, tree, size, 0, 0);

    //Scrierea header-ului
    f = fopen(output, "w");
    fprintf(f, "%s\n%d %d\n%d\n", "P6", size, size, max);

    //Scrierea culorilor pe baza matricei de pixeli
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            fprintf(f, "%c%c%c", grid2[i][j].red, grid2[i][j].green, grid2[i][j].blue);
    fclose(f);

    //Eliberarea de memorie
    for (i = 0; i < size; i++)
        free(grid2[i]);
    free(grid2);
    freeTree(tree);
    for (i = 0; i < size; i++)
        free(grid[i]);
    free(grid);
    return;
}

/*Obtinerea unui pixel ce are ca elemente mediile culorilor dintre
doua noduri.*/
Pixel makePix(quadTree tree1, quadTree tree2) {
    Pixel pixel;
    pixel.red = (tree1->red + tree2->red) / 2;
    pixel.green = (tree1->green + tree2->green) / 2;
    pixel.blue = (tree1->blue + tree2->blue) / 2;

    return pixel;
}

/*Crearea unui arbore ce are ca elemente, media elementelor celor
doi arbori primiti ca input.*/
quadTree overlayedTree(quadTree tree1, quadTree tree2, int size) {
    Pixel pixel = makePix(tree1, tree2);
    quadTree node = initNode(pixel, size);

    /*Daca ambii au copii se realizeaza media lor, altfel media se va
    face intre nodul fara copil si copilul celuilalt*/
    if (tree1->copil1 != NULL && tree2->copil1 != NULL) {
        node->copil1 = overlayedTree(tree1->copil1, tree2->copil1, size / 2);
        node->copil2 = overlayedTree(tree1->copil2, tree2->copil2, size / 2);
        node->copil3 = overlayedTree(tree1->copil3, tree2->copil3, size / 2);
        node->copil4 = overlayedTree(tree1->copil4, tree2->copil4, size / 2);
    } else if (tree1->copil1 != NULL && tree2->copil1 == NULL) {
        node->copil1 = overlayedTree(tree1->copil1, tree2, size / 2);
        node->copil2 = overlayedTree(tree1->copil2, tree2, size / 2);
        node->copil3 = overlayedTree(tree1->copil3, tree2, size / 2);
        node->copil4 = overlayedTree(tree1->copil4, tree2, size / 2);
    } else if (tree1->copil1 == NULL && tree2->copil1 != NULL) {
        node->copil1 = overlayedTree(tree1, tree2->copil1, size / 2);
        node->copil2 = overlayedTree(tree1, tree2->copil2, size / 2);
        node->copil3 = overlayedTree(tree1, tree2->copil3, size / 2);
        node->copil4 = overlayedTree(tree1, tree2->copil4, size / 2);
    }

    return node;
}

//Functie pentru rezolvarea bonusului
void overlay(char* factor, char* input1, char* input2, char* output) {
    Pixel **grid1;
    Pixel **grid2;
    int prag = atoi(factor);
    char ftype[3];
    char c;
    int height, width, max, i, j;

    //Citirea header-ului
    FILE *f;
    f = fopen(input1, "r");
    fscanf(f, "%s\n%d %d\n%d%c", ftype, &height, &width, &max, &c);
    int size = height;

    //Cititrea primei matrice de pixeli
    grid1 = calloc(size, sizeof(Pixel *));
    for (i = 0; i < size; i++) {
        grid1[i] = calloc(size, sizeof(Pixel));
        fread(grid1[i], sizeof(Pixel), size, f);
    }
    fclose(f);

    int x = 0, y = 0;
    quadTree tree1 = makeTree(grid1, size, x, y, prag);

    f = fopen(input2, "r");
    fscanf(f, "%s\n%d %d\n%d%c", ftype, &height, &width, &max, &c);
    size = height;

    //Citirea celei de-a doua matrice
    grid2 = calloc(size, sizeof(Pixel *));
    for (i = 0; i < size; i++) {
        grid2[i] = calloc(size, sizeof(Pixel));
        fread(grid2[i], sizeof(Pixel), size, f);
    }
    fclose(f);

    x = 0;
    y = 0;
    quadTree tree2 = makeTree(grid2, size, x, y, prag);

    //Overlay-ul arborilor primiti
    quadTree tree = overlayedTree(tree1, tree2, size);

    //Crearea matricei de pixeli bazata pe arborele rezultat anterior
    Pixel **grid;
    grid = calloc(size, sizeof(Pixel *));
    for (i = 0; i < size; i++)
    {
        grid[i] = calloc(size, sizeof(Pixel));
    }
    grid = pixMatrix(grid, tree, size, 0, 0);

    //Scrierea fisierului PPM
    f = fopen(output, "w");
    fprintf(f, "%s\n%d %d\n%d\n", "P6", size, size, max);

    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            fprintf(f, "%c%c%c", grid[i][j].red, grid[i][j].green, grid[i][j].blue);
    fclose(f);

    //Dealocari
    freeTree(tree1);
    freeTree(tree2);
    freeTree(tree);
    for (i = 0; i < size; i++)
        free(grid[i]);
    free(grid);
    for (i = 0; i < size; i++)
        free(grid1[i]);
    free(grid1);
    for (i = 0; i < size; i++)
        free(grid2[i]);
    free(grid2);
    return;
}

int main(int argc, char* argv[]) {
   if (argv[1][1] == 'c') {
       compression(argv[2], argv[3], argv[4]);
   } else
   if (argv[1][1] == 'd') {
       decompression(argv[2], argv[3]);
   } else
   if (argv[1][1] == 'm') {
       mirroring(argv[2][0], argv[3], argv[4], argv[5]);
   } else
   if (argv[1][1] == 'o') {
       overlay(argv[2], argv[3], argv[4], argv[5]);
   }
   
   return 0;
}
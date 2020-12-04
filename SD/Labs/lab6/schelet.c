/*
*	Created by Nan Mihai on 30.03.2017
*	Copyright (c) 2017 Nan Mihai. All rights reserved.
*	Laborator 6 - Structuri de date
*	Grupa 312CC
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2016-2017, Seria CC
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define sd_assert(message, test) \
	do { \
		if (!(test)) \
			return message; \
	} while (0)

#define sd_run_test(test, score) \
	do { \
		char *message = test(); \
		tests_run++; \
		if (message) \
			return message; \
		else \
			total_score += score; \
	} while (0)

int tests_run = 0;
float total_score = 0;

int test1[] = {9, 7, 5, 9, 4, 10, 6, 8, -8, 12};
int test2[] = {11, 9, 7, 25, 12, 29, 27, 8, 5, 1, 35, 26};
int test3[] = {26, 50, 150, 35, 175, 155, 100, 95, 9, 15, 45, 40, 4, 47, 98, \
	97, 99, 90, 200, 50, 68, 35, 39, 37, 44, 43, 46};

typedef struct tree {
	int value;
	struct tree* left;
	struct tree* right;
}*Tree;

//Problema 1 - 4 puncte
Tree initTree(int value) {
	Tree tree = malloc(sizeof(struct tree));
	tree->value = value;
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}

Tree insert(Tree tree, int value) {
	if (tree == NULL) {
		tree = initTree(value);
		return tree;
	} else if (tree->value == value) {
		printf("Nodul exista\n");
		return tree;
	} else if (tree->value > value) {
		if (tree->left == NULL) {
			tree->left = initTree(value);
			return tree;
		} else {
			tree->left = insert(tree->left, value);
			return tree;
		}
	} else {
		if (tree->right == NULL) {
			tree->right = initTree(value);
			return tree;
		} else {
			tree->right = insert(tree->right, value);
			return tree;
		}
	}
}

void inorder(Tree tree) {
	if (tree != NULL) {
		inorder(tree->left);
		printf("%d ", tree->value);
		inorder(tree->right);
	}
}

void preorder(Tree tree) {
	if (tree != NULL) {
		printf("%d ", tree->value);
		preorder(tree->left);
		preorder(tree->right);
	}
}

void postorder(Tree tree) {
	if (tree != NULL) {
		postorder(tree->left);
		postorder(tree->right);
		printf("%d ", tree->value);
	}
}

int contains(Tree tree, int value) {
	if (tree != NULL) {
		if (tree->value == value) {
			return 1;
		} else {
			if (tree->value > value)
				return contains(tree->left, value);
			else
				return contains(tree->right, value);
		}
	}
	return 0;
}

int minimum(Tree tree) {
	if (tree != NULL) {
		while (tree->left != NULL) {
			tree = tree->left;
		}
		return tree->value;
	}
}

int maximum(Tree tree) {
	if (tree != NULL) {
		while (tree->right != NULL) {
			tree = tree->right;
		}
		return tree->value;
	}
}

//Problema 2 - 2 puncte
int height(Tree tree) {
	if (tree == NULL)
		return 0;
	else {
		Tree tmp = tree;
		int left = height(tmp->left);
		int right = height(tmp->right);
		if (left >= right) {
			left = left + 1;
			return left;
		} else {
			right = right + 1;
			return right;
		}
	}
}

//Problema 3 - 2 puncte
Tree delete(Tree tree, int value) {
	if (tree == NULL) {
		printf("Nodul nu a fost gasit\n");
		return tree;
	}
	if (tree->value > value) {
		tree->left = delete(tree->left, value);
	} else if (tree->value < value) {
		tree->right = delete(tree->right, value);
	} else {
		if (tree->left != NULL && tree->right != NULL) {
			int tmp = minimum(tree->right);
			tree->value = tmp;
			tree->right = delete(tree->right, tmp);
		} else {
			Tree aux = tree;
			if (tree->left != NULL)
				tree = tree->left;
			else
				tree = tree->right;
			free(aux);
		}
	}
	return tree;
}

//Problema 4 - 2 puncte
Tree findLCA(Tree tree, int value1, int value2) {
	if (tree == NULL)
		return tree;
	if (tree->value == value1 || tree->value == value2)
		return tree;
	Tree left = findLCA(tree->left, value1, value2);
	Tree right = findLCA(tree->right, value1, value2);
	if (left && right) {
		return tree;
	} else if (left) {
		return left;
	} else {
		return right;
	}
}
int lowestCommonAncestor(Tree tree, int value1, int value2) {
	return findLCA(tree, value1, value2)->value;
}

//Problema 5
int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}
int diameter(Tree tree) {
	if (tree == NULL)
		return 0;
	int lheight = height(tree->left);
	int rheight = height(tree->right);

	int ldiameter = diameter(tree->left);
	int rdiameter = diameter(tree->right);

	return max(lheight + rheight + 1, max(ldiameter, rdiameter));
}

int checkBST(Tree node) { 
	if (node == NULL) 
		return 1;
	if (node->left != NULL && node->left->value > node->value)
		return 0; 
	if (node->right != NULL && node->right->value < node->value) 
		return 0; 
	if (!checkBST(node->left) || !checkBST(node->right)) 
		return 0; 
	return 1; 
}

void bst_print_dot_aux(Tree node, FILE* stream) {
    static int nullcount = 0;

    if (node->left) {
        fprintf(stream, "    %d -> %d;\n", node->value, node->left->value);
        bst_print_dot_aux(node->left, stream);
    }
    if (node->right) {
        fprintf(stream, "    %d -> %d;\n", node->value, node->right->value);
        bst_print_dot_aux(node->right, stream);
    }
}

void bst_print_dot(Tree tree, FILE* stream, int type) {
    fprintf(stream, "digraph BST {\n");
    if (type == 1)
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=red];\n");
    else
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=blue];\n");
    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->value);
    else
        bst_print_dot_aux(tree, stream);
    fprintf(stream, "}\n");
}

void bst_print_dot_aux_min(Tree node, FILE* stream) {
    static int nullcount = 0;

    if (!node)
    	return;
    if (node->left) {
        bst_print_dot_aux_min(node->left, stream);
    } else {
    	fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n", node->value);
    }
    
}

void bst_print_dot_aux_max(Tree node, FILE* stream) {
    static int nullcount = 0;

    if (!node)
    	return;
    if (node->right) {
        bst_print_dot_aux_max(node->right, stream);
    } else {
    	fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=green];\n", node->value);
    }
    
}

void bst_print_dot_minmax(Tree tree, FILE* stream, int type) {
    fprintf(stream, "digraph BST {\n");
    if (type == 1)
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=red];\n");
    else
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=blue];\n");
    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->value);
    else {
        bst_print_dot_aux(tree, stream);
    	bst_print_dot_aux_min(tree, stream);
    	bst_print_dot_aux_max(tree, stream);
    }
    fprintf(stream, "}\n");
}

void bst_print_dot_values(Tree tree, FILE* stream, int type, int min, int max) {
    fprintf(stream, "digraph BST {\n");
    if (type == 1)
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=red];\n");
    else
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=blue];\n");
    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->value);
    else {
        bst_print_dot_aux(tree, stream);
    	fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n", min);
    	if (max != -1)
    		fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=green];\n", max);
    }
    fprintf(stream, "}\n");
}

void bst_print_dot_lca(Tree tree, FILE* stream, int type, int value1, int value2, int lca) {
    fprintf(stream, "digraph BST {\n");
    if (type == 1)
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=red];\n");
    else
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=blue];\n");
    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->value);
    else {
        bst_print_dot_aux(tree, stream);
    	fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n", value1);
    	fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n", value2);
    	fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=green];\n", lca);
    }
    fprintf(stream, "}\n");
}

Tree freeTree(Tree tree) {
	if (tree == NULL)
		return tree;
	tree->left = freeTree(tree->left);
	tree->right = freeTree(tree->right);
	free(tree);
	return NULL;
}

static char *test_insert() {
	Tree tree = NULL;
	FILE *f;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_insert1.png");
	sd_assert("Problema1 - Test1 insert picat", checkBST(tree) && tree != NULL);
	tree = freeTree(tree);

	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_insert2.png");
	sd_assert("Problema1 - Test2 insert picat", checkBST(tree) && tree != NULL);
	tree = freeTree(tree);
	
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_insert3.png");
	sd_assert("Problema1 - Test3 insert picat", checkBST(tree) && tree != NULL);
	tree = freeTree(tree);
	return 0;
}

static char *test_minmax() {
	Tree tree = NULL;
	int min, max, i;
	FILE *f;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	min = minimum(tree);
	max = maximum(tree);
	f = fopen("test.dot", "w");
	bst_print_dot_values(tree, f, 1, min, max);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_minmax1.png");
	sd_assert("Problema1 - Test1 min picat", min == -8);
	sd_assert("Problema1 - Test1 max picat", max == 12);
	tree = freeTree(tree);
	
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	min = minimum(tree);
	max = maximum(tree);
	f = fopen("test.dot", "w");
	bst_print_dot_values(tree, f, 1, min, max);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_minmax2.png");
	sd_assert("Problema1 - Test2 min picat", min == 1);
	sd_assert("Problema1 - Test2 max picat", max == 35);
	tree = freeTree(tree);

	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	min = minimum(tree);
	max = maximum(tree);
	f = fopen("test.dot", "w");
	bst_print_dot_values(tree, f, 1, min, max);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_minmax3.png");
	sd_assert("Problema1 - Test3 min picat", min == 4);
	sd_assert("Problema1 - Test3 max picat", max == 200);
	tree = freeTree(tree);

	return 0;
}

static char *test_height() {
	Tree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	sd_assert("Problema2 - Test1 height picat", height(tree) == 4);
	tree = freeTree(tree);
	
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	sd_assert("Problema2 - Test2 height picat", height(tree) == 5);
	tree = freeTree(tree);

	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	sd_assert("Problema2 - Test3 min picat", height(tree) == 6);
	tree = freeTree(tree);

	return 0;
}

static char *test_delete() {
	Tree tree = NULL;
	int value, i;
	FILE *f;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	value = 12;
	f = fopen("test.dot", "w");
	bst_print_dot_values(tree, f, 1, value, -1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_delete1_before.png");
	tree = delete(tree, value);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_delete1_after.png");
	sd_assert("Problema3 - Test1 delete picat", checkBST(tree) && !contains(tree, value));
	tree = freeTree(tree);
	
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	value = 29;
	f = fopen("test.dot", "w");
	bst_print_dot_values(tree, f, 1, value, -1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_delete2_before.png");
	tree = delete(tree, value);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_delete2_after.png");
	sd_assert("Problema3 - Test2 delete picat", checkBST(tree) && !contains(tree, value));
	tree = freeTree(tree);

	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	value = 50;
	f = fopen("test.dot", "w");
	bst_print_dot_values(tree, f, 1, value, -1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_delete3_before.png");
	tree = delete(tree, value);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_delete3_after.png");
	sd_assert("Problema3 - Test2 delete picat", checkBST(tree) && !contains(tree, value));
	tree = freeTree(tree);

	return 0;
}

static char *test_lca() {
	Tree tree = NULL;
	int value1, value2, i, lca;
	FILE *f;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	value1 = 12;
	value2 = -8;
	lca = lowestCommonAncestor(tree, value1, value2);
	f = fopen("test.dot", "w");
	bst_print_dot_lca(tree, f, 1, value1, value2, lca);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_lca1.png");
	sd_assert("Problema4 - Test1 lca picat", lca == 7);
	tree = freeTree(tree);
	
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	value1 = 12;
	value2 = 35;
	lca = lowestCommonAncestor(tree, value1, value2);
	f = fopen("test.dot", "w");
	bst_print_dot_lca(tree, f, 1, value1, value2, lca);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_lca2.png");
	sd_assert("Problema4 - Test2 lca picat", lca == 25);
	tree = freeTree(tree);

	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	value1 = 4;
	value2 = 43;
	lca = lowestCommonAncestor(tree, value1, value2);
	f = fopen("test.dot", "w");
	bst_print_dot_lca(tree, f, 1, value1, value2, lca);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_lca3.png");
	sd_assert("Problema4 - Test3 delete picat", lca == 35);
	tree = freeTree(tree);

	return 0;
}

static char *all_tests() {
	sd_run_test(test_insert, 2);
	sd_run_test(test_minmax, 2);
	sd_run_test(test_height, 2);
	sd_run_test(test_delete, 2);
	sd_run_test(test_lca, 2);
	return 0;
}

int main() {
	srand(time(NULL));
	char *result = all_tests();
	if (result != 0) {
		printf("%s\n", result);
	}
	else {
		printf("Toate testele au trecut! Felicitari!\n");
	}
	printf("Punctajul obtinut este: %.2lf\n", total_score);
	printf("Teste rulate: %d\n", tests_run);

	Tree tree;
	int i;
	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	int diam = diameter(tree);
	printf("Diametrul este %d\n", diam);

	return result != 0;
}
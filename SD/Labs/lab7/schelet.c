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
	97, 99, 90, 200, 55, 68, 36, 39, 37, 44, 43, 46};
int test4[] = {7, 15, 9, 6, 1, 2, 8, 4};

typedef struct tree {
	int value;
	char operand;
	struct tree* left;
	struct tree* right;
}*Tree;

Tree initTree(int value) {
	Tree tree = (Tree) malloc(sizeof(struct tree));
	tree->value = value;
	tree->left = NULL;
	tree->right = NULL;
	return tree;
}

int height(Tree tree) {
	if (tree == NULL)
		return 0;
	Tree tmp;
	int left, right;
	tmp = tree;
	left = height(tmp->left);
	right = height(tmp->right);
	if (left >= right) {
		left = left + 1;
		return left;
	} else {
		right = right + 1;
		return right;
	}
}

int getSubTree(Tree tree) {
	int left, right;
	if (tree->left == NULL && tree->right == NULL)
		return 0;
	if (tree->left == NULL)
		return 1;
	else if (tree->right == NULL)
		return 2;
	left = getSubTree(tree->left);
	right = getSubTree(tree->right);
	if (left == 0 && right == 0)
		return 0;
	else if (left == 0)
		return 2;
	else
		return 1;
}

Tree insert(Tree tree, int value) {
	if (tree == NULL)
		return initTree(value);
	else if (height(tree->left) < height(tree->right))
		tree->left = insert(tree->left, value);
	else if (height(tree->left) > height(tree->right))
		tree->right = insert(tree->right, value);
	else { 
		if (getSubTree(tree) == 0)
			tree->right = insert(tree->right, value);
		else
			tree->left = insert(tree->left, value);
	}
	return tree;
}

int isLeaf(Tree tree) {
	return (!tree->left && !tree->right);
}

//Problema 1 - 1 punct
int countLeaf(Tree tree) {
	int nr = 0;
	if (tree == NULL)
		return 0;
	else {
		if (isLeaf(tree))
			nr++;
		else {
			nr = nr + countLeaf(tree->left);
			nr = nr + countLeaf(tree->right);
		}
	}
	return nr;
}

//Problema 2 - 2 puncte
int checkSumTree(Tree tree) {
	int ok = 1;
	if (isLeaf(tree) == 0) {
		if (tree->right == NULL)
			tree->right->value = 0;
		if (tree->left == NULL)
			tree->left->value = 0;
		if (tree->value != tree->right->value + tree->left->value)
			return 0;
		else {
			ok = 1;
			ok = checkSumTree(tree->left);
			if (ok == 0)
				return 0;
			ok = checkSumTree(tree->right);
			if (ok == 0)
				return 0;
		}
	}
	return ok;
}

//Problema 3 - 3 puncte
int level(Tree tree, int val, int lev) {
	if (tree == NULL)
		return 0;
	if (tree->value == val)
		return lev;
	int l = level(tree->left, tree->value, lev + 1);
	if (l != 0)
		return l;
	return level(tree->right, tree->value, lev + 1);
}
/*
Tree findValue(Tree tree, int value) {
	if (tree == NULL)
		return NULL;
	else {
		if (tree->value == value)
			return tree;
		else {
			Tree aux;
				aux = findValue(tree->left, value);
				if (aux->value == value)
					return aux;
				aux = findValue(tree->right, value);
				if (aux->value == value)
					return aux;
		}
	}
	return NULL;
}*/

int isSibling(Tree tree, int value1, int value2) {
	if (tree == NULL)
		return 0;
		if (tree->left != NULL && tree->right != NULL)
	return ((tree->left->value == value1 && tree->right->value == value2) ||
			(tree->left->value == value2 && tree->right->value == value1) ||
			isSibling(tree->left, value1, value2) ||
			isSibling(tree->right, value1, value2));
}

int isCousin(Tree tree, int value1, int value2) {
	if (tree == NULL) {
		return 0;
	} else {
		if ((level(tree, value1, 1) == level(tree, value2, 1)) && 
			isSibling(tree, value1, value2) == 0)
			return 1;
	}
	return 0;
}

//Problema 4 - 4 puncte
int isOperand(Tree tree) {

}

Tree parse(const char *expr) {
	return NULL;
}

int evaluate(Tree tree) {
	return 0;
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

void bst_print_dot_aux_expr(Tree node, FILE* stream) {
    static int nullcount = 0;
    if (node->left != NULL && node->right != NULL)
    	fprintf(stream, "    %c [fontname=\"Arial\", shape=circle, style=filled, fillcolor=blue];\n", node->operand);
    else
    	fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=red];\n", node->value);
    if (node->left) {
    	if (isLeaf(node->left))
        	fprintf(stream, "    %c -> %d;\n", node->operand, node->left->value);
        else
        	fprintf(stream, "    %c -> %c;\n", node->operand, node->left->operand);
        bst_print_dot_aux_expr(node->left, stream);
    }
    if (node->right) {
    	if (isLeaf(node->right))
        	fprintf(stream, "    %c -> %d;\n", node->operand, node->right->value);
        else
        	fprintf(stream, "    %c -> %c;\n", node->operand, node->left->operand);
        bst_print_dot_aux_expr(node->right, stream);
    }
}

void bst_print_dot_expr(Tree tree, FILE* stream, int type) {
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
        bst_print_dot_aux_expr(tree, stream);
    fprintf(stream, "}\n");
}

void bst_print_dot_aux_leaf(Tree node, FILE* stream) {
    static int nullcount = 0;

    if (node->left) {
        fprintf(stream, "    %d -> %d;\n", node->value, node->left->value);
        bst_print_dot_aux_leaf(node->left, stream);
    }
    if (node->right) {
        fprintf(stream, "    %d -> %d;\n", node->value, node->right->value);
        bst_print_dot_aux_leaf(node->right, stream);
    }
    if (node->left == NULL && node->right == NULL) {
    	fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n", node->value);
    }
}

void bst_print_dot_leaf(Tree tree, FILE* stream, int type) {
    fprintf(stream, "digraph BST {\n");
    if (type == 1)
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=red];\n");
    else
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=blue];\n");
    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left) {
        fprintf(stream, "    %d [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n", tree->value);
    }
    else
        bst_print_dot_aux_leaf(tree, stream);
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

Tree freeTree(Tree tree) {
	if (tree == NULL)
		return tree;
	tree->left = freeTree(tree->left);
	tree->right = freeTree(tree->right);
	free(tree);
	return NULL;
}

static char *test_countLeaf() {
	Tree tree = NULL;
	FILE *f;
	int i, leafs;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot_leaf(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_countLeaf1.png");
	leafs = countLeaf(tree);
	sd_assert("Problema 1 - Test1 countLeaf picat", leafs == 4);
	tree = freeTree(tree);

	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot_leaf(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_countLeaf2.png");
	leafs = countLeaf(tree);
	sd_assert("Problema 1 - Test2 countLeaf picat", leafs == 5);
	tree = freeTree(tree);
	
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot_leaf(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_countLeaf3.png");
	leafs = countLeaf(tree);
	sd_assert("Problema 1 - Test3 countLeaf picat", leafs == 10);
	tree = freeTree(tree);
	return 0;
}

static char *test_sumTree() {
	Tree tree = NULL;
	FILE *f;
	int i, ok;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_sumTree1.png");
	ok = checkSumTree(tree);
	sd_assert("Problema 2 - Test1 sumTree picat", !ok);
	tree = freeTree(tree);

	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_sumTree2.png");
	ok = checkSumTree(tree);
	sd_assert("Problema 2 - Test2 sumTree picat", !ok);
	tree = freeTree(tree);
	
	tree = initTree(15);
	tree->left = initTree(9);
	tree->right = initTree(6);
	tree->left->right = initTree(8);
	tree->left->left = initTree(1);
	tree->right->left = initTree(2);
	tree->right->right = initTree(4);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_sumTree3.png");
	ok = checkSumTree(tree);
	sd_assert("Problema 2 - Test3 sumTree picat", ok);
	tree = freeTree(tree);
	return 0;
}

static char *test_isCousin() {
	Tree tree = NULL;
	FILE *f;
	int i, ok;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot_values(tree, f, 1, 6, 12);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_isCousin1.png");
	ok = isCousin(tree, 6, 12);
	sd_assert("Problema 3 - Test1 isCousin picat", !ok);
	tree = freeTree(tree);

	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot_values(tree, f, 1, 26, 8);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_isCousin2.png");
	ok = isCousin(tree, 26, 8);
	sd_assert("Problema 3 - Test2 isCousin picat", ok);
	tree = freeTree(tree);
	
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot_values(tree, f, 1, 55, 200);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_isCousin3.png");
	ok = isCousin(tree, 55, 200);
	sd_assert("Problema 3 - Test3 isCousin picat", !ok);

	f = fopen("test.dot", "w");
	bst_print_dot_values(tree, f, 1, 200, 97);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_isCousin4.png");
	ok = isCousin(tree, 200, 97);
	sd_assert("Problema 3 - Test4 isCousin picat", ok);
	tree = freeTree(tree);
	return 0;
}

static char *test_evaluate() {
	Tree tree = NULL;
	FILE *f;
	int i, result;

	tree = parse("(7+((5+(8*3))-2))");
	result = evaluate(tree);
	f = fopen("test.dot", "w");
	bst_print_dot_expr(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_exprTree1.png");
	sd_assert("Problema 4 - Test1 expression tree picat", result == 34);
	tree = freeTree(tree);

	tree = parse("(15+(100-((7+((5+(8*3))-2))*2)))");
	result = evaluate(tree);
	f = fopen("test.dot", "w");
	bst_print_dot_expr(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_exprTree2.png");
	sd_assert("Problema 4 - Test2 expression tree picat", result == 47);
	tree = freeTree(tree);

	tree = parse("((((((5+6)*7)+9)*10)/2)+(7*(2*(4*(10-(7+(1*(2-1))))))))");
	result = evaluate(tree);
	f = fopen("test.dot", "w");
	bst_print_dot_expr(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_exprTree3.png");
	sd_assert("Problema 4 - Test3 expression tree picat", result == 542);
	tree = freeTree(tree);

	tree = parse("(((5+(7-(2*(3+(9-(7+(8+(5*2))))))))+(5*(((2+2)*(3+7))+(7*(9-(4+7))))))/2)");
	result = evaluate(tree);
	f = fopen("test.dot", "w");
	bst_print_dot_expr(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_exprTree4.png");
	sd_assert("Problema 4 - Test4 expression tree picat", result == 84);
	tree = freeTree(tree);
	
	return 0;
}

static char *all_tests() {
	sd_run_test(test_countLeaf, 1);
	sd_run_test(test_sumTree, 2);
	sd_run_test(test_isCousin, 3);
	sd_run_test(test_evaluate, 4);
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
	return result != 0;
}

#include "huffman.h"

int treeNode_compare(const void* a_pointer, const void* b_pointer) {
	TreeNode a, b;
	a = *(TreeNode*) a_pointer;
	b = *(TreeNode*) b_pointer;
	if (a->frequency > b->frequency) {
		return -1;
	} else if (a->frequency < b->frequency) {
		return 1;
	} else {
		return 0;
	}
}

TreeNode initHuffman(double frequency,
					 unsigned char value,
					 TreeNode left,
					 TreeNode right) {
	//TODO 1
	return NULL;
}

TreeNode createHuffmanTree(char *text) {
	//TODO 2
	return NULL;
}

char *compress(TreeNode huffman, char *text) {
	//TODO 3
	return NULL;
}

char *decompress(TreeNode huffman, char *text) {
	//TODO 4
	return NULL;
}

TreeNode freeTree(TreeNode root) {
	//TODO 5
	return NULL;
}
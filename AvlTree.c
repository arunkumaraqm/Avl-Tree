// Avl Tree using self referential structures

#include <stdio.h>
#include <stdlib.h>

struct Node;
typedef struct Node* NodePointer;

// Macro to free any pointer and assign it to NULL
#define free_and_null(ptr){\
				           \
		free(ptr);         \
		ptr = NULL;        \
}

struct Node{

	int value;
	NodePointer parent, left, right;
	short int balance;
	int height;
};

typedef struct Tree{

	NodePointer root;
}Tree;

// Should be called after creating a Tree object
void constructor(Tree* tree){

	tree->root = NULL;
}

// Should be called when Tree object is not used anymore
// Frees memory occupied by every node
void destructor(Tree* tree){

	//TODO
}

// Returns the address of a newly created node
NodePointer create_node(int value, 
						NodePointer parent){

	NodePointer new_node = malloc(sizeof *new_node);
	new_node->value = value;
	new_node->parent = parent;
	new_node->left = new_node->right = NULL;
	new_node->balance = 0;
	new_node->height = 0;
	return new_node;
}

// Representation of a node
void repr_node(NodePointer node){

	printf("[%d, %p, %p, %p, %d, %d]\n", 
		     node->value, node->parent, node->left, node->right, node->balance, node->height);
}

// Driver function
void main(){

	Tree* tree = malloc(sizeof *tree);
	constructor(tree);

	tree->root = create_node(50, NULL);
	repr_node(tree->root);
	
	destructor(tree);
	free_and_null(tree);
}


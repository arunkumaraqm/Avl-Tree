// Avl Tree using self referential structures

#include <stdio.h>
#include <stdlib.h>


struct Node; // A forward declaration
typedef struct Node* NodePointer;

// Macro to free any pointer and assign it to NULL
#define free_and_null(ptr){        \
				   \
		free(ptr);         \
		ptr = NULL;        \
}

struct Node{

	int value;
	NodePointer parent, left, right; //parent might be redundant
	short int balance;
	int height; // height might be redundant
};

typedef struct Tree{

	NodePointer root;
}Tree;

// Should be called after creating a Tree object
void constructor(Tree* tree){ // Modifies root node

	tree->root = NULL;
}


// Representation of a node
void repr_node(NodePointer node){ // Temparory function

	printf("[%d, %p, %p, %p, %d, %d]\n", 
		     node->value, node->parent, node->left, node->right, node->balance, node->height);
}

// This function does not kill a parent, but kills the children. 
// If the children are dead, the parent is no longer a parent.
// So, the parent is killed after the function returns.
void recursive_destroy_children(NodePointer parent){ // Modifies non-root nodes

	if (parent->left != NULL){

		recursive_destroy_children(parent->left);
		//printf("Killing %d.\n", parent->left->value);//
		free_and_null(parent->left);
	}
	
	if (parent->right != NULL){

		recursive_destroy_children(parent->right);
		//printf("Killing %d.\n", parent->right->value);//
		free_and_null(parent->right);
	}
}

// Should be called when Tree object is not used anymore
// Frees memory occupied by every node
void destructor(Tree* tree){ // Modifies root node

	if (tree->root != NULL){
	
		recursive_destroy_children(tree->root);
		//printf("Killing %d.\n", tree->root->value);//
		free_and_null(tree->root);
	}
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

// Recursive insertion into binary search tree
void insert_into_tree(int value, NodePointer parent){ // Modifies non-root nodes

	// If parent->child is a subtree, then insert into that subtree.
	// Otherwise, parent->child is given the value.
	
	if (value < parent->value){

		if (parent->left == NULL){

			parent->left = create_node(value, parent);
		}
		else{

			insert_into_tree(value, parent->left);
		}
	}

	else{

		if (parent->right == NULL){

			parent->right = create_node(value, parent);
		}
		else{

			insert_into_tree(value, parent->right);
		}
	}
}

void read_tree(Tree* tree){ // Modifies root node

	int value; char choice;

	// Read the root node first
	{
		scanf("%d %c", &value, &choice);
		tree->root = create_node(value, NULL);
	}

	// If choice is yes, read more elements
	while(choice == 'y' || choice == 'Y'){

		scanf("%d %c", &value, &choice);
		insert_into_tree(value, tree->root);
	}
}

// Printing with tabspaces
void recursive_print_node(NodePointer parent, int noof_tabs){

// parent->value
//     parent->left->value
//         parent->left->...->value
//             						... Null
//         parent->right->...->value
//             						... Null
//     parent->right->value
//         parent->right->...->value
//             						... Null
//         parent->right->...->value
//             						... Null

	for (int i = 0; i < noof_tabs; printf("    "), ++i);

	if (parent == NULL){

		printf("Null\n");
		return;
	}

	printf("%d\n", parent->value);
	recursive_print_node(parent->left, noof_tabs + 1);
	recursive_print_node(parent->right, noof_tabs + 1);
}

void print_tree(Tree *tree){

	recursive_print_node(tree->root, 0); // 0 - no indentation in output for root node
}

// Driver function
void main(){

	Tree* tree = malloc(sizeof *tree);
	constructor(tree);

	read_tree(tree);
	print_tree(tree);
	
	destructor(tree);
	free_and_null(tree);
}


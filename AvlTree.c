// Avl Tree using self referential structures

#include <stdio.h>
#include <stdlib.h>
#include "AvlTree.h"

//https://github.com/amitbansal7/value-Structures-and-Algorithms/blob/master/8.AVL-tree/AVLTree.c


//***********************************************
// CONSTRUCTOR AND DESTRUCTOR

// Should be called after creating a Tree object
void constructor(Tree* tree){ // Modifies root node

	tree->root = NULL;
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

//***********************************************
// DISPLAY FUNCTIONALITY

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

//***********************************************
// ROTATION FUNCTIONS

// Pass in the old root of the subtree
// Returns the new root of the subtree

NodePointer rotate_left(NodePointer node){

	NodePointer other = node->right;
	node->right = other->left;
	other->left = node;
	
	node->height = max(height(node->left), height(node->right)) + 1;
	other->height = max(height(other->left), height(other->right)) + 1;
	
	return other; 
}

NodePointer rotate_right(NodePointer node){

	NodePointer other = node->left;
	node->left = other->right;
	other->right = node;
	
	node->height = max(height(node->left), height(node->right)) + 1;
	other->height = max(height(other->left), height(other->right)) + 1;
	
	return other; 
}

NodePointer rotate_left_right(NodePointer node){

	node->left = rotate_left(node->left);
	return rotate_right(node);
}

NodePointer rotate_right_left(NodePointer node){

	node->right = rotate_right(node->right);
	return rotate_left(node);
}

//***********************************************
// INSERTION FUNCTIONALITY

// Returns the address of a newly created node
NodePointer create_node(int value){

	NodePointer new_node = malloc(sizeof *new_node);
	new_node->value = value;
	new_node->left = new_node->right = NULL;
	new_node->height = 1;
	return new_node;
}

// Recursive insertion into binary search tree
void insert_into_tree(int value, NodePointer parent){ // Modifies non-root nodes

	// If parent->child is a subtree, then insert into that subtree.
	// Otherwise, parent->child is given the value.
	
	if (value < parent->value){

		if (parent->left == NULL){

			parent->left = create_node(value);
		}
		else{

			insert_into_tree(value, parent->left);
		}
	}

	else{

		if (parent->right == NULL){

			parent->right = create_node(value);
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
		tree->root = create_node(value);
	}

	// If choice is yes, read more elements
	while(choice == 'y' || choice == 'Y'){

		scanf("%d %c", &value, &choice);
		insert_into_tree(value, tree->root);
	}
}

//***********************************************
// DELETION FUNCTIONALITY

// Returns parent of minimum element
NodePointer get_parent_of_minimum(NodePointer parent){

	if (parent->left->left){
		return get_parent_of_minimum(parent->left);
	}
	else{
		return parent;
	}
}

NodePointer delete_node(NodePointer root, int item){ // Modifies non-root nodes and returns modified root
	
	// Empty subtree
	if (root == NULL)
		return NULL;

	if (item < root->value)
		root->left = delete_node(root->left, item);

	else if (item > root->value)
		root->right = delete_node(root->right, item);

	else{

		if (root->right == NULL){
			
			// Node to be deleted is a leaf
			if (root->left == NULL){
			
				free(root);
				root = NULL;
				return NULL;
			}
			
			// Node to be deleted has only left child
			else{
				NodePointer temp = root->left;
				root = root->left;
				free(temp);
			}
		}
		
		// Node to be deleted has only right child
		else if (root->left == NULL){
	
			{
				NodePointer temp = root->right;
				root = root->right;
				free(temp);
			}
		}

		// Node to be deleted has both children
		else
		{
			// The minimum value is copied onto 
			NodePointer temp = get_parent_of_minimum(root->right);
			root->value = temp->value;
			root->right = delete_node(root->right, temp->value);
		}
	}
	
	root->height = 1 + max(height(root->left), height(root->right));

	int balance = calc_balance(root);

	//Left Left Case
	if (balance > 1){
		
		if (calc_balance(root->left) < 0)
			return rotate_left_right(root);
		else
			return rotate_right(root);
	}
	
	else if (balance < -1){
		
		if (calc_balance(root->right) > 0)
			return rotate_right_left(root);
		else
			return rotate_left(root);
	}
	
	return root;
}

void delete_from_tree(TreePointer tree, int item){

	tree->root = delete_node(tree->root, item);
}

//***********************************************
// MAIN

void main(){

	Tree* tree = malloc(sizeof *tree);
	constructor(tree);

	read_tree(tree);
	print_tree(tree);
	
	destructor(tree);
	free_and_null(tree);
}

//***********************************************

#include <stdio.h>
#include <stdlib.h> // for malloc

struct Node; // Forward declaration
typedef struct Node* NodePointer;

struct Node{

	int data;
	NodePointer left;
	NodePointer right;
};

// struct Tree contains the root of the tree. 
// It's just here to make passing to functions much easier.
typedef struct Tree{

	NodePointer root;
} Tree;

typedef Tree* TreePointer;

// Macro to free the pointer and then assign it to NULL
#define free_and_null(ptr){\
			   \
	free(ptr); \
	ptr = NULL;\
}\

// Called after a TreePointer is delared.
void constructor(TreePointer tree){ // Modifies tree.root

	tree->root = NULL;
}

// Recursive function to free memory
void destroy_children(NodePointer parent){ // Modifies non-root nodes

	if (parent->left){
	
		destroy_children(parent->left);
		free_and_null(parent->left);
	}
	
	if (parent->right){
	
		destroy_children(parent->right);
		free_and_null(parent->right);
	}
}

// Called when a TreePointer is no longer needed
void destructor(TreePointer tree){ // Modifies tree.root

	if (tree->root){
	
		destroy_children(tree->root);
		free_and_null(tree->root);
	}
}

// Returns newly created Node
NodePointer create(int data){

	NodePointer new_node = malloc(sizeof *new_node);
	new_node->left = new_node->right = NULL;
	new_node->data = data; 
}

// Inserting an element into the tree
void recursive_insert(NodePointer parent, int element){ // Modifies non-root nodes

	if (element < parent->data){
	
		if (parent->left){
		
			recursive_insert(parent->left, element);
		}
		else{
		
			parent->left = create(element);
		}
	}
	
	else{
	
		if (parent->right){
		
			recursive_insert(parent->right, element);
		}
		else{
		
			parent->right = create(element);
		}
	}
}

// Inserting an element into a tree
void insert_into_tree(TreePointer tree, int element){ // Modifies tree.root in one of the cases

	if (tree->root){
	
		recursive_insert(tree->root, element);
	}
	else{
	
		tree->root = create(element);
	}
}

//TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO

// 1. a recursive function to find the item in the tree. Do NOT call any kind of delete function from within it.
// Maybe, return the address of the parent's child pointer to the delete_from_tree function
// Eg: If the item to be deleted is found at root->left->right->left, 
// then return &(root->left->right->left)
// Again, this is just an idea. If you have a better design, go for it.
// I have implemented this function myself - scroll to the bottom.
// However, it hasn't been tested / debugged

// 2. a function to delete any node in the tree given its address (derived from the address of the parent's child pointer)
// You can follow the standard algorithm for deletion from a tree

// 3. int delete_from_tree(TreePointer tree, int item)
// This function should be able to delete root node if the item is found in the root.
// Otherwise it calls the find function [1] and then the delete any node function [2]
// If the item is not found, return 0

//TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO

// Tabbed display
void recursive_display(NodePointer parent, int noof_tabs){

	for (int i = 0; i < noof_tabs; ++i){
	
		printf("\t");
	}
	
	if (parent){
	
		printf("%d\n", parent->data);
		recursive_display(parent->left, noof_tabs + 1);
		recursive_display(parent->right, noof_tabs + 1);
	}
	
	else{
	
		printf("NULL\n");
	}
}

void display_tree(Tree tree){ //Note: Tree is passed by value

	recursive_display(tree.root, 0);
}

void recursive_preorder(NodePointer parent){

	if (parent){
		
		printf("%d ", parent->data);
		recursive_preorder(parent->left);
		recursive_preorder(parent->right);
	}
}

void recursive_inorder(NodePointer parent){

	if (parent){
		
		recursive_inorder(parent->left);
		printf("%d ", parent->data);
		recursive_inorder(parent->right);
	}
}

void recursive_postorder(NodePointer parent){

	if (parent){
		
		recursive_postorder(parent->left);
		recursive_postorder(parent->right);
		printf("%d ", parent->data);
	}
}

void preorder_traversal(Tree tree){

	recursive_preorder(tree.root);
	printf("\n");
}

void inorder_traversal(Tree tree){

	recursive_inorder(tree.root);
	printf("\n");
}

void postorder_traversal(Tree tree){

	recursive_postorder(tree.root);
	printf("\n");
}

// The menu
void main(){

	Tree tree;
	constructor(&tree);

	int choice;
	do{
	
		scanf("%d", &choice);
		
	switch(choice){
	
		case 1: {int element;
			    scanf("%d", &element); 
			    insert_into_tree(&tree, element); 
			    break;} // Shows a compilation error without braces - not entirely sure why
			    
		case 2: {int item;
			    scanf("%d", &item); 
			    if (delete_from_tree(&tree, item) == 0){
			    	
			    	printf("Not Found.\n");
			    } 
			    break;}
		
		case 3: preorder_traversal(tree); break;
		
		case 4: inorder_traversal(tree); break;
		
		case 5: postorder_traversal(tree); break;
		
		case 6: display_tree(tree); break;

		default: choice = 0;
	}
	
	} while (choice);
	
	destructor(&tree);
}


/* Abandoned Approach - You can modify these functions if you want
// Merges the two trees. New root will be one
void merge_trees(NodePointer one, NodePointer two){

	//This is a bad idea.
}

NodePointer* recursive_find(NodePointer parent, int item){

	if (item < parent->data){

		if (parent->left == NULL) return NULL;
		
		if (item == parent->left->data){
		
			return &(parent->left);
		}
		
		else{
		
			return recursive_find(parent->left);
		}
	}
	
	else{

		if (parent->right == NULL) return NULL;
		
		if (item == parent->right->data){
		
			return &(parent->right);
		}
		
		else{
		
			return recursive_find(parent->right);
		}
	}
}

int delete_from_tree(TreePointer tree, int item){

	if (tree->root){
	
	//TODO: case when tree->root->data is item
	
		address_of_parents_child_pointer = recursive_find(tree->root, item);
			
		if (address_of_parents_child_pointer == NULL){
				
			return 0;
		}	
			
		else{
				
			NodePointer node = *address_of_parents_child_pointer;
			merge(node->left, node->right);
			*address_of_parents_child_pointer = node->left;
			free_and_null(node);
		}
	}
	else{
	
		return 0;
	}
}*/


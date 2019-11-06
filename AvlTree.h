
//***********************************************
// MACROS

// Macro to free any pointer and assign it to NULL
#define free_and_null(ptr){\
				           \
		free(ptr);         \
		ptr = NULL;        \
}

#define max(one, two) (one > two)? one: two

#define height(node) (node == NULL)? 0: node->height

#define calc_balance(parent) (parent == NULL)? 0: height(parent->left) - height(parent->right)

//***********************************************
// STRUCTURES

struct Node; // A forward declaration
typedef struct Node* NodePointer;

struct Node{

	int value;
	NodePointer left, right; 
	int height; 
};

typedef struct Tree{

	NodePointer root;
}Tree;

typedef Tree* TreePointer;

//***********************************************


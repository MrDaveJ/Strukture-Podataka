#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ALOC -1
#define FOP -2

typedef struct Tree* Position;

typedef struct Tree {
	int value;
	Position left;
	Position right;
}Tree;


Position addLeaf(Position, int);                 //Function adds a leaf to the tree
Position clearValue(Position, int);              //Function deletes a leaf of a certain value
Position FindMin(Position);                      //Function find the minimum valued leaf from the tree
int inorder(Position);                           //Function writes the whole tree to console inorder
int preorder(Position);                          //Function writes the whole tree to console preorder
int postorder(Position);						 //Function writes the whole tree to console postorder
Position freeTree(Position);                     //Function deletes the whole tree
Position insert(Position);                       //Function that inserts 10 randomly generated numbers to the tree
int replace(Position);                           //Function that replaces the tree with the sum of it's children
int writeToFile(Position);                       //Function that writes the entire tree to a file
int fileInorder(Position, FILE*);                //Function that is used by 'writeToFile' so that the tree can be writen inorder

int main() {
	srand(time(NULL));
	Position tree = NULL;

	tree = insert(tree);
	writeToFile(tree);

	inorder(tree);
	printf(" - INORDER\n");
	preorder(tree);
	printf(" - PREORDER\n");
	postorder(tree);
	printf(" - POSTORDER\n");

	replace(tree);
	writeToFile(tree);

	printf("\nAfter replace:\n");
	inorder(tree);
	printf(" - INORDER\n");
	preorder(tree);
	printf(" - PREORDER\n");
	postorder(tree);
	printf(" - POSTORDER\n");

	freeTree(tree);
	return 0;
}

Position addLeaf(Position root, int value) {
	Position newLeaf;
	if (root == NULL) {                                //If the current position is NULL, create a new leaf
		newLeaf = (Position)malloc(sizeof(Tree));
		if (!newLeaf) {
			printf("Allocation Error!");
			return ALOC;
		}

		newLeaf->value = value;
		newLeaf->left = NULL;
		newLeaf->right = NULL;
		return newLeaf;
	}

	else {                                                //If there is a root already
		if (root->value > value) {                        //If the inputed value is lower than the root value, go left
			root->left = addLeaf(root->left, value);
		}

		if (root->value <= value) {                      //If the inputed value is higher or equal than the root value, go right
			root->right = addLeaf(root->right, value);
		}
	}


	return root;
}

Position clearValue(Position root, int value) {
	if (root == NULL) {
		return NULL;
	}

	else if (root->value > value) {
		root->left = clearValue(root->left, value);
	}

	else if (root->value < value) {
		root->right = clearValue(root->right, value);
	}

	else if (root->left != NULL && root->right != NULL) {    //Found the value and it has two children
		Position temp = FindMin(root->right);                //Find the lowest value child from the right branch and set it as the new root of the subtree
		root->value = temp->value;
		root->right = clearValue(root->right, temp->value);
	}

	else {                                                  //Found the value and it has 0-1 children
		Position temp = root;
		if (root->left == NULL) {
			root = root->right;
		}
		else
			root = root->left;

		free(temp);
	}



	return root;
}

Position FindMin(Position root) {
	if (root == NULL){
		return NULL;
	}
	else if (root->left == NULL) {           //If the element doesnt have a left child, return the element
		return root;                    
	}

	return FindMin(root->left);
}

int inorder(Position root) {
	if (root == NULL) {
		return 0;
	}

	inorder(root->left);                           //Print all children from the left
	printf("%d ", root->value);                    //Print the current element
	inorder(root->right);                          //Print all children from the right
	return 0;
}

int preorder(Position root) {
	if (root == NULL) {
		return 0;
	}

	printf("%d ", root->value);                 //Print the current element
	preorder(root->left);                       //Print all children from the left
	preorder(root->right);                      //Print all children from the right
	return 0;
}

int postorder(Position root) {
	if (root == NULL) {
		return 0;
	}

	postorder(root->left);                     //Print all children from the left
	postorder(root->right);                    //Print all children from the right 
	printf("%d ", root->value);                //Print the current element
	return 0;
}

Position freeTree(Position root) { //Frees the tree using postorder logic
	if (root != NULL) {
		freeTree(root->left);
		root->left = NULL;
		freeTree(root->right);
		root->right = NULL;
		free(root);
	}
	return NULL;
}

Position insert(Position root) {
	for (int i = 0; i < 10; i++) {
		int num = rand() % (99 - 10 + 1) + 10;           //Generate a random number from 10 to 99
		root = addLeaf(root, num);
	}
	return root;
}

int replace(Position root) {
	int sum = 0;
	int old_value;
	if (root == NULL) {
		return 0;
	}

	old_value = root->value;           //Storing the current value
	sum += replace(root->left);        //Finding the sum of the left child
	sum += replace(root->right);       //Finding the sum of the right child
	root->value = sum;                 //Set the current value to the sum of children

	return old_value + sum;           //Return current value and the sum of both children
}

int writeToFile(Position root) {
	FILE *f = fopen("tree.txt", "a");         //Opening file, appending so that it can store both insert and replace trees
	if (!f) {
		printf("File failed to open!");
		return FOP;
	}

	fileInorder(root, f); // Inorder to not open the same file multiple times I needed to create a new function that goes through the tree inorder and writes it to the file
	fprintf(f, "\n");

	fclose(f);                              //Closing the file
	return 0;
}

int fileInorder(Position root, FILE* f) {           //Same logic as printing to console inorder
	if (root == NULL) {
		return 0;
	}

	fileInorder(root->left, f);
	fprintf(f, "%d ", root->value);
	fileInorder(root->right, f);
	return 0;
}
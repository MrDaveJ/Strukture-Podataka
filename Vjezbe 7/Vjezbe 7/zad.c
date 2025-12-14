#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALOC -1

typedef struct Directory* Position;

typedef struct Directory {
	char name[10];
	Position parent;
	Position next;
	Position nextChild;
}Directory;

int mkdir(Position, char*);          //Creates a directory at the current position
int clearTree(Position);             //Deletes the entire tree
int tree(Position, int);             //Writes the entire tree
int dir(Position);                   //Writes all the subdirectories from the current position
Position cdBack(Position, Position); //Returns to the previous position
Position cd(Position, char*);        //Moves to a subdirectory (requires name of directory)
void menu();                         //Main Menu for the user

int main() {
	int x;
	char name[10];
	Directory head;
	head.parent = NULL;
	head.next = NULL;
	head.nextChild = NULL;

	mkdir(&head, "ROOT");
	Position current = head.nextChild;

	do {
		menu();
		printf("\n%s\n\n", current->name);
		scanf("%d", &x);
		switch (x) {
			case 1:
				printf("Enter dir name: \n");
				scanf(" %s", name);
				mkdir(current, name);
				break;
			case 2:
				printf("Enter dir name: \n");
				scanf(" %s", name);
				current = cd(current, name);
				break;
			case 3:
				current = cdBack(&head, current);
				break;
			case 4:
				dir(current);
				break;
			case 5:
				tree(head.nextChild, 0);
				break;
			case 6:
				printf("Exiting...");
				break;
			default:
				break;
		}
	} while (x != 6);
	clearTree(head.nextChild);

	return 0;
}

int mkdir(Position head, char* name) {
	Position q;

	q = (Position)malloc(sizeof(Directory));        //Allocation of memmory
	if (!q) {
		return ALOC;
	}

	strcpy(q->name, name);
	q->parent = head;
	q->nextChild = NULL;

	if (head->nextChild == NULL) {                //Checking if there is already a child, if not the inputed child is the first child
		q->next = head->nextChild;
		head->nextChild = q;
	}
	else {                                       //If there is a child, add the inputed directory at the end of the list
		Position p = head->nextChild;
		while (p->next != NULL) {
			p = p->next;
		}

		q->next = p->next;
		p->next = q;
	}

	return 0;
}

int clearTree(Position head) {
	if (head == NULL)                 //Check if everything is cleared
		return 0;

	clearTree(head->nextChild);      //Clear all subdirectories
	head->nextChild = NULL;
	clearTree(head->next);           //Clear all "brother" directories
	head->next = NULL;
	free(head);                      //Clear the directory

	return 0;
}

int tree(Position head, int level) {
	if (head == NULL)
		return;

	for (int i = 0; i < level; i++) {             //Checking the depth
		printf("|   ");
	}

	printf("%s\n", head->name);                   //Writing the parent

	tree(head->nextChild, level + 1);             //Writing the children, increases the depth
	tree(head->next, level);                      //Writing the "brother" directories

	return 0;
}

int dir(Position head) {
	Position child = head->nextChild;
	printf("%s:\n", head->name);               //Writing the parent 
	while (child != NULL) {                    //Writing all the children of the parent dir
		printf("%s\t", child->name);
		child = child->next;
	}
	return 0;
}

Position cdBack(Position root, Position head) {
	if (head->parent != root) {                    //Checking if the parent is the root dir
		return head->parent;
	}
	return root;
}

Position cd(Position head, char* name) {
	Position p = head->nextChild;           
	if (p != NULL) {
		if (strcmp(p->name, name) == 0) {        //Checking if there is a directory with the inputed name
			return p;
		}
		p = p->next;
	}
	printf("No directory of that name !\n");
	return head;
}

void menu() {
	printf("\n--- Main Menu---\n");
	printf("1 - mkdir\n");
	printf("2 - cd <name>\n");
	printf("3 - cd ..\n");
	printf("4 - dir\n");
	printf("5 - tree\n");
	printf("6 - exit\n");
	printf("\n");
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALOC -1                            // Define allocation error number

typedef struct person* pos;                // Define position pointer
typedef struct person {                    // Define structure
	char name[20];
	char surname[20];
	int year;
	pos next;
}person;

int ui();                                  //User interface for the program (waits for user input)
person input();                            //Function returns the person inputed by the user
int inputStart(char*, char*, int, pos);    //Adds the inputed user at the start of the list
int inputEnd(char*, char*, int, pos);      //Adds the inputed user at the end of the list
void write(pos);                           //Writes the list 
pos search(char*, pos);                    //Function that searches for a person by their surnamme
pos searchPrev(char*, pos);                //Function that searches for a person before the inputed person
int clear(char*, pos);                     //Clears a person from the list by searching their surname



int main() {

	person head;
	person temp;
	int x;

	head.next = NULL;

	do {
		x = ui();
		switch (x) {

		case 1:

			temp = input();
			inputStart(temp.name, temp.surname, temp.year, &head);
			break;

		case 2:

			temp = input();

			inputEnd(temp.name, temp.surname, temp.year, &head);
			break;

		case 3:

			printf("Enter the surname: \n");
			scanf(" %s", temp.surname);

			pos p = search(temp.surname, &head);

			if (p != NULL)
				printf("Address: %p\n", p);
			else
				printf("Person not found.\n");
			break;

		case 4:

			printf("Enter the surname: \n");
			scanf(" %s", temp.surname);

			clear(temp.surname, &head);
			break;

		case 5:

			write(head.next);
			break;

		default:

			break;
		}
	} while (x != 0);

	printf("\nGoodbye!\n");

	return 0;
}

int ui() {

	int x;

	printf("\n-----Main Menu-----\n\n");        
	printf("0) End program\n");
	printf("1) Add to start\n");
	printf("2) Add to end\n");
	printf("3) Search by surname\n");
	printf("4) Clear\n");
	printf("5) Write list\n");

	scanf("%d", &x);
	printf("\n");

	return x;
}

person input() {
	person temp;

	printf("Enter the name: \n");
	scanf(" %s", temp.name);
	printf("Enter the surname: \n");
	scanf(" %s", temp.surname);
	printf("Enter the year of birth: \n");
	scanf("%d", &temp.year);

	return temp;
}

int inputStart(char *name, char *prez, int god, pos p) {

	pos q;
	q = (person*)malloc(sizeof(person));
	if (q == NULL) {                                               //Checking if the program allocated the memmory succesfully
		printf("Allocation error!");
		return ALOC;
	}

	strcpy(q->name, name);
	strcpy(q->surname, prez);
	q->year = god;
	q->next = p->next;
	p->next = q;

	return 0;
}

void write(pos p) {
	printf("\n");
	while (p != NULL) {
		printf("%s %s: %d\n", p->name, p->surname, p->year);         //Printing on to the console
		p = p->next;                                                 //Moving to the next person in the list
	}
}

int inputEnd(char* name, char* surname, int year, pos p) {
	pos q;

	while (p->next != NULL) {                                         //Shifting the p pointer to the end of the list
		p = p->next;                                                  
	}

	q = (person*)malloc(sizeof(person));
	if (q == NULL) {
		printf("Allocation error!");
		return ALOC;
	}

	strcpy(q->name, name);
	strcpy(q->surname, surname);
	q->year = year;
	q->next = p->next;
	p->next = q;

	return 0;
}

pos search(char* surname, pos p) {
	while (p != NULL && strcmp(p->surname, surname) != 0) {               //Shifting the poiter to the wanted postition
		p = p->next;
	}
	return p;
}

pos searchPrev(char* surname, pos p) {
	while (p->next != NULL && strcmp(p->next->surname, surname) != 0) {
		p = p->next;
	}
	if (p->next == NULL) {
		return NULL;
	}
	return p;
}

int clear(char* surname, pos p) {
	pos temp;
	p = searchPrev(surname, p);
	if (p != NULL) {                     
		temp = p->next;                                         
		p->next = temp->next;                       //The object before the soon-to-be deleted object has the adress of the next object in line
		free(temp);                                 //Removing the wanted person
	}
	return 0;
}

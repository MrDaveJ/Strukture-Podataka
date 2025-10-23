#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALOC -1                                 //Define allocation error number
#define FOP -2                                  //Define file opening error

typedef struct person* pos;                     //Define position pointer
typedef struct person {                         //Define structure
	char name[20];
	char surname[20];
	int year;
	pos next;
}person;

int ui();                                       //User interface for the program (waits for user input)
person input();                                 //Function returns the person inputed by the user

int inputStart(char*, char*, int, pos);         //Adds the inputed person at the start of the list
int inputEnd(char*, char*, int, pos);           //Adds the inputed person at the end of the list
int inputBack(char*, char*, int, char*, pos);   //Adds the inputed person behind the wanted person in the list
int inputFront(char*, char*, int, char*, pos);  //Adds the inputed person in front the wanted person in the list

pos search(char*, pos);                         //Function that searches for a person by their surnamme
pos searchPrev(char*, pos);                     //Function that searches for a person before the inputed person

void swapData(pos, pos);                        //Swaps the data between two nodes
int sortList(pos);                              //Sorts the whole list using bubble sort

void write(pos);                                //Writes the list 
int writeToFile(pos);                           //Function that stores the list into a text file

int clear(char*, pos);                          //Clears a person from the list by searching their surname
int clearAll(pos);                              //Function that clears the whole list

int readFile(pos);                              //Function that reads the file and adds the people into the current list




int main() {

	person head;
	person temp, target;
	int x;

	head.next = NULL;
	do {
		x = ui();
		switch (x) {

		case 1:

			temp = input();
			inputStart(temp.name, temp.surname, temp.year, &head);
			printf("\nTask done!\n");
			break;

		case 2:

			temp = input();

			inputEnd(temp.name, temp.surname, temp.year, &head);
			printf("\nTask done!\n");
			break;

		case 3:
			
			temp = input();
			printf("\nEnter the surname: \n");
			scanf(" %s", target.surname);
			inputFront(temp.name, temp.surname, temp.year, target.surname, &head);
			break;

		case 4:

			temp = input();
			printf("\nEnter the surname: \n");
			scanf(" %s", target.surname);
			inputBack(temp.name, temp.surname, temp.year, target.surname, &head);
			break;

		case 5:

			printf("Enter the surname: \n");
			scanf(" %s", temp.surname);

			pos p = search(temp.surname, &head);

			if (p != NULL)
				printf("Address: %p\n", p);
			else
				printf("Person not found.\n");
			break;

		case 6:

			printf("Enter the surname: \n");
			scanf(" %s", temp.surname);

			clear(temp.surname, &head);
			printf("\nTask done!\n");
			break;

		case 7:

			clearAll(&head);
			printf("Task done!\n");
			break;

		case 8:

			write(head.next);
			break;

		case 9:

			writeToFile(head.next);
			printf("Task done!\n");
			break;

		case 10:

			readFile(&head);
			printf("Task done!\n");
			break;

		case 11:

			sortList(head.next);
			printf("Task done!\n");
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
	printf("3) Add in front of person\n");
	printf("4) Add in behind of person\n");
	printf("5) Search by surname\n");
	printf("6) Clear by surname\n");
	printf("7) Clear list\n");
	printf("8) Write list\n");
	printf("9) Write to file\n");
	printf("10) Read file\n");
	printf("11) Sort list\n\n");

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

int inputStart(char* name, char* surname, int year, pos p) {

	pos q;
	q = (person*)malloc(sizeof(person));
	if (q == NULL) {                                               //Checking if the program allocated the memmory succesfully
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

int inputBack(char* name, char* surname, int year, char* target, pos p) {
	pos q;
	p = search(target, p);

	q = (person*)malloc(sizeof(person));
	if (q == NULL) {                                               //Checking if the program allocated the memmory succesfully
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

int inputFront(char* name, char* surname, int year, char* target, pos p) {
	pos q;
	p = searchPrev(target, p);

	q = (person*)malloc(sizeof(person));
	if (q == NULL) {                                               //Checking if the program allocated the memory succesfully
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
	return p;                                                             //Returning the adress of the wanted person
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

void swapData(pos p, pos q) {
	person temp;
	temp.next == NULL;

	strcpy(temp.surname, p->surname);             //Swapping the surnames
	strcpy(p->surname, q->surname);
	strcpy(q->surname, temp.surname);

	strcpy(temp.name, p->name);                   //Swapping the first names
	strcpy(p->name, q->name);
	strcpy(q->name, temp.name);

	temp.year = p->year;                          //Swapping the years
	p->year = q->year;
	q->year = temp.year;
}

int sortList(pos p) {
	int cmp, flag;
	pos q;

	if (p == NULL) {
		return 0;
	}

	do {
		flag = 0;
		q = p;

		while (q->next != NULL) {
			cmp = strcmp(q->surname, q->next->surname);
			if (cmp > 0 || (cmp == 0 && strcmp(q->surname, q->next->surname) > 0)) {          //Comparing the surnames
				swapData(q, q->next);
				flag = 1;
			}
			q = q->next;
		}
	} while (flag);
	return 0;
}

void write(pos p) {
	printf("\n");
	while (p != NULL) {
		printf("%s %s: %d\n", p->name, p->surname, p->year);         //Printing on to the console
		p = p->next;                                                 //Moving to the next person in the list
	}
}

int writeToFile(pos p) {
	FILE* f = fopen("people.txt", "w");                 //Opening the file
	if (f == NULL) {                                    //Checking if the file opened successfully
		printf("Error while opening file!");
		return FOP;
	}

	while (p != NULL) {
		fprintf(f, "%s %s %d\n", p->name, p->surname, p->year);        //Writing to file
		p = p->next;
	}

	fclose(f);                                        //Closing the file
	return 0;
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

int clearAll(pos p) {
	pos temp;
	while (p->next != NULL) {
		temp = p->next;
		p->next = temp->next;
		free(temp);                                      //Removing the person from the list
	}
	return 0;
}

int readFile(pos p) {
	person temp;
	FILE* f = fopen("people.txt", "r");
	if (f == NULL) {
		printf("Error while opening file!");
		return FOP;
	}

	while (!feof(f)) {
		fscanf(f, "%s %s %d\n", temp.name, temp.surname, &temp.year);       //Reading the people from the file
		inputEnd(temp.name, temp.surname, temp.year, p);                    //Adding the people from the file to the end of the list
	}

	fclose(f);
	return 0;
}

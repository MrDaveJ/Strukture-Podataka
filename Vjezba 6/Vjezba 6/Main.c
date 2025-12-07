#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Date.h"
#include "Product.h"
#include "Bill.h"


int ui();             //User interface (graphic console)
int menu(PositionB);  //Main Menu with which the user can interact with via console

int main() {
	Bill head;
	head.nextBill = NULL;
	head.nextProduct = NULL;

	menu(&head);
	clearAllBills(&head);

	return 0;
}

int ui() {

	int x;

	printf("\n-----Main Menu-----\n\n");
	printf("0) End Program\n");
	printf("1) Read Bills\n");
	printf("2) Write Bills\n");
	printf("3) Search Products Within Time Frame\n");
	printf("4) Merge Same Date Bill\n");
	printf("5) Find Most Sold Product Within Time Frame\n");
	printf("6) All Sold Products Within Time Frame\n");
	scanf("%d", &x);
	printf("\n");

	return x;
}

int menu(PositionB head) {
	int x;
	char name[20];
	Date date1, date2;
	do {
		x = ui();
		switch (x) {
		case 1:
			readBills(head);
			break;
		case 2:
			writeBills(head);
			break;
		case 3:
			printf("Enter product name: \n");
			scanf("%s", name);
			printf("\nStart date: \n");
			date1 = input();
			printf("\nEnd date: \n");
			date2 = input();
			searchProductDates(head, name, date1, date2);
			break;
		case 4:
			printf("Enter date: \n");
			date1 = input();		
			mergeSameDateBill(head, date1);
			break;
		case 5:
			printf("\nStart date: \n");
			date1 = input();
			printf("\nEnd date: \n");
			date2 = input();
			mostSoldProduct(head, date1, date2);
			break;
		case 6:
			printf("\nStart date: \n");
			date1 = input();
			printf("\nEnd date: \n");
			date2 = input();
			everySold(head, date1, date2);
			break;
		default:
			break;
		}
	} while (x != 0);
	printf("Goodbye!");

	return 0;
}



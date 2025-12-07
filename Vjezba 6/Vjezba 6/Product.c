#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Product.h"
#include "Bill.h"
#include "Date.h"


int addProduct(PositionB p, char* s, int num, double price) {
	PositionA current = p->nextProduct;
	PositionA prev = NULL;
	PositionA q;
	while (current != NULL && strcmp(current->name, s) < 0) {          //Checking the name of the product for sorted input
		prev = current;
		current = current->next;
	}

	if (current != NULL && strcmp(current->name, s) == 0) {            //If there are two same products within the same bill... add them together
		current->num += num;
		return 0;
	}

	q = (PositionA)malloc(sizeof(Product));
	if (!q) {
		printf("File allocation error");
		return ALOC;
	}

	if (prev == NULL) {
		p->nextProduct = q;
	}
	else
		prev->next = q;

	strcpy(q->name, s);
	q->num = num;
	q->price = price;
	q->next = current;

	return 0;
}

PositionA searchProduct(PositionB head, char* s){
	PositionA q = head->nextProduct;
	while (q != NULL && strcmp(q->name, s) != 0) {         //Searching for the product with the same name
		q = q->next;
	}
	return q;
}

PositionA findProduct(PositionA head, char* s) {                 //Used for searching same named products between different bills
	while (head != NULL && strcmp(head->name, s) != 0) {         //Searching for the product with the same name
		head = head->next;
	}
	return head;
}

int searchProductDates(PositionB head, char* name, Date from, Date to) {
	PositionA prod = NULL;
	PositionB bill = head->nextBill;
	double sum = 0;
	int num = 0;

	while (bill != NULL) {                         //Searching for all the products within a given time frame that have the same name as the inputed product
		if (compareDate(&bill->dat, &from) >= 0 && compareDate(&bill->dat, &to) <= 0) {
			if (prod = searchProduct(bill, name)) {
				num += prod->num;
				sum += prod->num * prod->price;
			}
		}
		bill = bill->nextBill;
	}

	if (num == 0) {
		printf("\nNo products within the time frame!\n");
	}
	else {
		printf("\nTime Frame: %d.%d.%d - %d.%d.%d\n", from.day, from.mon, from.year, to.day, to.mon, to.year);
		printf("Product: %s\nAmount: %d\nTotal price: %.2lf\n", name, num, sum);
	}

	return 0;
}

double writeProducts(PositionB head) {          //Writing all the products and returning the total cost of the bill
	PositionA curr = head->nextProduct;
	double sum = 0;
	printf("\n");
	for (int i = 0; i < 40; i++) {
		printf("-");
	}
	while (curr != NULL) {
		printf("\n%s\t%dx\t%.2lf\t\t%.2lf", curr->name, curr->num, curr->price, curr->num * curr->price);
		sum += curr->num * curr->price;
		curr = curr->next;
	}
	return sum;
}

int mostSoldProduct(PositionB head, Date from, Date to) {
	Product prod;
	prod.next = NULL;
	PositionA products = &prod;                     //Head element of the linked list with all the products
	PositionB bill = head->nextBill;

	while (bill != NULL) {                         //Searching for all the products within a given time frame
		if (compareDate(&bill->dat, &from) >= 0 && compareDate(&bill->dat, &to) <= 0) {
			PositionA p = bill->nextProduct;

			while (p != NULL) {		
				PositionA temp = findProduct(products, p->name);

				if (temp) {                                        //If Product is already in the list add the amount
					temp->num += p->num;
				}
				else {                                            //If it isn't add it to the list
					PositionA new = malloc(sizeof(Product));
					if (!new) {
						printf("File allocation error");
						return ALOC;
					}

					strcpy(new->name, p->name);
					new->num = p->num;
					new->price = p->price;
					new->next = products->next;
					products->next = new;
				}
				p = p->next;                                      //Move to the next product
			}
		}
		bill = bill->nextBill;                                    //Move to the next bill
	}

	if (products->next == NULL) {                                 //Check if there are any products
		printf("\nNo products within the time frame!\n");
		return 0;
	}
	
	PositionA max = products->next;                               //Find the product with the highest amount of purchases
	PositionA check = max->next;
	while (check != NULL) {
		if (max->num < check->num) {
			max = check;
		}
		check = check->next;
	}


	printf("\nMost sold product:\nProduct: %s\tAmount: %d\n", max->name, max->num);

	while (products->next != NULL) {                            //Clear the temporary list
		PositionA clear = products->next;
		products->next = clear->next;
		free(clear);
	}
	return 0;
}

int everySold(PositionB head, Date from, Date to) {
	Product prod;
	prod.next = NULL;
	PositionA products = &prod;                     //Head element of the linked list with all the products
	PositionB bill = head->nextBill;

	while (bill != NULL) {                         //Searching for all the products within a given time frame
		if (compareDate(&bill->dat, &from) >= 0 && compareDate(&bill->dat, &to) <= 0) {
			PositionA p = bill->nextProduct;

			while (p != NULL) {
				PositionA temp = findProduct(products, p->name);

				if (temp) {                                        //If Product is already in the list add the amount
					temp->num += p->num;
				}
				else {                                            //If it isn't add it to the list
					PositionA new = malloc(sizeof(Product));
					if (!new) {
						printf("File allocation error");
						return ALOC;
					}

					strcpy(new->name, p->name);
					new->num = p->num;
					new->price = p->price;
					new->next = products->next;
					products->next = new;
				}
				p = p->next;                                      //Move to the next product
			}
		}
		bill = bill->nextBill;                                    //Move to the next bill
	}

	if (products->next == NULL) {                                 //Check if there are any products
		printf("\nNo products within the time frame!\n");
		return 0;
	}

	PositionA curr = products->next;                             //Writing every sold product and total value
	double sum = 0;
	printf("\n");
	while (curr != NULL) {
		printf("\n%s\t%dx\t%.2lf\t\t%.2lf", curr->name, curr->num, curr->price, curr->num * curr->price);
		sum += curr->num * curr->price;
		curr = curr->next;
	}

	printf("\nTotal:\t\t\t\t%.2lf\n", sum);

	while (products->next != NULL) {                            //Clear the temporary list
		PositionA clear = products->next;
		products->next = clear->next;
		free(clear);
	}
	return 0;
}
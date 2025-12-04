#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Product.h"
#include "Bill.h"


int addProduct(PositionB p, char* s, int num, double price) {
	PositionA current = p->nextProduct;
	PositionA prev = NULL;
	PositionA q;
	while (current != NULL && strcmp(current->name, s) < 0) {
		prev = current;
		current = current->next;
	}

	if (current != NULL && strcmp(current->name, s) == 0) {
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

int writeProducts(PositionB head) {
	PositionA curr = head->nextProduct;
	printf("\n");
	for (int i = 0; i < 20; i++) {
		printf("-");
	}
	while (curr != NULL) {
		printf("\n%s %d %.2lf", curr->name, curr->num, curr->price);
		curr = curr->next;
	}
	printf("\n");
	return 0;
}
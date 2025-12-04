#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H
#define ALOC -2
#include <stdio.h>

typedef struct Product* PositionA;

typedef struct Product {
	char name[20];
	int num;
	double price;
	PositionA next;
}Product;

struct Bill;  
typedef struct Bill* PositionB;

int addProduct(PositionB, char*, int, double);
int writeProducts(PositionB);

#endif
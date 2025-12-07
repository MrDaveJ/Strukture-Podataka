#pragma once

#include <stdio.h>
#include "Date.h"

#ifndef PRODUCT_H
#define PRODUCT_H
#define ALOC -2


typedef struct Product* PositionA;

typedef struct Product {
	char name[20];
	int num;
	double price;
	PositionA next;
}Product; //Defining the structure
                                        //All comments describing the functions are in Product.c

struct Bill;  
typedef struct Bill* PositionB;

int addProduct(PositionB, char*, int, double);
PositionA searchProduct(PositionB, char*);
int searchProductDates(PositionB, char*, Date, Date);
double writeProducts(PositionB);
int mostSoldProduct(PositionB, Date, Date);
int everySold(PositionB, Date, Date);
#endif
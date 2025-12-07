#pragma once

#include "Date.h"
#include "Product.h"

#ifndef BILL_H
#define BILL_H
#define FOP -1

typedef struct Bill* PositionB;

typedef struct Bill {
    Date dat;
    PositionB nextBill;
    PositionA nextProduct;
} Bill;                    //Defining the structure
                                                      //All comments describing the functions are in Bill.c

int addBill(PositionB, char*);
int readBill(PositionB, char*);
int readBills(PositionB);
int writeBills(PositionB);
int clearBill(PositionB);
int clearAllBills(PositionB);
int mergeSameDateBill(PositionB, Date);

#endif

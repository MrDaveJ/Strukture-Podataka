#pragma once
#ifndef BILL_H
#define BILL_H
#include "Date.h"
#include "Product.h"
#define FOP -1

typedef struct Bill* PositionB;

typedef struct Bill {
    Date dat;
    PositionB nextBill;
    PositionA nextProduct;
} Bill;

int addBill(PositionB, char*);
int readBill(PositionB, char*);
int readBills(PositionB);
int writeBills(PositionB);
int clearBill(PositionB);
int clearAllBills(PositionB);

#endif

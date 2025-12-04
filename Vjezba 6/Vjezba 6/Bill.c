#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Bill.h"
#include "Date.h"
#include "Product.h"

int readBill(PositionB head, char* path) {
    char name[20];
    int num;
    double price;
    Date dat;
    FILE* f = fopen(path, "r");
    if (!f) {
        printf("File opening error!");
        return FOP;
    }

    if (fscanf(f, "%d-%d-%d", &dat.year, &dat.mon, &dat.day) == 3) {
        head->dat = dat;
        while (fscanf(f, "%s %d %lf", name, &num, &price) == 3) {
            addProduct(head, name, num, price);
        }
    }

    fclose(f);
    return 0;
}

int addBill(PositionB head, char* path) {
    PositionB newBill;
    newBill = (PositionB)malloc(sizeof(Bill));

    newBill->nextProduct = NULL;
    newBill->nextBill = NULL;

    readBill(newBill, path);

    PositionB current = head->nextBill;
    PositionB prev = head;

    while (current != NULL && compareDate(&current->dat, &newBill->dat) < 0) {
        prev = current;
        current = current->nextBill;
    }

    newBill->nextBill = current;
    prev->nextBill = newBill;

    return 0;


}

int readBills(PositionB head) {
    char path[256];
    FILE* f = fopen("racuni.txt", "r");
    if (!f) {
        printf("File opening error!\n");
        return FOP;
    }

    while (fscanf(f, "%s", path) == 1) {
        addBill(head, path);
    }

    fclose(f);
    return 0;
}

int writeBills(PositionB head) {
    PositionB temp = head;
    while (temp->nextBill != NULL) {
        temp = temp->nextBill;
        printf("\nBill: %d.%d.%d", temp->dat.day, temp->dat.mon, temp->dat.year);
        writeProducts(temp);
    }
    return 0;
}

int clearBill(PositionB p)
{
    PositionA q = p->nextProduct;
    PositionA temp;

    while (q != NULL) {
        temp = q;
        p->nextProduct = temp->next;
        q = q->next;
        temp->next = NULL;
        free(temp);
    }

    return 0;
}

int clearAllBills(PositionB p) {
    PositionB q = p->nextBill;
    PositionB temp;

    while (q != NULL) {
        temp = q;
        clearBill(q);
        p->nextBill = temp->nextBill;
        q = q->nextBill;
        temp->nextBill = NULL;
        free(temp);
    }
    return 0;
}

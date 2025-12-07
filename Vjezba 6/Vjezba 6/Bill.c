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
    FILE* f = fopen(path, "r");             //Opening the given file
    if (!f) {
        printf("File opening error!");
        return FOP;
    }

    if (fscanf(f, "%d-%d-%d", &dat.year, &dat.mon, &dat.day) == 3) {            //Scanning the date inside the file
        head->dat = dat;                                                        //Connecting the date to the bill
        while (fscanf(f, "%s %d %lf", name, &num, &price) == 3) {               //Reading the product from the file
            addProduct(head, name, num, price);                                 //Adding the product to the linked list
        }
    }

    fclose(f);                            //Closing the given file
    return 0;
}

int addBill(PositionB head, char* path) {
    PositionB newBill;
    newBill = (PositionB)malloc(sizeof(Bill));

    newBill->nextProduct = NULL;
    newBill->nextBill = NULL;

    readBill(newBill, path);            //Reading the bill and adding all the products associated with that bill

    PositionB current = head->nextBill;
    PositionB prev = head;

    while (current != NULL && compareDate(&current->dat, &newBill->dat) < 0) {    //Checking if the date of the next date for sorted input
        prev = current;
        current = current->nextBill;
    }

    newBill->nextBill = current;
    prev->nextBill = newBill;

    return 0;


}

int readBills(PositionB head) {
    char path[256];
    FILE* f = fopen("racuni.txt", "r");          //Opening the "main" file with all the other file names
    if (!f) {
        printf("File opening error!\n");
        return FOP;
    }

    while (fscanf(f, "%s", path) == 1) {
        addBill(head, path);                    //Adding the bill and sending the name of the read file name
    }

    fclose(f);                                 //Closing the bill
    return 0;
}

int writeBills(PositionB head) {
    PositionB temp = head;
    while (temp->nextBill != NULL) {
        temp = temp->nextBill;
        printf("\nBill: %d.%d.%d", temp->dat.day, temp->dat.mon, temp->dat.year);                 //Writing the bill with all the products
        printf("\nTotal:\t\t\t\t%.2lf\n", writeProducts(temp));
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
        free(temp);                             //Clearing the bill and all of the products associated with bill
    }

    return 0;
}

int clearAllBills(PositionB p) {
    PositionB q = p->nextBill;
    PositionB temp;

    while (q != NULL) {                 //Removing all the bills 
        temp = q;                    
        clearBill(q);
        p->nextBill = temp->nextBill;
        q = q->nextBill;
        temp->nextBill = NULL;
        free(temp);
    }
    return 0;
}

int mergeSameDateBill(PositionB head, Date dat) {
    PositionB current = head->nextBill;

    while (current != NULL && current->nextBill != NULL) {
        if (compareDate(&current->dat, &current->nextBill->dat) == 0 && compareDate(&current->dat, &dat) == 0) { //Checking if there are two bills with the same date and if the date is the same as the inputed one
            PositionA p = current->nextBill->nextProduct;

            while (p != NULL) {                                             //Adding all the products from one bill to another
                addProduct(current, p->name, p->num, p->price);
                p = p->next;
            }

            PositionB temp = current->nextBill;                           //Freeing the products and the bill while also reconnecting the links 
            current->nextBill = temp->nextBill;
            temp->nextBill = NULL;
            clearBill(temp);
            free(temp);
        }
        else
            current = current->nextBill;
    }
    return 0;
}

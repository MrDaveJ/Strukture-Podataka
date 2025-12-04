#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Date.h"
#include "Product.h"
#include "Bill.h"

int main() {
	Bill head;
	head.nextBill = NULL;
	head.nextProduct = NULL;

	readBills(&head);
	writeBills(&head);
	clearAllBills(&head);

	return 0;
}

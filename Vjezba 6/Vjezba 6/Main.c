#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FOP -1
#define ALOC -2


typedef struct Date {
	int day;
	int mon;
	int year;
}Date;

typedef struct Artikl* PositionA;

typedef struct Artikl{
	char name[20];
	int kol;
	double price;
	PositionA next;
}Artikl;

typedef struct Bill* PositionB;

typedef struct Bill{
	Date dat;
	PositionB nextBill;
	PositionA nextArtikl;
}Bill;


int compareDate(Date*, Date*);
int clearBill(PositionB);
int clearAllBills(PositionB);
int addArtikl(PositionB, char*, int, double);
int readBill(PositionB, char*);
int readBills(PositionB);
int addBill(PositionB, char*);
int writeArtikl(PositionB);
int writeBills(PositionB);



int main() {
	Bill head;
	head.nextBill = NULL;
	head.nextArtikl = NULL;

	readBills(&head);
	writeBills(&head);
	clearAllBills(&head);

	return 0;
}



int compareDate(Date *dat1, Date *dat2) {
	if (dat1->year != dat2->year) {
		return dat1->year - dat2->year;
	}
	if (dat1->mon != dat2->mon) {
		return dat1->mon - dat2->mon;
	}
	return dat1->day - dat2->day;
}
int clearBill(PositionB p)
{
	PositionA q = p->nextArtikl;
	PositionA temp;

	while (q != NULL) {
		temp = q;
		p->nextArtikl = temp->next;
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
int addArtikl(PositionB p, char* s, int kol, double price) {
	PositionA current = p->nextArtikl;
	PositionA prev = NULL;
	PositionA q;
	while (current != NULL && strcmp(current->name, s) < 0) {
		prev = current;
		current = current->next;
	}

	if (current != NULL && strcmp(current->name, s) == 0) {
		current->kol += kol;
		return 0;
	}

	q = (PositionA)malloc(sizeof(Artikl));
	if (!q) {
		printf("File allocation error");
		return ALOC;
	}

	if (prev == NULL) {
		p->nextArtikl = q;
	}
	else
		prev->next = q;

	strcpy(q->name, s);
	q->kol = kol;
	q->price = price;
	q->next = current;

	return 0;
}
int readBill(PositionB head, char* path) {
	char name[20];
	int kol;
	double price;
	Date dat;
	FILE* f = fopen(path, "r");
	if (!f) {
		printf("File opening error!");
		return FOP;
	}

	if (fscanf(f, "%d-%d-%d", &dat.year, &dat.mon, &dat.day) == 3) {
		head->dat = dat;
		while (fscanf(f, "%s %d %lf", name, &kol, &price) == 3) {
			addArtikl(head, name, kol, price);
		}
	}

	fclose(f);
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
int addBill(PositionB head, char* path) {
	PositionB newBill;
	newBill = (PositionB)malloc(sizeof(Bill));

	newBill->nextArtikl = NULL;
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
int writeArtikl(PositionB head) {
	PositionA curr = head->nextArtikl;
	printf("\n");
	for (int i = 0; i < 20; i++) {
		printf("-");
	}
	while (curr != NULL) {
		printf("\n%s %d %.2lf", curr->name, curr->kol, curr->price);
		curr = curr->next;
	}
	printf("\n");
	return 0;
}
int writeBills(PositionB head) {
	PositionB temp = head;
	while (temp->nextBill != NULL) {
		temp = temp->nextBill;
		printf("\nBill: %d.%d.%d", temp->dat.day, temp->dat.mon, temp->dat.year);
		writeArtikl(temp);
	}
	return 0;
}
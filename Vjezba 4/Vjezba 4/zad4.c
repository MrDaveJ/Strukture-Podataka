#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define ALOC -1
#define FOP -2

typedef struct poly* position;
typedef struct poly {
	int coef;
	int pow;
	position next;
}poly;



int sortAdd(position, int, int);                  //Function that inputs a monomial to the list (sorted)
int clearAll(position);                           //Function that clears the whole list
int writePoly(position);                          //Function that writes the polynomial
int readPolys(position, position);                //Function that reads the polynomials from the list and adds them to their respected lists
int sumPoly(position, position, position);        //Function that returns the sum of the 2 polynomials
int multiPoly(position, position, position);      //Function that returns the multiplication of the 2 polynomials

int main() {
	poly p1, p2, sum, mult;
	p1.next = NULL;
	p2.next = NULL;
	sum.next = NULL;
	mult.next = NULL;

	readPolys(&p1, &p2);
	writePoly(&p1);
	writePoly(&p2);

	printf("\nSum of two polynomials: \n");
	sumPoly(&sum, &p1, &p2);
	writePoly(&sum);

	printf("\nMultiplication of two polynomials: \n");
	multiPoly(&mult, &p1, &p2);
	writePoly(&mult);

	clearAll(&p1);
	clearAll(&p2);
	clearAll(&sum);
	clearAll(&mult);
	return 0;
}

int sortAdd(position p, int coef, int pow) {
	position temp;

	while (p->next != NULL && p->next->pow > pow) {   //Searching for a position where the power of the inputed monomial is lower than the monomial within the list
		p = p->next;
	}

	if (p->next != NULL && p->next->pow == pow) {      //If there are two monomials with the same power within the polynomial, add them together
		p->next->coef += coef;
		if (p->next->coef == 0) {                      //If the sum equals zero remove the monomial
			temp = p->next;
			p->next = temp->next;
			free(temp);
		}
		return 0;
	}

	temp = (position)malloc(sizeof(poly));
	if (temp == NULL) {
		return ALOC;
	}
	temp->coef = coef;
	temp->pow = pow;
	temp->next = p->next;
	p->next = temp;
	return 0;
}

int clearAll(position p) {
	position temp;
	while (p->next != NULL) {          //Remove elements until head points to NULL
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
	return 0;
}

int writePoly(position p) {
	position q = p->next;
	printf("%dx^%d", q->coef, q->pow);      //Writing the first monomial within the polynomial in the correct format
	while (q->next != NULL) {               //Writing the rest of the polynomial
		q = q->next;
		printf(" + %dx^%d", q->coef, q->pow);
	}
	printf("\n");
	return 0;
}

int readPolys(position p1, position p2) {
	int coef, pow;
	int c;
	FILE* f = fopen("poly.txt", "r");       //Opening the file
	if (f == NULL) {		                //Checking if the file has opened correctly
		return FOP;
	}

	while (1) {
		c = fgetc(f);
		if (c == '\n' || c == EOF)        //Checking if the buffer is at the end of the file or line 
			break;
		ungetc(c, f);                     //If the character was not '\n' or EOF return the character from the buffer
		fscanf(f, "%d %d", &coef, &pow);
		sortAdd(p1, coef, pow);
	}

	while (1) {
		c = fgetc(f);
		if (c == '\n' || c == EOF)
			break;
		ungetc(c, f);
		fscanf(f, "%d %d", &coef, &pow);
		sortAdd(p2, coef, pow);
	}

	fclose(f);                           //Closing the file
	return 0;
}

int sumPoly(position sum, position p1, position p2) {
	int coef, pow;

	position a = p1->next;
	position b = p2->next;

	while (a != NULL && b != NULL) {
		if (a->pow == b->pow) {                  //If two elements have the same power, add their coefficients 
			coef = a->coef + b->coef;
			sortAdd(sum, coef, a->pow);
			a = a->next;
			b = b->next;
		}

		else if (a->pow > b->pow) {             //If the element from poly a has a bigger power then element from poly b
			sortAdd(sum, a->coef, a->pow);
			a = a->next;
		}


		else {                                  //If the element from poly b has a bigger power then element from poly a
			sortAdd(sum, b->coef, b->pow);
			b = b->next;
		}

	}

	while (a != NULL) {                         //Adding the rest of the elements from poly a
		sortAdd(sum, a->coef, a->pow);
		a = a->next;
	}

	while (b != NULL) {                        //Adding the rest of the elements from poly b
		sortAdd(sum, b->coef, b->pow);
		b = b->next;
	}

	return 0;
}

int multiPoly(position mult, position p1, position p2) {
	int coef, pow;

	position a = p1->next;
	position b;

	while (a != NULL) {
		b = p2->next;                           //Set the pointer to the beginning of poly b
		while (b != NULL) {
			coef = a->coef * b->coef;           //Multiply the coefficients
			pow = a->pow + b->pow;              //Add the powers
			sortAdd(mult, coef, pow);
			b = b->next;                        //Move to the next element from poly b
		}
		a = a->next;                            //Move to the next element from poly a
	}
	return 0;
}
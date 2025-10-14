#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 60                                             // Definiranje maksimalnog broja bodova na ispitu


typedef struct stud {                                                    // Stvaranje strukture 
	char ime[20];
	char prez[20];
	int bod;
	float rel;
}stud;


int count();                                            //Funkcija vraca broj linija u dokumentu tj. broj studenata
stud* load(stud*, int);                                     // Funkcija ucitava studente iz dokumenta u strukturu
void write(stud*, int);                                                // Funkcija ispisuje studente


int main() {

	int br;
	stud *s;

	br = count();
	printf("\t\t%d studenata\n\n", br);

	s = (stud*)malloc(sizeof(stud) * br);                              // Dinamicko alociranje memorije
	if (s == NULL) {
		printf("Greska pri alociranju");
		return -2;
	}

	load(s, br);
	write(s, br);

	free(s);
	return 0;
}



int count() {

	int br = 0;
	FILE* f = fopen("studenti.txt", "r");
	if (f == NULL) {
		printf("Greska pri otvaranju!");
		return -1;
	}

	while (!feof(f)) { 
		char ch = fgetc(f);
		if (ch == '\n')                             // Provjera za znak '\n' koja oznacava kraj linije u txt dokumentu
			br++;
	}

	fclose(f);
	return br;
}

stud* load(stud* s, int br) {

	int i;
	FILE* f = fopen("studenti.txt", "r"); 
	if (f == NULL) {
		printf("Greska pri otvaranju!");
		return -1;
	}

	for (i = 0; i < br; i++) {                                            // Ucitavanje studenata 
		fscanf(f, " %s %s %d", s[i].ime, s[i].prez, &s[i].bod);
		s[i].rel = ((float)s[i].bod / MAX) * 100;
	}

	fclose(f);
	return s;
}

void write(stud* s, int br) {
	int i;
	for (i = 0; i < br; i++) {
		printf("\t%s %s: %d bodova -> %.2f%% \n", s[i].ime, s[i].prez, s[i].bod, s[i].rel);
	}
}
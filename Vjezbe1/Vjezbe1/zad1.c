#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 60

typedef struct stud {
	char ime[20];
	char prez[20];
	int bod;
	float rel;
}stud;

int count(FILE *f)  //Funkcija vraca broj linija u dokumentu
{
	int br = 0;

	if (f == NULL)
		return 0;

	while (!feof(f)) {
		char ch = fgetc(f);
		if (ch == '\n')
			br++;
	}
	rewind(f);
	return br;
}


int main() {

	int br, i;
	FILE* fp = fopen("studenti.txt", "r");
	stud *s;

	br = count(fp);
	printf("%d studenata\n\n", br);

	s = (stud*)malloc(sizeof(stud) * br);

	for (i = 0; i < br; i++) {
		fscanf(fp, " %s %s %d", s[i].ime, s[i].prez, &s[i].bod);
		s[i].rel = ((float)s[i].bod / MAX) * 100;
	}

	for (i = 0; i < br; i++) {
		printf("\t%s %s: %d bodova -> %.2f%% \n", s[i].ime, s[i].prez, s[i].bod, s[i].rel);
	}

	free(s);
	fclose(fp);
	return 0;
}
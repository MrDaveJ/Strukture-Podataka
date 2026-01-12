#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALOC -1
#define FOP -2


//                                                                              10.a)
/*
typedef struct Country* PositionCountry;
typedef struct City* PositionCity;

typedef struct Country {
	char name[30];
	PositionCountry nextCountry;
	PositionCity nextCity;
}Country;


typedef struct City {
	char name[30];
	int population;
	PositionCity left;
	PositionCity right;
}City;

int addCountry(PositionCountry, char*); //Adds a country to the linked list
int clearCountries(PositionCountry);  //Cleares the linked list
int printCountries(PositionCountry);  //Writes the entire linked list with all of the trees
PositionCity addCity(PositionCity, char*, int); //Adds a city to the tree
PositionCity clearCities(PositionCity); //Cleares the entire tree
int printCities(PositionCity); //Writes all the entire tree
PositionCountry findCountry(PositionCountry, char*); //Find a country with the inputed name
int readFile(PositionCountry); //Reads the file and adds the countries and the cities
int printCountryCity(PositionCountry head, char* name, int pop); //Searches for the country and prints the cities with population equal or higher than inputed
int printCityPopulation(PositionCountry con, int pop); //Prints all the cities in a country with population equal or highr than inputed

int main() {
	Country head;
	char name[30];
	int pop;
	head.nextCountry = NULL;
	head.nextCity = NULL;

	readFile(&head);
	printCountries(&head);
	
	printf("\nInput name of country: \n");
	scanf("%s", name);
	printf("Input population: \n");
	scanf(" %d", &pop);
	printCountryCity(&head, name, pop);

	clearCountries(&head);

	return 0;
}

int addCountry(PositionCountry head, char* name) {
	PositionCountry q;

	while (head->nextCountry != NULL && strcmp(head->nextCountry->name, name) < 0) {  //Moving the pointer to a position where the inputed name is alphabetically lower than the next one
		head = head->nextCountry;
	}

	q = (PositionCountry)malloc(sizeof(Country));                         //Allocation of the inputed country
	if (!q) {
		printf("Country Allocation Error!");
		return ALOC;
	}

	strcpy(q->name, name);
	q->nextCountry = head->nextCountry;
	head->nextCountry = q;
	q->nextCity = NULL;

	return 0;
}
int clearCountries(PositionCountry head) {
	PositionCountry curr = head->nextCountry;
	PositionCountry temp;
	while (curr != NULL) {               //Deleting the list from the first node to the last node
		temp = curr;
		curr = curr->nextCountry;

		temp->nextCity = clearCities(temp->nextCity);
		free(temp);
	}

	head->nextCountry = NULL;
	return 0;
}
int printCountries(PositionCountry head) {
	PositionCountry curr = head->nextCountry;
	while (curr != NULL) {
		printf("%s: \n", curr->name);
		printCities(curr->nextCity);
		curr = curr->nextCountry;
	}
	return 0;
}
PositionCity addCity(PositionCity root, char* name, int pop) {
	PositionCity new;
	if (root == NULL) {                                         //Allocation of the leaf
		new = (PositionCity)malloc(sizeof(City));
		if (!new) {
			printf("City Allocation Error!");
			return NULL;
		}

		strcpy(new->name, name);
		new->population = pop;
		new->left = NULL;
		new->right = NULL;
		return new;
	}
	else {
		if (root->population > pop) {                   //If the inputed populationme is lower move left, otherwise move right
			root->left = addCity(root->left, name, pop);
		}
		else {
			root->right = addCity(root->right, name, pop);
		}
	}
	return root;
}
PositionCity clearCities(PositionCity root) {
	if (root != NULL) {                        //Deleting the tree inorder
		clearCities(root->left);
		root->left = NULL;
		clearCities(root->right);
		root->right = NULL;
		free(root);
	}
	return NULL;
}
int printCities(PositionCity root) {
	if (root == NULL) {
		return 0;
	}
	printCities(root->left);           //Writing all the cities from the left
	printf("\t%s %d\n", root->name, root->population);
	printCities(root->right);          //Writing all the cities from the right
	return 0;
}
PositionCountry findCountry(PositionCountry head, char* name) {
	while (head->nextCountry != NULL) {
		if (strcmp(head->nextCountry->name, name) == 0)
			return head->nextCountry;
		head = head->nextCountry;
	}
	return NULL;
}
int readFile(PositionCountry head) {
	char name[30];
	char path[256];
	int pop;
	FILE* f = fopen("drzave.txt", "r");                  //Opening the main file "drzave.txt"
	if (!f) {
		printf("File Opening Error!");
		return FOP;
	}

	while (fscanf(f, "%s %s", name, path) == 2) {           //Scaning the name of the country and the file with all of the cities of the country
		addCountry(head, name);
		PositionCountry temp = findCountry(head, name);    //Finding the position of the inputed country
		FILE* tempf = fopen(path, "r");
		if (!tempf) {
			printf("File Opening Error!");
			return FOP;
		}
		while (fscanf(tempf, "%s %d", name, &pop) == 2) {  //Opening the scanned file and adding the scanned cities
			temp->nextCity = addCity(temp->nextCity, name, pop);
		}
		fclose(tempf);                                     //Closing the file with the cities
	}

	fclose(f);                                             //Closing the file with the countries
	return 0;
}
int printCountryCity(PositionCountry head, char* name, int pop) {
	PositionCountry con = findCountry(head, name);     //Finding the position of the country
	if (!con) {
		printf("Country not found!");
		return 0;
	}

	PositionCity city = con->nextCity;                //Checking if the country tree is empty
	if (!city) {
		printf("No cities in country!");
		return 0;
	}
	printCityPopulation(city, pop);                   //Printing the cities
	return 0;
}
int printCityPopulation(PositionCity root, int pop) {
	if (!root)
		return 0;

	if (root->population >= pop) {                                //If the inputed population is lower than the root, check left branches
		printCityPopulation(root->left, pop);
		printf("\t%s: %d\n", root->name, root->population);
		printCityPopulation(root->right, pop);
	}
	else
		printCityPopulation(root->right, pop);                   //If the inputed population is higher than the root, check and print the right branches

	return 0;
}
*/

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//                                                                             10.b)

typedef struct Country* PositionCountry;
typedef struct City* PositionCity;

typedef struct Country {
	char name[30];
	PositionCountry left;
	PositionCountry right;
	PositionCity nextCity;
}Country;


typedef struct City {
	char name[30];
	int population;
	PositionCity next;
}City;


int addCity(PositionCountry, char*, int); //Adds cities by population to linked list
int clearCities(PositionCountry); //Cleares cities from linked list
int printCountry(PositionCountry); //Printes country and all cities (linked list)
PositionCountry addCountry(PositionCountry, char*); //Adds a country to the tree
PositionCountry clearCountries(PositionCountry); //Cleares the whole tree
int printCountries(PositionCountry); //Prints the whole tree inorder
PositionCountry findCountry(PositionCountry root, char* name); //Finds the country in the tree
PositionCountry readFile(); //Reads the file "drzave.txt" and adds the countries to the tree and connects the linked list to its correct leaf
int printCountryCity(PositionCountry root, char* name, int pop);

int main() {
	PositionCountry root = NULL;
	char name[30];
	int pop;
	root = readFile();
	if (!root) {
		printf("No data!");
	}

	printCountries(root);

	printf("\nInput name of country: \n");
	scanf("%s", name);
	printf("Input population: \n");
	scanf(" %d", &pop);
	printCountryCity(root, name, pop);

	root = clearCountries(root);

	return 0;
}


int addCity(PositionCountry state, char* name, int pop) {
	PositionCity curr = state->nextCity;
	PositionCity prev = NULL;
	PositionCity q;

	while (curr != NULL && pop > curr->population) {          //Moving the pointer to a position where the population of the next city is higher than the inputed population
		prev = curr;
		curr = curr->next;
	}

	q = (PositionCity)malloc(sizeof(City));                  //Allocation of the inputed city
	if (!q) {
		printf("City Allocation Error!");
		return ALOC;
	}

	if (prev == NULL) {                                      //Inputing the first city to the list (connecting the node to the leaf of the tree with the countries)
		state->nextCity = q;
	}
	else {
		prev->next = q;
	}

	strcpy(q->name, name);
	q->population = pop;
	q->next = curr;

	return 0;
}
int clearCities(PositionCountry state) {
	PositionCity curr = state->nextCity;
	PositionCity temp;
	while (curr != NULL) {               //Deleting the list from the first node to the last node
		temp = curr;
		curr = curr->next;
		state->nextCity = curr;
		temp->next = NULL;
		free(temp);
	}
	return 0;
}
int printCountry(PositionCountry state) {
	PositionCity curr = state->nextCity;

	printf("%s: \n", state->name);                 //Printing the name of the country

	while (curr != NULL) {                         //Printing every city of the country
		printf("\t%s: %d\n", curr->name, curr->population);
		curr = curr->next;
	}
	return 0;
}
PositionCountry addCountry(PositionCountry root, char* name) {
	PositionCountry new;
	if (root == NULL) {                                         //Allocation of the leaf
		new = (PositionCountry)malloc(sizeof(Country));
		if (!new) {
			printf("Country Allocation Error!");
			return NULL;
		}

		strcpy(new->name, name);
		new->left = NULL;
		new->right = NULL;
		new->nextCity = NULL;
		return new;
	}
	else {
		if (strcmp(root->name, name) > 0) {                   //If the inputed name is alphabethically lower move left, otherwise move right
			root->left = addCountry(root->left, name);
		}
		else {
			root->right = addCountry(root->right, name);
		}
	}
	return root;
}
PositionCountry clearCountries(PositionCountry root) {
	if (root != NULL) {                        //Deleting the tree inorder
		clearCountries(root->left);
		root->left = NULL;
		clearCountries(root->right);
		root->right = NULL;
		clearCities(root);                     //Deleting all the cities of the leaf
		root->nextCity = NULL;
		free(root);
	}
	return NULL;
}
int printCountries(PositionCountry root) {
	if (root == NULL) {
		return 0;
	}
	printCountries(root->left);           //Writing all the countries from the left
	printCountry(root);                   //Writing all the cities of the current country
	printCountries(root->right);          //Writing all the countries from the right
	return 0;
}
PositionCountry findCountry(PositionCountry root, char* name) {
	while (root != NULL) {                           //Finding the position in the tree where the name is same as the inputed name
		if (strcmp(root->name, name) == 0)
			return root;
		else if (strcmp(root->name, name) > 0)
			root = root->left;
		else
			root = root->right;
	}
	return NULL;
}
PositionCountry readFile() {
	PositionCountry root = NULL;
	char name[30];
	char path[256];
	int pop;
	FILE* f = fopen("drzave.txt", "r");                  //Opening the main file "drzave.txt"
	if (!f) {
		printf("File Opening Error!");
		return FOP;
	}

	while (fscanf(f, "%s %s", name, path) == 2) {           //Scaning the name of the country and the file with all of the cities of the country
		root = addCountry(root, name);
		PositionCountry temp = findCountry(root, name);    //Finding the position of the inputed country
		FILE* tempf = fopen(path, "r");
		if (!tempf) {
			printf("File Opening Error!");
			return FOP;
		}
		while (fscanf(tempf, "%s %d", name, &pop) == 2) {  //Opening the scanned file and adding the scanned cities
			addCity(temp, name, pop);
		}
		fclose(tempf);                                     //Closing the file with the cities
	}

	fclose(f);                                             //Closing the file with the countries
	return root;
}
int printCountryCity(PositionCountry root, char* name, int pop) {
	PositionCountry con = findCountry(root, name);                  //Finding country in tree
	if (!con) {
		printf("Country not found!");
		return 0;
	}

	PositionCity city = con->nextCity;                               //Checking if country has cities
	if (!city) {
		printf("No cities in country!");
		return 0;
	}

	printf("\n");
	while (city != NULL && city->population < pop) {                //Skiping the cities that have population lower than inputed
		city = city->next;
	}
	while (city != NULL && city->population >= pop) {                //Printing the citites that have cities that have population higher or equal than inputed
		printf("\t%s: %d\n", city->name, city->population);
		city = city->next;
	}

	return 0;
}



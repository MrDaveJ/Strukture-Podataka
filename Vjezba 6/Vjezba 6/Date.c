#include "Date.h"

int compareDate(Date* dat1, Date* dat2) {                 //Comparing the two dates 
	if (dat1->year != dat2->year) {                       //Checking if the two years are the same
		return dat1->year - dat2->year;
	}
	if (dat1->mon != dat2->mon) {                         //Checking if the two months are the same
		return dat1->mon - dat2->mon;
	}
	return dat1->day - dat2->day;
}

Date input() {                                     //Function that is used for inputing a date via console 
	Date temp;

	do{
		printf("Enter the day: \n");
		scanf(" %d", &temp.day);
	} while (temp.day > 31 || temp.day < 0);         //Making sure the day is inputed correctly

	do {
		printf("Enter the month: \n");
		scanf(" %d", &temp.mon);
	} while (temp.mon > 12 || temp.mon < 0 );       //Making sure the month is inputed correctly

	do {
		printf("Enter the year: \n");
		scanf(" %d", &temp.year);
	} while (temp.year < 0);                      //Making sure the year is inputed correctly (not negative)

	return temp;
}
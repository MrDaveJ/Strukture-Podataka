#include "Date.h"

int compareDate(Date* dat1, Date* dat2) {
	if (dat1->year != dat2->year) {
		return dat1->year - dat2->year;
	}
	if (dat1->mon != dat2->mon) {
		return dat1->mon - dat2->mon;
	}
	return dat1->day - dat2->day;
}
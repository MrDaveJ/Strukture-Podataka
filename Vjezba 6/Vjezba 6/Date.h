#pragma once
#ifndef DATE_H
#define DATE_H

typedef struct Date {
	int day;
	int mon;
	int year;
}Date;

int compareDate(Date*, Date*);

#endif
#pragma once
#ifndef DATE_H
#define DATE_H

typedef struct Date {
	int day;
	int mon;
	int year;
}Date;  //Defining the structure
                                   //All comments describing the functions are in Date.c

int compareDate(Date*, Date*);
Date input();

#endif
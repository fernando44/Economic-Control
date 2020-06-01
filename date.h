/*
	This library contains a function to return date 
	of splitered and integer form
*/

//Dependencies
#include<time.h>

//Global variables
char Date[11];
char Month[11];
char Year[5];
char DateTimeNow[20];
char Time[10];

//Matrix of months of year
const char MonthsOfYear[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

//Function to get system date
void getDate(){
	
	//Struct for get system date
	struct tm * tm;
	time_t t;
	time(&t);
	tm = localtime(&t);
	
	//Fills global variables
	strftime(Date,11,"%d/%m/%Y", tm);
	strftime(Month,11,"%B",tm);
	strftime(Year,5,"%Y",tm);
	strftime(DateTimeNow,20,"%Y-%m-%d %X",tm);
	strftime(Time,10,"%X",tm);

}


#include<time.h>

/*
	This library contains a function to return date 
	of splitered and integer form
*/

//global strings to get date value
char Date[11];
char Month[11];
char Year[5];

//function to get system date
void getDate(){
	
	//struct for get system date
	struct tm * tm;
	time_t t;
	time(&t);
	tm = localtime(&t);
	
	strftime(Date,11,"%d/%m/%Y", tm);
	strftime(Month,11,"%B",tm);
	strftime(Year,5,"%Y",tm);
}


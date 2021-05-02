/*
 *	This library contains a function to return date 
 *	of splitered and integer form
 */

#ifndef DATETIME_H
#define DATETIME_H

#include <stdlib.h>
#include <time.h>

/* Date time structure  */
typedef struct datetime
{
	struct tm *Date;
	time_t Time_secs;
	struct datetime (*now)(void);
	char *(*fmt_str)(struct datetime item);
} DateTime;

/* Constants of months of year */
enum months_of_year
{
	January = 1,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December,
};

/* Max sizes constants */
enum dims
{
	MAX_DATETIME = 20,
	MAX_DATE = 11,
	MAX_TIME = 10,
	MAX_YEAR = 5,
	MAX_MONTH = 10,
	MAX_DAY = 3
};

DateTime now(void);
int year(DateTime datetime);
char *month(DateTime datetime);
int month_num(DateTime datetime);
int day(DateTime datetime);
char *tm_str(DateTime datetime);
char *dtm_str(DateTime datetime);
DateTime new_dtm();
DateTime new_dtm_ovr(int tm_sec, int tm_min, int tm_hour, int tm_mday, int tm_mon, int tm_year, int tm_wday, int tm_yday, int tm_isdst, time_t time_secs);

#endif
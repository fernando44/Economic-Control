/*
 *  This library contains a function to return date 
 *  of splitered and integer form
 */

#include <stdlib.h>
#include <time.h>
#if defined(_WIN32) || defined(WIN32)
    #include "..\include\date_time.h"
#elif defined(__unix__)
    #include "../include/date_time.h"
#endif

/* Return current datetime */
DateTime now(void)
{
    DateTime dt;
    time(&dt.Time_secs);
    dt.Date = localtime(&dt.Time_secs);
    return dt;
}

/* Return year of datetime */
int year(DateTime datetime)
{
    char year[MAX_YEAR];
    strftime(year, MAX_YEAR, "%Y", datetime.Date);
    return atoi(year);
}

/* Return month name of datetime */
char *month(DateTime datetime)
{
    char *month = (char*)malloc(MAX_MONTH*sizeof(char));
    strftime(month, MAX_MONTH, "%B", datetime.Date);
    month[MAX_MONTH - 1] = '\0';
    return month;
}

/* Return number of month of datetime */
int month_num(DateTime datetime)
{
    char month[MAX_DAY];
    strftime(month, MAX_DAY, "%m", datetime.Date);
    return atoi(month);
}

/* Return day of datetime */
int day(DateTime datetime)
{
    char day[MAX_DAY];
    strftime(day, MAX_DAY, "%d", datetime.Date);
    return atoi(day);
}

/* Return time string of datetime */
char *tm_str(DateTime datetime)
{
    char *curr_t = (char*)malloc(MAX_TIME*sizeof(char));
    strftime(curr_t, MAX_TIME, "%X", datetime.Date);
    curr_t[MAX_TIME - 1] = '\0';
    return curr_t;
}

/* Return datetime string of datetime */
char *dtm_str(DateTime datetime)
{
    char *curr_dt = (char*)malloc(MAX_DATETIME*sizeof(char));
    strftime(curr_dt, MAX_DATETIME, "%Y-%m-%d %X", datetime.Date);
    curr_dt[MAX_DATETIME - 1] = '\0';
    return curr_dt;
}

/* Default datetime constructor */
DateTime new_dtm()
{
    DateTime dtm;
    dtm = now();
    dtm.now = &now;
    dtm.fmt_str = &dtm_str;

    return dtm;
}

/* Overloaded datetime constructor */
DateTime new_dtm_ovr(int tm_sec, int tm_min, int tm_hour, int tm_mday, int tm_mon, int tm_year, int tm_wday, int tm_yday, int tm_isdst, time_t time_secs)
{
    DateTime dtm;
    dtm.Date = (struct tm *)malloc(sizeof(struct tm));

    dtm.Date->tm_sec = tm_sec;                      /* seconds,  range 0 to 59          */
    dtm.Date->tm_min = tm_min;                      /* minutes, range 0 to 59           */
    dtm.Date->tm_hour = tm_hour;                    /* hours, range 0 to 23             */
    dtm.Date->tm_mday = tm_mday;                    /* day of the month, range 1 to 31  */
    dtm.Date->tm_mon = tm_mon-1;                    /* month, range 1 to 12             */
    dtm.Date->tm_year = tm_year-1900;               /* The number of years since 1900   */
    dtm.Date->tm_wday = tm_wday-1;                  /* day of the week, range 1 to 7    */
    dtm.Date->tm_yday = tm_yday;                    /* day in the year, range 0 to 365  */
    dtm.Date->tm_isdst = tm_isdst;                  /* daylight saving time             */	
    dtm.Time_secs = time_secs;                      /* The number of seconds since 1900 */
    dtm.now = &now;
    dtm.fmt_str = &dtm_str;

    return dtm;
}
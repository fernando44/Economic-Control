/*
 *	This library contains a definition of the
 *	data type of the "rec" and methods to
 *	manipulate dinamic lists of him
 *	
 *   Author: Quemuel Alves Nassor
 *   Date: 01/05/21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(WIN32)
    #include "..\include\record.h"
#elif defined(__unix__)
    #include "../include/record.h"
#endif

/* Function to initialize strings */
void init_str(char *string, int length)
{
    int i;
    for (i = length - 1; i > -1; i--)
    {
        string[i] = '\0';
    };
}

/* Function to display record */
void show_rec(rec *item)
{
    printf("          Id: %li\n", item->id);
    printf("          Date: %s\n", item->datetime.fmt_str(item->datetime));
    printf("          Category: %s\n", item->category);
    printf("          Description: %s\n", item->description);
    printf("          Value: %.2Lf\n", item->value);
    printf("          Details: %s\n", item->details);
    printf("----------------------------------------------------------------------------------------------------\n");
}

/* Function to get end of list */
rec *nav_end(rec *list)
{
    rec *end = list;

    while (end != NULL)
    {
        end = list->next;
    }
    return end;
}

/* Function to get start of list */
rec *nav_start(rec *list)
{
    rec *start = list;

    while (start != NULL)
    {
        start = list->prev;
    }
    return start;
}

/* Function to add on start of list */
rec *add_start(rec *list, rec *newItem)
{
    list = nav_start(list);
    newItem->prev = list->prev;
    list->prev = newItem;
    newItem->next = list;
    return newItem;
}

/* Function to add on middle of list */
rec *add_middle(rec *list, rec *newItem)
{
    newItem->next = list->next;
    list->next != NULL ? list->next->prev = newItem : 0;
    newItem->prev = list;
    list->next = newItem;
    return nav_start(list);
}

/* Function to add on end of list */
void add_end(rec *list, rec *newItem)
{
    list = nav_end(list);
    newItem->prev = list;
    newItem->next = list->next;
    list->next = newItem;
}

/* Function to remove record of start of list */
rec *rem_start(rec *list)
{
    list = nav_start(list);
    rec *temp = list->next;
    (temp != NULL) ? (temp->prev = list->prev) : 0;
    free(list);
    return temp;
}

/* Function to remove record of middle of list */
rec *rem_middle(rec *list)
{
    rec *temp = nav_start(list);
    if (list->prev != NULL && list->next != NULL)
    {
        list->prev->next = list->next;
        list->next->prev = list->prev;
        free(list);
    }
    return temp;
}

/* Function to remove record of end of list */
void rem_end(rec *list)
{
    list = nav_end(list);
    (list->prev != NULL) ? (list->prev->next = list->next) : 0;
    free(list);
}

/* Function to remove all record of list */
void clean_list(rec *list)
{
    list = list->prev != NULL ? nav_start(list) : list;

    while (list->next != NULL)
    {
        rem_end(list);
    }
    free(list);
}

/* Default record constructor */
rec *new_rec(void)
{
    rec *emptyRec = (rec *)malloc(sizeof(rec));
    emptyRec->next = NULL;
    emptyRec->prev = NULL;
    emptyRec->datetime = new_dtm();
    init_str(emptyRec->description, MAX_DESCRIPTION);
    init_str(emptyRec->category, MAX_CATEGORY);
    init_str(emptyRec->details, MAX_DETAILS);
    emptyRec->value = 0.00;
    emptyRec->id = 0;
    emptyRec->show = &show_rec;
    emptyRec->add = &add_end;
    return emptyRec;
}

/* Overloaded record constructor */
rec *new_rec_ovr(size_t id, double value, DateTime datetime, char *description, char *category, char *details)
{
    rec *newItem = new_rec();
    newItem->datetime = datetime;
    strncpy(newItem->description, description, MAX_DESCRIPTION);
    strncpy(newItem->category, category, MAX_CATEGORY);
    strncpy(newItem->details, details, MAX_DETAILS);
    newItem->value = value;
    newItem->id = id;
    return newItem;
}

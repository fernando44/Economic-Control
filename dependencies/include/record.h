/*
 *	This library contains a definition of the
 *	data type of the "rec" and methods to
 *	manipulate dinamic lists of him
 *
 *	Author: Quemuel Alves Nassor
 *	Date: 01/05/21
 */

#ifndef RECORD_H
#define RECORD_H

#include <stdio.h>
#include <stdlib.h>
#include "date_time.h"

/* Max sizes constants */
enum sizes
{
	MAX_DESCRIPTION = 100,
	MAX_CATEGORY = 50,
	MAX_DETAILS = 100,
};

/* Record data structure */
typedef struct record
{
	struct record *prev;
	struct record *next;
	size_t id;
	char description[MAX_DESCRIPTION];
	char category[MAX_CATEGORY];
	char details[MAX_DETAILS];
	DateTime datetime;
	long double value;
	void (*add)(struct record *list, struct record *newItem);
	void (*show)(struct record *item);
} rec;

void init_str(char *string, int length);
void show_rec(rec *item);
rec *nav_end(rec *list);
rec *nav_start(rec *list);
rec *add_start(rec *list, rec *newItem);
rec *add_middle(rec *list, rec *newItem);
void add_end(rec *list, rec *newItem);
rec *rem_start(rec *list);
rec *rem_middle(rec *list);
void rem_end(rec *list);
void clean_list(rec *list);
rec *new_rec(void);
rec *new_rec_ovr(size_t id, double value, DateTime datetime, char *description, char *category, char *details);

#endif
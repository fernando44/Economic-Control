/*
	This library contains a definition of the
	data type of the "reg" and methods to 
	manipulate dinamic lists of him
*/

<<<<<<< HEAD

=======
>>>>>>> dev
//Dependencies
#include<stdio.h>
#include<stdlib.h>

//Dinamic data struct for lists
<<<<<<< HEAD
typedef struct dataType{
	struct dataType *ant; 
	struct dataType *prox; 
	char description[100];
	char category[14];	
	char details[100]; 
	char date[11];		
=======
typedef struct regType{
	struct regType *prev; 
	struct regType *next;
	int id; 
	char description[100];
	char category[50];	
	char details[100]; 
	char date[20];		
>>>>>>> dev
	double value;		
}reg;

//Function to initalize strings
void initalizeString(char* String, int Size){
	int i;
	for(i=Size-1;i > -1; i--){										//Scroll the vector from the end to the beginning
		String[i] = '\0';											//Set \0 character in each position
	};
}

<<<<<<< HEAD
//Create an empty reg
reg *newReg(){
    reg *emptyReg = (reg *)malloc(sizeof(reg));						//Allocates *reg size memory
    emptyReg->prox = emptyReg->ant = NULL;							//Initalize poiters with NULL
    initalizateString(emptyReg->date,11);							//Initialize date with \0
    initalizateString(emptyReg->description,100);					//Initialize description with \0
    initalizateString(emptyReg->category,14);						//Initialize category with \0
    initalizateString(emptyReg->details,100);						//Initialize details with \0
    emptyReg->value = 0.00;											//Initialize value with 0.00
=======
//Create an empty register
reg *newReg(){
    reg *emptyReg = (reg *)malloc(sizeof(reg));						//Allocates *reg size memory
    emptyReg->next = emptyReg->prev = NULL;							//Initalize poiters with NULL
    initalizeString(emptyReg->date,20);								//Initialize date with \0
    initalizeString(emptyReg->description,100);						//Initialize description with \0
    initalizeString(emptyReg->category,50);							//Initialize category with \0
    initalizeString(emptyReg->details,100);							//Initialize details with \0
    emptyReg->value = 0.00;											//Initialize value with 0.00
    emptyReg->id = 0;												//Initialize id with 0
>>>>>>> dev
    return emptyReg;
}

//Returns to the end of the list
reg *navEnd(reg *regsList){
<<<<<<< HEAD
	return (regsList->prox != NULL ? navEnd(regsList->prox) : regsList);
=======
	return (regsList->next != NULL ? navEnd(regsList->next) : regsList);
>>>>>>> dev
};

//Returns to the beginning of the list
reg *navStart(reg *regsList){
<<<<<<< HEAD
	return (regsList->ant != NULL ? navStart(regsList->ant) : regsList);
=======
	return (regsList->prev != NULL ? navStart(regsList->prev) : regsList);
>>>>>>> dev
};

//Add a new item at the beginning of the list
reg *addStart(reg *regsList, reg *newItem){
	regsList = navStart(regsList);
<<<<<<< HEAD
	newItem->ant = regsList->ant;
	regsList->ant = newItem;
	newItem->prox = regsList;
=======
	newItem->prev = regsList->prev;
	regsList->prev = newItem;
	newItem->next = regsList;
>>>>>>> dev
	return newItem;
};

//Add a new item at the middle of the list
reg *addMiddle(reg *regsList, reg *newItem){
<<<<<<< HEAD
	newItem->prox = regsList->prox;
	regsList->prox != NULL ? regsList->prox->ant = newItem : 0;
	newItem->ant = regsList;
	regsList->prox = newItem;
=======
	newItem->next = regsList->next;
	regsList->next != NULL ? regsList->next->prev = newItem : 0;
	newItem->prev = regsList;
	regsList->next = newItem;
>>>>>>> dev
	return navStart(regsList);
};

//Add a new item to the end of the list
<<<<<<< HEAD
reg *addEnd(reg *regsList, reg *newItem){
	regsList = navEnd(regsList);
	newItem->ant = regsList;
	newItem->prox = regsList->prox;
	regsList->prox = newItem;
	return navStart(regsList);
=======
void addEnd(reg *regsList, reg *newItem){
	regsList = navEnd(regsList);
	newItem->prev = regsList;
	newItem->next = regsList->next;
	regsList->next = newItem;
>>>>>>> dev
};

//Remove the first item at the beginning of the list
reg *remStart(reg *regsList){
	regsList = navStart(regsList);
<<<<<<< HEAD
	reg *temp = regsList->prox;
	(temp != NULL) ? (temp->ant = regsList->ant) : 0;
=======
	reg *temp = regsList->next;
	(temp != NULL) ? (temp->prev = regsList->prev) : 0;
>>>>>>> dev
	free(regsList);
	return temp;
};

//Remove an item in the middle of the list
reg *remMiddle(reg *regsList){
	reg *temp = navStart(regsList);
<<<<<<< HEAD
	if(regsList->ant != NULL && regsList->prox != NULL){
		regsList->ant->prox = regsList->prox;
		regsList->prox->ant = regsList->ant;
=======
	if(regsList->prev != NULL && regsList->next != NULL){
		regsList->prev->next = regsList->next;
		regsList->next->prev = regsList->prev;
>>>>>>> dev
		free(regsList);
	}
	return temp;
};

//Remove the last item at the end of the list
<<<<<<< HEAD
reg *remEnd(reg *regsList){
	regsList = navEnd(regsList);
	reg *temp = navStart(regsList);
	(regsList->ant != NULL) ? (regsList->ant->prox = regsList->prox) : 0;
	free(regsList);
	return temp;
=======
void remEnd(reg *regsList){
	regsList = navEnd(regsList);
	(regsList->prev != NULL) ? (regsList->prev->next = regsList->next) : 0;
	free(regsList);
>>>>>>> dev
};

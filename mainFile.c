/*
	This mainFile contains library additions and the basic 
	program execution and verification environment
*/

//Constants
#define LIN 50
#define COL 50

//Custom libraries and dependencies
#include<stdio.h>
#include<string.h>

//Custom libraries 
#include"register.h"
#include"date.h"
#include"menu.h"

//Pointers for files
FILE *dataBase,*yearList;

//Check data base
void checkDatabase(){
	
	//Local variables
	char directory[30] = "Database\\";
	char verify[30]; 
	char itemResult[7]; 
	char year[5];
	
	//Call datetime function
	getDate();
	strcpy(year,Year);
	
	//Creating path to data base
	strcat(year,"\\");
	strcat(directory,year);
	
	//Creating path to check if a data base exists
	strcpy(verify,directory);
	strcat(verify,"file_check.txt");
	
	//Checking if an old data base exists
	if((dataBase = fopen(verify,"rb")) == NULL){
        
		//Creating directory to data base
		mkdir("Database");
		mkdir(directory);
		
		//Validating new data base
		dataBase = fopen(verify,"wb");
		fprintf(dataBase,"%s","file_check is an internal file, if it is modified or deleted the program may not work correctly");
		
		//Opening list of years in reading mode
		yearList = fopen("Database\\list_years.txt","r");		
		
		//Search current year in file
		do{				
			//Add current year in file if don't exist
			if(fscanf(yearList,"%s",itemResult) == EOF && strcmp(itemResult,year) != 0){
				
				//Open the file in write mode
				fclose(yearList);
				yearList = fopen("Database\\list_years.txt","a");
				
				//Write the current year in the file
				fprintf(yearList,"%s",year);
				fprintf(yearList,"%c",'\n');
			}
		}while(strcmp(itemResult,"-1") == 0);
		
		//Close the files
		fclose(yearList);
		fclose(dataBase);
	}
}

//Main function
int main(){
	
	//Call checks data base function
	checkDatabase();
		
	//Load category list
	loadConfig(categoryList);
	
	//Call menu program function
	Menu(newReg(),dataBase);
	
	return(EXIT_SUCCESS);
}


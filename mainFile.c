/*
	This mainFile contains library additions and the basic 
	program execution and verification environment
*/

//libraries
#include<stdio.h>
#include<string.h>

//Constprevs
#define LIN 50
#define COL 50

//Defines '\' or '/' on unix/windows environtments
const char unix[2] = "//";
const char win[2] = "\\";
#ifdef __unix__         
    
	#define BARKEY unix

#elif defined(_WIN32) || defined(WIN32) 

   #define BARKEY win

#endif

//Custom libraries 
#include"register.h"
#include"date.h"
#include"menu.h"

//Pointers for files
FILE *dataBase,*yearList;

//Check data base
void checkDatabase(){
	
	//Local variables
	char directory[30] = "Database";
	strcat(directory,BARKEY);
	char yearsPath[30] = "Database";
	strcat(yearsPath,BARKEY);
	strcat(yearsPath,"list_years.txt");
	char verify[30]; 
	char itemResult[7]; 
	char year[5];
	
	//Call datetime function
	getDate();
	strcpy(year,Year);
	
	//Creating path to data base
	strcat(year,BARKEY);
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
		yearList = fopen(yearsPath,"r");		
		
		//Search current year in file
		do{				
			//Add current year in file if don't exist
			if(fscanf(yearList,"%s",itemResult) == EOF && strcmp(itemResult,year) != 0){
				
				//Open the file in write mode
				fclose(yearList);
				yearList = fopen(yearsPath,"a");
				
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
	
	//Local variables
	getDate();
	char path[30] = "Database";
	strcat(path,BARKEY);
	strcat(path,Year);
	strcat(path,BARKEY);
	strcat(path,Month);
	
	//Call checks data base function
	checkDatabase();
		
	//Load category list
	loadConfig(categoryList);
	
	//Call menu program function
	Menu(newReg(),path,dataBase);

	return(EXIT_SUCCESS);
}


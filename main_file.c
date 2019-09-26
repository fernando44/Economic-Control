/*
	This main file contains library additions and the basic 
	program execution and verification environment
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<locale.h>
#include<unistd.h>

//constants 
#define LIN 8
#define COL 14

//pointers for files
FILE *data_base,*files;

//global variables
char month[3],year[5];
char directory[25],verify[30];
char category[LIN][COL] = {"Informatica <","Contas      <","Vestimenta  <","Escolar     <","Alimenticio <","Medicamentos<","Documentos  <","Compras     <"};

//custom libraries 
#include"date.h"
#include"type.h"
#include"cad_library_1.1.h"
#include"load_library_1.1.h"
#include"tools_library_1.1.h"
#include"buble-sort_library.h"
#include"menu.h"

//main function
int main(){
    
	//enable local language in console
	setlocale(LC_ALL,"");
	
	//date function
	getDate();
	strcpy(month,Month);
	strcpy(year,Year);
	
	//creating main_list
	list_cad *main_list = (list_cad *)malloc(sizeof(list_cad));
	main_list->prox = NULL;
	main_list->ant = NULL;
	
	//creating path to data base
	strcpy(directory,"mkdir Database\\");
        
	//composition of name of place of data base
	strcat(directory,year);
	strcat(year,"\\");
        
	//composition of string of verifying if data base exists
	strcpy(verify,"Database");
	strcat(verify,year);
	strcat(verify,"file_cheker.txt");
		
	//verifying if the Database directory exists
	if((data_base = fopen(verify,"rb")) == NULL){
        
        //reading string
		char input[7];
		    
		//create a folder for save data base
		system(directory);
		
		//creating the verifier file
		data_base = fopen(verify,"wb");
		fprintf(data_base,"%s","file_checker is an internal file, if it is modified or deleted the program may not work correctly");
		
		//validating data in the file
		files = fopen("Database\\list_years.txt","r");
		
		//search loop
		do{				
			//adding the years in file
			if(fscanf(files,"%s",input) == EOF && strcmp(input,year) != 0){
				
				//close the file
				fclose(files);
				
				//open add mode file
				files = fopen("Database\\list_years.txt","a");
				
				//write the year in the file
				fprintf(files,"%s",year);
				fprintf(files,"%c",'\n');
			}
		}while(strcmp(input,"-1") == 0);
		
		//close the files
		fclose(files);
		fclose(data_base);
		
	}

	Menu(main_list,data_base);
	
	return(EXIT_SUCCESS);
}


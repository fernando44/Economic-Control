#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<locale.h>
#include<unistd.h>
#define LIN 8
#define COL 14

//pointers for files
FILE *data_base,*files;

//global variables
char month[3],year[5];
char directory[25],verify[30];
char category[LIN][COL] = {"Informatica <","Contas      <","Vestimenta  <","Escolar     <","Alimenticio <","Medicamentos<","Documentos  <","Compras     <"};
char header[366] = {"***********************************************************************************************************************\n\n*****************************************| Controle Econômico |********************************************************\n\n***********************************************************************************************************************\n\n\n\n"};

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
	
	//define window title 
	system ("title Controle Econï¿½mico");
	
	//start point of main_list
	list_cad *main_list = (list_cad *)malloc(sizeof(list_cad));
	main_list->prox = NULL;
	main_list->ant = NULL;
	
	//create an folder for data base
	strcpy(directory,"mkdir Database\\");
			
	//complement of name of directory of folder of data base
	strcat(directory,year);
	strcat(year,"\\");
		
	//complement of name of of data base
	strcpy(verify,"Database\\");
	strcat(verify,year);
	strcat(verify,"file_cheker.txt");
		
	//verifying if the Database directory exists
	if((data_base = fopen(verify,"rb")) == NULL){
		
		//create a folder for save data base
		system(directory);
		
		//create the verifier file
		data_base = fopen(verify,"wb");
		fprintf(data_base,"%s","file_checker is an internal file, if it is modified or deleted the program may not work correctly");
		
		//add the year in file
		files = fopen("Database\\list_years.txt","a");
		
		//burn the year in file
		fprintf(files,"%s",year);
		fprintf(files,"%c",'\n');
		
		//close the files
		fclose(files);
		fclose(data_base);
		
	}

	Menu(main_list,data_base);
	
	return(EXIT_SUCCESS);
}

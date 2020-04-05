/*
	This library contains functions to display de header of program
	and to display program menu options 
*/

//Custom libraries and dependencies
#include<unistd.h>
#include<stdio.h>

//Custom libraries 
#include"feedLibrary.h"
#include"loadLibrary.h"
#include"toolsLibrary.h"
#include"sortLibrary.h"

//Global variables
char month[11], year[5],path[50];

//Function to clean screen
void ClrScr(){
	int i = 0;
     for(i = 0; i < 500; i++){
          printf("\n");
     }
} 

//Function to display program header
void HEADER(){
	
	printf("****************************************************************************************************\n\n");
	printf("****************************************| Economic Control |****************************************\n\n");
	printf("****************************************************************************************************\n\n\n\n");
}

//Function to display menu of program
void Menu(reg *regsList,FILE *dataBase){
	
	//Local variables
	int option = -1;
	
	//Creating path to data base
	getDate();
	strcpy(year,Year);
	strcpy(month,Month);
	strcat(year,"\\");
	strcpy(path,"Database\\");
	strcat(path,year);
	strcat(path,month);
	
	//Menu and submenu string options
	char menuOptions[115] = "\n\n1 - New register \n2 - View registers \n3 - Change register \n4 - Switch data base \n5 - About \n6 - Exit";
	char submenuOptions[215] = "\n\n   1 - Order by Date \n   2 - Order by Id  \n   3 - Order by Value \n   4 - Return to menu \n";
	
	//Clearing the list of records
	cleanList(regsList);
	regsList = newReg();
				
	//Loading data from archives for regsList
	regsList = loadListFromTxt(regsList,dataBase,path);
//	loadListFromJson(regsList,dataBase,path);
	ClrScr();
	HEADER();
	
	//Displays menu options
	printf("Select an option: %s\n",menuOptions);
	
	//Selection menu
	setbuf(stdin,NULL);
	switch(getchar()-48){
		
		case 1:{				
			
			//Add a new register in the list
			ClrScr();
			if(strcmp(regsList->date,"") != 0){
				
				addEnd(regsList,newReg());
				dataFeed(navEnd(regsList));
				
			}else{
				
				dataFeed(regsList);
			}
			
			//Sort by ascending date before writing to file
			regsList = orderByDate(regsList);
			
			//Write regsList in file
			saveListAsJson(regsList,dataBase,path);
			saveListAsTxt(regsList,dataBase,path);
			
			//Return to menu
			Menu(regsList,dataBase);	
			break;
		}
		
		case 2:{
			
			//Loop of submenu
			if(regsList != NULL || strcmp(regsList->date ,"\0") != 0){
				do{
					
					//Displaying regsList
					ClrScr();
					HEADER();
					showRecords(orderByDate(regsList));
					
					printf("\n\n   Select an option: %s",submenuOptions);
					
					//Receives new value for option
					setbuf(stdin,NULL);
					option = getchar()-48;
					
					if(option == 1){
						
						//Sort by ascending date
						regsList = orderByDate(regsList);
						
					}else if(option == 2){
					
						//Sort by ascending id
						regsList = orderById(regsList);
						
					}else if(option == 3){
						
						//Sort by ascending value
						regsList = orderByValue(regsList);
					
					}
					
					if(option != 1 && option != 2 && option != 4 && option !=3){
						
						//Feedback default
						ClrScr();
						printf("\n\n\n\t\t\t\tInvalid option!");
						sleep (1);
						
					}
					
				}while(option != 4);
			}
			
			showRecords(regsList);
			printf("\n\n\nlista que vai para o menu");
			//Return to menu
			Menu(regsList,dataBase);
			break;
		}
		
		case 3:{
			ClrScr();
			HEADER();
			
			//Edit a register of regsList
			editRecord(regsList);
			
			//Sort by ascending date before writing to file
//			orderByDate(regsList);
			
			//Write regsList in file
			saveListAsJson(regsList,dataBase,path);
			saveListAsTxt(regsList,dataBase,path);

			//Return to menu
			Menu(regsList,dataBase);		
			break;
		}
		
		case 4:{
			
			ClrScr();
			HEADER();	
						
			//Switch data base
//			show_data_base(Month,Year,yearList);

			//Return to menu
			Menu(regsList,dataBase);				
			break;
		}
			
		case 5:{
			
			//About
			ClrScr();
			HEADER();
			printf("This software is free and intended for personal use.\nIts use in business environments is not recommended for security reasons !!!\n\n");
			printf("Developer: Quemuel Alves Nassor\n\nContact or support: quemuelalp@hotmail.com\n\n");
			setbuf(stdin,NULL);
			getchar();
			
			//Return to menu
			Menu(regsList,dataBase);
			break;
			
		}
		
		case 6:{
			
			//Exit of program
			ClrScr();
			exit(0);
			break;
		}
			
		default:
			
			//Feedback default
			ClrScr();
			printf("\n\n\n\t\t\t\tInvalid option!");
			sleep(1);
			
			//Return to menu
			Menu(regsList,dataBase);
	}
		
	//Clearing the list of records
	cleanList(regsList);
	regsList = newReg();
}

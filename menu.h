<<<<<<< HEAD
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
=======
>>>>>>> master
void HEADER(){
	
	printf("****************************************************************************************************\n\n");
	printf("****************************************| Economic Control |****************************************\n\n");
	printf("****************************************************************************************************\n\n\n\n");
}

<<<<<<< HEAD
//Function to display menu of program
void Menu(reg *regsList,char path[30],FILE *dataBase){
	
	//Local variables
	int option = -1;

	//Menu and submenu string options
	char menuOptions[115] = "\n\n1 - New register \n2 - View registers \n3 - Change register \n4 - Switch data base \n5 - About \n6 - Exit";
	char submenuOptions[215] = "\n\n   1 - Order by Date \n   2 - Order by Id  \n   3 - Order by Value \n   4 - Return to menu \n";
	
	//Clearing the list of records
	cleanList(regsList);
	regsList = newReg();
				
	//Loading data from archives for regsList 
	regsList = (loadListFromTxt(regsList,dataBase,path)) == NULL ? (loadListFromJson(regsList,dataBase,path)) == NULL ? newReg() : 0 : (loadListFromTxt(regsList,dataBase,path));
	ClrScr();
	HEADER();
	
	//Displays menu options and informations
	printf("Active Database: %c%s%c\n\n",34,path,34);
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
			Menu(regsList,path,dataBase);
			break;
		}
		
		case 2:{
			
			//Loop of submenu
			if(regsList != NULL && strcmp(regsList->date,"") != 0){
				do{
=======
//Menu function
void Menu(list_cad *main_list,FILE *data_base){
		
		//submenu sorting options
		char submenu[220] ="\n\n  ================================\n |   1 - Ordenar por Data         |\n |   2 - Ordenar por Valor        |\n |   3 - Ordenar por Categoria    |\n |   ESC - Retornar ao menu       |\n  ================================\n";
		
		//frees memory allocated by main_list
		deallocate_list(main_list);
					
		//read data from files for main_list and sort for date
		load_list(main_list,data_base,month,year);
		
		//define color green
		system("COLOR 0A");
		
		//displays menu options
		system("cls");
		HEADER();
		printf("Selecione uma opção:\n\n1 - Novo cadastro \n2 - Exibir cadastros \n3 - Alterar cadastro\n4 - Alternar base de dados\n5 - Sobre\n6 - Sair");
		int option = -1;
		
		//selection menu
		setbuf(stdin,NULL);
		switch(getch()-48){
			
			case 1:{				
				system("cls");
				//concatenate a new record in the list
				add_new(category,main_list,"",Date);
				
				//sort for date before burn in file
				ord_date(main_list);
				
				//writes main_list in file
				download_list(main_list,data_base,month,year);
				Menu(main_list,data_base);	
				break;
			}
			
			case 2:{
				
				//check if main_list is empty
				if(main_list->prox == NULL){
					
					//define color red
					system("COLOR 0C");
			
					//feedback if main_list is empty
					system("cls");
					printf("\n\n\n\t\t\t\tNão existem cadastros na main_lista!!!");
					sleep (2);
>>>>>>> master
					
					//Displaying regsList
					ClrScr();
					HEADER();
					showRecords(orderByDate(regsList));
					
<<<<<<< HEAD
					printf("\n\n   Select an option: %s",submenuOptions);
					
					//Receives new value for option
					setbuf(stdin,NULL);
					option = getchar()-48;
					
					if(option == 1){
=======
					//Loop of submenu
					do{
						
						//define color green
						system("COLOR 0A");
						
						//displaying main_list
						system("cls");
						HEADER();
						ord_date(main_list);
						show_records(main_list);
						printf("%s",submenu);
>>>>>>> master
						
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
						
<<<<<<< HEAD
					}
					
				}while(option != 4);
=======
						if(option != 1 && option != 2 && option != -21 && option !=3){
							
							//define color red
							system("COLOR 0C");
							
							//feedback default
							system("cls");
							printf("\n\n\n\t\t\t\tOpção inválida!");
							sleep (1);
							
						}
					}while(option != -21);
				}
				Menu(main_list,data_base);
				break;
			}
			
			case 3:{
				system("cls");
				HEADER();
>>>>>>> master
				
			}else{
				
<<<<<<< HEAD
				//Feedback if regsList is empty
				ClrScr();
				printf("\n\n\n\t\t\t\tNo exists records to display!!!");
				sleep (2);
				
			}
			
			//Return to menu
			Menu(regsList,path,dataBase);
			break;
		}
		
		case 3:{
			ClrScr();
			HEADER();
			
			//Edit a register of regsList
			editRecord(regsList);
			
			//Sort by ascending date before writing to file
			orderByDate(regsList);
			
			//Write regsList in file
			saveListAsJson(regsList,dataBase,path);
			saveListAsTxt(regsList,dataBase,path);

			//Return to menu
			Menu(regsList,path,dataBase);
			break;
=======
				//sort for date before burn in file
				ord_date(main_list);
				
				//writes list in file
				download_list(main_list,data_base,month,year);
				Menu(main_list,data_base);		
				break;
			}
			
			case 4:{
				
				system("cls");
				HEADER();	
							
				//selects other periods to load in main_file
				show_data_base(month,year,"",files);
				Menu(main_list,data_base);				
				break;
			}
				
			case 5:{
				
				//about
				system("cls");
				HEADER();
				printf("Este software é gratuito e destinado para uso pessoal.\nSeu uso em ambientes empresariais não é recomendado por questões de segurança!!!\n\n");
				printf("Desenvolvedor: Quemuel Alves Nassor\n\nContato ou suporte: quemuelalp@hotmail.com\n\nVersão: 1.0.2");
				setbuf(stdin,NULL);
				getch();
				Menu(main_list,data_base);
				break;
				
			}
			
			case 6:{
				
				//exit of program
				system("cls");
				exit(0);
				break;
			}
				
			default:
				
				//define color red
				system("COLOR 0C");
				
				//feedback default
				system("cls");
				printf("\n\n\n\t\t\t\tOpção inválida!");
				sleep(1);
				Menu(main_list,data_base);
>>>>>>> master
		}
		
		case 4:{
			
			//Switch data base
			switchDataBase(path,dataBase);
						
			//Return to menu
			Menu(regsList,path,dataBase);
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
			Menu(regsList,path,dataBase);
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
			Menu(regsList,path,dataBase);
	}
		
	//Clearing the list of records
	cleanList(regsList);
	regsList = newReg();
}

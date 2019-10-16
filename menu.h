/*
	This library contains functions to display de header of program
	and to display program menu options 
*/

//Header function
void HEADER(){
	
	int i = 1;

	while(i < 281){
		printf("*");
		if( i == 100){
			printf("\n\n");
		}
		if(i == 140){
			printf("| Economic Control |");
		}
		if(i == 180){
			printf("\n\n");
		}
		i++;
	}
	printf("\n\n\n\n");
}

//Menu function
void Menu(list_cad *main_list,FILE *data_base){
		
		//set console dimension and title
		system("mode con cols=100 lines=30");
		system("title Economic-Control");
	
		//menu and submenu string options
		char menu_options[115] = "\n\n1 - New register \n2 - View registers \n3 - Change register \n4 - Switch data base \n5 - About \n6 - Exit";
		char submenu_options[215] = "\n\n  =============================\n |   1 - Order by Date         |\n |   2 - Order by Value        |\n |   3 - Order by Category     |\n |   ESC - Return to menu      |\n  =============================\n";
		
		//frees memory allocated by main_list
		deallocate_list(main_list);
					
		//read data from files for main_list and sort for date
		load_list(main_list,data_base,month,year);
		
		//define color green
		system("COLOR 0A");
		system("cls");
		HEADER();
		
		//displays menu options
		printf("Select an option: %s",menu_options);
		int option = -1;
		
		//selection menu
		setbuf(stdin,NULL);
		switch(getch()-48){
			
			case 1:{				
				system("cls");
				//concatenate a new register in the list
				add_new(category,main_list,Date);
				
				//sort for date before write in file
				ord_date(main_list);
				
				//write main_list in file
				download_list(main_list,data_base,month,year);
				Menu(main_list,data_base);	
				break;
			}
			
			case 2:{
				
				//set console dimension
				system("mode con cols=100 lines=9001");
				 
				//check if main_list is empty
				if(main_list->prox == NULL){
					
					//define color red
					system("COLOR 0C");
			
					//feedback if main_list is empty
					system("cls");
					printf("\n\n\n\t\t\t\tNo exists records to display!!!");
					sleep (2);
					
				}else{
					
					//Loop of submenu
					do{
						
						//define color green
						system("COLOR 0A");
						
						//displaying main_list
						system("cls");
						HEADER();
//						ord_date(main_list);
						show_records(main_list);
						printf("%s",submenu_options);
						
						//receives new value for option
						setbuf(stdin,NULL);
						option = getch()-48;
						
						if(option == 1){
							
							//sorting main_list by date
							ord_date(main_list);
							
						}else if(option == 2){
						
							//sorting main_list by value
							ord_value(main_list);
							
						}else if(option == 3){
							
							//sorting main_list by category
							ord_category(main_list);
						
						}
						
						if(option == -21){
							
							//return to main menu
							break;
							
						}
						
						if(option != 1 && option != 2 && option != -21 && option !=3){
							
							//define color red
							system("COLOR 0C");
							
							//feedback default
							system("cls");
							printf("\n\n\n\t\t\t\tInvalid option!");
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
				
				//edit a item of main_list
				edit_register(category,main_list,"",Date);
				
				//sort for date before write into file
				ord_date(main_list);
				
				//write list into file
				download_list(main_list,data_base,month,year);
				Menu(main_list,data_base);		
				break;
			}
			
			case 4:{
				
				system("cls");
				HEADER();	
							
				//selects other periods to load in main_file
				show_data_base(month,year,files);
				Menu(main_list,data_base);				
				break;
			}
				
			case 5:{
				
				//about
				system("cls");
				HEADER();
				printf("This software is free and intended for personal use.\nIts use in business environments is not recommended for security reasons !!!\n\n");
				printf("Developer: Quemuel Alves Nassor\n\nContact or support: quemuelalp@hotmail.com\n\n");
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
				printf("\n\n\n\t\t\t\tInvalid option!");
				sleep(1);
				Menu(main_list,data_base);
		}
		
		//frees memory allocated by main_list
		deallocate_list(main_list);
					
}

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
		printf("%s",header);
		printf("Selecione uma opção:\n\n1 - Novo cadastro \n2 - Exibir cadastros \n3 - Alterar cadastro\n4 - Alternar base de dados\n5 - Sobre\n6 - Sair");
		int option = -1;
		
		//selection menu
		setbuf(stdin,NULL);
		switch(getch()-48){
			
			case 1:{				
				system("cls");
				//concatenate a new record in the list
				add_new(category,main_list,header,Date);
				
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
					
				}else{
					
					//Loop of submenu
					do{
						
						//define color green
						system("COLOR 0A");
						
						//displaying main_list
						system("cls");
						printf("%s",header);
						ord_date(main_list);
						show_records(main_list);
						printf("%s",submenu);
						
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
				printf("%s",header);
				
				//edit a item of main_list
				edit_register(category,main_list,header,Date);
				
				//sort for date before burn in file
				ord_date(main_list);
				
				//writes list in file
				download_list(main_list,data_base,month,year);
				Menu(main_list,data_base);		
				break;
			}
			
			case 4:{
				
				system("cls");
				printf("%s",header);	
							
				//selects other periods to load in main_file
				show_data_base(month,year,header,files);
				Menu(main_list,data_base);				
				break;
			}
				
			case 5:{
				
				//about
				system("cls");
				printf("%s",header);
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
		}
		
		//frees memory allocated by main_list
		deallocate_list(main_list);
					
}

/*
	This library contains functions to read data from files for memory,
	write data into files, frees memory, and switch data base 
*/

extern void HEADER();

//local variables
char matrix_years[10000][7];
char matrix_months[12][10] = {"janeiro","fevereiro","março","abril","maio","junho","julho","agosto","setembro","outubro","novembro","dezembro"};

//Load_list function 
void load_list(list_cad *main_list,FILE *data_base,char name[11],char folder[7]){
	
//	//contador sinalizar fim de dado 
//	int count = 0;
//	
//	//variáveis para receber o value e os caracteres do arquivo
//	char value[500],digito[2];
//
//	//variável para receber o nome do arquivo
//	char arquivo[50];
//	
//	//copia e adiciona a extensão do nome do arquivo
//	strcpy(arquivo,"Database\\");
//	strcat(arquivo,folder);
//	strcat(arquivo,name);
//	strcat(arquivo,".txt");
//	
//	//cria uma alocação para ler os dados do arquivo
//	list_cad *recebe = (list_cad *)malloc(sizeof(list_cad));
//	recebe->prox = NULL;
//	recebe->ant = NULL;
//	
//	//reinicialização da struct receptora e da variável value
//	strcpy(recebe->date,"");
//	recebe->value = 0;
//	strcpy(recebe->category,"");
//	strcpy(recebe->description,"");
//	strcpy(recebe->details,"");
//	strcpy(value,"");
//	
//	//inicializa a variável que receberá os valuees dos cadastros
//	strcpy(value,"");
//	
//	//finaliza a string
//	digito[1] = '\0';
//			
//	//teste de abertura de arquivo para leitura
//	if((data_base = fopen(arquivo,"r"))==NULL){
//		
//		system("cls");
//		
//		//altera a cor do texto para vermelho
//		system("COLOR 0C");
//		printf("\n\n\n\t\t\t\tNão foi possível abrir o arquivo %s !!!", arquivo);
//		sleep(2);
//			
//	//abre o arquivo em modo de leitura	
//	}else{
//			system("cls");
//		//transfere os dados do arquivo para a lista de structs
//		while((digito[0] = fgetc(data_base))!=EOF){
//			
//			//verifica a quebra de linha para adicionar uma nova alocação
//			if(digito[0]=='\n' && count == 4){
//			
//				//reseta o contador de verificação
//				count = 0;
//				
//				//cria uma nova alocação a cada nova leitura do arquivo
//				list_cad *novo = (list_cad *)malloc(sizeof(list_cad));
//				novo->prox = NULL;
//				novo->ant = NULL;
//				
//				//tranferência dos dados da struct receptora para a lista
//				strcpy(novo->date,recebe->date);
//				novo->value = recebe->value;
//				strcpy(novo->category,recebe->category);
//				strcpy(novo->description,recebe->description);
//				strcpy(novo->details,recebe->details);
//				
//				//inserção das novas alocações na lista
//				//verifica o inicio da lista
//				if(main_list->prox == NULL){
//					
//					novo->prox = main_list->prox;
//					main_list->prox = novo;
//					novo->ant = main_list;
//					
//				}else if(main_list->prox != NULL){
//				
//					//reorganização da lista de cadastros	
//					novo->prox = main_list->prox;
//					main_list->prox = novo;
//					novo->ant = main_list;
//					novo->prox->ant = novo;
//				}
//				
//				//reinicialização da struct receptora e da variável value
//				strcpy(recebe->date,"");
//				recebe->value = 0;
//				strcpy(recebe->category,"");
//				strcpy(recebe->description,"");
//				strcpy(recebe->details,"");
//				strcpy(value,"");
//				
//			//aloca os dados em suas respectivas variáveis na struct
//			}else if((digito[0] !='\n')){
//					
//				//incrementa o sinalizador de fim de dado
//				if(digito[0] == '\t'){
//					count++;
//				}
//				
//				//recebe a date	do cadastro
//				if(strlen(recebe->date) < 10 && count == 0 && digito[0] != '\t' ){
//						
//						strcat(recebe->date,digito);
//					
//				}
//				
//				//recebe o value do cadastro
//				if((strlen(recebe->date) == 10 ) && count == 1 && digito[0] != '\t'){
//					
//						strcat(value,digito);				
//						recebe->value = atof(value);
//						
//				}
//				
//				//recebe a category do cadastro
//				if((recebe->value != 0) && count == 2 && digito[0] != '\t'){
//					
//						strcat(recebe->category,digito);
//						
//				}
//				
//				//recebe a descrição do cadastro
//				if((recebe->category != 0) && count == 3 && digito[0] != '\t'){
//						
//						strcat(recebe->description,digito);
//						
//				}
//				
//				//recebe os details do cadastro
//				if((recebe->description != 0) && count == 4 && digito[0] != '\t'){
//					
//						strcat(recebe->details,digito);
//				
//				}
//			}
//		}
//		
//		//fecha o arquivo de texto
//		fclose(data_base);
//	}
	//local variables 
	int count = 0, i = 0;
	char character,file[50],string[10000] = "";
	
	//creating path to data base
	strcpy(file,"Database\\");
	strcat(file,folder);
	strcat(file,name);
	strcat(file,".txt");
	
	//verifying if the file exists
	if((data_base = fopen(file,"r"))==NULL){
		
		//failure feedback
		system("cls");
		system("COLOR 0C");//define color red
		printf("\n\n\n\t\t\t\tUnable to open file %s.txt !!!", name);
		sleep(2);
				
	}else{
		
		//temporary variable
//		list_cad *temp = main_list;
		
//		do{
		while((character = fgetc(data_base))!=EOF){
			
			//verifying if character is valid
			if(character != '\t' && character != '\n'){
				string[strlen(string)] = character;
				
			//reseting string to receive data
			}else if(character == '\t' || character == '\n'){
            	for(i = strlen(string);i>=0;i--){//cleaning string
					string[i] = '\0';
				}
				if(character == '\n'){
//					printf("Data: %s      ",main_list->prox->date);
//					printf("Categoria: %s      ",main_list->prox->category);
//					printf("Descrição: %s\n\n",main_list->prox->description);
//					printf("Valor: %f      ",main_list->prox->value);
//					printf("Detalhes: %s\n",main_list->prox->details);
//					printf("-----------------------------------------------------------------------------------------------------------\n");
//					getch();
				}
			}
			
			//verifying new register
            if(character == '\n' && count == 4){
				
//				//percussing the list
//				while(temp->prox != NULL){
//					temp = temp->prox;	
//				}
				//create a new allocation and add in main_list
				list_cad *new_cad = (list_cad *)malloc(sizeof(list_cad));
				if(main_list->prox == NULL){
					new_cad->prox = main_list->prox;
					main_list->prox = new_cad;
					new_cad->ant = main_list;
					
				}else if(main_list->prox != NULL){
					new_cad->prox = main_list->prox;
					main_list->prox = new_cad;
					new_cad->ant = main_list;
					new_cad->prox->ant = new_cad;
				}
				
				//inicializating the new register				
				strcpy(new_cad->date,"");
				strcpy(new_cad->category,"");
				strcpy(new_cad->description,"");
				strcpy(new_cad->details,"");
				new_cad->value = 0;
				count = 0;
				getch();
			}
			
			//allocating data into struct of the main_list	
			if(character == '\t'){
				count++;
			}else if(character != '\t' && count == 0 && character != '\n'){
				printf("%s\n\n",string);
				strcpy(main_list->prox->date, string);
			}else if(character != '\t' && count == 1 && character != '\n'){
				printf("%s\n\n",string);
				main_list->prox->value = atof(string);
			}else if(character != '\t' && count == 2 && character != '\n'){
				printf("%s\n\n",string);
				strcpy(main_list->prox->category, string);
			}else if(character != '\t' && count == 3 && character != '\n'){
				printf("%s\n\n",string);
				strcpy(main_list->prox->description, string);
			}else if(character != '\t' && count == 4 && character != '\n'){
				printf("%s\n\n",string);
				strcpy(main_list->prox->details, string);
//			}else if(strcmp(main_list->prox->date,"") == 0 && strcmp(main_list->prox->category,"") == 0 && (main_list->prox->value == 0)){
////				strcpy(main_list->prox->date,"1");
////				strcpy(main_list->prox->category,"1");
////				main_list->prox->value = 0;
////				strcpy(main_list->prox->description,"cadastro em branco");
//				break;
			}
//		}while((character = fgetc(data_base))!=EOF);
		}
		//close the file
		fclose(data_base);
	}
}

//deallocate_list function
void deallocate_list(list_cad *main_list){
	
	//verifying if main_list is null
	if(main_list != NULL){
			
		deallocate_list(main_list->prox);
		//deallocate register
		free(main_list);
		
	}
}

//Write function
void Write(list_cad *main_list,FILE *data_base,char file[100]){
	
	//verifying if main_list is null
	if(main_list != NULL){
		
		fprintf(data_base,"%s\t",main_list->date);
		fprintf(data_base,"%.2f\t",main_list->value);
		fprintf(data_base,"%s\t",main_list->category);
		fprintf(data_base,"%s\t",main_list->description);
		fprintf(data_base,"%s\n",main_list->details);

		//recursive call	
		Write(main_list->prox,data_base,file);
	}
		printf("failure");

}

//download_list function
void download_list(list_cad *main_list,FILE *data_base,char name[11],char folder[7]){
	
	//local variable
	char file[50];
	
	//creating path to data base
	strcpy(file,"Database\\");
	strcat(file,folder);
	strcat(file,name);
	strcat(file,".txt");
	
	//open write mode file
	data_base = fopen(file,"w");
	
	//Write function call
	Write(main_list->prox,data_base,file);
	
	//close the file
	fclose(data_base);
}

//show_data_base function
void show_data_base(char month[11],char year[7],FILE *file){
	
	//local variables
	int count = 0,max = 0,key = 0;
	
	//opens the year record in read mode
	file = fopen("Database\\list_years.txt","r");
	
	//loop for fill matrix of years
	while(fscanf(file,"%s",matrix_years[count]) != EOF || (count == 9999)){
		max = count;
		count++;
	}
	count = 0;
	
	//close the file
	fclose(file);
	
	//loop to display and select years
	while(key != -35 || key != -21){
		
		system("cls");
		HEADER();
		printf("Press ESC to stay in current year\n\n");
		printf("%s",matrix_years[count]);
		
		//key pressed reading
		setbuf(stdin,NULL);
		key = getch()-48;
		
		//enter key pressed
		if(key == -35){
			strcpy(year,matrix_years[count]);
			break;
		//rolling matrix up 	
		}else if(key == 24){
			count--;
		//rolling matrix down	
		}else if(key == 32){
			count++;
		}
		
		//back to start
		if(count == max +1){
			count = 0;
		//back to end	
		}else if(count<0){
			count = max;
		}		
	}
	count = key = 0;
	
	
	//loop to display and select months
	while(key != -35 || key != -21){
		
		system("cls");
		HEADER();
		printf("Press ESC to stay in current month\n\n");
		printf("%s",matrix_months[count]);
		
		//key pressed reading
		setbuf(stdin,NULL);
		key = getch()-48;
		
		//enter key pressed
		if(key == -35){
			strcpy(month,matrix_months[count]);
			break;
		//rolling matrix up	
		}else if(key == 24){
			count--;			
		//rolling matrix down	
		}else if(key == 32){
			count++;
		}
		
		//back to start
		if(count == 12 ){
			count = 0;
		//back to end	
		}else if(count<0){
			count = 11;
		}		
	}
}

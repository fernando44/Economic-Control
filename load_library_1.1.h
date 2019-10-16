/*
	This library contains functions to read data from files for memory,
	write data into files, frees memory, and switch data base 
*/

//local variables
char matrix_years[10000][7];
char matrix_months[12][10] = {"January", "February", "March", "April", "May", "June", "June", "July", "August", "September", "October", "November", "December"};

//Load_list function 
void load_list(list_cad *main_list,FILE *data_base,char name[11],char folder[7]){
	
	//local variables 
	int count = 0, i = 0;
	char character,file[50];
	char string[10000] = "";
	list_cad *temp = main_list;
	
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
		printf("\n\n\n\t\t\t\tUnable to open file %s !!!", file);
		sleep(2);
				
	}else{
		
		//temporary variable
		list_cad *temp = main_list;
		
		do{
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
				new_cad->prox = temp->prox;
				temp->prox = new_cad;
				new_cad->ant = temp;
										
				//inicializating the new register				
				strcpy(new_cad->date,"");
				strcpy(new_cad->category,"");
				strcpy(new_cad->description,"");
				strcpy(new_cad->details,"");
				new_cad->value = 0;
				count = 0;
			}
			
			//allocating data into struct of the main_list	
			if(character == '\t'){
				count++;
			}else if(character != '\t' && count == 0 && character != '\n'){
				printf("%i",count);getch();
				strcpy(temp->prox->date, string);
			}else if(character != '\t' && count == 1 && character != '\n'){
				temp->prox->value = atof(string);
			}else if(character != '\t' && count == 2 && character != '\n'){
				strcpy(temp->prox->category, string);
			}else if(character != '\t' && count == 3 && character != '\n'){
				strcpy(temp->prox->description, string);
			}else if(character != '\t' && count == 4 && character != '\n'){
				strcpy(temp->prox->details, string);
			}else if(strcmp(temp->prox->date,"") == 0 && strcmp(temp->prox->category,"") == 0 && (temp->prox->value == 0)){
//				list_cad *del = temp->prox;
//				del->ant->prox = NULL;
//				free(del);
				strcpy(temp->prox->date,"1");
				strcpy(temp->prox->category,"1");
				temp->prox->value = 0;
			}
		}while((character = fgetc(data_base))!=EOF);
		
		//close the file
		fclose(data_base);
	}
}


//declaração da função desaloca
//=============================================================================================================================================================

//função para liberar memória alocada
void deallocate_list(list_cad *main_list){
	
	list_cad *temp;	
	//laço que percorre e libera a lista
	while(main_list->prox!= NULL){
			
		//reorganização dos apontamentos da lista
		temp = main_list->prox;
		main_list->prox = temp->prox;
		
		//verifica se a a variável temporária chegou ao fim da lista 
		if(temp->prox == NULL){
			
			//reorgazinação do apontamento da lista
			main_list->prox = temp->prox;
			
			//liberação de memória alocada
			free(temp);
			break;
		}	
		
		//reorganização dos apontamento na lista
		temp->prox->ant = main_list;
		free(temp);	
	}	
}


//declaração da função descarregar
//=============================================================================================================================================================

//função para escrever dados da lista de struct no file
void download_list(list_cad *main_list,FILE *data_base,char nome[11],char pasta[5]){
	
	//variável para new_cadr o nome do file
	char file[50];
	
	//copia e adiciona a extensão do nome do file
	strcpy(file,"Database\\");
	strcat(file,pasta);
	strcat(file,nome);
	strcat(file,".txt");
	
	//verifica se a lista possui itens ou se está vazia
	if(main_list->prox != NULL){
	
		//ponteiro temporario
		list_cad *temp = main_list->prox;
		
		//abre file em modo escrita
		data_base = fopen(file,"w");
		
		if(temp->prox != NULL){
			//loop para percorrer e gravar a lista de structs no file		
			while(temp->prox != NULL){
				
				fprintf(data_base,"%s\t",temp->date);
				fprintf(data_base,"%.2f\t",temp->value);
				fprintf(data_base,"%s\t",temp->category);
				fprintf(data_base,"%s\t",temp->description);
				fprintf(data_base,"%s\n",temp->details);
					
				//new_cad o ponteiro seguinte
				temp = temp->prox;
			}
		}
		
		//armazena os dados da ultima struct
		if(temp->prox == NULL){
						
			fprintf(data_base,"%s\t",temp->date);
			fprintf(data_base,"%.2f\t",temp->value);
			fprintf(data_base,"%s\t",temp->category);
			fprintf(data_base,"%s\t",temp->description);
			fprintf(data_base,"%s\n",temp->details);
			
		}
				
		//fecha o file
		fclose(data_base);
	}
}


//declaração da função alt_data_base
//=============================================================================================================================================================

//função para alternar a base de dados que o usuário deseja acessar
void show_data_base(char sel_mes[11],char sel_ano[7],char titulo[366],FILE *places){
	
	//variáveis places
	int i = 0,max,opc = 0,sel = 0;
	
//seleção do ano de cadastro
//===================================================================
	
	//loop para inicialização da matriz dos anos cadastrados
	while(i < 10000){
		
		//atribui espaços em branco à string
		strcpy(matrix_years[i],"      ");
		i++;
	}
	
	//reinicializa o contador
	i = 0;
	
	//abre o file lista_anos para leitura
	places = fopen("Database\\list_years.txt","r");
	
	//loop para new_cadr os anos do file para a matriz
	while(fscanf(places,"%s",matrix_years[i]) != EOF){
		
		i++;
		
		//para o loop se o índice chegar ao value máximo
		if(i == 9999){
			break;
		}
	}
	
	//fecha o file lista_anos
	fclose(places);
	
	/*variável max new_cad a última posição em que a matriz 
	new_cadu valuees e reinicializa o contador*/
	max = i-1;	
	i = 0;
	
	//loop para exibir os anos cadastrados e selecioná-los
	while(sel != -35){
		
		//limpa a tela e exibe os matrix_months para seleção
		system("cls");
		printf("%sPressione ESC para permanecer no ano atual\n\n",titulo);
		int u;
		//loop para exibir os anos sem as barras(\\)
		for(u = 0;u<4;u++){
			printf("%c",matrix_years[i][u]);
		}
		
		//variável de seleção
		setbuf(stdin,NULL);
		sel = getch()-48;
		
		//permanece no mês atual
		if(sel == -21){
			
			break;
		
		}else if(sel == -35){
			
			//new_cad o ano selecionado
			strcpy(sel_ano,matrix_years[i]);
			
		}else if(sel == 24){
			
			//decrementa o value de i e exibe anos acima
			i--;
			
		}else if(sel == 32){
			
			//incrementa o value de i e exibe anos abaixo
			i++;
		}
		
		if(i == max +1){
			
			//volta no primeiro item 
			i = 0;
			
		}else if(i<0){
			
			//volta no último item 
			i = max;
		}		
	}
	
//seleção do mês de cadastro
//===================================================================

	//reinicializa o contador
	i = 0;
	
	//loop de seleção do mês do base de dados
	while(opc != -35){
		
		//limpa a tela e exibe os matrix_months para seleção
		system("cls");
		printf("%sPressione ESC para permanecer no mês atual\n\n",titulo);
		printf("%s",matrix_months[i]);
		
		//variável de seleção
		setbuf(stdin,NULL);
		opc = getch()-48;
		
		//permanece no mês atual
		if(opc == -21){
			
			break;
		
		}else if(opc == -35){
			
			//new_cad o mês selecionado
			strcpy(sel_mes,matrix_months[i]);
			
		}else if(opc == 24){
			
			//decrementa o value de i e exibe matrix_months acima
			i--;
			
		}else if(opc == 32){
			
			//incrementa o value de i e exibe matrix_months abaixo
			i++;
		}
		
		if(i == 12 ){
			
			//volta no primeiro item 
			i = 0;
			
		}else if(i<0){
			
			//volta no último item 
			i = 11;
		}		
	}
}

//declaração da função recebe_date
//=============================================================================================================================================================

//função para ler a date do cadastro
void recebe_date(char recebe[11],char titulo[500]){
	
	//variável inicial
	char date[11];
	
	//recebe o dia
	printf("Data: ");
	setbuf(stdin,NULL);
	fgets(date,11,stdin);

	//verifica se a primeira tecla pressionada foi enter
	if(date[0] != '\n'){
		
		//recebe a date
		strcpy(recebe,date);
		//finaliza a string da date
		recebe[10] = '\0';
		
	}
}


//declaração da função listar
//=============================================================================================================================================================

//função para exibir a lista de cadastros
void show_records(list_cad *ficha){
	
	//ponteiro temporário para percorrer a lista
	list_cad *temp = ficha->prox;
	
	//variável para exibir a soma total
	float total = 0;
	
	//verifica se a lista de structs está ou não vazia
	if(temp != NULL){
		
		printf("-----------------------------------------------------------------------------------------------------------\n");
		//loop para exibição da struct
		while(temp->prox!=NULL){
			
			//exibe os dados do cadastro
			printf("Data: %s      ",temp->date);
			printf("Categoria: %s      ",temp->category);
			printf("Descrição: %s\n\n",temp->description);
			printf("Valor: %.2f      ",temp->value);
			printf("Detalhes: %s\n",temp->details);
			printf("-----------------------------------------------------------------------------------------------------------\n");
			
			total += temp->value;
			
			temp = temp->prox;
		}
		
		
		//exibe os dados do cadastro da struct na última posição da lista
		printf("Data: %s      ",temp->date);
		printf("Categoria: %s      ",temp->category);
		printf("Descrição: %s\n\n",temp->description);
		printf("Valor: %.2f      ",temp->value);
		printf("Detalhes: %s\n",temp->details);
		printf("-----------------------------------------------------------------------------------------------------------\n");
		
		total += temp->value;
		
		printf("\n   ===========================\n    Total: %.2f   \n   ===========================\n",total);
	}
	
	total = 0;
}

//declaração da função alterar
//=============================================================================================================================================================

//função para alterar cadastro
void edit_register(char category[8][14],list_cad *ficha,char titulo[500],char date[11]){
	
	//variaveis locais
	list_cad *temp = ficha->prox;
	char busca_date[11],busca_category[15];	
	int i = 0;
	float value = 0;
	
	//inicialização de variáveis
	strcpy(busca_date,"__/__/____");
	strcpy(busca_category,"-------------");
	
	//verifica se a lista de structs está ou não vazia
	if(ficha->prox == NULL){
			
			//altera a cor do texto para vermelho
			system("COLOR 0C");
			
			//limpa a tela e exibe uma menssagem informativa
			system("cls");
			printf("\n\n\n\t\t\t\tNão existem cadastros na lista!!!");
			sleep (2);
		
	}else{

//recebe a date para busca
		
		//limpa a tela e exibe o título
		system("cls");
		printf("%s",titulo);
			
		//exibe a variavel busca_date
		printf("Informe a data do cadastro \n");
		
		//recebe a date	
		recebe_date(busca_date,titulo);

//recebe a category para busca
		
		printf("\n\nInforme a categoria do cadastro \nCategoria: ");
							
		//inicializa os índices da matriz de categorys
		i = 0;
		int j = 0;
		char sel;		
		//laço de seleção da category
		while(1){
					
			//variável de controle
			setbuf(stdin,NULL);
			sel = getch()-48;
				
			//interrompre o loop para receber a category se a primeira tecla digitada for enter
			if(j == 0  && sel == -35){
				
				printf("\nCategoria: %s\n\n",busca_category);
				break;
						
			}else if(sel == -35 && j !=0){
						
				//recebe o value selecionado pelo usuário
				strcpy(busca_category,category[i]);
				busca_category[12] = ' ';
				system("cls");
				printf("%s",titulo);
				printf("Informe a data do cadastro \nData: %s\n\nInforme a categoria do cadastro \nCategoria: %s\n\n",busca_date,busca_category);
				break;
						
			}else if(sel == 24){
						
				//decrementa i e exibe categorys acima
				i--;
					
			}else if(sel == 32){
						
				//incrementa i e exibe categorys abaixo
				i++;
			}
					
			if(i == 8 ){
						
				//volta no primeiro item 
				i = 0;
						
			}else if(i<0){
						
				//volta no último item 
				i = 7;
			}
			
			system("cls");
			printf("%s",titulo);
			printf("Informe a data do cadastro \nData: %s\n\n\nInforme a categoria do cadastro \nCategoria: %s",busca_date,category[i]);
			j++;
		}
		
//recebe o value para busca
		
		//limpa a tela e exibe o título
		system("cls");
		printf("%s",titulo);
		printf("Informe a data do cadastro \nData: %s\n\n\nInforme a categoria do cadastro \nCategoria: %s\n\n\nInforme o valor do cadastro \nValor: ",busca_date,busca_category);
		
		//recebe o value para busca
		scanf("%f",&value);

//efetua a busca e seleção do cadastro indicado para edição
//=============================================================================================================================================================

		//string vazia
		char cabecalho[500];
		strcpy(cabecalho,titulo);
		strcat(cabecalho,"Tecle enter para manter os dados que aparecem nos campos ou digite novos dados: \n\n\n");
	
		//loop para busca e comparação 
		while(temp->prox != NULL){
			
			if((strcmp(busca_date,temp->date)) == 0 && (strcmp(busca_category,temp->category)) == 0 && (value == temp->value)){
				
				//recebe a nova date
				system("cls");
				printf("%s",titulo);
				recebe_date(temp->date,cabecalho);
				
				//recebe os novos valuees da struct selecionada na lista
				system("cls");
				preencher(category,temp,cabecalho,temp->date);
				break;
			}
			temp = temp->prox;
		}

		//verifica se o cadastro procurado se encontra na última posição da lista
		if((temp->prox == NULL) && (strcmp(busca_date,temp->date)) == 0 && (strcmp(busca_category,temp->category)) == 0 && (value == temp->value)){
				
				//recebe a nova date
				system("cls");
				printf("%s",titulo);
				recebe_date(temp->date,cabecalho);
				
				//recebe os novos valuees da struct selecionada na lista
				system("cls");
				preencher(category,temp,cabecalho,temp->date);
				
		//se não for encontrado nenhum cadastro com os dados informados	
		}else if((temp->prox == NULL) && (strcmp(busca_date,temp->date)) != 0 && (strcmp(busca_category,temp->category)) != 0 && (value != temp->value)){
			
			//altera a cor do texto para vermelho
			system("COLOR 0C");
			
			//feedback de cadastro não encontrado	
			system("cls");
			printf("\n\n\n\t\t\t\tNão encontramos nada, por favor verifique os dados da busca tente novamente!");
			sleep (2);			
		}
	}
}

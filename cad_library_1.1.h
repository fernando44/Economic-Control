//declaração da função preencher
//=============================================================================================================================================================
	
//função de adição de dados do cadastro
void preencher(char category[8][14],list_cad *ficha,char titulo[500],char Date[11]){
	
	//variáveis locais
	int i;
	char sel,vlr[10];
	
	//variável para receber o value
	char value[1000000];
	
	//variável sinalizadora de mudança de variável
	int n = 0;
	
	//variável de inicialização padrão
	char reseta[100];
	
//Recebe os dados da data do cadastro
//===================================================================
	
	//copia a data do sistema para o cadastro
	strcpy(ficha->date,Date);
	
	//atualiza a tela com os dados recebidos
	system("cls");
	printf("%s",titulo);
	printf("Data: %s\n",ficha->date);
	
//Recebe os dados da descrição do cadastro
//===================================================================

	//recebe o value padrão
	strcpy(reseta,"");
	strcpy(reseta,ficha->description);
	
	//inicializa a descrição 
	strcpy(ficha->description," ");
	printf("Descrição: ");
	
	//recebe a descrição
	setbuf(stdin,NULL);
	fgets(ficha->description,100,stdin);
	
	//verifica se a primeira tecla pressionada foi enter
	if(ficha->description[0] == '\n'){
			
		//inicializa de forma padrão a descrição
		strcpy(ficha->description,reseta);
		system("cls");
		printf("%s",titulo);
		printf("Data: %s\nDescrição: %s\nCategoria: %s",ficha->date,ficha->description,ficha->category);
			
	}else{
			
		//susbstitui o \n por \0
		ficha->description[strlen(ficha->description)-1] = '\0';
		printf("Categoria: %s",ficha->category);
		
	}
		
//Recebe os dados da category do cadastro
//===================================================================
	
	//inicializa os índices da matriz de categorys
	i = 0;
	int j = 0;
	
	//laço de seleção da category
	while(1){
				
		//variável de controle
		sel = getch()-48;
			
		//interrompre o loop para receber a category se a primeira tecla digitada for enter
		if(j == 0  && sel == -35){
			
			printf("\nValor: ");
			break;
					
		}else if(sel == -35 && j !=0){
					
			//recebe o value selecionado pelo usuário
			strcpy(ficha->category,category[i]);
			ficha->category[12] = ' ';
			system("cls");
			printf("%s",titulo);
			printf("Data: %s\nDescrição: %s\nCategoria: %s\nValor: ",ficha->date,ficha->description,ficha->category);
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
		printf("Data: %s\nDescrição: %s\nCategoria: %s",ficha->date,ficha->description,category[i]);
		j++;
	}
					
//Recebe os dados do value do cadastro
//===================================================================		
	
	//converte para string recebe o value padrão 
	strcpy(reseta,"");
	sprintf(reseta,"%f",ficha->value);
	
	//recebe a variável de verificação
	strcpy(value," ");
	setbuf(stdin,NULL);
	fgets(value,1000000,stdin);		
			
	//verifica se a primeira tecla pressionada foi o enter		
	if(value[0] != '\n'){
			
		//susbstitui o \n por \0, converte e recebe os details
		value[strlen(value)-1] = '\0';
		ficha->value = atof(value);
		system("cls");
		printf("%s",titulo);
		printf("Data: %s\nDescrição: %s\nCategoria: %s\nValor: %.2f\nDescrição: ",ficha->date,ficha->description,ficha->category,ficha->value);
			
	}else{
		
		//retorna o value padrão
		ficha->value = atof(reseta);
		system("cls");
		printf("%s",titulo);
		printf("Data: %s\nDescrição: %s\nCategoria: %s\nValor: %.2f\nDescrição: ",ficha->date,ficha->description,ficha->category,ficha->value);
		
	}
	
//Recebe details do cadastro
//===================================================================
	
	//reinicializa com os valuees padrão
	strcpy(reseta,"");
	strcpy(reseta,ficha->details);
	
	//reseta e recebe os details
	strcpy(ficha->details," ");
	setbuf(stdin,NULL);
	fgets(ficha->details,100,stdin);
	
	if(ficha->details[0] == '\n'){
		
		//inicializa de forma padrão os details	
		strcpy(ficha->details,reseta);
	
	}else{
		
		//susbstitui o \n por \0 
		ficha->details[strlen(ficha->details)-1] = '\0';	
			
	}
}	


//declaração da função adicionar
//=============================================================================================================================================================

//função para adicionar cadastro na lista
void add_new(char category[LIN][COL],list_cad *list,char titulo[500],char Date[11]){
	
	//alocação de memória para o novo cadastro
	list_cad *novo = (list_cad *)malloc(sizeof(list_cad));
	novo->prox = NULL;
	novo->ant = NULL;
	
	//inicialização do novo cadastro
	strcpy(novo->description,"(Null)");
	strcpy(novo->category,"-------------");
	strcpy(novo->details,"(Null)");
	novo->value = 0;
	
	//chamada da função preencher para receber os valuees da nova alocação
	preencher(category,novo,titulo,Date); 
	
	//verifica se o cadastro não está vazio ou não para adicioná-lo na lista
	if((strcmp(novo->description,"(Null)") != 0) && (strcmp(novo->category,"-------------") != 0) && novo->value != 0){
			
		//verifica se a lista está vazia
		if(list->prox == NULL){
			
			//organização da nova alocação na lista de structs
			novo->prox = list->prox;
			list->prox = novo;
			novo->ant = list;
			
		//verifica se a lista já possui termos	
		}else if(list->prox != NULL){
			
			//organização da nova alocação na lista de structs
			novo->prox = list->prox;
			list->prox = novo;
			novo->ant = list;
			novo->prox->ant = novo;
				
		}
	}
}

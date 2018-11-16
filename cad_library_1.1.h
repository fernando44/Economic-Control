//declaração da função preencher
//=============================================================================================================================================================
	
//função de adição de dados do cadastro
void preencher(char categoria[8][14],lista_cadastro *ficha,char titulo[500],char data_sistema[11]){
	
	//variáveis locais
	int i;
	char sel,vlr[10];
	
	//variável para receber o valor
	char valor[1000000];
	
	//variável sinalizadora de mudança de variável
	int n = 0;
	
	//variável de inicialização padrão
	char reseta[100];
	
//Recebe os dados da data do cadastro
//===================================================================
	
	//copia a data do sistema para o cadastro
	strcpy(ficha->data,data_sistema);
	
	//atualiza a tela com os dados recebidos
	system("cls");
	printf("%s",titulo);
	printf("Data: %s\n",ficha->data);
	
//Recebe os dados da descrição do cadastro
//===================================================================

	//recebe o valor padrão
	strcpy(reseta,"");
	strcpy(reseta,ficha->descricao);
	
	//inicializa a descrição 
	strcpy(ficha->descricao," ");
	printf("Descrição: ");
	
	//recebe a descrição	
	fgets(ficha->descricao,100,stdin);
	
	//verifica se a primeira tecla pressionada foi enter
	if(ficha->descricao[0] == '\n'){
			
		//inicializa de forma padrão a descrição
		strcpy(ficha->descricao,reseta);
		system("cls");
		printf("%s",titulo);
		printf("Data: %s\nDescrição: %s\nCategoria: %s",ficha->data,ficha->descricao,ficha->categoria);
			
	}else{
			
		//susbstitui o \n por \0
		ficha->descricao[strlen(ficha->descricao)-1] = '\0';
		printf("Categoria: %s",ficha->categoria);
		
	}
		
//Recebe os dados da categoria do cadastro
//===================================================================
	
	//inicializa os índices da matriz de categorias
	i = 0;
	int j = 0;
	
	//laço de seleção da categoria
	while(1){
				
		//variável de controle
		sel = getch()-48;
			
		//interrompre o loop para receber a categoria se a primeira tecla digitada for enter
		if(j == 0  and sel == -35){
			
			printf("\nValor: ");
			break;
					
		}else if(sel == -35 and j !=0){
					
			//recebe o valor selecionado pelo usuário
			strcpy(ficha->categoria,categoria[i]);
			ficha->categoria[12] = ' ';
			system("cls");
			printf("%s",titulo);
			printf("Data: %s\nDescrição: %s\nCategoria: %s\nValor: ",ficha->data,ficha->descricao,ficha->categoria);
			break;
					
		}else if(sel == 24){
					
			//decrementa i e exibe categorias acima
			i--;
				
		}else if(sel == 32){
					
			//incrementa i e exibe categorias abaixo
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
		printf("Data: %s\nDescrição: %s\nCategoria: %s",ficha->data,ficha->descricao,categoria[i]);
		j++;
	}
					
//Recebe os dados do valor do cadastro
//===================================================================		
	
	//converte para string recebe o valor padrão 
	strcpy(reseta,"");
	sprintf(reseta,"%f",ficha->valor);
	
	//recebe a variável de verificação
	strcpy(valor," ");
	fgets(valor,1000000,stdin);		
			
	//verifica se a primeira tecla pressionada foi o enter		
	if(valor[0] != '\n'){
			
		//susbstitui o \n por \0, converte e recebe os detalhes
		valor[strlen(valor)-1] = '\0';
		ficha->valor = atof(valor);
			
	}else{
		
		//retorna o valor padrão
		ficha->valor = atof(reseta);
		system("cls");
		printf("%s",titulo);
		printf("Data: %s\nDescrição: %s\nCategoria: %s\nValor: %.2f\nDescrição",ficha->data,ficha->descricao,ficha->categoria,ficha->valor);
		
	}
	
//Recebe detalhes do cadastro
//===================================================================
	
	//reinicializa com os valores padrão
	strcpy(reseta,"");
	strcpy(reseta,ficha->detalhes);
	
	//reseta e recebe os detalhes
	strcpy(ficha->detalhes," ");
	fgets(ficha->detalhes,100,stdin);
	
	if(ficha->detalhes[0] == '\n'){
		
		//inicializa de forma padrão os detalhes	
		strcpy(ficha->detalhes,reseta);
	
	}else{
		
		//susbstitui o \n por \0 
		ficha->detalhes[strlen(ficha->detalhes)-1] = '\0';	
			
	}
}	


//declaração da função adicionar
//=============================================================================================================================================================

//função para adicionar cadastro na lista
void adicionar(char categoria[8][14],lista_cadastro *list,char titulo[500],char data_sistema[11]){
	
	//alocação de memória para o novo cadastro
	lista_cadastro *novo = (lista_cadastro *)malloc(sizeof(lista_cadastro));
	novo->prox = NULL;
	novo->ant = NULL;
	
	//inicialização do novo cadastro
	strcpy(novo->descricao,"(Null)");
	strcpy(novo->categoria,"-------------");
	strcpy(novo->detalhes,"(Null)");
	novo->valor = 0;
	
	//chamada da função preencher para receber os valores da nova alocação
	preencher(categoria,novo,titulo,data_sistema); 
	
	//verifica se o cadastro não está vazio ou não para adicioná-lo na lista
	if((strcmp(novo->descricao,"(Null)") != 0) and (strcmp(novo->categoria,"-------------") != 0) and novo->valor != 0){
			
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

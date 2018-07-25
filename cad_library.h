//declaração da matriz da categoria
char categoria[8][14];

//declaração da função preencher
//=============================================================================================================================================================
	
//função de adição de dados do cadastro
void preencher(lista_cadastro *ficha,char titulo[500],char data_sistema[11]){
	
	//variáveis locais
	int i;
	char sel,vlr[10];
	
	//incialização da matriz de categoria
	strcpy(categoria[0],"Informatica <");
	strcpy(categoria[1],"Contas      <");
	strcpy(categoria[2],"Vestimenta  <");
	strcpy(categoria[3],"Escolar     <");
	strcpy(categoria[4],"Alimenticio <");
	strcpy(categoria[5],"Medicamentos<");
	strcpy(categoria[6],"Documentos  <");
	strcpy(categoria[7],"Compras     <");
	
	
//Recebe os dados da data do cadastro
//===================================================================
	
	//copia a data do sistema para o cadastro
	strcpy(ficha->data,data_sistema);
	
	//exibe a ficha de cadastro
	printf("%s",titulo);
	printf("Data: %s\t\t\tDescrição: %s<\n\n\n\nCategoria: %s\t\tValor: %.2f\n\n\n\nDetalhes(opcional): %s",ficha->data,ficha->descricao,ficha->categoria,ficha->valor,ficha->detalhes);
	
//Recebe os dados da descrição do cadastro
//===================================================================

	//inicializa o contador
	i = 0;
	
	//loop de inserção da descrição
	while(1){
		
		//variável de fluxo de dados
		fflush(stdin);
		sel = getch();
		
		//interrompre o loop para receber a descrição se a primeira tecla pessionada for enter
		if(i == 0 and sel == 13){
			
			break;
			
		}else if(sel != 13 and i == 0){
			
			//inicializa a descrição 
			strcpy(ficha->descricao,"                ");
			//recebe cada caractere da descrição
			ficha->descricao[i] = sel;
			
		}else if(sel != 13 and i != 0){
			
			//recebe cada caractere da descrição
			ficha->descricao[i] = sel;	
			
		}else if(sel == 13){
			
			//substitui o caractere \n por \0 e para o loop
			ficha->descricao[i] = '\0';
			break;
			
		}
		
		//limpa a tela e exibe a ficha de cadastro
		system("cls");
		printf("%s",titulo);
		printf("Data: %s\t\t\tDescrição: %s<\n\n\n\nCategoria: %s\t\tValor: %.2f\n\n\n\nDetalhes(opcional): %s",ficha->data,ficha->descricao,ficha->categoria,ficha->valor,ficha->detalhes);
		i++;
		
		//finaliza a string e interrompe o loop se o contador chegar ao índice máximo
		if(i == 98 ){
			ficha->descricao[99] = '\0';
			break;
		}
	}
	

//Recebe os dados da categoria do cadastro
//===================================================================

	//reinicializa o contador i
	i = 0;
	int j = 0;
	
	//limpa a tela e exibe a ficha de cadastro
	system("cls");
	printf("%s",titulo);
	printf("Data: %s\t\t\tDescrição: %s\n\n\n\nCategoria: %s<\t\tValor: %.2f\n\n\n\nDetalhes(opcional): %s",ficha->data,ficha->descricao,ficha->categoria,ficha->valor,ficha->detalhes);
	
	
	//laço de seleção da categoria
	while(1){
		
		//variável de controle
		sel = getch()-48;
		
		//interrompre o loop para receber a categoria se a primeira tecla digitada for enter
		if(j == 0  and sel == -35){
			
			break;
			
		}else if(sel == -35 and j !=0){
			
			//recebe o valor selecionado pelo usuário
			strcpy(ficha->categoria,categoria[i]);
			ficha->categoria[12] = ' ';
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
		
		//limpa a tela e exibe a ficha de cadastro
		system("cls");
		printf("%s",titulo);
		printf("Data: %s\t\t\tDescrição: %s\n\n\n\nCategoria: %s\t\tValor: %.2f\n\n\n\nDetalhes(opcional): %s",ficha->data,ficha->descricao,categoria[i],ficha->valor,ficha->detalhes);
		j++;
	}
	
	
//Recebe os dados do valor do cadastro
//===================================================================	
	
	//reinicializa o contador i e o valor
	i = 0;
	strcpy(vlr,"            ");
	
	//limpa a tela e exibe a ficha de cadastro 
	system("cls");
	printf("%s",titulo);
	printf("Data: %s\t\t\tDescrição: %s\n\n\n\nCategoria: %s\t\tValor: %.2f        <\n\n\n\nDetalhes(opcional): %s",ficha->data,ficha->descricao,ficha->categoria,ficha->detalhes);
	
		
	//loop para inserção do valor
	while(1){
				
		//inserção do valor
		fflush(stdin);
		vlr[i] = getch();
		
		//interrompe o loop de entrada do valor se a primeira tecla pessionada não for enter 
		if(vlr[0] == 13){
			
			break;
		}
		
		//verifica se a tecla enter foi pressionada
		if(vlr[i] == 13){
			
			//substitui o caractere \n por \0
			vlr[i] = '\0';
			
			//converte e tranfere o valor para o cadastro
			ficha->valor = atof(vlr);
			break;
		
		//verifica se o contador chegou ao valor máximo
		}else if(i == 9){
			
			//finaliza a string
			vlr[i] = '\0';
			break;
			
		//finaliza a string se a vírgula estiver 2 casas antes
		}else if(vlr[i-3] == ','){
			
			//finaliza a string
			vlr[i] = '\0';
			//converte e tranfere o valor para o cadastro
			ficha->valor = atof(vlr);
			break;
		
		}
		
		
		//limpa a tela e exibe a ficha de cadastro 
		system("cls");
		printf("%s",titulo);
		printf("Data: %s\t\t\tDescrição: %s\n\n\n\nCategoria: %s\t\tValor: %s<\n\n\n\nDetalhes(opcional): %s",ficha->data,ficha->descricao,ficha->categoria,vlr,ficha->detalhes);
		i++;
	
	}
	
		
//Recebe detalhes do cadastro
//===================================================================
	
	//reinicialização do contador e da variável de seleção
	i = 0;
	sel = 0;
	
	//limpa a tela e exibe a ficha de cadastro
	system("cls");
	printf("%s",titulo);
	printf("Data: %s\t\t\tDescrição: %s\n\n\n\nCategoria: %s\t\tValor: %.2f\n\n\n\nDetalhes(opcional): %s<",ficha->data,ficha->descricao,ficha->categoria,ficha->valor,ficha->detalhes);
	
	
	//declaração e incialização da variável local
	char detalhes[500];
	for(int i = 0;i <500;i++)
		detalhes[i] = ' ';
	
	//loop para inserção dos destalhes
	while(sel != 13){
		
		//entrada de dados
		fflush(stdin);
		sel = getch();
	
		
		//verifica se o primeiro caractere inserido foi o enter
		if(sel != 13 and i == 0){
						
			//inicializa a variável detalhes
			strcpy(ficha->detalhes,"                     ");
										
		}
		
		//limpa a tela e exibe a ficha de cadastro
		system("cls");
		printf("%s",titulo);
		printf("Data: %s\t\t\tDescrição: %s\n\n\n\nCategoria: %s\t\tValor: %.2f\n\n\n\nDetalhes(opcional): %s<",ficha->data,ficha->descricao,ficha->categoria,ficha->valor,ficha->detalhes);
		
		//verifica se a tecla digitada foi enter
		if(sel != 13){
		
			//recebe o os detalhes caratere por caractere
			ficha->detalhes[i] = sel;
			
		}else if(sel == 13 or i == 499){
			
			//finaliza a string dos detalhes
			ficha->detalhes[i] = '\0';
		}
		
		i++;
	}	
	
	//verifica se o valor da descrição possui os valores padrão
	if((strcmp(ficha->detalhes,"Ex: toalha da mesa..."))==0){
			
		//inicializa a variável detalhes
		for(int j=0;j<500;j++)
			ficha->detalhes[j] = 0;
		
	}
}


//declaração da função adicionar
//=============================================================================================================================================================

//função para adicionar cadastro na lista
void adicionar(lista_cadastro *list,char titulo[500],char data_sistema[11]){
	
	//alocação de memória para o novo cadastro
	lista_cadastro *novo = (lista_cadastro *)malloc(sizeof(lista_cadastro));
	novo->prox = NULL;
	novo->ant = NULL;
	
	//inicialização do novo cadastro
	strcpy(novo->descricao,"Ex: arroz,etc...");
	strcpy(novo->categoria,"-------------");
	strcpy(novo->detalhes,"Ex: toalha da mesa...");
	novo->valor = 0;
	
	//chamada da função preencher para receber os valores da nova alocação
	preencher(novo,titulo,data_sistema);
	
	//verifica se o cadastro não está vazio ou não para adicioná-lo na lista
	if((strcmp(novo->descricao,"Ex: arroz,etc...") != 0) and (strcmp(novo->categoria,"-------------") != 0) and novo->valor != 0){
	
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

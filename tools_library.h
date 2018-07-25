//declaração da função recebe_data
//=============================================================================================================================================================

//função para ler a data do cadastro
void recebe_data(lista_cadastro *ficha,char titulo[500]){
	
	//variável local
	int i = 1;
	char tecla;
	
	//exibe o cabeçalho e o informativo
	printf("%s",titulo);
	printf("Data: %s<\t\t\tDescrição: %s\n\n\n\nCategoria: %s\t\tValor: %.2f\n\n\n\nDetalhes(opcional): %s",ficha->data,ficha->descricao,ficha->categoria,ficha->valor,ficha->detalhes);
	
	fflush(stdin);
	tecla = getch();
	
	if(tecla != 13){
			
		//loop para receber a data 
		while(i<10){
			
			//recebe o primeiro dígito
			ficha->data[0] = tecla;
			
			//insere as barras de separação, ex: dd/mm/aa
			if (i == 2 or i == 5){
				
				ficha->data[i] = '/';
			
			}else{
				//recebe cada caractere da data
				fflush(stdin);
				ficha->data[i] = getch();
			}
			
			//exibe a variavel busca_data
			system("cls");
			printf("%s",titulo);
			printf("Data: %s<\t\t\tDescrição: %s\n\n\n\nCategoria: %s\t\tValor: %.2f\n\n\n\nDetalhes(opcional): %s",ficha->data,ficha->descricao,ficha->categoria,ficha->valor,ficha->detalhes);
			i++;
		}
		//finaliza a string da data
		ficha->data[10] = '\0';
		fflush(stdin);
		getch();
	}
}


//declaração da função listar
//=============================================================================================================================================================

//função para exibir a lista de cadastros
void listar(lista_cadastro *ficha){
	
	//ponteiro temporário para percorrer a lista
	lista_cadastro *temp = ficha->prox;
	
	//variável para exibir a soma total
	float total = 0;
	
	//verifica se a lista de structs está ou não vazia
	if(temp != NULL){
		
		printf("-----------------------------------------------------------------------------------------------------------\n");
		//loop para exibição da struct
		while(temp->prox!=NULL){
			
			//exibe os dados do cadastro
			printf("Data: %s      ",temp->data);
			printf("Categoria: %s      ",temp->categoria);
			printf("Descrição: %s\n\n",temp->descricao);
			printf("Valor: %.2f      ",temp->valor);
			printf("Detalhes: %s\n",temp->detalhes);
			printf("-----------------------------------------------------------------------------------------------------------\n");
			
			total += temp->valor;
			
			temp = temp->prox;
		}
		
		
		//exibe os dados do cadastro da struct na última posição da lista
		printf("Data: %s      ",temp->data);
		printf("Categoria: %s      ",temp->categoria);
		printf("Descrição: %s\n\n",temp->descricao);
		printf("Valor: %.2f      ",temp->valor);
		printf("Detalhes: %s\n",temp->detalhes);
		printf("-----------------------------------------------------------------------------------------------------------\n");
		
		total += temp->valor;
		
		printf("\n   ===========================\n    Total: %.2f   \n   ===========================\n",total);
	}
	
	total = 0;
}

//declaração da função alterar
//=============================================================================================================================================================

//função para alterar cadastro
void alterar(lista_cadastro *ficha,char titulo[500],char data_sistema[11]){
	
	//variaveis locais
	lista_cadastro *temp = ficha->prox;
	char busca_data[11],busca_categoria[15];	
	int i = 0;
	float valor;
	
	//inicialização de variáveis
	strcpy(busca_data,"__/__/____");
	strcpy(busca_categoria,"---------------");
	
	//verifica se a lista de structs está ou não vazia
	if(ficha->prox == NULL){
			
			//altera a cor do texto para vermelho
			system("COLOR 0C");
			
			//limpa a tela e exibe uma menssagem informativa
			system("cls");
			printf("\n\n\n\t\t\t\tNão existem cadastros na lista!!!");
			sleep (2);
		
	}else{
		
		//limpa a tela e exibe o título
		system("cls");
		printf("%s",titulo);
			
		//exibe a variavel busca_data
		printf("Informe a data do cadastro: %s\n",busca_data);
			
		//loop para receber a data 
		while(i<10){
			
			//insere as barras de separação, ex: dd/mm/aa
			if (i == 2 or i == 5){
				busca_data[i] = '/';
			}else{
				//recebe cada caractere da data
				fflush(stdin);
				busca_data[i] = getch();
			}
			//limpa a tela e exibe o título
			system("cls");
			printf("%s",titulo);
		
			//exibe a variavel busca_data
			printf("Informe a data do cadastro: %s\n",busca_data);
			i++;
		}
		fflush(stdin);
		getch();
		
		//limpa a tela e exibe o título
		system("cls");
		printf("%s",titulo);
					
		//recebe a categoria para busca
		printf("\nInforme a categoria do cadastro: ");
		fgets(busca_categoria,15,stdin);
		
		//inicializa o contador na primeira posição em branco
		i = strlen(busca_categoria)-1;
		
		//loop para preencher o restante da string com espaços em branco
		while(i<13){
			
			busca_categoria[i] = ' ';
			i++;
		}
		
		//finaliza a string 
		busca_categoria[13] = '\0';
		
		//limpa a tela e exibe o título
		system("cls");
		printf("%s",titulo);
		
		//recebe o valor para busca
		printf("Informe o valor do cadastro: ");
		scanf("%f",&valor);
		
		//string vazia
		char cabecalho[500];
		strcpy(cabecalho,titulo);
		strcat(cabecalho,"Aperte enter para manter os dados que aparecem nos campos ou digite novos dados!\n\n\n\n");
	
		//loop para busca e comparação 
		while(temp->prox != NULL){
			
			if((strcmp(busca_data,temp->data)) == 0 and (strcmp(busca_categoria,temp->categoria)) == 0 and (valor == temp->valor)){
				
				//recebe a nova data
				system("cls");
				recebe_data(temp,cabecalho);
				
				//recebe os novos valores da struct selecionada na lista
				system("cls");
				preencher(temp,cabecalho,temp->data);
				break;
			}
			temp = temp->prox;
		}

		//verifica se o cadastro procurado se encontra na última posição da lista
		if((temp->prox == NULL) and (strcmp(busca_data,temp->data)) == 0 and (strcmp(busca_categoria,temp->categoria)) == 0 and (valor == temp->valor)){
				
				//recebe a nova data
				system("cls");
				recebe_data(temp,cabecalho);
				
				//recebe os novos valores da struct selecionada na lista
				system("cls");
				preencher(temp,cabecalho,temp->data);
				
			
		}else if((temp->prox == NULL) and (strcmp(busca_data,temp->data)) != 0 and (strcmp(busca_categoria,temp->categoria)) != 0 and (valor != temp->valor)){
			
			//altera a cor do texto para vermelho
			system("COLOR 0C");
			
			//feedback de cadastro não encontrado	
			system("cls");
			printf("\n\n\n\t\t\t\tNão encontramos nada, por favor verifique os dados da busca tente novamente!");
			sleep (2);			
		}
	}
}

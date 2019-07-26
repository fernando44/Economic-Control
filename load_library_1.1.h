//matriz para armazenar anos que possuem cadastro
char m_ano[10000][7];


//declaração e inicialização da matriz dos meses do ano
char meses[12][10] = {"janeiro","fevereiro","março","abril","maio","junho","julho","agosto","setembro","outubro","novembro","dezembro"};


//declaração da função carregar
//=============================================================================================================================================================

//função para ler dados do arquivo para a struct
void load_list(list_cad *ficha,FILE *base_dados,char nome[11],char pasta[7]){
	
	//contador sinalizar fim de dado 
	int cnt = 0;
	
	//variáveis para receber o value e os caracteres do arquivo
	char value[500],digito[2];

	//variável para receber o nome do arquivo
	char arquivo[50];
	
	//copia e adiciona a extensão do nome do arquivo
	strcpy(arquivo,"Database\\");
	strcat(arquivo,pasta);
	strcat(arquivo,nome);
	strcat(arquivo,".txt");
	
	//cria uma alocação para ler os dados do arquivo
	list_cad *recebe = (list_cad *)malloc(sizeof(list_cad));
	recebe->prox = NULL;
	recebe->ant = NULL;
	
	//reinicialização da struct receptora e da variável value
	strcpy(recebe->date,"");
	recebe->value = 0;
	strcpy(recebe->category,"");
	strcpy(recebe->description,"");
	strcpy(recebe->details,"");
	strcpy(value,"");
	
	//inicializa a variável que receberá os valuees dos cadastros
	strcpy(value,"");
	
	//finaliza a string
	digito[1] = '\0';
			
	//teste de abertura de arquivo para leitura
	if((base_dados = fopen(arquivo,"r"))==NULL){
		
		system("cls");
		
		//altera a cor do texto para vermelho
		system("COLOR 0C");
		printf("\n\n\n\t\t\t\tNão foi possível abrir o arquivo %s !!!", arquivo);
		sleep(2);
			
	//abre o arquivo em modo de leitura	
	}else{
			system("cls");
		//transfere os dados do arquivo para a lista de structs
		while((digito[0] = fgetc(base_dados))!=EOF){
			
			//verifica a quebra de linha para adicionar uma nova alocação
			if(digito[0]=='\n' && cnt == 4){
			
				//reseta o contador de verificação
				cnt = 0;
				
				//cria uma nova alocação a cada nova leitura do arquivo
				list_cad *novo = (list_cad *)malloc(sizeof(list_cad));
				novo->prox = NULL;
				novo->ant = NULL;
				
				//tranferência dos dados da struct receptora para a lista
				strcpy(novo->date,recebe->date);
				novo->value = recebe->value;
				strcpy(novo->category,recebe->category);
				strcpy(novo->description,recebe->description);
				strcpy(novo->details,recebe->details);
				
				//inserção das novas alocações na lista
				//verifica o inicio da lista
				if(ficha->prox == NULL){
					
					novo->prox = ficha->prox;
					ficha->prox = novo;
					novo->ant = ficha;
					
				}else if(ficha->prox != NULL){
				
					//reorganização da lista de cadastros	
					novo->prox = ficha->prox;
					ficha->prox = novo;
					novo->ant = ficha;
					novo->prox->ant = novo;
				}
				
				//reinicialização da struct receptora e da variável value
				strcpy(recebe->date,"");
				recebe->value = 0;
				strcpy(recebe->category,"");
				strcpy(recebe->description,"");
				strcpy(recebe->details,"");
				strcpy(value,"");
				
			//aloca os dados em suas respectivas variáveis na struct
			}else if((digito[0] !='\n')){
					
				//incrementa o sinalizador de fim de dado
				if(digito[0] == '\t'){
					cnt++;
				}
				
				//recebe a date	do cadastro
				if(strlen(recebe->date) < 10 && cnt == 0 && digito[0] != '\t' ){
						
						strcat(recebe->date,digito);
					
				}
				
				//recebe o value do cadastro
				if((strlen(recebe->date) == 10 ) && cnt == 1 && digito[0] != '\t'){
					
						strcat(value,digito);				
						recebe->value = atof(value);
						
				}
				
				//recebe a category do cadastro
				if((recebe->value != 0) && cnt == 2 && digito[0] != '\t'){
					
						strcat(recebe->category,digito);
						
				}
				
				//recebe a descrição do cadastro
				if((recebe->category != 0) && cnt == 3 && digito[0] != '\t'){
						
						strcat(recebe->description,digito);
						
				}
				
				//recebe os details do cadastro
				if((recebe->description != 0) && cnt == 4 && digito[0] != '\t'){
					
						strcat(recebe->details,digito);
				
				}
			}
		}
		
		//fecha o arquivo de texto
		fclose(base_dados);
	}
}


//declaração da função desaloca
//=============================================================================================================================================================

//função para liberar memória alocada
void deallocate_list(list_cad *ficha){
	
	list_cad *temp;	
	//laço que percorre e libera a lista
	while(ficha->prox!= NULL){
			
		//reorganização dos apontamentos da lista
		temp = ficha->prox;
		ficha->prox = temp->prox;
		
		//verifica se a a variável temporária chegou ao fim da lista 
		if(temp->prox == NULL){
			
			//reorgazinação do apontamento da lista
			ficha->prox = temp->prox;
			
			//liberação de memória alocada
			free(temp);
			break;
		}	
		
		//reorganização dos apontamento na lista
		temp->prox->ant = ficha;
		free(temp);	
	}	
}


//declaração da função descarregar
//=============================================================================================================================================================

//função para escrever dados da lista de struct no arquivo
void download_list(list_cad *ficha,FILE *base_dados,char nome[11],char pasta[5]){
	
	//variável para receber o nome do arquivo
	char arquivo[50];
	
	//copia e adiciona a extensão do nome do arquivo
	strcpy(arquivo,"Database\\");
	strcat(arquivo,pasta);
	strcat(arquivo,nome);
	strcat(arquivo,".txt");
	
	//verifica se a lista possui itens ou se está vazia
	if(ficha->prox != NULL){
	
		//ponteiro temporario
		list_cad *temp = ficha->prox;
		
		//abre arquivo em modo escrita
		base_dados = fopen(arquivo,"w");
		
		if(temp->prox != NULL){
			//loop para percorrer e gravar a lista de structs no arquivo		
			while(temp->prox != NULL){
				
				fprintf(base_dados,"%s\t",temp->date);
				fprintf(base_dados,"%.2f\t",temp->value);
				fprintf(base_dados,"%s\t",temp->category);
				fprintf(base_dados,"%s\t",temp->description);
				fprintf(base_dados,"%s\n",temp->details);
					
				//recebe o ponteiro seguinte
				temp = temp->prox;
			}
		}
		
		//armazena os dados da ultima struct
		if(temp->prox == NULL){
						
			fprintf(base_dados,"%s\t",temp->date);
			fprintf(base_dados,"%.2f\t",temp->value);
			fprintf(base_dados,"%s\t",temp->category);
			fprintf(base_dados,"%s\t",temp->description);
			fprintf(base_dados,"%s\n",temp->details);
			
		}
				
		//fecha o arquivo
		fclose(base_dados);
	}
}


//declaração da função alt_base_dados
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
		strcpy(m_ano[i],"      ");
		i++;
	}
	
	//reinicializa o contador
	i = 0;
	
	//abre o arquivo lista_anos para leitura
	places = fopen("Database\\list_years.txt","r");
	
	//loop para receber os anos do arquivo para a matriz
	while(fscanf(places,"%s",m_ano[i]) != EOF){
		
		i++;
		
		//para o loop se o índice chegar ao value máximo
		if(i == 9999){
			break;
		}
	}
	
	//fecha o arquivo lista_anos
	fclose(places);
	
	/*variável max recebe a última posição em que a matriz 
	recebeu valuees e reinicializa o contador*/
	max = i-1;	
	i = 0;
	
	//loop para exibir os anos cadastrados e selecioná-los
	while(sel != -35){
		
		//limpa a tela e exibe os meses para seleção
		system("cls");
		printf("%sPressione ESC para permanecer no ano atual\n\n",titulo);
		int u;
		//loop para exibir os anos sem as barras(\\)
		for(u = 0;u<4;u++){
			printf("%c",m_ano[i][u]);
		}
		
		//variável de seleção
		setbuf(stdin,NULL);
		sel = getch()-48;
		
		//permanece no mês atual
		if(sel == -21){
			
			break;
		
		}else if(sel == -35){
			
			//recebe o ano selecionado
			strcpy(sel_ano,m_ano[i]);
			
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
		
		//limpa a tela e exibe os meses para seleção
		system("cls");
		printf("%sPressione ESC para permanecer no mês atual\n\n",titulo);
		printf("%s",meses[i]);
		
		//variável de seleção
		setbuf(stdin,NULL);
		opc = getch()-48;
		
		//permanece no mês atual
		if(opc == -21){
			
			break;
		
		}else if(opc == -35){
			
			//recebe o mês selecionado
			strcpy(sel_mes,meses[i]);
			
		}else if(opc == 24){
			
			//decrementa o value de i e exibe meses acima
			i--;
			
		}else if(opc == 32){
			
			//incrementa o value de i e exibe meses abaixo
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

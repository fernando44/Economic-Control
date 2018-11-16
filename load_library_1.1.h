//estrutura de cadastro dos dados sem ponteiros
typedef struct dados{
	
	char data[11];		//ex: 05/11/2002...
	char descricao[100];//ex: arroz, carne....
	char categoria[14];	//ex: alimentício, informática, material escolar....
	float valor;		//ex: 4.67 R$...
	char detalhes[100]; //ex: teclado para computador .....
	
}cadastro;


//matriz para armazenar anos que possuem cadastro
char m_ano[10000][7];


//matriz dos meses do ano
char meses[12][10];


//declaração da função carregar
//=============================================================================================================================================================

//função para ler dados do arquivo para a struct
void carregar(lista_cadastro *ficha,FILE *base_dados,char nome[11],char pasta[7]){
	
	//contador sinalizar fim de dado 
	int cnt = 0;
	
	//variáveis para receber o valor e os caracteres do arquivo
	char valor[500],digito[2];

	//variável para receber o nome do arquivo
	char arquivo[50];
	
	//copia e adiciona a extensão do nome do arquivo
	strcpy(arquivo,"Database\\");
	strcat(arquivo,pasta);
	strcat(arquivo,nome);
	strcat(arquivo,".txt");
	
	//cria uma alocação para ler os dados do arquivo
	lista_cadastro *recebe = (lista_cadastro *)malloc(sizeof(lista_cadastro));
	recebe->prox = NULL;
	recebe->ant = NULL;
	
	//reinicialização da struct receptora e da variável valor
	strcpy(recebe->data,"");
	recebe->valor = 0;
	strcpy(recebe->categoria,"");
	strcpy(recebe->descricao,"");
	strcpy(recebe->detalhes,"");
	strcpy(valor,"");
	
	//inicializa a variável que receberá os valores dos cadastros
	strcpy(valor,"");
	
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
			if(digito[0]=='\n' and cnt == 4){
			
				//reseta o contador de verificação
				cnt = 0;
				
				//cria uma nova alocação a cada nova leitura do arquivo
				lista_cadastro *novo = (lista_cadastro *)malloc(sizeof(lista_cadastro));
				novo->prox = NULL;
				novo->ant = NULL;
				
				//tranferência dos dados da struct receptora para a lista
				strcpy(novo->data,recebe->data);
				novo->valor = recebe->valor;
				strcpy(novo->categoria,recebe->categoria);
				strcpy(novo->descricao,recebe->descricao);
				strcpy(novo->detalhes,recebe->detalhes);
				
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
				
				//reinicialização da struct receptora e da variável valor
				strcpy(recebe->data,"");
				recebe->valor = 0;
				strcpy(recebe->categoria,"");
				strcpy(recebe->descricao,"");
				strcpy(recebe->detalhes,"");
				strcpy(valor,"");
				
			//aloca os dados em suas respectivas variáveis na struct
			}else if((digito[0] !='\n')){
					
				//incrementa o sinalizador de fim de dado
				if(digito[0] == '\t'){
					cnt++;
				}
				
				//recebe a data	do cadastro
				if(strlen(recebe->data) < 10 and cnt == 0 and digito[0] != '\t' ){
						
						strcat(recebe->data,digito);
					
				}
				
				//recebe o valor do cadastro
				if((strlen(recebe->data) == 10 ) and cnt == 1 and digito[0] != '\t'){
					
						strcat(valor,digito);				
						recebe->valor = atof(valor);
						
				}
				
				//recebe a categoria do cadastro
				if((recebe->valor != 0) and cnt == 2 and digito[0] != '\t'){
					
						strcat(recebe->categoria,digito);
						
				}
				
				//recebe a descrição do cadastro
				if((recebe->categoria != 0) and cnt == 3 and digito[0] != '\t'){
						
						strcat(recebe->descricao,digito);
						
				}
				
				//recebe os detalhes do cadastro
				if((recebe->descricao != 0) and cnt == 4 and digito[0] != '\t'){
					
						strcat(recebe->detalhes,digito);
				
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
void desaloca(lista_cadastro *ficha){
		
	//laço que percorre e libera a lista
	while(ficha->prox!= NULL){
			
		//reorganização dos apontamentos da lista
		lista_cadastro *temp = ficha->prox;
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
void descarregar(lista_cadastro *ficha,FILE *base_dados,char nome[11],char pasta[7]){
	
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
		lista_cadastro *temp = ficha->prox;
		
		//abre arquivo em modo escrita
		base_dados = fopen(arquivo,"w");
		
		if(temp->prox != NULL){
			//loop para percorrer e gravar a lista de structs no arquivo		
			while(temp->prox != NULL){
				
				fprintf(base_dados,"%s\t",temp->data);
				fprintf(base_dados,"%f\t",temp->valor);
				fprintf(base_dados,"%s\t",temp->categoria);
				fprintf(base_dados,"%s\t",temp->descricao);
				fprintf(base_dados,"%s\n",temp->detalhes);
					
				//recebe o ponteiro seguinte
				temp = temp->prox;
			}
		}
		
		//armazena os dados da ultima struct
		if(temp->prox == NULL){
						
			fprintf(base_dados,"%s\t",temp->data);
			fprintf(base_dados,"%f\t",temp->valor);
			fprintf(base_dados,"%s\t",temp->categoria);
			fprintf(base_dados,"%s\t",temp->descricao);
			fprintf(base_dados,"%s\n",temp->detalhes);
			
		}
				
		//fecha o arquivo
		fclose(base_dados);
	}
}


//declaração da função alt_base_dados
//=============================================================================================================================================================

//função para alternar a base de dados que o usuário deseja acessar
void alt_base_dados(char sel_mes[11],char sel_ano[7],char titulo[366],FILE *locais){
	
	//variáveis locais
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
	locais = fopen("Database\\lista_anos.txt","r");
	
	//loop para receber os anos do arquivo para a matriz
	while(fscanf(locais,"%s",m_ano[i]) != EOF){
		
		i++;
		
		//para o loop se o índice chegar ao valor máximo
		if(i == 9999){
			break;
		}
	}
	
	//fecha o arquivo lista_anos
	fclose(locais);
	
	/*variável max recebe a última posição em que a matriz 
	recebeu valores e reinicializa o contador*/
	max = i-1;	
	i = 0;
	
	//loop para exibir os anos cadastrados e selecioná-los
	while(sel != -35){
		
		//limpa a tela e exibe os meses para seleção
		system("cls");
		printf("%sPressione ESC para permanecer no ano atual\n\n",titulo);
		
		//loop para exibir os anos sem as barras(\\)
		for(int u = 0;u<4;u++){
			printf("%c",m_ano[i][u]);
		}
		
		//variável de seleção
		fflush(stdin);
		sel = getch()-48;
		
		//permanece no mês atual
		if(sel == -21){
			
			break;
		
		}else if(sel == -35){
			
			//recebe o ano selecionado
			strcpy(sel_ano,m_ano[i]);
			
		}else if(sel == 24){
			
			//decrementa o valor de i e exibe anos acima
			i--;
			
		}else if(sel == 32){
			
			//incrementa o valor de i e exibe anos abaixo
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
	
	//inicalização da matriz de seleção dos meses
	strcpy(meses[0],"janeiro");
	strcpy(meses[1],"fevereiro");
	strcpy(meses[2],"março");
	strcpy(meses[3],"abril");
	strcpy(meses[4],"maio");
	strcpy(meses[5],"junho");
	strcpy(meses[6],"julho");
	strcpy(meses[7],"agosto");
	strcpy(meses[8],"setembro");
	strcpy(meses[9],"outubro");
	strcpy(meses[10],"novembro");
	strcpy(meses[11],"dezembro");
	
	//loop de seleção do mês do base de dados
	while(opc != -35){
		
		//limpa a tela e exibe os meses para seleção
		system("cls");
		printf("%sPressione ESC para permanecer no mês atual\n\n",titulo);
		printf("%s",meses[i]);
		
		//variável de seleção
		fflush(stdin);
		opc = getch()-48;
		
		//permanece no mês atual
		if(opc == -21){
			
			break;
		
		}else if(opc == -35){
			
			//recebe o mês selecionado
			strcpy(sel_mes,meses[i]);
			
		}else if(opc == 24){
			
			//decrementa o valor de i e exibe meses acima
			i--;
			
		}else if(opc == 32){
			
			//incrementa o valor de i e exibe meses abaixo
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

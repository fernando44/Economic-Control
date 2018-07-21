//estrutura de cadastro dos dados sem ponteiros
typedef struct dados{
	
	char data[11];		//ex: 05/11/2002...
	char descricao[100];//ex: arroz, carne....
	char categoria[14];	//ex: alimentício, informática, material escolar....
	float valor;		//ex: 4.67 R$...
	char detalhes[500]; //ex: teclado para computador .....
	
}cadastro;


//matriz para armazenar anos que possuem cadastro
char m_ano[10000][7];


//matriz dos meses do ano
char meses[12][10];


//declaração da função carregar
//=============================================================================================================================================================

//função para ler dados do arquivo para a struct
void carregar(lista_cadastro *ficha,FILE *base_dados,char nome[11],char pasta[7]){
	
	//variável para receber o nome do arquivo
	char arquivo[50];
	
	//copia e adiciona a extensão do nome do arquivo
	strcpy(arquivo,"Database\\");
	strcat(arquivo,pasta);
	strcat(arquivo,nome);
	strcat(arquivo,".txt");
	
	if((base_dados = fopen(arquivo,"rb")) != NULL){
		
		//cria uma alocação para leitura do arquivo
		cadastro recebe;
		
		//passa os dados do arquivo para a lista de structs
		while((fread(&recebe,sizeof(recebe),1,base_dados))==1){
			
			//cria uma nova alocação a cada nova leitura do arquivo
			lista_cadastro *novo = (lista_cadastro *)malloc(sizeof(lista_cadastro));
			novo->prox = NULL;
			novo->ant = NULL;
			
			//transfere os dados de uma estrutura para outra
			strcpy(novo->data,recebe.data);
			novo->valor = recebe.valor;
			strcpy(novo->descricao,recebe.descricao);
			strcpy(novo->categoria,recebe.categoria);
			strcpy(novo->detalhes,recebe.detalhes);
			
			
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
		
		//liberação de memória alocada e reorganização dos apontamentos da lista
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
		
		//struct para guardar em arquivo
		cadastro armazena;
		
		//abre arquivo em modo escrita binária
		base_dados = fopen(arquivo,"wb");
	
		//loop para percorrer e gravar a lista de structs no arquivo		
		while(temp->prox != NULL){
			
			//transpõe os dados para struct de armazenamento
			strcpy(armazena.categoria,temp->categoria);
			strcpy(armazena.data,temp->data);
			strcpy(armazena.descricao,temp->descricao);
			strcpy(armazena.detalhes,temp->detalhes);
			armazena.valor = temp->valor;
			
			//grava os dados da lista de structs no arquivo
			fwrite(&armazena,sizeof(armazena),1,base_dados);
			
			temp = temp->prox;
		}
		
		//armazena os dados da ultima struct
		if(temp->prox == NULL){
		
			//transpõe os dados para struct de armazenamento
			strcpy(armazena.categoria,temp->categoria);
			strcpy(armazena.data,temp->data);
			strcpy(armazena.descricao,temp->descricao);
			strcpy(armazena.detalhes,temp->detalhes);
			armazena.valor = temp->valor;
			
			//grava os dados da lista de structs no arquivo
			fwrite(&armazena,sizeof(armazena),1,base_dados);
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
			
			//decrementa o valor de i e anos meses acima
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

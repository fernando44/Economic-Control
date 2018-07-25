//declaração de bibliotecas nativas
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<locale.h>
#include<unistd.h>

//===================================================================
//ponteiro para arquivos de texto
FILE *base_dados,*locais;

//===================================================================
//estrutura de cadastro dos dados para listas
typedef struct lista_dados{
	
	struct lista_dados *ant; //ponteiro para posição anterior
	struct lista_dados *prox; //ponteiro para posição seguinte
	char data[11];		//ex: 05/11/2002...
	char descricao[100];//ex: arroz, carne....
	char categoria[14];	//ex: alimentício, informática, material escolar....
	float valor;		//ex: 4.67 R$...
	char detalhes[500]; //ex: teclado para computador .....
	
}lista_cadastro;

//===================================================================
//declaração de bibliotecas exclusivas
#include"cad_library.h"
#include"load_library.h"
#include"tools_library.h"
#include"buble-sort_library.h"


//variáveis globais
char data_sistema[11],mes[11],ano[7];
char pasta[25],verifica[14];

//declaração da função principal
//=============================================================================================================================================================
int main(){

//Configura o nome da janela e acentuação
//===================================================================
	
	//habilita a acentuação com base na localidade padrão do sistema
	setlocale(LC_ALL,"");
	
	//renomeia a janela do terminal
	system ("title Controle Econômico");


//Recebe a data do sistema
//===================================================================	
	//estrutura para obter a data do sistema
	struct tm * tm;
	time_t t;
	time(&t);
	tm = localtime(&t);
	
	//recebe a data no formato dd-mm-aa
	strftime(data_sistema, 11, "%d-%m-%Y", tm);
	
	//formatação da data
	data_sistema[2] = data_sistema[5] = '/';
	
	//recebe o mês que será utilizado para nomear a base de dados
	strftime(mes, 11, "%B", tm);
	
	//recebe caminho que será utilizado para nomear o diretório de armazenamento da base de dados
	strftime(ano, 5, "%Y", tm);
	
//Concatena comandos e nomes para diretórios e arquivos da base de dados
//===================================================================	

	//copia o comando para criar o diretório principal de armazenamento da base de dados
	strcpy(pasta,"mkdir Database\\");
		
	//recebe o nome do diretório de armazenamento da base de dados
	strcat(pasta,ano);
		
	//concatena barras para posterior acesso ao diretório de armazenamento da base de dados ex: '2014\\outubro.txt'
	strcat(ano,"\\");
	
	//adiciona o caminho, a extensão e o nome do arquivo de verificação
	strcpy(verifica,"Database\\");
	strcat(verifica,ano);
	strcat(verifica,"directory_scan");
	strcat(verifica,".mdf");
	
//Verificação da existência do diretório da base de dados
//===================================================================
	
	//verifica se o diretório já existe
	if((base_dados = fopen(verifica,"rb")) == NULL){
		
		//cria uma pasta para armazenar a base de dados 
		system(pasta);
		
		//cria o arquivo de verificação
		base_dados = fopen(verifica,"wb");
		
		//adiciona o novo ano ao arquivo lista_anos
		locais = fopen("Database\\lista_anos.txt","a");
		
		//grava o novo ano no arquivo
		fprintf(locais,"%s",ano);
		fprintf(locais,"%c",'\n');
		
		//fecha o arquivo de lista_anos
		fclose(locais);
		
		//fecha o arquivo de verificação
		fclose(base_dados);
		
	}
	
//Estrutura do menu
//===================================================================
	
	//declaração de variáveis locais
	int sel = -1;
	char titulo[366];
	char sel_mes[11];
	char sel_ano[7];
	
	//cria um cabeçalho para o programa
	strcpy(titulo,"***********************************************************************************************************************\n\n*****************************************| Controle Econômico |********************************************************\n\n***********************************************************************************************************************\n\n\n\n");
	
	//declaração da ficha de cadastro(referência do início da lista)
	lista_cadastro *lista_cad = (lista_cadastro *)malloc(sizeof(lista_cadastro));
	lista_cad->prox = NULL;
	lista_cad->ant = NULL;
	
	//recebe o mês e ano atual
	strcpy(sel_mes,mes);
	strcpy(sel_ano,ano);
	
	//loop do menu	
	while(1){
		
		//mantém a cor do texto verde
		system("COLOR 0A");
		
		//carrega dados dos arquivos para a lista
		carregar(lista_cad,base_dados,sel_mes,sel_ano);
		
		//exibe o menu de opções para seleção
		system("cls");
		printf("%s",titulo);
		printf("Selecione uma opção:\n\n1 - Novo cadastro \n2 - Exibir cadastros \n3 - Alterar cadastro\n4 - Alternar base de dados\n5 - Sobre\n6 - Sair");
		
		fflush(stdin);
		sel = getch()-48;
			
		//estrutura para direcionamento da opção selecionada	
		switch(sel){
			
			case 1:{
				
				system("cls");
				//realiza um novo cadastro
				adicionar(lista_cad,titulo,data_sistema);
				//grava a lista em arquivos
				descarregar(lista_cad,base_dados,sel_mes,sel_ano);	
				break;
			}
			
			case 2:{
				
				//verifica se a lista está vazia ou não 
				if(lista_cad->prox == NULL){
					
					//altera a cor do texto para vermelho
					system("COLOR 0C");
			
					//feedback de lista vazia
					system("cls");
					printf("\n\n\n\t\t\t\tNão existem cadastros na lista!!!");
					sleep (2);
					
				}else{
				
					//reinicializa a variável de seleção
					sel = 1;
					
					//variável de eibição do submenu
					char submenu[220];
					
					//inicializa o submenu
					strcpy(submenu,"\n\n  ================================\n |   1 - Ordenar por data         |\n |   2 - Ordenar por valor        |\n |   3 - Ordenar por categoria    |\n |   ESC - Retornar ao menu       |\n  ================================\n");
					
					while(1){
							
						//mantém a cor do texto verde
						system("COLOR 0A");
						
						if(sel == 1){
							
							//ordena a lista por data
							ord_data(lista_cad);
							//exibe a lista de cadastros ordenados por data
							system("cls");
							printf("%s",titulo);
							listar(lista_cad);
							printf("%s",submenu);
							
						}else if(sel == 2){
						
							//ordena a lista por valor
							ord_valor(lista_cad);
							//exibe a lista de cadastros ordenados por valor
							system("cls");
							printf("%s",titulo);
							listar(lista_cad);
							printf("%s",submenu);
							
						}else if(sel == 3){
							
							//ordena por categoria
							ord_categoria(lista_cad);
							//exibe a lista de cadastros ordenados por categoria
							system("cls");
							printf("%s",titulo);
							listar(lista_cad);
							printf("%s",submenu);
						}
						
						//recebe as opções do menu de exibição
						fflush(stdin);
						sel = getch()-48;
						
						if(sel == -21){
							//sai do menu de exibição da lista
							break;
							
						}
						
						if(sel != 1 and sel != 2 and sel != -21 and sel !=3){
							
							//altera a cor do texto para vermelho
							system("COLOR 0C");
							
							//feedback default
							system("cls");
							printf("\n\n\n\t\t\t\tOpção inválida!");
							sleep (1);
							sel = 1;
							
							
						}
					}
				}
				break;
			}
			
			case 3:{
				system("cls");
				printf("%s",titulo);
				//altera um cadastro
				alterar(lista_cad,titulo,data_sistema);
				//grava a lista em arquivos
				descarregar(lista_cad,base_dados,sel_mes,sel_ano);		
				break;
			}
			
			case 4:{
				
				//permite o acesso a dados de outros períodos
				system("cls");
				printf("%s",titulo);	
							
				//alterna a base de dados que o usuário deseja utilizar
				alt_base_dados(sel_mes,sel_ano,titulo,locais);
								
				break;
			}
				
			case 5:{
				//adicionais
				system("cls");
				printf("%s",titulo);
				printf("Este software é destinado para uso pessoal.\nNão é recomendado o uso ambientes empresariais !!!\n\n");
				printf("Desenvolvedor: Quemuel Alves Nassor\n\nContato ou suporte: quemuelalp@hotmail.com\n\nVersão: 1.0.1");
				fflush(stdin);
				getch();
				
				break;
			}
			
			case 6:{
				
				//sair do programa
				system("cls");
				exit(0);
				break;
			}
				
			default:
				
				//muda a cor do texto para vermelho
				system("COLOR 0C");
				
				//feedback default
				system("cls");
				printf("\n\n\n\t\t\t\tOpção inválida!");
				sleep(1);
				
		}
		//liberação da memória alocada na lista
		desaloca(lista_cad);
					
	}
	
	return(0);
}

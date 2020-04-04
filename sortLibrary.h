/*
	This library contains functions to
	sort the regList by date, or by Id
	or by value
*/

//Dependencies
#include<string.h>

//Function to order regList by ascending date
reg *orderByDate(reg *regList){
	
	//Local variables
	reg *aux, *percursor;
	
	//Set start point of percursor
	percursor = navStart(regList);
		
	//percursor loop
	while(percursor != NULL){	
			
		//atribuição de valuees das variáveis temporárias
		aux = percursor->prox;
			
		//Aux loop
		 while(aux != NULL){
				
			//Check and sort the items in the list
			if(strcmp(percursor->date,aux->date)>0){
		 		
				percursor->prox = aux->prox;
				aux->prox  != NULL ? aux->prox->ant = percursor : 0;
				aux->ant = percursor->ant;
				percursor->ant != NULL ? percursor->ant->prox = aux : 0;
				percursor->ant = aux;
				aux->prox = percursor;
				percursor = aux;
			}
			aux = aux->prox;
		}
		percursor = percursor->prox;
	}
	
	return navStart(regList);
}

//Function to order regList by ascending id
reg *orderById(reg *regList){
	
	//Local variables
	reg *aux, *percursor;
	
	//Set start point of percursor
	percursor = navStart(regList);
		
	//percursor loop
	while(percursor != NULL){	
			
		//atribuição de valuees das variáveis temporárias
		aux = percursor->prox;
			
		//Aux loop
		 while(aux != NULL){
				
			//Check and sort the items in the list
			if(percursor->id > aux->id){
		 		
				percursor->prox = aux->prox;
				aux->prox  != NULL ? aux->prox->ant = percursor : 0;
				aux->ant = percursor->ant;
				percursor->ant != NULL ? percursor->ant->prox = aux : 0;
				percursor->ant = aux;
				aux->prox = percursor;
				percursor = aux;
			}
			aux = aux->prox;
		}
		percursor = percursor->prox;
	}
	
	return navStart(regList);
}

//Function to order regList by ascending value
reg *orderByValue(reg *regList){
	
	//Local variables
	reg *aux, *percursor;
	
	//Set start point of percursor
	percursor = navStart(regList);
		
	//percursor loop
	while(percursor != NULL){	
			
		//atribuição de valuees das variáveis temporárias
		aux = percursor->prox;
			
		//Aux loop
		 while(aux != NULL){
				
			//Check and sort the items in the list
			if(percursor->value > aux->value){
		 		
				percursor->prox = aux->prox;
				aux->prox  != NULL ? aux->prox->ant = percursor : 0;
				aux->ant = percursor->ant;
				percursor->ant != NULL ? percursor->ant->prox = aux : 0;
				percursor->ant = aux;
				aux->prox = percursor;
				percursor = aux;
			}
			aux = aux->prox;
		}
		percursor = percursor->prox;
	}
	
	return navStart(regList);
}

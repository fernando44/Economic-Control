/*
	This library contains functions to
	sort the regList by date, or by Id
	or by value
*/

//Dependencies
#include<string.h>
#include<unistd.h>

//Function to order regList by ascending date
reg *orderByDate(reg *regList){
	
	//Local variables
	reg *aux, *percursor;
	
	//Check if regsList is empty
	if(regList == NULL || strcmp(regList->date ,"\0") == 0){
		
		//Feedback if regsList is empty
		ClrScr();
		printf("\n\n\n\t\t\t\tNo exists records to order!!!");
		sleep (2);
		
	}else{
	
		//Set start point of percursor
		percursor = navStart(regList);
			
		//percursor loop
		while(percursor != NULL){	
				
			//set aux variable value
			aux = percursor->next;
				
			//Aux loop
			 while(aux != NULL){
					
				//Check and sort the items in the list
				if(strcmp(percursor->date,aux->date)>0){
			 		
					percursor->next = aux->next;
					aux->next  != NULL ? aux->next->prev = percursor : 0;
					aux->prev = percursor->prev;
					percursor->prev != NULL ? percursor->prev->next = aux : 0;
					percursor->prev = aux;
					aux->next = percursor;
					percursor = aux;
				}
				aux = aux->next;
			}
			percursor = percursor->next;
		}
	}
	
	return navStart(regList);
}

//Function to order regList by ascending id
reg *orderById(reg *regList){
	
	//Local variables
	reg *aux, *percursor;
	
	//Check if regsList is empty
	if(regList == NULL || strcmp(regList->date ,"\0") == 0){
		
		//Feedback if regsList is empty
		ClrScr();
		printf("\n\n\n\t\t\t\tNo exists records to order!!!");
		sleep (2);
		
	}else{
		
		//Set start point of percursor
		percursor = navStart(regList);
			
		//percursor loop
		while(percursor != NULL){	
				
			//set aux variable value
			aux = percursor->next;
				
			//Aux loop
			 while(aux != NULL){
					
				//Check and sort the items in the list
				if(percursor->id > aux->id){
			 		
					percursor->next = aux->next;
					aux->next  != NULL ? aux->next->prev = percursor : 0;
					aux->prev = percursor->prev;
					percursor->prev != NULL ? percursor->prev->next = aux : 0;
					percursor->prev = aux;
					aux->next = percursor;
					percursor = aux;
				}
				aux = aux->next;
			}
			percursor = percursor->next;
		}
	}
	
	return navStart(regList);
}

//Function to order regList by ascending value
reg *orderByValue(reg *regList){
	
	//Local variables
	reg *aux, *percursor;
	
	//Check if regsList is empty
	if(regList == NULL || strcmp(regList->date ,"\0") == 0){
		
		//Feedback if regsList is empty
		ClrScr();
		printf("\n\n\n\t\t\t\tNo exists records to order!!!");
		sleep (2);
		
	}else{
	
		//Set start point of percursor
		percursor = navStart(regList);
			
		//percursor loop
		while(percursor != NULL){	
				
			//set aux variable value
			aux = percursor->next;
				
			//Aux loop
			 while(aux != NULL){
					
				//Check and sort the items in the list
				if(percursor->value > aux->value){
			 		
					percursor->next = aux->next;
					aux->next  != NULL ? aux->next->prev = percursor : 0;
					aux->prev = percursor->prev;
					percursor->prev != NULL ? percursor->prev->next = aux : 0;
					percursor->prev = aux;
					aux->next = percursor;
					percursor = aux;
				}
				aux = aux->next;
			}
			percursor = percursor->next;
		}
	}
	
	return navStart(regList);
}

//declaração da função ord_date
//=============================================================================================================================================================

//função de ordenação por date
void ord_date(list_cad *ordena){
	
	//variáveis locais
	list_cad *teste = ordena->prox;
	
	//indicador de passagem do loop
	int marcador = -5;
	
	//verifica se a lista de structs está vazia
	if(teste->prox != NULL){
		
		//variáveis temporárias para percorrer e ordenar a lista
		list_cad *temp1, *temp2;
		
		//loop secundário de verificação de ordenação 
		while(marcador !=0){
			
			//atribuição de valuees das variáveis temporárias
			temp1 = ordena->prox;
			temp2 = temp1->prox;
			
			//contador para verificar se a lista possui termos desordenados
			marcador = 0;
			
			//loop primário de ordenação 
		 	while(temp2->prox != NULL){
				
				//verifica se o segundo item é menor que o primeiro	
				if(strcmp(temp2->date,temp1->date)<0){
			 		
					temp1->prox = temp2->prox;
					temp2->prox->ant = temp1;
					temp2->ant = temp1->ant;
					temp1->ant->prox = temp2;
					temp1->ant = temp2;
					temp2->prox = temp1;
					
					marcador++;
	
				}
				
				//reatribuição de valuees das variáveis temporárias
				temp1 = temp2;
				temp2 = temp2->prox;
			
			}
			
			//verificação de termos desordenados ao fim da lista
			if((temp2->prox == NULL ) && (strcmp(temp2->date,temp1->date)<0)){
				 
				 	temp1->prox = temp2->prox;
				 	temp2->prox = temp1;
				 	temp2->ant = temp1->ant;
				 	temp1->ant = temp2;
				 	temp2->ant->prox = temp2;
				 	marcador++;
				
			}
		}
	}
}

//declaração da função ord_value
//=============================================================================================================================================================

//função de ordenação por value
void ord_value(list_cad *ordena2){
	
	//variáveis locais
	list_cad *teste = ordena2->prox;
	
	//indicador de passagem do loop
	int marcador = -5;
	
	//verifica se a lista de structs está vazia
	if(teste->prox != NULL){
		
		//variáveis temporárias para percorrer e ordenar a lista
		list_cad *temp1, *temp2;
		
		//loop secundário de verificação de ordenação 
		while(marcador !=0){
			
			//atribuição de valuees das variáveis temporárias
			temp1 = ordena2->prox;
			temp2 = temp1->prox;
			
			//contador para verificar se a lista possui termos desordenados
			marcador = 0;
			
			//loop primário de ordenação 
		 	while(temp2->prox != NULL){
				
				//verifica se o segundo item é menor que o primeiro	
				if(temp2->value < temp1->value){
			 		
					temp1->prox = temp2->prox;
					temp2->prox->ant = temp1;
					temp2->ant = temp1->ant;
					temp1->ant->prox = temp2;
					temp1->ant = temp2;
					temp2->prox = temp1;
					
					marcador++;
				 	
				}
				
				//reatribuição de valuees das variáveis temporárias
				temp1 = temp2;
				temp2 = temp2->prox;
			
			}
			
			//verificação de termos desordenados ao fim da lista
			if((temp2->prox == NULL ) && (temp2->value < temp1->value)){
				 
				 	temp1->prox = temp2->prox;
				 	temp2->prox = temp1;
				 	temp2->ant = temp1->ant;
				 	temp1->ant = temp2;
				 	temp2->ant->prox = temp2;
				 	marcador++;
				 
			}
		}
	}
}

//declaração da função ord_category
//=============================================================================================================================================================

//função de ordenação por date
void ord_category(list_cad *ordena){
	
	//variáveis locais
	list_cad *teste = ordena->prox;
	
	//indicador de passagem do loop
	int marcador = -5;
	
	//verifica se a lista de structs está vazia
	if(teste->prox != NULL){
		
		//variáveis temporárias para percorrer e ordenar a lista
		list_cad *temp1, *temp2;
		
		//loop secundário de verificação de ordenação 
		while(marcador !=0){
			
			//atribuição de valuees das variáveis temporárias
			temp1 = ordena->prox;
			temp2 = temp1->prox;
			
			//contador para verificar se a lista possui termos desordenados
			marcador = 0;
			
			//loop primário de ordenação 
		 	while(temp2->prox != NULL){
				
				//verifica se o segundo item é menor que o primeiro	
				if(strcmp(temp2->category,temp1->category)<0){
			 		
					temp1->prox = temp2->prox;
					temp2->prox->ant = temp1;
					temp2->ant = temp1->ant;
					temp1->ant->prox = temp2;
					temp1->ant = temp2;
					temp2->prox = temp1;
					
					marcador++;
	
				}
				
				//reatribuição de valuees das variáveis temporárias
				temp1 = temp2;
				temp2 = temp2->prox;
			
			}
			
			//verificação de termos desordenados ao fim da lista
			if((temp2->prox == NULL ) && (strcmp(temp2->category,temp1->category)<0)){
				 
				 	temp1->prox = temp2->prox;
				 	temp2->prox = temp1;
				 	temp2->ant = temp1->ant;
				 	temp1->ant = temp2;
				 	temp2->ant->prox = temp2;
				 	marcador++;
				
			}
		}
	}
}

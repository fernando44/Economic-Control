//declaração da função ord_data
//=============================================================================================================================================================

//função de ordenação por data
void ord_data(lista_cadastro *ordena){
	
	//variáveis locais
	lista_cadastro *teste = ordena->prox;
	
	//indicador de passagem do loop
	int marcador = -5;
	
	//verifica se a lista de structs está vazia
	if(teste->prox != NULL){
		
		//variáveis temporárias para percorrer e ordenar a lista
		lista_cadastro *temp1, *temp2;
		
		//loop secundário de verificação de ordenação 
		while(marcador !=0){
			
			//atribuição de valores das variáveis temporárias
			temp1 = ordena->prox;
			temp2 = temp1->prox;
			
			//contador para verificar se a lista possui termos desordenados
			marcador = 0;
			
			//loop primário de ordenação 
		 	while(temp2->prox != NULL){
				
				//verifica se o segundo item é menor que o primeiro	
				if(strcmp(temp2->data,temp1->data)<0){
			 		
					temp1->prox = temp2->prox;
					temp2->prox->ant = temp1;
					temp2->ant = temp1->ant;
					temp1->ant->prox = temp2;
					temp1->ant = temp2;
					temp2->prox = temp1;
					
					marcador++;
	
				}
				
				//reatribuição de valores das variáveis temporárias
				temp1 = temp2;
				temp2 = temp2->prox;
			
			}
			
			//verificação de termos desordenados ao fim da lista
			if((temp2->prox == NULL ) and (strcmp(temp2->data,temp1->data)<0)){
				 
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

//declaração da função ord_valor
//=============================================================================================================================================================

//função de ordenação por valor
void ord_valor(lista_cadastro *ordena2){
	
	//variáveis locais
	lista_cadastro *teste = ordena2->prox;
	
	//indicador de passagem do loop
	int marcador = -5;
	
	//verifica se a lista de structs está vazia
	if(teste->prox != NULL){
		
		//variáveis temporárias para percorrer e ordenar a lista
		lista_cadastro *temp1, *temp2;
		
		//loop secundário de verificação de ordenação 
		while(marcador !=0){
			
			//atribuição de valores das variáveis temporárias
			temp1 = ordena2->prox;
			temp2 = temp1->prox;
			
			//contador para verificar se a lista possui termos desordenados
			marcador = 0;
			
			//loop primário de ordenação 
		 	while(temp2->prox != NULL){
				
				//verifica se o segundo item é menor que o primeiro	
				if(temp2->valor < temp1->valor){
			 		
					temp1->prox = temp2->prox;
					temp2->prox->ant = temp1;
					temp2->ant = temp1->ant;
					temp1->ant->prox = temp2;
					temp1->ant = temp2;
					temp2->prox = temp1;
					
					marcador++;
				 	
				}
				
				//reatribuição de valores das variáveis temporárias
				temp1 = temp2;
				temp2 = temp2->prox;
			
			}
			
			//verificação de termos desordenados ao fim da lista
			if((temp2->prox == NULL ) and (temp2->valor < temp1->valor)){
				 
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

//declaração da função ord_categoria
//=============================================================================================================================================================

//função de ordenação por data
void ord_categoria(lista_cadastro *ordena){
	
	//variáveis locais
	lista_cadastro *teste = ordena->prox;
	
	//indicador de passagem do loop
	int marcador = -5;
	
	//verifica se a lista de structs está vazia
	if(teste->prox != NULL){
		
		//variáveis temporárias para percorrer e ordenar a lista
		lista_cadastro *temp1, *temp2;
		
		//loop secundário de verificação de ordenação 
		while(marcador !=0){
			
			//atribuição de valores das variáveis temporárias
			temp1 = ordena->prox;
			temp2 = temp1->prox;
			
			//contador para verificar se a lista possui termos desordenados
			marcador = 0;
			
			//loop primário de ordenação 
		 	while(temp2->prox != NULL){
				
				//verifica se o segundo item é menor que o primeiro	
				if(strcmp(temp2->categoria,temp1->categoria)<0){
			 		
					temp1->prox = temp2->prox;
					temp2->prox->ant = temp1;
					temp2->ant = temp1->ant;
					temp1->ant->prox = temp2;
					temp1->ant = temp2;
					temp2->prox = temp1;
					
					marcador++;
	
				}
				
				//reatribuição de valores das variáveis temporárias
				temp1 = temp2;
				temp2 = temp2->prox;
			
			}
			
			//verificação de termos desordenados ao fim da lista
			if((temp2->prox == NULL ) and (strcmp(temp2->categoria,temp1->categoria)<0)){
				 
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

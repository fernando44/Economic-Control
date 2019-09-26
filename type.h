/*
	This library contains a definition of the
	data type of the "object" of register 
*/

//dinamic data struct for list
typedef struct data_din{
	
	struct data_din *ant; 
	struct data_din *prox; 
	char date[11];		
	char description[100];
	char category[14];	
	float value;		
	char details[100]; 
	
}list_cad;


//static data struct for vector
typedef struct data{
	
	char date[11];		
	char description[100];
	char category[14];	
	float value;		
	char details[100]; 
	
}cad;



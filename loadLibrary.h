/*
	This library contains functions to read data from files for memory,
	write data into files, and switch data base 
*/

//Dependencies
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//Constants 
#define L 1000
#define C 7

//Global variables and extern declarations
int sizeOfCategoryList;
char matrixYears[L][C];
char categoryList[LIN][COL];// = {"Informatica","Contas","Vestimenta","Escolar","Alimenticio","Medicamentos","Documentos","Compras"};
extern char MonthsOfYear[12][10];

//Function to load configurations
loadConfig(char categoryList[LIN][COL]){
	
	//Local variables
	long start = 76;
	sizeOfCategoryList = 0;
	
	//Opening file in read mode
	FILE *config = fopen("config.txt","r");
	
	//Positioning file pointer
	fseek(config,start,SEEK_CUR);
	
	//Get categories, and increment sizeOfCategoryList
	while(fgets(categoryList[sizeOfCategoryList],COL,config) != NULL){
		sizeOfCategoryList++;
	}
	
	//Close the file
	fclose(config);
}

//Function to load data from txt file at data base to regList
reg *loadListFromTxt(reg *regList,FILE *dataBase, char path[30]){
	
	//Local variables
	char localPath[50], strLine[500], value[100];
	int index, chrKeyCount;
	strcpy(localPath,path);
	strcat(localPath,".txt");
	
	//Verifying if the archive exists
	if((dataBase = fopen(localPath,"r"))==NULL){
		
		//Failure feedback
		ClrScr();
		printf("\n\n\n\t\t\t\tUnable to open file %s !!!", localPath);
		sleep(2);
				
	}else{
		
		//Creating a new record and adding it to the regList
		reg *newRecord;
		initalizeString(value,100);
		initalizeString(strLine,500);
		
		//Reading file by lines
		setbuf(stdin,NULL);
		while(fgets(strLine,500,dataBase) != NULL){
			
			//Creating a new record to storage data
			newRecord = newReg();
			
			//Splitting line content
			chrKeyCount = 0;
			initalizeString(value,100);
			for(index = 0; index<strlen(strLine);index++){
				
				//Mapping key characters and separating content
				strLine[index] != '\t' && chrKeyCount == 0 ? (newRecord->date[strlen(newRecord->date)] = strLine[index]) : 0;
				strLine[index] != '\t' && chrKeyCount == 1 ? (value[strlen(value)] = strLine[index]) && (newRecord->value = atof(value)) : 0;
				strLine[index] != '\t' && chrKeyCount == 2 ? (newRecord->category[strlen(newRecord->category)] = strLine[index]) : 0;
				strLine[index] != '\t' && chrKeyCount == 3 ? (newRecord->description[strlen(newRecord->description)] = strLine[index]) : 0;
				strLine[index] != '\n' && chrKeyCount == 4 ? (newRecord->details[strlen(newRecord->details)] = strLine[index]) : 0;
				strLine[index] == '\t' ? chrKeyCount++ : 0;
			}
			
			//Insert file data into regList
			strcmp(regList->date,"") == 0 ? regList = newRecord : addEnd(regList,newRecord);
		};
		
		//Close the files
		fclose(dataBase);
	}
	
	//Returns list of content from file
	return regList;
}

//Function to load data from json file at data base to regList
void loadListFromJson(reg *regList,FILE *dataBase, char path[30]){
	
	//Local variables
	char localPath[50];
	strcpy(localPath,path);
	strcat(localPath,".json");
	
	//Verifying if the archive exists
	if((dataBase = fopen(localPath,"r"))==NULL){
		
		//Failure feedback
		ClrScr();
		printf("\n\n\n\t\t\t\tUnable to open file %s !!!", localPath);
		sleep(2);
				
	}else{
		
		//Need implementation
	
	}
	
}

//Function to clean list
void cleanList(reg *regList){
	
	//Verifying if regList is null
	if(regList->prox != NULL){
			
		//Function call to remove records
		remEnd(regList);
		cleanList(regList);
		
	}
	regList = newReg();
}

//Function to write list to data base in format at txt
void saveListAsTxt(reg *regList, FILE *dataBase, char path[30]){
	
	//Local variables
	char localPath[50];
	strcpy(localPath,path);
	strcat(localPath,".txt");
	
	//Opens the data base in recording mode 
	dataBase = fopen(localPath,"w");
	
	//Writing list inside the file
	while(regList != NULL){
		
		fprintf(dataBase,"%i\t",regList->id);
		fprintf(dataBase,"%s\t",regList->date);
		fprintf(dataBase,"%f\t",regList->value);
		fprintf(dataBase,"%s\t",regList->category);
		fprintf(dataBase,"%s\t",regList->description);
		fprintf(dataBase,"%s\n",regList->details);
	
		regList = regList->prox,dataBase,path;
	}
	
	//Close the file
	fclose(dataBase);
}

//Function to write list to data base in format at json
void saveListAsJson(reg *regList, FILE *dataBase, char path[30]){
	
	//Local variables
	char localPath[50];
	strcpy(localPath,path);
	strcat(localPath,".json");
	
	//Opens the data base in recording mode 
	dataBase = fopen(localPath,"w");
	
	//Writing list inside the file
	while(regList != NULL){
		
		regList->ant == NULL ? fprintf(dataBase,"%c",'[') : 0;
		
		fprintf(dataBase,"%c",'{');
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","id");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%i",regList->id);
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","date");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s",regList->date);
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","value");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%f",regList->value);
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","category");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s",regList->category);
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","description");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s",regList->description);
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","details");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s",regList->details);
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",'}');
		
		regList->prox != NULL ? fprintf(dataBase,"%c",',') : 0;
	
		regList = regList->prox;
	}
	fprintf(dataBase,"%c",']');
	
	//Close the file
	fclose(dataBase);
}

//show_data_base function
//void show_data_base(char month[11],char year[7],FILE *file){
//	
//	//local variables
//	int count = 0,max = 0,key = 0;
//	
//	//opens the year record in read mode
//	file = fopen("Database\\list_years.txt","r");
//	
//	//loop for fill matrix of years
//	while(fscanf(file,"%s",matrix_years[count]) != EOF || (count == 9999)){
//		max = count;
//		count++;
//	}
//	count = 0;
//	
//	//close the file
//	fclose(file);
//	
//	//loop to display and select years
//	while(key != -35 || key != -21){
//		
//		system("cls");
//		HEADER();
//		printf("Press ESC to stay in current year\n\n");
//		printf("%s",matrix_years[count]);
//		
//		//key pressed reading
//		setbuf(stdin,NULL);
//		key = getch()-48;
//		
//		//enter key pressed
//		if(key == -35){
//			strcpy(year,matrix_years[count]);
//			break;
//		//rolling matrix up 	
//		}else if(key == 24){
//			count--;
//		//rolling matrix down	
//		}else if(key == 32){
//			count++;
//		}
//		
//		//back to start
//		if(count == max +1){
//			count = 0;
//		//back to end	
//		}else if(count<0){
//			count = max;
//		}		
//	}
//	count = key = 0;
//	
//	
//	//loop to display and select months
//	while(key != -35 || key != -21){
//		
//		system("cls");
//		HEADER();
//		printf("Press ESC to stay in current month\n\n");
//		printf("%s",matrix_months[count]);
//		
//		//key pressed reading
//		setbuf(stdin,NULL);
//		key = getch()-48;
//		
//		//enter key pressed
//		if(key == -35){
//			strcpy(month,matrix_months[count]);
//			break;
//		//rolling matrix up	
//		}else if(key == 24){
//			count--;			
//		//rolling matrix down	
//		}else if(key == 32){
//			count++;
//		}
//		
//		//back to start
//		if(count == 12 ){
//			count = 0;
//		//back to end	
//		}else if(count<0){
//			count = 11;
//		}		
//	}
//}

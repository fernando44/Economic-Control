/*
	This library contains functions to read data from files for memory,
	write data into files, and switch data base 
*/

//Dependencies
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

//Constants
#define L 1000
#define C 7

//Global variables and extern declarations
char matrixYears[L][C];
extern int sizeOfCategoryList;
extern char categoryList[LIN][COL];
extern char yearsPath[25];
extern char basePath[30];
extern FILE *dataBase;

//Function to load configurations
void loadConfig(char categoryList[LIN][COL]){
	
	//Local variables
	long start = 76;
	sizeOfCategoryList = 0;
	
	//Opening file in read mode
	FILE *file = fopen("config.txt","r");
	
	//Positioning file pointer
	fseek(file,start,SEEK_CUR);
	
	//Get categories, and increment sizeOfCategoryList
	while(fgets(categoryList[sizeOfCategoryList],COL,file) != NULL){
		sizeOfCategoryList++;
	}
	
	//Close the file
	fclose(file);
}

//Function to load data from txt file at data base to recList
rec *loadListFromTxt(rec *recList,FILE *dataBase, char path[30]){
	
	//Local variables
	char localPath[30], strLine[500], value[100];
	int index, chrKeyCount;
	strcpy(localPath,path);
	strcat(localPath,".txt");
	
	//Verifying if the archive exists
	if((dataBase = fopen(localPath,"r"))==NULL){
		
		//Failure feedback
		ClrScr();
		printf("\n\n\n\t\t\t\tCould not open the file %c%s%c !!!", 34,localPath,34);
		sleep(2);
		recList = NULL;
				
	}else{
		
		//Creating a new record and adding it to the recList
		rec *new_record;
		init_str(value,100);
		init_str(strLine,500);
		
		//Reading file by lines
		setbuf(stdin,NULL);
		while(fgets(strLine,500,dataBase) != NULL){
			
			//Creating a new record to storage data
			new_record = new_rec();
			
			//Splitting line content
			chrKeyCount = 0;
			init_str(value,100);
			for(index = 0; index<strlen(strLine);index++){
				
				
				//Mapping key characters and separating content
				strLine[index] == '\t' && chrKeyCount == 1 ? init_str(value,100) : 0;
				strLine[index] != '\t' && chrKeyCount == 0 ? (value[strlen(value)] = strLine[index]) && (new_record->id = atoi(value)) : 0;
				// strLine[index] != '\t' && chrKeyCount == 1 ? (new_record->date[strlen(new_record->date)] = strLine[index]) : 0;
				strLine[index] != '\t' && chrKeyCount == 2 ? (value[strlen(value)] = strLine[index]) && (new_record->value = atof(value)) : 0;
				strLine[index] != '\t' && chrKeyCount == 3 ? (new_record->category[strlen(new_record->category)] = strLine[index]) : 0;
				strLine[index] != '\t' && chrKeyCount == 4 ? (new_record->description[strlen(new_record->description)] = strLine[index]) : 0;
				strLine[index] != '\n' && chrKeyCount == 5 ? (new_record->details[strlen(new_record->details)] = strLine[index]) : 0;
				strLine[index] == '\t' ? chrKeyCount++ : 0;
			}
			
			//Insert file data into recList
			// strcmp(recList->date,"") == 0 ? recList = new_record : addEnd(recList,new_record);
		};
		
		//Close the files
		fclose(dataBase);
	}
	
	//Returns list of content from file
	return recList;
}

//Function to load data from json file at data base to recList
rec *loadListFromJson(rec *recList,FILE *dataBase, char path[30]){
		
	//Local variables
	char localPath[30], strLine[500], value[100];
	int index, chrKeyCount;
	strcpy(localPath,path);
	strcat(localPath,".json");
		
	//Verifying if the archive exists
	if((dataBase = fopen(localPath,"r"))==NULL){
		
		//Failure feedback
		ClrScr();
		printf("\n\n\n\t\t\t\tCould not open the file %c%s%c !!!", 34,localPath,34);
		sleep(2);
		recList = NULL;
				
	}else{
		
//		//Creating a new record and adding it to the recList
//		rec *new_record;
//		init_str(value,100);
//		init_str(strLine,500);
//		
//		//Reading file by lines
//		setbuf(stdin,NULL);
//		while(fgets(strLine,500,dataBase) != NULL){
//			
//			//Splitting line content
//			chrKeyCount = 0;
//			init_str(value,100);
//			for(index = 0; index<strlen(strLine);index++){
//				
//				if(strLine[index] == '{'){
//					
//					//Creating a new record to storage data
//					new_record = new_rec();
//					
//				}else if(strLine[index] == '}'){
//					
//					//Insert file data into recList
//					strcmp(recList->date,"") == 0 ? recList = new_record : addEnd(recList,new_record);
//					
//				}
//
//				if(new_record != NULL){
//				
//				strLine[index] != ',' && strLine[index-2-strlen(value)] == ':' ? (strLine[index] != '"' ? value[strlen(value)] = strLine[index] : 0) : strLine[index] == ',' ? init_str(value,100) : 0;
//				strLine[index] != ',' && chrKeyCount == 0 ? (new_record->id = atoi(value)) : 0;
//				strLine[index] != ',' && strLine[index-3-strlen(new_record->date)] == ':' && chrKeyCount == 1 ? strLine[index] != '"' ? (new_record->date[strlen(new_record->date)] = strLine[index]) : 0 : 0;
//				strLine[index] != ',' && chrKeyCount == 2 ? (new_record->value = atof(value)) : 0;
//				strLine[index] != ',' && strLine[index-3-strlen(new_record->category)] == ':' && chrKeyCount == 3 ? strLine[index] != '"' ? (new_record->category[strlen(new_record->category)] = strLine[index]) : 0 : 0;
//				strLine[index] != ',' && strLine[index-3-strlen(new_record->description)] == ':' && chrKeyCount == 4 ? strLine[index] != '"' ? (new_record->description[strlen(new_record->description)] = strLine[index]) : 0 : 0;
//				strLine[index] != '}' && strLine[index-3-strlen(new_record->details)] == ':' && chrKeyCount == 5 ? strLine[index] != '"' ? (new_record->details[strlen(new_record->details)] = strLine[index]) : 0 : 0;
//				strLine[index] != '{' && strLine[index] == ',' ? chrKeyCount++ : 0;
////				printf("\n\n id: %i\n date: %s\n category: %s\n value: %f\n description: %s\n details: %s",new_record->id,new_record->date,new_record->category,new_record->value,new_record->description,new_record->details);
////				setbuf(stdin,NULL);
////				getchar();
//				}
//				
//			}
////			printf("\n\nconteudo lido:\n id: %i\n date: %s\n category: %s\n value: %f\n description: %s\n details: %s",new_record->id,new_record->date,new_record->category,new_record->value,new_record->description,new_record->details);
////			setbuf(stdin,NULL);
////			getchar();
//			
//			//Insert file data into recList
////			strcmp(recList->date,"") == 0 ? recList = new_record : addEnd(recList,new_record);
//		};
//		
//		//Close the files
//		fclose(dataBase);
	}
	
	//Returns list of content from file
	return recList;
}

//Function to write list to data base in format at txt
void saveListAsTxt(rec *recList, FILE *dataBase, char path[30]){
	
	//Local variables
	char localPath[30];
	strcpy(localPath,path);
	strcat(localPath,".txt");
	
	//Opens the data base in recording mode 
	dataBase = fopen(localPath,"w");
	
	//Writing list inside the file
	while(recList != NULL){
		
		fprintf(dataBase,"%li\t",recList->id);
		fprintf(dataBase,"%s\t",recList->datetime.fmt_str(recList->datetime));
		fprintf(dataBase,"%Lf\t",recList->value);
		fprintf(dataBase,"%s\t",recList->category);
		fprintf(dataBase,"%s\t",recList->description);
		fprintf(dataBase,"%s\n",recList->details);
	
		recList = recList->next,dataBase,path;
	}
	
	//Close the file
	fclose(dataBase);
}

//Function to write list to data base in format at json
void saveListAsJson(rec *recList, FILE *dataBase, char path[30]){
	
	//Local variables
	char localPath[30];
	strcpy(localPath,path);
	strcat(localPath,".json");
	
	//Opens the data base in recording mode 
	dataBase = fopen(localPath,"w");
	
	//Writing list inside the file
	while(recList != NULL){
		
		recList->prev == NULL ? fprintf(dataBase,"%c",'[') : 0;
		
		fprintf(dataBase,"%c",'{');
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","id");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%li",recList->id);
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","date");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s",recList->datetime.fmt_str(recList->datetime));
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","value");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%Lf",recList->value);
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","category");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s",recList->category);
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","description");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s",recList->description);
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",',');
		
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s","details");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s"," : ");
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%s",recList->details);
		fprintf(dataBase,"%c",'"');
		fprintf(dataBase,"%c",'}');
		
		recList->next != NULL ? fprintf(dataBase,"%c",',') : 0;
	
		recList = recList->next;
	}
	fprintf(dataBase,"%c",']');
	
	//Close the file
	fclose(dataBase);
}

//Function to switch database
void switchDataBase(void){
	
	//Local variables
	int i, countSeparators = 0, countYears = 0, option = 0;
	char newPath[30], chrOption[6], currentYear[7], currentMonth[11];
	
	//Loop to get year and month from current data base
	for(i=0;i<strlen(basePath);i++){
		
		//Get year
		if(basePath[i] != (char) DIRECTORY_SEPARATOR_CHAR[0] && countSeparators == 1){
			currentYear[i] = basePath[i];
		}
		
		//Get month
		if(basePath[i] != (char) DIRECTORY_SEPARATOR_CHAR[0] && countSeparators == 2){
			currentMonth[i] = basePath[i];
		}
		
		//Increase the count of directory separators
		basePath[i] == (char) DIRECTORY_SEPARATOR_CHAR[0] ? countSeparators++ : 0;
		
	}
	
	//Opens the year record in read mode
	FILE *yearList = fopen(yearsPath,"r");
	
	//Loop for fill matrix of years
	while(fscanf(yearList,"%s",matrixYears[countYears]) != EOF || (countYears == 999)){
		countYears++;
	}
	
	//Close the file
	fclose(yearList);
	
	ClrScr();
	HEADER();
	printf("Active Database: %c%s%c\n\n",34,basePath,34);
	printf("Select a year\n\n");

	//loop to display and select years
	for(i=0;i<countYears;i++){

		i <= 8 ? printf(" ") : 0;
		printf("   %i - %s\n",i+1,matrixYears[i]);
	}

	//Get selected option
	setbuf(stdin,NULL);
	fgets(chrOption,5,stdin);
	chrOption[5] = '\0';
	option = atoi(chrOption);

	//Checking if is currente or other
	if(strcmp(currentYear,matrixYears[option-1]) != 0){
		strcpy(currentYear, option-1 > countYears || option-1 < 0 ? currentYear : matrixYears[option-1]);
	}

	//Reset option
	chrOption[0] = '\0';
	option = 0;
	
	ClrScr();
	HEADER();
	printf("Active Database: %c%s%c\n\n",34,basePath,34);
	printf("Select a month\n\n");

	DateTime display;
	display.Date->tm_mon = option-1;

	//loop to display and select months
	for(i=January;i<December;i++){
		display.Date->tm_mon = i;
		i <= 8 ? printf(" ") : 0;
		printf("   %i - %s\n",i,month(display));
	}

	//Get selected option
	setbuf(stdin,NULL);
	fgets(chrOption,3,stdin);
	chrOption[5] = '\0';
	option = atoi(chrOption);
	display.Date->tm_mon = option-1;
		
	//Checking if is currente or other
	if(strcmp(currentMonth,month(display)) != 0){
		strcpy(currentMonth, option-1 > 12 || option-1 < 0 ? currentMonth : month(display));
	}
	
	//Creating path to data base
	strcpy(basePath,"Database");
	strcat(basePath,DIRECTORY_SEPARATOR_CHAR);
	strcat(basePath,currentYear);
	strcat(basePath,DIRECTORY_SEPARATOR_CHAR);
	strcat(basePath,currentMonth);
	
	//Switch dataBase
	dataBase = fopen(basePath,"r");
	fclose(dataBase);
	
}

//Function to check yearsPath directory
void checkYearsPath(void){
	
	char itemResult[7]; 
	DateTime dtm = now();
	
	//Opening list of years in append mode
	yearList = fopen(yearsPath,"a");		
	
	//Search current year in file
	while(fscanf(yearList,"%s",itemResult) != EOF){

		//Add current year in file if don't exist
		if(atoi(itemResult) == EOF && atoi(itemResult) == year(dtm)){
			
			//Write the current year in the file
			fprintf(yearList,"%i",year(dtm));
			fprintf(yearList,"%c",'\n');
			
		}else if (atoi(itemResult) != EOF && atoi(itemResult) == year(dtm)){
			
			break;
		}
	}
	
	//Close the files
	fclose(yearList);
}

//Check data base
void checkDatabase(void){
	
	//Local variables
	char dataBaseFileCheck[30]; 
	char filePathTxt[30]; 
	char filePathJson[30]; 
	
	DateTime dtm = now();
	
	//Creating path to list years
	strcat(basePath,DIRECTORY_SEPARATOR_CHAR);
	strcpy(yearsPath,basePath);
	strcat(yearsPath,"list_years.txt");
	
	//Call datetime function
	// getDate();
	
	char y_str[5];
	snprintf(y_str,5,"%d",year(dtm));

	//Creating path to data base
	strcat(basePath,y_str);
	strcat(basePath,DIRECTORY_SEPARATOR_CHAR);
	
	//Creating path to check if a data base exists
	strcpy(dataBaseFileCheck,basePath);
	strcat(dataBaseFileCheck,"file_check.txt");
	
	//Checking if an old data base exists
	if((dataBase = fopen(dataBaseFileCheck,"rb")) == NULL){
        
		//Creating directory to data base
		___mkdir("Database");
		___mkdir(basePath);
		
		//Validating new data base
		dataBase = fopen(dataBaseFileCheck,"wb");
		fprintf(dataBase,"%s","file_check is an internal file, if it is modified or deleted the program may not work correctly");
		
		//Close the file
		fclose(dataBase);
		
		//Concatenate current month
		strcat(basePath,month(dtm));
		strcpy(filePathTxt,basePath);
		strcpy(filePathJson,basePath);
		
		//Concatenate file extensions
		strcat(filePathTxt,".txt");
		strcat(filePathJson,".json");
		
		//Write new files
		dataBase = fopen(filePathJson,"w");
		dataBase = fopen(filePathTxt,"w");
		
		//Opening list of years in append mode
		yearList = fopen(yearsPath,"a");
		
		//Write the current year in the file
			fprintf(yearList,"%i",year(dtm));
			fprintf(yearList,"%c",'\n');
		
		//Close the file
		fclose(yearList);
		fclose(dataBase);
		
	}else{
		
		//Concatenate current month
		strcat(basePath,month(dtm));
	}
	
	checkYearsPath();
}


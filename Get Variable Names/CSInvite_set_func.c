#include "CSInvite.h"

int find_function(int function_number,char *funcs, Functions function_list[])
{
	int i;
	
	for(i = 0; i < function_number; i++)
		if(strcmp(funcs,function_list[i].name) == 0)
			return i;

	return -1;
	
}

int set_parameters(char *definition, Parameter parameters[])
{

	int i;
	char *running;
	char *each_running;
  	char *token;
  	char *tmpt;	
	int tmpyy = 0;
	int params = 0;
	char tmp_dec[MAX_LENGTH];
	char tmp_dec2[MAX_LENGTH];
	
	for(i = 0; i < MAX_LENGTH; i++)
	{
		tmp_dec[i] = '\0';
		tmp_dec2[i] = '\0';
	}
	
	running = strdup(definition);
	
	token = strtok(running, "{");
	
	tmpt = token;
			
	if(token != NULL){
		int tmpy = 0;
		while(*tmpt != '\0'){
			tmp_dec[tmpy]=*tmpt;
			tmpy++;
			tmpt++;
		}
	}
	
	running = strdup(tmp_dec);
	
	for(i = 0; i < MAX_LENGTH; i++)
	{
		tmp_dec[i] = '\0';
	}
	
	token = strtok(running, "()");
	token = strtok(NULL, "()");
	
	tmpt = token;
			
	if(token != NULL){
		int tmpy = 0;
		while(*tmpt != '\0'){
			tmp_dec[tmpy]=*tmpt;
			tmpy++;
			tmpt++;
		}
	}
	
	if( (strlen(tmp_dec) == 0) || (strcmp(tmp_dec, "void") == 0) )return params;
	
	if( findsubstr(tmp_dec,",") == 0)
	{
		running = strdup(tmp_dec);
		
		for(i = 0; i < MAX_LENGTH; i++)
		{
			tmp_dec[i] = '\0';
		}
		
		token = strtok(running," ");
	
		tmpt = token;
			
		if(token != NULL){
			int tmpy = 0;
			while(*tmpt != '\0'){
				tmp_dec[tmpy]=*tmpt;
				tmpy++;
				tmpt++;
			}
			tmpyy = tmpy;
		}
		
		strcpy(parameters[params].type,tmp_dec);
		
		for(i = 0; i < MAX_LENGTH; i++)
		{
			tmp_dec[i] = '\0';
		}
		
		if( (strcmp(parameters[params].type,"struct") == 0) || (strcmp(parameters[params].type,"unsigned") == 0)
			|| (strcmp(parameters[params].type,"long") == 0) || (strcmp(parameters[params].type,"short") == 0))
		{
		
			token = strtok(NULL , " ");
			
					if(token != NULL){
						//int tmpy = 0;
						tmpt = token;
						parameters[params].type[tmpyy++] = ' ';
						while(*tmpt != '\0'){
							parameters[params].type[tmpyy]=*tmpt;
							tmpyy++;
							tmpt++;
						}
				
					}
		
		} 
		
		for(i = 0; i < MAX_LENGTH; i++)
		{
			tmp_dec[i] = '\0';
		}
		
		token = strtok(NULL," []");
			
		if(token != NULL){
		
			tmpt = token;
		
			if(findsubstr(token,"**") == 1){
					parameters[params].type[tmpyy++] = '*';
					parameters[params].type[tmpyy++] = '*';
					tmpt++;
					tmpt++;
				}
				else if(findsubstr(token,"*") == 1){
					parameters[params].type[tmpyy++] = '*';
					tmpt++;
				}			
		
			int tmpy = 0;
			while(*tmpt != '\0'){
				tmp_dec[tmpy]=*tmpt;
				tmpy++;
				tmpt++;
			}		
	
		token = strtok(NULL , "[]");				
			
		if( token != NULL){
					
			tmpt = token;		
			parameters[params].type[tmpyy++] = '[';
				
			while(*tmpt != '\0'){
				parameters[params].type[tmpyy]=*tmpt;
				tmpyy++;
				tmpt++;
			}
					
			parameters[params].type[tmpyy++] = ']';
			
		}
				
		token = strtok(NULL , "[]");				
			
		if( (token != NULL) && (findsubstr(token,";") == 0)){
					
			tmpt = token;			
			parameters[params].type[tmpyy++] = '[';
				
			while(*tmpt != '\0'){
				parameters[params].type[tmpyy]=*tmpt;
				tmpyy++;
				tmpt++;
			}
			
			parameters[params].type[tmpyy++] = ']';
				
		}		
		
		strcpy(parameters[params++].vars,tmp_dec);
		}
		
		tmpyy = 0;
		
		for(i = 0; i < MAX_LENGTH; i++)
		{
			tmp_dec[i] = '\0';
		}
		
		return params;
		
	}
	else {
	
		strcpy(tmp_dec2,tmp_dec);
	
		running = strdup(tmp_dec);
				
		token = strtok(running,",");
		
		while(token != NULL)
		{
		tmpt = token;
		
		for(i = 0; i < MAX_LENGTH; i++)
		{
			tmp_dec[i] = '\0';
		}		
		
		int tmpy = 0;
		while(*tmpt != '\0'){
			tmp_dec[tmpy]=*tmpt;
			tmpy++;
			tmpt++;
		}
		
		
		each_running = strdup(tmp_dec);
		
		for(i = 0; i < MAX_LENGTH; i++)
		{
			tmp_dec[i] = '\0';
		}
		
		token = strtok(each_running," ");
	
		tmpt = token;
			
		if(token != NULL){
			int tmpy = 0;
			while(*tmpt != '\0'){
				tmp_dec[tmpy]=*tmpt;
				tmpy++;
				tmpt++;
			}
			tmpyy = tmpy;
		}
		
		strcpy(parameters[params].type,tmp_dec);
		
		for(i = 0; i < MAX_LENGTH; i++)
		{
			tmp_dec[i] = '\0';
		}
		
		if( (strcmp(parameters[params].type,"struct") == 0) || (strcmp(parameters[params].type,"unsigned") == 0)
			|| (strcmp(parameters[params].type,"long") == 0) || (strcmp(parameters[params].type,"short") == 0))
		{
		
			token = strtok(NULL , " ");
			
					if(token != NULL){
						//int tmpy = 0;
						tmpt = token;
						parameters[params].type[tmpyy++] = ' ';
						while(*tmpt != '\0'){
							parameters[params].type[tmpyy]=*tmpt;
							tmpyy++;
							tmpt++;
						}
				
					}
		
		} 
		
		for(i = 0; i < MAX_LENGTH; i++)
		{
			tmp_dec[i] = '\0';
		}
		
		token = strtok(NULL," []");
			
		if(token != NULL){
		
			tmpt = token;
		
			if(findsubstr(token,"**") == 1){
					parameters[params].type[tmpyy++] = '*';
					parameters[params].type[tmpyy++] = '*';
					tmpt++;
					tmpt++;
				}
				else if(findsubstr(token,"*") == 1){
					parameters[params].type[tmpyy++] = '*';
					tmpt++;
				}			
		
			int tmpy = 0;
			while(*tmpt != '\0'){
				tmp_dec[tmpy]=*tmpt;
				tmpy++;
				tmpt++;
			}		
	
		token = strtok(NULL , "[]");				
			
		if( token != NULL){
					
			tmpt = token;		
			parameters[params].type[tmpyy++] = '[';
				
			while(*tmpt != '\0'){
				parameters[params].type[tmpyy]=*tmpt;
				tmpyy++;
				tmpt++;
			}
					
			parameters[params].type[tmpyy++] = ']';
			
		}
				
		token = strtok(NULL , "[]");				
			
		if( token != NULL){
					
			tmpt = token;			
			parameters[params].type[tmpyy++] = '[';
				
			while(*tmpt != '\0'){
				parameters[params].type[tmpyy]=*tmpt;
				tmpyy++;
				tmpt++;
			}
			
			parameters[params].type[tmpyy++] = ']';
				
		}		
		
		strcpy(parameters[params].vars,tmp_dec);
		
		params++;
		}		
		
			running = strdup(tmp_dec2);
			token = strtok(running, ",");
			for(i = 0; i < params;i++){
				if(token != NULL)token = strtok(NULL,",");
				else break;
			}
			
		}		
		
		tmpyy = 0;
		
		for(i = 0; i < MAX_LENGTH; i++)
		{
			tmp_dec[i] = '\0';
			tmp_dec2[i] = '\0';
		}
		
		return params;
			
	}
	
}

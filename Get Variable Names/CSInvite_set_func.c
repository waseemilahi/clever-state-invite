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

int set_statement_scopes(char * definition, Scoped_Statements function_scoped_statements[])
{
	int i;
	char *running;
  	char *token;
  	char *tmpt;		
	int statement = 0;
	int running_scope = 0;
	int original_scope = 0;
	char tmp_dec[MAX_LENGTH];
	char sub1[MAX_LENGTH];
	char sub2[MAX_LENGTH];
	char tmp_dec2[MAX_LENGTH];
	
	for(i = 0; i < MAX_LENGTH; i++)
	{
		tmp_dec[i] = '\0';
		sub1[i] = '\0';
		sub2[i] = '\0';
		tmp_dec2[i] = '\0';
	}
	
	//Need to mutate this function to get appropriate statements.
	
	running = strdup(definition);
	
	token = strtok(running, "{}");
	token = strtok(NULL, "");
	
	tmpt = token;
			
	if(token != NULL){
		int tmpy = 0;
		while(*tmpt != '\0'){
			tmp_dec[tmpy]=*tmpt;
			tmpy++;
			tmpt++;
		}
		tmp_dec[tmpy-1] = '\0';
	}
	
	strcpy(tmp_dec2 , tmp_dec);
	
	//	fprintf(stdout, "\n\n tmp_dec ==>> %s \n\n",tmp_dec);
	
	running_scope = split(tmp_dec2 , sub1 , sub2 , original_scope);
		
	strcpy(tmp_dec2 , sub2);
	strcpy(tmp_dec , sub1);
	//fprintf(stdout, "\n\n tmp_dec ==>> %s \n\n",tmp_dec);
	running = strdup(tmp_dec);
	
	token = strtok(running, "\r\n\t;");
	
	int number = 0;
	
	while(token != NULL)
	{
		tmpt = token;
		
		for(i = 0; i < MAX_LENGTH; i++)
		{
			tmp_dec[i] = '\0';
		}
		
		if(token != NULL){
			int tmpy = 0;
			while(*tmpt != '\0'){
				tmp_dec[tmpy]=*tmpt;
				tmpy++;
				tmpt++;
			}
		}
		
		char tmp_tmp[MAX_LENGTH];	
			
		for(i = 0; i < MAX_LENGTH; i++)
		{
			tmp_tmp[i] = '\0';
		}
		strcpy(tmp_tmp,tmp_dec);
		
			
		if( findsubstr(tmp_tmp, "for(") == 1){			
		
			for(i = 0; i < MAX_LENGTH; i++)
			{
				tmp_dec[i] = '\0';
			}
			
			for(i = 0; i < strlen(tmp_tmp) - 4;i++){
				tmp_dec[i] = tmp_tmp[i+4];
			}
			
		}
				
		if((findsubstr(tmp_dec,"++)") == 0) || (findsubstr(tmp_dec,"--)") == 0))
			if( (strlen(tmp_dec) > 1) || (strcmp(tmp_dec, " ") != 0) ){
				strcpy(function_scoped_statements[statement].statements,tmp_dec);
				function_scoped_statements[statement].scope = original_scope;
				function_scoped_statements[statement++].number = number++;
			}
		
		token = strtok(NULL, "\r\n\t;");
		
	}
	
	//fprintf(stdout, "\n\n orig = %d , running = %d \n\n",original_scope , running_scope);
	
	original_scope = running_scope;
	/* if there are other blocks. */
	while( running_scope != -1){
	
		for(i = 0; i < MAX_LENGTH; i++)
		{
			sub1[i] = '\0';
			sub2[i] = '\0';
		}	
	
		running_scope = split(tmp_dec2 , sub1 , sub2 , original_scope);
		
		strcpy(tmp_dec2 , sub2);
		strcpy(tmp_dec , sub1);
		//fprintf(stdout, "\n\n tmp_dec ==>> %s \n\n",tmp_dec);
	
		running = strdup(tmp_dec);
	
		token = strtok(running, "\r\n\t;");
	
		while(token != NULL)
		{
			tmpt = token;
		
			for(i = 0; i < MAX_LENGTH; i++)
			{
				tmp_dec[i] = '\0';
			}
		
			if(token != NULL){
				int tmpy = 0;
				while(*tmpt != '\0'){
					tmp_dec[tmpy]=*tmpt;
					tmpy++;
					tmpt++;
				}	
			}
		
			char tmp_tmp[MAX_LENGTH];	
			
			for(i = 0; i < MAX_LENGTH; i++)
			{
				tmp_tmp[i] = '\0';
			}
			strcpy(tmp_tmp,tmp_dec);
		
			
			if( findsubstr(tmp_tmp, "for(") == 1){			
		
				for(i = 0; i < MAX_LENGTH; i++)
				{
					tmp_dec[i] = '\0';
				}
			
				for(i = 0; i < strlen(tmp_tmp) - 4;i++){
					tmp_dec[i] = tmp_tmp[i+4];
				}
			
			}
				
			if((findsubstr(tmp_dec,"++)") == 0) || (findsubstr(tmp_dec,"--)") == 0))
				if( (strlen(tmp_dec) > 1) || (strcmp(tmp_dec, " ") != 0) ){
					strcpy(function_scoped_statements[statement].statements,tmp_dec);					
					function_scoped_statements[statement].scope = original_scope;
					function_scoped_statements[statement++].number = number++;
				}
		
			token = strtok(NULL, "\r\n\t;");			
		
		}
	//fprintf(stdout, "\n\n orig = %d , running = %d \n\n",original_scope , running_scope);
		if(running_scope != -1)original_scope = running_scope;
	
	}
		
	return statement;
}

int set_declared_local_variables(Scoped_Statements function_scoped_statements[], int total_scoped_statements, LocalVar declared_local_variables[],Parameter parameters[],int total_params, GlobalVar global_variables[], int total_globals, char (*global_constants)[MAX_LENGTH], int total_constants)
{
	int i,k,l,j;
	char *running , *each_running;
  	char *token;
  	char *tmpt;
	int tmpyy = 0;
	int var_found = -1;
	int total_variables = 0;
	//int tmpty = 0;
	char tmp_dec[MAX_LENGTH];
	char tmp_dec2[MAX_LENGTH];
	char tmp_dec3[MAX_LENGTH];
	
	for(i = 0; i < MAX_LENGTH; i++){
		tmp_dec[i] = '\0';
		tmp_dec2[i] = '\0';
		tmp_dec3[i] = '\0';
	}
	
	int tmpy = 0;
	
	for(i = 0; i < total_scoped_statements; i++){
		tmpy = 0;	
			
		strcpy(tmp_dec , "");
		strcpy(tmp_dec2 , "");
		running = strdup(function_scoped_statements[i].statements);			
		token = strtok(running , ";");

		tmpt = token;
			
		if(token != NULL){
			tmpy = 0;
			while(*tmpt != '\0'){
				tmp_dec[tmpy]=*tmpt;
				tmpy++;
				tmpt++;
			}
		}
	
	if( findsubstr(tmp_dec,",") == 0)
	{
		
		running = strdup(tmp_dec);
		
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec[j] = '\0';
		}
		
		token = strtok(running,"=");
	
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
	
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec[j] = '\0';
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
		
		if( (findsubstr(tmp_dec, "if") == 1) || (findsubstr(tmp_dec, "else") == 1))continue;
				
		if( (strcmp(tmp_dec , "++") == 0) || (strcmp(tmp_dec , "--") == 0))continue;
		
		if( (strcmp(tmp_dec,"struct") == 0) || (strcmp(tmp_dec,"unsigned") == 0)
			|| (strcmp(tmp_dec,"long") == 0) || (strcmp(tmp_dec,"short") == 0))
		{
		
			token = strtok(NULL , " ");
			
					if(token != NULL){
						//int tmpy = 0;printf
						//printf("\n\n --- \n\n");
						tmpt = token;
						tmp_dec[tmpyy++] = ' ';
						while(*tmpt != '\0'){
							tmp_dec[tmpyy]=*tmpt;
							tmpyy++;
							tmpt++;
						}
				
					}
		
		}
		
		tmpy = 0;
			
			if(strcmp(tmp_dec , "return") == 0){
				strcpy(tmp_dec , "");
				continue;
			}	
			
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec2[j] = '\0';
		}			
		
		token = strtok(NULL,"[]()*");
			
		if(token != NULL){
		
			tmpt = token;			
		
			int tmpy = 0;
			while(*tmpt != '\0'){
				tmp_dec2[tmpy]=*tmpt;
				tmpy++;
				tmpt++;
			}		
			
		char *ptr = trimwhitespace(tmp_dec2);
		
		//printf("\n\n ptr -->> %s \n\n",ptr);
		
		/* Check the Globals Variables Now. */					
		for(k = 0; k < total_globals; k++){
			if( strcmp(ptr , global_variables[k].vars) == 0){
				var_found = 0;
				for(l = 0; l < total_variables; l++){
					if(  strcmp(declared_local_variables[l].name , ptr) == 0){
						var_found = 1;
						break;
					}										
				}
								
				if(var_found == 1){
					break;
				}
				else {
					strcpy(declared_local_variables[l].type , tmp_dec);
					strcpy(declared_local_variables[l].name , ptr);
					declared_local_variables[l].scope = function_scoped_statements[i].scope;
					declared_local_variables[l].number = function_scoped_statements[i].number;
					total_variables++;
					break;
				}
				
				break;
			}
		}
						
		/* Check the Globals Constants Now. */						
		for(k = 0; k < total_constants; k++){
			if( strcmp(ptr , global_constants[k]) == 0){
				var_found = 0;
				for(l = 0; l < total_variables; l++){
					if(  strcmp(declared_local_variables[l].name , ptr) == 0){
						var_found = 1;
						break;
					}										
				}
						
				if(var_found == 1){
					break;
				}
				else {
					strcpy(declared_local_variables[l].type , tmp_dec);
					strcpy(declared_local_variables[l].name , ptr);
					declared_local_variables[l].scope = function_scoped_statements[i].scope;
					declared_local_variables[l].number = function_scoped_statements[i].number;
					total_variables++;
					break;
				}
				break;
			}
		}
		
		for(k = 0; k < total_params; k++){
			if( strcmp(ptr , parameters[k].vars) == 0){
				var_found = 0;
				for(l = 0; l < total_variables; l++){
					if( strcmp(declared_local_variables[l].name , ptr) == 0){
						var_found = 1;
						break;
					}										
				}
							
				if(var_found == 1){
					break;
				}
				else {
					strcpy(declared_local_variables[l].type , tmp_dec);
					strcpy(declared_local_variables[l].name , ptr);
					declared_local_variables[l].scope = function_scoped_statements[i].scope;
					declared_local_variables[l].number = function_scoped_statements[i].number;
					total_variables++;
					break;
				}
				
				break;
			}
		}
		
		
		}
		
		tmpyy = 0;
		
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec[j] = '\0';
			tmp_dec2[j] = '\0';
			tmp_dec3[j] = '\0';
		}
		
		//return total_globals;
		
	}
	else if( (findsubstr(tmp_dec,",") == 1) && (findsubstr(tmp_dec , "for(") == 0))
	{
	
		int first = 1;
	
		strcpy(tmp_dec2,tmp_dec);
	
		running = strdup(tmp_dec);
				
		token = strtok(running,",");
		
		while(token != NULL)
		{
		tmpt = token;
		
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec[j] = '\0';
			tmp_dec3[j] = '\0';
		}		
		
		int tmpy = 0;
		while(*tmpt != '\0'){
			tmp_dec[tmpy]=*tmpt;
			tmpy++;
			tmpt++;
		}
		
		each_running = strdup(tmp_dec);
		
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec[j] = '\0';
		}
		
		token = strtok(each_running,"=");
	
		tmpt = token;
					
		if(token != NULL){
			int tmpy = 0;
			while(*tmpt != '\0'){
				tmp_dec[tmpy]=*tmpt;
				tmpy++;
				tmpt++;
			}
		}
		
		if(first == 1){
		
		each_running = strdup(tmp_dec);		
	
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec[j] = '\0';
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
		
		if( (findsubstr(tmp_dec, "if") == 1) || (findsubstr(tmp_dec, "else") == 1))continue;
				
		if( (strcmp(tmp_dec , "++") == 0) || (strcmp(tmp_dec , "--") == 0))continue;
		
		if( (strcmp(tmp_dec,"struct") == 0) || (strcmp(tmp_dec,"unsigned") == 0)
			|| (strcmp(tmp_dec,"long") == 0) || (strcmp(tmp_dec,"short") == 0))
		{
		
			token = strtok(NULL , " ");
			
					if(token != NULL){
						//int tmpy = 0;printf
						//printf("\n\n --- \n\n");
						tmpt = token;
						tmp_dec[tmpyy++] = ' ';
						while(*tmpt != '\0'){
							tmp_dec[tmpyy]=*tmpt;
							tmpyy++;
							tmpt++;
						}
				
					}
		
		}
		
		tmpy = 0;
			
			if(strcmp(tmp_dec , "return") == 0){
				strcpy(tmp_dec , "");
				continue;
			}	
			
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec3[j] = '\0';
		}			
		
		token = strtok(NULL,"[]()*");
			
		if(token != NULL){
		
			tmpt = token;			
		
			int tmpy = 0;
			while(*tmpt != '\0'){
				tmp_dec3[tmpy]=*tmpt;
				tmpy++;
				tmpt++;
			}		
			
		char *ptr = trimwhitespace(tmp_dec3);	

		/* Check the Globals Variables Now. */					
		for(k = 0; k < total_globals; k++){
			if( strcmp(ptr , global_variables[k].vars) == 0){
				var_found = 0;
				for(l = 0; l < total_variables; l++){
					if(  strcmp(declared_local_variables[l].name , ptr) == 0){
						var_found = 1;
						break;
					}										
				}
								
				if(var_found == 1){
					break;
				}
				else {
					strcpy(declared_local_variables[l].type , tmp_dec);
					strcpy(declared_local_variables[l].name , ptr);
					declared_local_variables[l].scope = function_scoped_statements[i].scope;
					declared_local_variables[l].number = function_scoped_statements[i].number;
					total_variables++;
					break;
				}
				
				break;
			}
		}
						
		/* Check the Globals Constants Now. */						
		for(k = 0; k < total_constants; k++){
			if( strcmp(ptr , global_constants[k]) == 0){
				var_found = 0;
				for(l = 0; l < total_variables; l++){
					if(  strcmp(declared_local_variables[l].name , ptr) == 0){
						var_found = 1;
						break;
					}										
				}
						
				if(var_found == 1){
					break;
				}
				else {
					strcpy(declared_local_variables[l].type , tmp_dec);
					strcpy(declared_local_variables[l].name , ptr);
					declared_local_variables[l].scope = function_scoped_statements[i].scope;
					declared_local_variables[l].number = function_scoped_statements[i].number;
					total_variables++;
					break;
				}
				break;
			}
		}
		
		for(k = 0; k < total_params; k++){
			if( strcmp(ptr , parameters[k].vars) == 0){
				var_found = 0;
				for(l = 0; l < total_variables; l++){
					if( strcmp(declared_local_variables[l].name , ptr) == 0){
						var_found = 1;
						break;
					}										
				}
							
				if(var_found == 1){
					break;
				}
				else {
					strcpy(declared_local_variables[l].type , tmp_dec);
					strcpy(declared_local_variables[l].name , ptr);
					declared_local_variables[l].scope = function_scoped_statements[i].scope;
					declared_local_variables[l].number = function_scoped_statements[i].number;
					total_variables++;
					break;
				}
				
				break;
			}
		}

		
		
		}
		
		
			first = 0;
			running = strdup(tmp_dec2);
			token = strtok(running, ",");
			for(j = 0; j < total_variables;j++){
				if(token != NULL){token = strtok(NULL,",");}
				else break;
			}
		}
		else if( first == 0){
				
				
				
				
				//printf("\n\n tmp_dec -->> %s \n\n",tmp_dec);
		each_running = strdup(tmp_dec);
				
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec3[j] = '\0';
		}			
		
		token = strtok(each_running,"[]()*");
			
		if(token != NULL){
		
			tmpt = token;			
		
			int tmpy = 0;
			while(*tmpt != '\0'){
				tmp_dec3[tmpy]=*tmpt;
				tmpy++;
				tmpt++;
			}		
			
		char *ptr = trimwhitespace(tmp_dec3);	

		/* Check the Globals Variables Now. */					
		for(k = 0; k < total_globals; k++){
			if( strcmp(ptr , global_variables[k].vars) == 0){
				var_found = 0;
				for(l = 0; l < total_variables; l++){
					if(  strcmp(declared_local_variables[l].name , ptr) == 0){
						var_found = 1;
						break;
					}										
				}
								
				if(var_found == 1){
					break;
				}
				else {
					strcpy(declared_local_variables[total_variables].type , declared_local_variables[total_variables - 1].type);
					strcpy(declared_local_variables[l].name , ptr);
					declared_local_variables[l].scope = function_scoped_statements[i].scope;
					declared_local_variables[l].number = function_scoped_statements[i].number;
					total_variables++;
					break;
				}
				
				break;
			}
		}
						
		/* Check the Globals Constants Now. */						
		for(k = 0; k < total_constants; k++){
			if( strcmp(ptr , global_constants[k]) == 0){
				var_found = 0;
				for(l = 0; l < total_variables; l++){
					if(  strcmp(declared_local_variables[l].name , ptr) == 0){
						var_found = 1;
						break;
					}										
				}
						
				if(var_found == 1){
					break;
				}
				else {
					strcpy(declared_local_variables[total_variables].type , declared_local_variables[total_variables - 1].type);
					strcpy(declared_local_variables[l].name , ptr);
					declared_local_variables[l].scope = function_scoped_statements[i].scope;
					declared_local_variables[l].number = function_scoped_statements[i].number;
					total_variables++;
					break;
				}
				break;
			}
		}
		
		for(k = 0; k < total_params; k++){
			if( strcmp(ptr , parameters[k].vars) == 0){
				var_found = 0;
				for(l = 0; l < total_variables; l++){
					if( strcmp(declared_local_variables[l].name , ptr) == 0){
						var_found = 1;
						break;
					}										
				}
							
				if(var_found == 1){
					break;
				}
				else {
					strcpy(declared_local_variables[total_variables].type , declared_local_variables[total_variables - 1].type);
					strcpy(declared_local_variables[l].name , ptr);
					declared_local_variables[l].scope = function_scoped_statements[i].scope;
					declared_local_variables[l].number = function_scoped_statements[i].number;
					total_variables++;
					break;
				}
				
				break;
			}
		}
				
				running = strdup(tmp_dec2);
			token = strtok(running, ",");
			for(j = 0; j < total_globals;j++){
				if(token != NULL){token = strtok(NULL,",");}
				else break;
			}
		}
		}
		
		}		
		
		tmpyy = 0;
		
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec[j] = '\0';
			tmp_dec2[j] = '\0';
			tmp_dec3[j] = '\0';
		}
	
		//return total_globals;
		
	}
		
	}		
				
	return total_variables;
	
}

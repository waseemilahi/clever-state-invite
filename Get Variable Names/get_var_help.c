#include "get_var.h"


/* The Find Substring Function. (acquired from an online forum*/
int findsubstr( char *str, char *substr)
{
  if ( !*substr )
    {
      return 0;
    }
  for ( ; *str; ++str )
    {
      if ( *str == *substr )
	{
	  const char *h, *n;
	  for ( h = str, n = substr; *h && *n; ++h, ++n )
	    {
	      if ( *h != *n )
		{
		  break;
		}
	    }
	  if ( !*n )return 1;	    
	}
    }
  
  return 0;
}

/*Get the input and put it into an array of strings.*/
int get_input(char (*statements)[MAX_LENGTH], char *filename)
{
	char ch;
	int brace = 0;
	int i;
	char line[MAX_LENGTH];
	char d_line[MAX_LENGTH];
	int statement_number = 0;
	FILE *input;

 for(i = 0; i < MAX_LENGTH; i++){
	d_line[i] = '\0';
    line[i] = '\0';
}
  
  if((input = fopen( filename, "r" )) == NULL)
    {
      fprintf(stderr, "\n File Could not be opened for reading. \n\n");
      return -1;
    }

	ch = getc( input );

	while( ch != EOF ) {

	    if(ch == '\n'){
	      ch = getc(input);
	      continue;
	    }

	    if(ch == '#'){
			line[strlen(line)] = ch;
	      while(ch != '\n'){
			ch = getc( input );  
			line[strlen(line)] = ch;
		  }
		  if(findsubstr(line,"define")==1){
		  
			if(statement_number >= MAX_LENGTH)break;
      
			strcpy(statements[statement_number] , line);
      
			statement_number ++;
      
			
		  }
		  for(i = 0; i < MAX_LENGTH; i++)
				line[i] = '\0';
      
      ch = getc( input );
      
		   continue;
		}

    if(ch == '/'){
      ch = getc(input);
      if( ch  == '/'){
	while(1){
	  ch = getc( input );
	  if(ch == '\n'){
	    ch = getc(input);
	    break;
	  }
	}
     	continue;
      }
      else if( ch  == '*'){
	while(1){
	  ch = getc( input );
	  if(ch == '*'){
	    if( (ch = getc(input)) == '/'){
	      ch = getc(input);
	      break;
	    }
	  }
	}
	continue;
      }
    }
    
    if(ch == '\t'){
      ch = getc(input);
      continue;
    }
    
    if(ch == '"'){
      while(1){
	ch = getc( input );
	if(ch == '"'){
	  ch = getc(input);
	  break;
	}
      }
      continue;
    }
    
	if(ch == '{')brace++;
    
    if( (ch == '}') || (ch == ';') ){
		if(ch == '}')brace--;
		if( brace != 0){		
			line[strlen(line)] = ch;
			ch = getc( input );
			continue;
		}
		
		if(ch == ';'){
			if((findsubstr(line,"(") == 1) && (findsubstr(line, "=") == 0)){
				for(i = 0; i < MAX_LENGTH; i++)
					line[i] = '\0';
					
				ch = getc( input );
				continue;
			}
		}
		
      if(statement_number >= MAX_LENGTH)break;
      line[strlen(line)] = ch;
      strcpy(statements[statement_number] , line);
      
      statement_number ++;
      
      for(i = 0; i < MAX_LENGTH; i++)
	line[i] = '\0';
      
      ch = getc( input );
	       
      continue;
    }

    line[strlen(line)] = ch;
    
    ch = getc( input );
  }

fclose(input);
return statement_number;
}

/* Set the function names and their definitions. */
int set_functions(char (*statements)[MAX_LENGTH],Functions function_list[],int statement_number)
{	
	int i;
	char *running;
  	char *token;
  	char *tmpt;
	int function_number = 0;

	for( i = 0 ; i < statement_number; i++){
		
		if( (strlen(statements[i]) > 5) && (findsubstr(statements[i],"(") == 1) && (findsubstr(statements[i], "{") == 1)){
		
			running = strdup(statements[i]);
   
			token = strtok(running , " *(");
			if(token != NULL)
				if(strcmp(token,"struct") == 0)
					token = strtok(NULL , " *(");
			if(token != NULL){
				token = strtok(NULL," *(");
			}
			tmpt = token;
				
			if(token != NULL){
				int tmpy = 0;
			while(*tmpt != '\0'){
				function_list[function_number].name[tmpy]=*tmpt;
				tmpt++;
				tmpy++;
			}
			
			strcpy(function_list[function_number].definition,statements[i]);
			
			}
			function_number++;
		}
		
	}
	return function_number;
}

int set_global_variables(char (*statements)[MAX_LENGTH],GlobalVar global_variables[], int statement_number)
{
	int i;
	char *running;
  	char *token;
  	char *tmpt;
	int total_globals = 0;
	int tmpty = 0;
	
	for(i = 0; i < statement_number; i++){
		if((findsubstr(statements[i],"{") == 0) && (strlen(statements[i]) > 2)){
		
			running = strdup(statements[i]);
			token = strtok(running , " =;");
			
			tmpt = token;
			
			if(token != NULL){
				int tmpy = 0;
				while(*tmpt != '\0'){
					global_variables[total_globals].type[tmpy]=*tmpt;
					tmpy++;
					tmpt++;
				}
				
				//fprintf(stdout, "\n\n token = %s\n\n",token);
				
				if( (strcmp(global_variables[total_globals].type,"struct") == 0) || (strcmp(global_variables[total_globals].type,"unsigned") == 0)){
					token = strtok(NULL , " ");
					//fprintf(stdout, "\n\n token = %s\n\n",token);
					if(token != NULL){
						tmpt = token;
						global_variables[total_globals].type[tmpy++] = ' ';
						
						while(*tmpt != '\0'){
							global_variables[total_globals].type[tmpy++]=*tmpt;
							
							tmpt++;
						}
				
					}
				}
				tmpty = tmpy;
			}
						
			int tmpy = 0;
		
			token = strtok(NULL , " []=;");
			
			if(token != NULL){
			
				tmpt = token;
			
				if(findsubstr(token,"**") == 1){
					global_variables[total_globals].type[tmpty++] = '*';
					global_variables[total_globals].type[tmpty++] = '*';
					tmpt++;
					tmpt++;
				}
				else if(findsubstr(token,"*") == 1){
					global_variables[total_globals].type[tmpty++] = '*';
					tmpt++;
				}
						
			
			
				while(*tmpt != '\0'){
					global_variables[total_globals].vars[tmpy]=*tmpt;
					tmpy++;
					tmpt++;
				}
						
				token = strtok(NULL , "[]");				
			
				if( (token != NULL) && (findsubstr(token,";") == 0)){
					
					tmpt = token;			
					global_variables[total_globals].type[tmpty++] = '[';
				
					while(*tmpt != '\0'){
						global_variables[total_globals].type[tmpty]=*tmpt;
						tmpty++;
						tmpt++;
					}
					
					global_variables[total_globals].type[tmpty++] = ']';
					
				}
				
				token = strtok(NULL , "[]");				
			
				if( (token != NULL) && (findsubstr(token,";") == 0)){
					
					tmpt = token;			
					global_variables[total_globals].type[tmpty++] = '[';
				
					while(*tmpt != '\0'){
						global_variables[total_globals].type[tmpty]=*tmpt;
						tmpty++;
						tmpt++;
					}
					
					global_variables[total_globals].type[tmpty++] = ']';
					
				}
			
			
			
			}
			else{
				strcpy(global_variables[total_globals].type , "");
				continue;
			}
			
			total_globals++;
			strcpy(statements[i],"\0");
		}
		
	}
	return total_globals;
}

int set_global_constants(char (*statements)[MAX_LENGTH],char (*global_constants)[MAX_LENGTH], int statement_number)
{
	int total_constants = 0;	
	int i;
	char *running;
  	char *token;
  	char *tmpt;
	
	for(i = 0; i < statement_number; i++){
		if( (findsubstr(statements[i],"define") == 1)  && (strlen(statements[i]) > 2)){
			running = strdup(statements[i]);
			token = strtok(running , " ");
			token = strtok(NULL , " ");
			token = strtok(NULL , " ");
			tmpt = token;
			if(token != NULL){
				while(*tmpt != '\0'){
					sprintf(global_constants[total_constants],"%s%c",global_constants[total_constants],*tmpt);
					
					tmpt++;
				}
			}
			total_constants++;
			strcpy(statements[i],"\0");
		}
	}
	
	return total_constants;
	
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
		
		if( (strcmp(parameters[params].type,"struct") == 0) || (strcmp(parameters[params].type,"unsigned") == 0))
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
		
		if( (strcmp(parameters[params].type,"struct") == 0) || (strcmp(parameters[params].type,"unsigned") == 0))
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

int set_function_statements(char *definition,char (*function_statements)[MAX_LENGTH])
{

	int i;
	char *running;
  	char *token;
  	char *tmpt;		
	int statements = 0;
	char tmp_dec[MAX_LENGTH];
	
	for(i = 0; i < MAX_LENGTH; i++)
	{
		tmp_dec[i] = '\0';
	}
	
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
	
	running = strdup(tmp_dec);
	
	token = strtok(running, ";{}");
	
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
			if( (strlen(tmp_dec) > 1) || (strcmp(tmp_dec, " ") != 0) )
				strcpy(function_statements[statements++],tmp_dec);
		
		token = strtok(NULL, ";{}");
		
	}
		
	return statements;

}

int find_function(int function_number,char *funcs, Functions function_list[])
{
	int i;
	
	for(i = 0; i < function_number; i++)
		if(strcmp(funcs,function_list[i].name) == 0)
			return i;

	return -1;
	
}

int set_dependency(int total_dependent_variables,char *statement,char (*dependent_variables)[28],Functions function_list[],Parameter parameters[],GlobalVar global_variables[],char (*global_constants)[MAX_LENGTH])
{

	if( (findsubstr(statement, ">") == 0) &&(findsubstr(statement, "<") == 0) &&(findsubstr(statement, "=") == 0) && (findsubstr(statement, "(") == 0) && (findsubstr(statement, "case ") == 0)  )return 0;
	
	if( strcmp(statement, "else") == 0)return 0;
	
	int i;
	char *running;
  	char *token;
  	char *tmpt;	
	int condition = 0;
	char tmp_dec[MAX_LENGTH];	
	int statement_number = 0;
	
	if( (findsubstr(statement, "while(") == 1) || (findsubstr(statement, "for(") == 1) || (findsubstr(statement, "if(") == 1) || (findsubstr(statement, "switch(") ==  1)
		 || (findsubstr(statement, "else(") == 1) ){
				
		condition = 1;
				
		running = strdup(statement);
	
		token = strtok(running,"("); 
	
		token = strtok(NULL,"(");
	
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
			tmp_dec[tmpy-1] = '\0';
		}
		
	}
	else strcpy(tmp_dec, statement);
	
	char key1[] = "=";
	char key2[] = "()"; 
	if(condition == 0  && ( strcspn(tmp_dec,key1) < strcspn(tmp_dec,key2)) ){
	
		running = strdup(tmp_dec);
	
		token = strtok(running, "=");
		
		token = strtok(NULL, "=");
	
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
	}
	
	running = strdup(tmp_dec);
	
	token = strtok(running, "=*+-%/!><&|(),[] ");
	
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
		
			if( ((strlen(tmp_dec) > 1) || (strcmp(tmp_dec, " ") != 0) ) && (strcmp("return",tmp_dec) != 0)
				&& (strcmp("stdout",tmp_dec) != 0)&& (strcmp("stderr",tmp_dec) != 0)&& (strcmp("stdin",tmp_dec) != 0)){
				if(findsubstr(tmp_dec,".") == 1){
					char key3[] = ".";
					char tmp_tmp[MAX_LENGTH];	
			
					for(i = 0; i < MAX_LENGTH; i++)
					{
						tmp_tmp[i] = '\0';
					}
					
					strcpy(tmp_tmp,tmp_dec);			
		
					for(i = 0; i < MAX_LENGTH; i++)
					{
						tmp_dec[i] = '\0';
					}
			
					for(i = 0; i < (strlen(tmp_tmp) - (strlen(tmp_tmp) - strcspn(tmp_tmp,key3) ) );i++){
						tmp_dec[i] = tmp_tmp[i];
					}
			
				}
				char *ptr = trimwhitespace(tmp_dec);
				strcpy(dependent_variables[total_dependent_variables + statement_number++],ptr);
			}
		
			token = strtok(NULL,"=*+-%/!><&|(),[]");
		}
		
	return statement_number;

}

/* Acquired from online blog. */
char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace(*str)) str++;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;

}

int set_variables(char (*done_func)[128], int total_done,int total_variables,int function_number, Functions function_list[],int total_params,Parameter parameters[],int total_globals,GlobalVar global_variables[],int total_constants,char (*global_constants)[MAX_LENGTH],int total_dependent_variables,char (*dependent_variables)[28],Variable variables[])
{

	int j,k,l = 0, done,m;
	int var_found = 0;
		
	for(j = 0; j < total_dependent_variables; j++){
		for(k = 0; k < total_params; k++){
			if( strcmp(dependent_variables[j] , parameters[k].vars) == 0){
				var_found = 0;
				for(l = 0; l < total_variables; l++){
					if( strcmp(variables[l].name , dependent_variables[j]) == 0){
						var_found = 1;
						break;
					}										
				}
							
				if(var_found == 1){
					break;
				}
				else {
					strcpy(variables[total_variables].type , parameters[k].type);
					strcpy(variables[total_variables].name , parameters[k].vars);
					total_variables++;
					break;
				}
			}
		}
						
		/* Check the Globals Variables Now. */					
		for(k = 0; k < total_globals; k++){
			if( strcmp(dependent_variables[j] , global_variables[k].vars) == 0){
				var_found = 0;
				for(l = 0; l < total_variables; l++){
					if( strcmp(variables[l].name , dependent_variables[j]) == 0){
						var_found = 1;
						break;
					}										
				}
								
				if(var_found == 1){
					break;
				}
				else {
					strcpy(variables[total_variables].type , global_variables[k].type);
					strcpy(variables[total_variables].name , global_variables[k].vars);
					total_variables++;
					break;
				}
			}
		}
						
		/* Check the Globals Constants Now. */						
		for(k = 0; k < total_constants; k++){
			if( strcmp(dependent_variables[j] , global_constants[k]) == 0){
				var_found = 0;
				for(l = 0; l < total_variables; l++){
					if( strcmp(variables[l].name , dependent_variables[j]) == 0){
						var_found = 1;
						break;
					}										
				}
						
				if(var_found == 1){
					break;
				}
				else {
					strcpy(variables[total_variables].type , "constant");
					strcpy(variables[total_variables].name , global_constants[k]);
					total_variables++;
					break;
				}
			}
		}
						
		/* Go into each function to get the variables from each. */
		k = find_function(function_number, dependent_variables[j], function_list);
				
		if( k == -1){
			continue;
		}
		else{
		
			done = 0;
			for(m = 0; m < total_done; m++)
				if( strcmp(done_func[m],dependent_variables[j]) == 0){
					done = 1;
				}
			
			if(done == 1)continue;
			
			strcpy(done_func[total_done++],dependent_variables[j]);
			
			int tmp_num = get_func_vars(done_func,total_done,dependent_variables[j],function_number,total_globals,total_constants,function_list[k].definition,total_dependent_variables,dependent_variables,total_variables,variables,function_list,global_variables,global_constants);

				total_variables += tmp_num;
			
		}
					
						
	}
		
	return total_variables;

}

int get_func_vars(char (*done_func)[128], int total_done,char *func,int function_number,int total_globals,int total_constants,char *definition,int total_dependent_variables,char (*dependent_variables)[28],int total_variables,Variable variables[],Functions function_list[],GlobalVar global_variables[],char (*global_constants)[MAX_LENGTH])
{
	int total_params = 0;
	int new_variables = 0;
	Parameter parameters[5];
	int total_function_statements = 0;
	char function_statements[MAX_NUMBER][MAX_LENGTH];
	char new_dependents[10][28];
	int new_total_dependent = 0;
	int i,j,k;
	
	for(i = 0; i < 10; i++)
		for(k = 0; k < 28; k++)
			new_dependents[i][k] = '\0';
		
	for(i = 0; i < MAX_NUMBER; i++)
		for(k = 0; k < MAX_LENGTH; k++)
			function_statements[i][k] = '\0';
	
	for(i = 0; i < 5; i++){
		strcpy(parameters[i].type,"");
		strcpy(parameters[i].vars,"");
	}

	total_params = set_parameters(definition, parameters);
	
	for(j = 0; j < total_dependent_variables; j++){
		if(strcmp(func,dependent_variables[j]) == 0)break;
	}
	j = j + 1;
		
	if( (total_function_statements = set_function_statements(definition,function_statements)) == 0)
	{
		return 0;
	}
	
	for(k = 0; k < total_params; k++){
		strcpy(parameters[k].vars, dependent_variables[j++]);
	}
									
	for(j = 0; j < total_function_statements; j++)
	{
		k =  set_dependency(new_total_dependent,function_statements[j],new_dependents,function_list, parameters, global_variables, global_constants );					
		new_total_dependent = new_total_dependent + k;
	}
									
	/* Get all the variables the function depends upon. */
	if(new_total_dependent > 0){
		new_variables = set_variables(done_func,total_done,total_variables,function_number,function_list,total_params, parameters,total_globals,global_variables,total_constants,global_constants,new_total_dependent,new_dependents,variables);					
	}				
	return new_variables;
}
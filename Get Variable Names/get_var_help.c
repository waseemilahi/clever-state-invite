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
	
	for(i = 0; i < statement_number; i++){
		if((findsubstr(statements[i],"{") == 0) && (strlen(statements[i]) > 2)){
		
			running = strdup(statements[i]);
			token = strtok(running , " =[;");
			
			tmpt = token;
			
			if(token != NULL){
				int tmpy = 0;
				while(*tmpt != '\0'){
					global_variables[total_globals].type[tmpy]=*tmpt;
					tmpy++;
					tmpt++;
				}
				if(strcmp(global_variables[total_globals].type,"struct") == 0){
					token = strtok(NULL , " =};");
					if(token != NULL){
						tmpt = token;
						global_variables[total_globals].type[tmpy] = ' ';
						tmpy++;
						while(*tmpt != '\0'){
							global_variables[total_globals].type[tmpy]=*tmpt;
							tmpy++;
							tmpt++;
						}
				
					}
				}
			}	
			
			token = strtok(NULL , " =[;");
			
			tmpt = token;
			
			if(token != NULL){
			int tmpy = 0;
				while(*tmpt != '\0'){
					global_variables[total_globals].vars[tmpy]=*tmpt;
					tmpy++;
					tmpt++;
				}
			}
			if(token == NULL)
			{
				strcpy(global_variables[total_globals].type , "");
				total_globals--;
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
  	char *token;
  	char *tmpt;	
	int tmpyy = 0;
	int params = 0;
	char tmp_dec[MAX_LENGTH];
	
	for(i = 0; i < MAX_LENGTH; i++)
	{
		tmp_dec[i] = '\0';
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
		
		token = strtok(running," *[");
	
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
		
		if(strcmp(parameters[params].type,"struct") == 0)
		{
		
			token = strtok(NULL , " *[");
			
					if(token != NULL){
						int tmpy = 0;
						tmpt = token;
						parameters[params].type[tmpyy] = ' ';
						while(*tmpt != '\0'){
							tmp_dec[tmpy]=*tmpt;
							tmpy++;
							tmpt++;
						}
				
					}
					
			strcat(parameters[params].type,tmp_dec);			
		
		} 
		
		for(i = 0; i < MAX_LENGTH; i++)
		{
			tmp_dec[i] = '\0';
		}
		
		token = strtok(NULL," *[");
	
		tmpt = token;
			
		if(token != NULL){
			int tmpy = 0;
			while(*tmpt != '\0'){
				tmp_dec[tmpy]=*tmpt;
				tmpy++;
				tmpt++;
			}
		}
		strcpy(parameters[params++].vars,tmp_dec);
		
		return params;
		
	}
	else {
	
		running = strdup(tmp_dec);
		
		for(i = 0; i < MAX_LENGTH; i++)
		{
			tmp_dec[i] = '\0';
		}
		
		token = strtok(running," *,");
		
		while(token != NULL)
		{
		
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
			
			if( findsubstr(tmp_dec, "]") == 1){ 
				
				token = strtok(NULL," *,");
				
				for(i = 0; i < MAX_LENGTH; i++)
				{
					tmp_dec[i] = '\0';
				}
				
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
				
			}			
		
			strcpy(parameters[params].type,tmp_dec);
		
			for(i = 0; i < MAX_LENGTH; i++)
			{
				tmp_dec[i] = '\0';
			}
		
			if(strcmp(parameters[params].type,"struct") == 0)
			{
		
				token = strtok(NULL , " *");
			
					if(token != NULL){
						int tmpy = 0;
						tmpt = token;
						parameters[params].type[tmpyy] = ' ';
						while(*tmpt != '\0'){
							tmp_dec[tmpy]=*tmpt;
							tmpy++;
							tmpt++;
						}
				
					}
					
				strcat(parameters[params].type,tmp_dec);			
		
			} 
		
			for(i = 0; i < MAX_LENGTH; i++)
			{
				tmp_dec[i] = '\0';
			}
		
			token = strtok(NULL," *[,");
	
			tmpt = token;
			
			if(token != NULL){
				int tmpy = 0;
				while(*tmpt != '\0'){
					tmp_dec[tmpy]=*tmpt;
					tmpy++;
					tmpt++;
				}
			}
		
			strcpy(parameters[params++].vars,tmp_dec);
			
			token = strtok(NULL, " ,");
			
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
		
		if( (strlen(tmp_dec) > 1) || (strcmp(tmp_dec, " ") != 0))
			strcpy(function_statements[statements++],tmp_dec);
		
		token = strtok(NULL, ";{}");
		
	}
		
	return statements;

}

#include "CSInvite.h"

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

int get_possible_constants(char (*statements)[MAX_LENGTH], int statement_number)
{
	int total_constants = 0;
	int i;
	
	for(i = 0; i < statement_number; i++)
		if( (findsubstr(statements[i],"define") == 1)  && (strlen(statements[i]) > 2))
			total_constants++;
		
	return total_constants;

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

int set_global_variables(char (*statements)[MAX_LENGTH],GlobalVar global_variables[], int statement_number)
{
	int i,j;
	char *running;
	//char *running2;
  	char *token;
  	char *tmpt;
	int total_globals = 0;
	char tmp_dec[MAX_LENGTH];
	char tmp_dec2[MAX_LENGTH];
	//int tmpty = 0;
	//int tmpy = 0;
	
	char *each_running;
  	
	int tmpyy = 0;
	
	for(i = 0; i < statement_number; i++){
		if((findsubstr(statements[i],"{") == 0) && (strlen(statements[i]) > 2)){
				
				strcpy(tmp_dec , "");
				strcpy(tmp_dec2 , "");
			
			running = strdup(statements[i]);
			token = strtok(running , ";");

	tmpt = token;
			
	if(token != NULL){
		int tmpy = 0;
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
		
		strcpy(global_variables[total_globals].type,tmp_dec);
				
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec[j] = '\0';
		}
		
		if( (strcmp(global_variables[total_globals].type,"struct") == 0) || (strcmp(global_variables[total_globals].type,"unsigned") == 0)
			|| (strcmp(global_variables[total_globals].type,"long") == 0) || (strcmp(global_variables[total_globals].type,"short") == 0))
		{
		
			token = strtok(NULL , " ");
			
					if(token != NULL){
						//int tmpy = 0;printf
						//printf("\n\n --- \n\n");
						tmpt = token;
						global_variables[total_globals].type[tmpyy++] = ' ';
						while(*tmpt != '\0'){
							global_variables[total_globals].type[tmpyy]=*tmpt;
							tmpyy++;
							tmpt++;
						}
				
					}
		
		}
		
		//return total_globals + 1;
		
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec[j] = '\0';
		}
		
		token = strtok(NULL,"[]()");
			
		if(token != NULL){
		
			tmpt = token;
		
			if(findsubstr(token,"**") == 1){
					global_variables[total_globals].type[tmpyy++] = '*';
					global_variables[total_globals].type[tmpyy++] = '*';
					tmpt++;
					tmpt++;
				}
				else if(findsubstr(token,"*") == 1){
					global_variables[total_globals].type[tmpyy++] = '*';
					tmpt++;
				}			
		
			int tmpy = 0;
			while(*tmpt != '\0'){
				tmp_dec[tmpy]=*tmpt;
				tmpy++;
				tmpt++;
			}		
	
		token = strtok(NULL , "[]()");				
			
		if( token != NULL){
					
			tmpt = token;		
			global_variables[total_globals].type[tmpyy++] = '[';
				
			while(*tmpt != '\0'){
				global_variables[total_globals].type[tmpyy]=*tmpt;
				tmpyy++;
				tmpt++;
			}
					
			global_variables[total_globals].type[tmpyy++] = ']';
			
		}
				
		token = strtok(NULL , "[]()");				
			
		if( (token != NULL) && (findsubstr(token,";") == 0)){
					
			tmpt = token;			
			global_variables[total_globals].type[tmpyy++] = '[';
				
			while(*tmpt != '\0'){
				global_variables[total_globals].type[tmpyy]=*tmpt;
				tmpyy++;
				tmpt++;
			}
			
			global_variables[total_globals].type[tmpyy++] = ']';
				
		}		
		char *ptr = trimwhitespace(tmp_dec);				
		strcpy(global_variables[total_globals++].vars,ptr);
		}
		
		tmpyy = 0;
		
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec[j] = '\0';
		}
		
		//return total_globals;
		
	}
	else if( findsubstr(tmp_dec,",") == 1)
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
		
		strcpy(global_variables[total_globals].type,tmp_dec);
		
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec[j] = '\0';
		}
		
		if( (strcmp(global_variables[total_globals].type,"struct") == 0) || (strcmp(global_variables[total_globals].type,"unsigned") == 0)
			|| (strcmp(global_variables[total_globals].type,"long") == 0) || (strcmp(global_variables[total_globals].type,"short") == 0))
		{
		
			token = strtok(NULL , " ");
			
					if(token != NULL){
						//int tmpy = 0;
						tmpt = token;
						global_variables[total_globals].type[tmpyy++] = ' ';
						while(*tmpt != '\0'){
							global_variables[total_globals].type[tmpyy]=*tmpt;
							tmpyy++;
							tmpt++;
						}
				
					}
		
		} 
		
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec[j] = '\0';
		}
		
		token = strtok(NULL,"[]()");
			
		if(token != NULL){
		
			tmpt = token;
		
			if(findsubstr(token,"**") == 1){
					global_variables[total_globals].type[tmpyy++] = '*';
					global_variables[total_globals].type[tmpyy++] = '*';
					tmpt++;
					tmpt++;
				}
				else if(findsubstr(token,"*") == 1){
					global_variables[total_globals].type[tmpyy++] = '*';
					tmpt++;
				}			
		
			int tmpy = 0;
			while(*tmpt != '\0'){
				tmp_dec[tmpy]=*tmpt;
				tmpy++;
				tmpt++;
			}		
	
		token = strtok(NULL , "[]()");				
			
		if( token != NULL){
					
			tmpt = token;		
			global_variables[total_globals].type[tmpyy++] = '[';
				
			while(*tmpt != '\0'){
				global_variables[total_globals].type[tmpyy]=*tmpt;
				tmpyy++;
				tmpt++;
			}
					
			global_variables[total_globals].type[tmpyy++] = ']';
			
		}
				
		token = strtok(NULL , "[]()");				
			
		if( token != NULL){
					
			tmpt = token;			
			global_variables[total_globals].type[tmpyy++] = '[';
				
			while(*tmpt != '\0'){
				global_variables[total_globals].type[tmpyy]=*tmpt;
				tmpyy++;
				tmpt++;
			}
			
			global_variables[total_globals].type[tmpyy++] = ']';
				
		}		
		char *ptr = trimwhitespace(tmp_dec);				
		strcpy(global_variables[total_globals].vars,ptr);
		//printf("\n\n --- %s %s\n\n",global_variables[total_globals].type , global_variables[total_globals].vars);
		total_globals++;
		}
		
		
			first = 0;
			running = strdup(tmp_dec2);
			token = strtok(running, ",");
			for(j = 0; j < total_globals;j++){
				if(token != NULL){token = strtok(NULL,",");}
				else break;
			}
		}
		else if( first == 0){
				strcpy(global_variables[total_globals].type , global_variables[total_globals - 1].type);
				
		each_running = strdup(tmp_dec);
				
		for(j = 0; j < MAX_LENGTH; j++)
		{
			tmp_dec[j] = '\0';
		}
		
		token = strtok(each_running,"[]()");
			
		if(token != NULL){
		
			tmpt = token;
		
			if(findsubstr(token,"**") == 1){
					global_variables[total_globals].type[tmpyy++] = '*';
					global_variables[total_globals].type[tmpyy++] = '*';
					tmpt++;
					tmpt++;
				}
				else if(findsubstr(token,"*") == 1){
					global_variables[total_globals].type[tmpyy++] = '*';
					tmpt++;
				}			
		
			int tmpy = 0;
			while(*tmpt != '\0'){
				tmp_dec[tmpy]=*tmpt;
				tmpy++;
				tmpt++;
			}		
	
		token = strtok(NULL , "[]()");				
			
		if( token != NULL){
					
			tmpt = token;		
			global_variables[total_globals].type[tmpyy++] = '[';
				
			while(*tmpt != '\0'){
				global_variables[total_globals].type[tmpyy]=*tmpt;
				tmpyy++;
				tmpt++;
			}
					
			global_variables[total_globals].type[tmpyy++] = ']';
			
		}
				
		token = strtok(NULL , "[]()");				
			
		if( token != NULL){
					
			tmpt = token;			
			global_variables[total_globals].type[tmpyy++] = '[';
				
			while(*tmpt != '\0'){
				global_variables[total_globals].type[tmpyy]=*tmpt;
				tmpyy++;
				tmpt++;
			}
			
			global_variables[total_globals].type[tmpyy++] = ']';
				
		}		
		char *ptr = trimwhitespace(tmp_dec);				
		strcpy(global_variables[total_globals].vars,ptr);
				total_globals++;
				
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
		}
	
		//return total_globals;
		
	}
	
	}
	}
	
	return total_globals;
	
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

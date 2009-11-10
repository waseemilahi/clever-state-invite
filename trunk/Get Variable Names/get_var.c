/* The Token Parser. */
# include "get_var.h"

int main(int argc, char **argv)
{
  
	if(argc != 2){
	    fprintf(stderr, "\n Usage: get_var file_name.\n\n");
    	exit(1);
 	}
	
	int i,j,k;
	int t = 0 ;
	int statement_number;
	int total_tokens = 0;
	int t_statements_number = 0;
	int truncated_number = 0;
  	int d_truncated_number = 0;
 	int d_statements_number = 0;
	int declared_vars = 0;
	int total_real_vars = 0;
	int total_vars = 0;
	int unique_real_vars = 0;
  	int found = 0;
	int dd_truncated_number = 0;
	int external_unique_vars = 0;
	int total_constants = 0;
	int total_globals = 0;
	int total_functions = 0;
	int function_number = 0;

  	char statements[MAX_NUMBER][MAX_LENGTH];
  	char tokens[MAX_NUMBER][MAX_LENGTH];
  	char declare_vars[MAX_NUMBER][MAX_LENGTH];
	char all_vars[MAX_NUMBER][MAX_LENGTH];
  	char global_constants[MAX_NUMBER][MAX_LENGTH];
  	GlobalVars global_variables[MAX_NUMBER];
	char function_names[MAX_NUMBER][MAX_LENGTH];

  	const char delimeters[] = "";
  	char *running;
  	char *token;
  	char *tmpt;
  	char *tmp;
  	char tmpstr[MAX_LENGTH];
  	const char delim[] = " ,*"; 
  	const char del[] = "=";  
	const char delims[] = "=-+*/% \\\"\'";
	char *pp;
	const char de[] = "[];";  
	
	for(i = 0; i < MAX_NUMBER; i++){
		strcpy(global_variables[i].type, "");
		strcpy(global_variables[i].vars ,"");
			
    	for(j =0; j < MAX_LENGTH; j++){
      		statements[i][j] = '\0';
			tokens[i][j] = '\0';
			declare_vars[i][j] = '\0';
			all_vars[i][j] = '\0';
      		global_constants[i][j]='\0';      		
			function_names[i][j]='\0';
    	}
	}

	/* Get the input from the file. */
 	if((statement_number = get_input(statements,argv[1])) == -1)exit(1);
	
	/* Set the Global Constants and Variables. */
	total_constants = set_global_constants(statements,global_constants,statement_number);
	total_globals = set_global_variables(statements,global_variables,statement_number);

	for(i = 0; i < statement_number; i++)
		if(strlen(statements[i]) > 5)total_functions++;
			
	if(total_functions == 0){
		fprintf(stderr, "\n No Function Definitions in the File. \n");
		exit(1);
	}	
			
	Functions function_list[total_functions];
	
	for(i = 0; i < total_functions; i++){
		strcpy(function_list[i].name, "");
		strcpy(function_list[i].definition, "");
	}
		
	function_number = set_functions(statements,function_list,statement_number);
	
	char funcs[MAX_LENGTH];
	int function_found = 0;
	for(i = 0; i < MAX_LENGTH; i++)funcs[i] = '\0';
	while(1){
		function_found = 0;
		fprintf(stdout,"\n Please enter the name of the Function/Test you want to check: ");
		fscanf(stdin,"%s", funcs);
		fprintf(stdout, "\n");
		
		for(i = 0; i < function_number; i++){
			if(strcmp(funcs,function_list[i].name) == 0){
				function_found = 1;
				fprintf(stdout,"\n Function Found. Processing...... \n ");
				//Do the stuff here...............
			}
		}
		if(function_found == 0){
			fprintf(stderr,"\n No Such Function/Test in this File. \n");
			fprintf(stdout," Try Again!\n");
		}
	}
	
	//------------------------------------------------------------------------------------------------------------------
	//We have global vars/constants and the function names and their def.(s). now parse the func. defs. to get the vars.
	
	for( i = 0 ; i < statement_number; i++){
		if((  ((findsubstr(statements[i] , "int")) == 1) || ((findsubstr(statements[i] , "float")) == 1) || ((findsubstr(statements[i] , "double")) == 1)
	  ||((findsubstr(statements[i] , "char")) == 1) || ((findsubstr(statements[i] , "long")) == 1) ||((findsubstr(statements[i] , "void")) == 1)
	  || ((findsubstr(statements[i] , "short")) == 1)
	  ||((findsubstr(statements[i] , "struct")) == 1)		) &&(((findsubstr(statements[i] , "(")) == 1) &&((findsubstr(statements[i] , ")")) == 1))){
				 running = strdup(statements[i]);
   // fprintf(stdout, "\n %s \n",running);
    token = strtok(running , "(");
	if((token!=NULL) && (strcmp(token,"struct")))token = strtok(NULL,"(");
	//token = strtok(NULL," ");
	tmpt = token;
	//fprintf(stdout, "\n %s \n",token);
	if(token != NULL){
	  while(*tmpt != '\0'){
	    sprintf(function_names[i],"%s%c",function_names[i],*tmpt);
	    tmpt++;
	  }
	  
	}
	  }
			
}
			
  
  for(i = 0; i <  statement_number; i++){
    
    running = strdup(statements[i]);
    
    token = strtok(running , delimeters);
    while(token != NULL){
      
      tmpt = token;
      if(token != NULL){
	while(*tmpt != '\0'){
	  sprintf(tokens[total_tokens],"%s%c",tokens[total_tokens],*tmpt);
	  tmpt++;
	}
	total_tokens++;
      }
      token = strtok(NULL,delimeters);
    }
  }
  
	char token_statements[total_tokens][MAX_LENGTH];
	char declare_statements[total_tokens][MAX_LENGTH];

  	for (i = 0; i < total_tokens; i++)
    	for(j = 0; j < MAX_LENGTH; j++){
      		token_statements[i][j] = '\0';
			declare_statements[i][j] = '\0';
		}
    
  for(i = 0; i < total_tokens; i++){
    if( ( ((findsubstr(tokens[i] , "int")) == 1) || ((findsubstr(tokens[i] , "float")) == 1) || ((findsubstr(tokens[i] , "double")) == 1)
	  ||((findsubstr(tokens[i] , "char")) == 1) || ((findsubstr(tokens[i] , "long")) == 1) || ((findsubstr(tokens[i] , "short")) == 1)
	  ||((findsubstr(tokens[i] , "struct")) == 1)		) &&(findsubstr(tokens[i] , "(")) == 0){
      strcpy(declare_statements[d_statements_number] , tokens[i]);
      d_statements_number++;
    }
  }

 
  for(i = 0; i < total_tokens; i++){
    if( (findsubstr(tokens[i] , "=")) == 1){
      strcpy(token_statements[t_statements_number] , tokens[i]);
      t_statements_number++;
    }
  }

	char truncated_statements[t_statements_number][MAX_LENGTH];
  
  for (i = 0; i < t_statements_number; i++)
    for(j = 0; j < MAX_LENGTH; j++)
      truncated_statements[i][j] = '\0';

  for(i = 0; i < MAX_LENGTH; i++)
    tmpstr[i] = '\0';

  
  /* We have all the '=' statements. Lets remove the left hand side of each. */
  for( i = 0; i < t_statements_number; i++){
    strcpy(tmpstr ,token_statements[i]);
    if( ((j = findsubstr(tmpstr,"(")) == 0) && ((k = findsubstr(tmpstr,",")) == 0)){     
      tmp = strstr(tmpstr,"=");
      tmp++;
      strcpy(truncated_statements[truncated_number],tmp);
      truncated_number++;
    }
  }  
   
  for(i = 0; i < truncated_number; i++){
    
    running = strdup(truncated_statements[i]);
    
    token = strtok(running , delims);
    while(token != NULL){
      
      tmpt = token;
      if(token != NULL){
	while(*tmpt != '\0'){
	  sprintf(all_vars[total_vars],"%s%c",all_vars[total_vars],*tmpt);
	  tmpt++;
	}
	total_vars++;
      }
      token = strtok(NULL,delims);
    }
  }
  
	char d_truncated_statements[d_statements_number][MAX_LENGTH];

  for (i = 0; i < d_statements_number; i++)
    for(j = 0; j < MAX_LENGTH; j++)
      d_truncated_statements[i][j] = '\0';
  
  for( i = 0; i < d_statements_number; i++){
    strcpy(tmpstr ,declare_statements[i]);
    tmp = strtok(tmpstr,del);t =0;
    
    strcpy(d_truncated_statements[d_truncated_number],tmp);
    d_truncated_number++;
    
  }  

  for(i = 0; i < d_truncated_number; i++){
    
    running = strdup(d_truncated_statements[i]);
    
    token = strtok(running , delim);
    while(token != NULL){
      if( (strcmp(token , "int") != 0) && (strcmp(token , "char") != 0) && (strcmp(token , "float") != 0)
	  &&(strcmp(token , "double") != 0) && (strcmp(token , "long") != 0) && (strcmp(token , "short") != 0)
	  &&(strcmp(token , "struct") != 0) &&(strcmp(token , "*") != 0)   ){
	tmpt = token;
	if(token != NULL){
	  while(*tmpt != '\0'){
	    sprintf(declare_vars[declared_vars],"%s%c",declare_vars[declared_vars],*tmpt);
	    tmpt++;
	  }
	  declared_vars++;
	}
      }
      
      token = strtok(NULL,delim);
    }
  }  
  
  for (i = 0; i < total_vars; i++){
    for(j = 0; j < MAX_LENGTH; j++){
      if(all_vars[i][j] == ' '){
	continue;
      }
      else if( (all_vars[i][j] < 48) || (all_vars[i][j] > 57)){
	total_real_vars++;
	break;
      }
      else break;
    }
  }

	char real_vars[total_real_vars][MAX_LENGTH];
	char real_unique_vars[total_real_vars][MAX_LENGTH];
  
  for (i = 0; i < total_real_vars; i++)
    for(j = 0; j < MAX_LENGTH; j++)
      real_vars[i][j] = '\0';
  
  
  k = 0;
  for(i = 0 ; i < total_vars; i++){
    pp = all_vars[i];
    for(j = 0; j < MAX_LENGTH; j++){
      
      if(all_vars[i][j] == ' '){
	pp++;continue;
      }
      else if((all_vars[i][j] < 48) || (all_vars[i][j] > 57)){
	strcpy(real_vars[k++],pp);//all_vars[i]);
	break;
      }
      else break;
    }
  }
  
  for (i = 0; i < total_real_vars; i++)
    for(j = 0; j < MAX_LENGTH; j++)
      real_unique_vars[i][j] = '\0';
  
  for(i = 0; i < total_real_vars; i++){
    found = 0;
    for(j = 0; j < total_real_vars; j++){
      if( (strcmp(real_unique_vars[j],real_vars[i])) == 0){
	found = 1;
	break;
      }
    }
    if(found == 1)continue;
    else strcpy(real_unique_vars[unique_real_vars++] , real_vars[i]);
    
  }

	char dd_truncated_statements[declared_vars][MAX_LENGTH];
	char external_vars[unique_real_vars][MAX_LENGTH];

  for (i = 0; i < declared_vars; i++)
    for(j = 0; j < MAX_LENGTH; j++)
      dd_truncated_statements[i][j] = '\0';

	for (i = 0; i < unique_real_vars; i++)
    	for(j = 0; j < MAX_LENGTH; j++)
      		external_vars[i][j] = '\0';
 
  for( i = 0; i < declared_vars; i++){
    strcpy(tmpstr ,declare_vars[i]);
    tmp = strtok(tmpstr,de);
    
    strcpy(dd_truncated_statements[dd_truncated_number],tmp);
    dd_truncated_number++;
    
  }   
  
  for(i = 0; i < unique_real_vars; i++){
    found = 0;
    for(j = 0; j < dd_truncated_number; j++){
      if( (strcmp(real_unique_vars[i],dd_truncated_statements[j])) == 0){
	found = 1;
	break;
      }
    }
    if(found == 1)continue;
    else strcpy(external_vars[external_unique_vars++] , real_unique_vars[i]);
    
  }

    print_output(statements,statement_number);
	print_output(global_constants, total_constants);
	print_global_vars(global_variables, total_globals);
	print_functions(function_list, function_number);
	/*
	print_output(tokens,total_tokens);
	print_output(token_statements,t_statements_number);
	print_output(truncated_statements,t_statements_number);
   	print_output(all_vars,total_vars);
	print_output(real_vars,total_real_vars);
    print_output(declare_vars,declared_vars);
    print_output(dd_truncated_statements,dd_truncated_number);
   	print_output(real_unique_vars,unique_real_vars);
	*/

  	fprintf(stdout, "\n\n --------------------------------------\n\n");
  	fprintf(stdout, "\n");
  
  for(i = 0; i < external_unique_vars; i++ )
    fprintf(stdout, "%d: %s  \n\n",i+1,external_vars[i]);
  
  fprintf(stdout, "\n Total External(required) Variable(s) = %d \n",external_unique_vars);
  
  fprintf(stdout, "\n");
  
  return 0;
}

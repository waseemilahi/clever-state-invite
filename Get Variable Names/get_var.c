/* The Token Parser. */
# include "get_var.h"

int main(int argc, char **argv)
{

	/* Check the arguments. */  
	if(argc != 2){
	    fprintf(stderr, "\n Usage: get_var file_name.\n\n");
    	exit(1);
 	}
	
	/* Variable declarations. */
	int i,j;
	int k = 0;	
	int statement_number;
	int total_constants = 0;
	int total_globals = 0;
	int total_functions = 0;
	int function_number = 0;
	int total_params = 0;
	int total_function_statements = 0;
	int total_scoped_statements = 0;
	int total_declared_local_variables = 0;
	int total_dependent_variables = 0;
	int function_found = 0;
	int total_variables = 0;
	int total_locals = 0;
	int total_unique_variables = 0;
	
	char statements[MAX_NUMBER][MAX_LENGTH];
	char funcs[VAR_LENGTH];
	char lower[VAR_LENGTH];	
  	GlobalVar global_variables[MAX_NUMBER];
	Parameter parameters[MAX_NUMBER];
	Variable variables[MAX_NUMBER];
	Variable local_variables[MAX_NUMBER];
	Variable unique_variables[MAX_NUMBER];
	Scoped_Statements function_scoped_statements[MAX_NUMBER];
	LocalVar declared_local_variables[MAX_NUMBER];
	char function_statements[MAX_NUMBER][MAX_LENGTH];
	char dependent_variables[10][28];	
	
	/* Initioalize the Variables. */	
	for(i = 0; i < MAX_NUMBER; i++){
		strcpy(global_variables[i].type, "");
		strcpy(global_variables[i].vars ,"");
		strcpy(parameters[i].type, "");
		strcpy(parameters[i].vars ,"");
		strcpy(variables[i].type, "");
		strcpy(variables[i].name ,"");
		strcpy(local_variables[i].type, "");
		strcpy(local_variables[i].name ,"");
		strcpy(unique_variables[i].type, "");
		strcpy(unique_variables[i].name ,"");		
		strcpy(function_scoped_statements[i].statements,"");
		function_scoped_statements[i].scope = -1;
		function_scoped_statements[i].number = -1;
		strcpy(declared_local_variables[i].type,"");
		strcpy(declared_local_variables[i].name,"");
		declared_local_variables[i].scope = -1;
		declared_local_variables[i].number = -1;
    	for(j =0; j < MAX_LENGTH; j++){
      		statements[i][j] = '\0';
			    		
			function_statements[i][j] = '\0';
    	}
	}
	for(i = 0 ; i < VAR_LENGTH; i++){
		lower[i] = '\0';
		funcs[i] = '\0';
	}
	for(i = 0; i < 10; i++)
		for(j = 0; j < 28; j++)
			dependent_variables[i][j] = '\0';
		
	/* Get the input from the file. */
 	if((statement_number = get_input(statements,argv[1])) == -1)exit(1);
		
	int possible_constants = get_possible_constants(statements, statement_number);
	
	char global_constants[possible_constants][MAX_LENGTH];
	
	for( i = 0; i < possible_constants; i++)
		for( j = 0; j < MAX_LENGTH; j++)
			global_constants[i][j]='\0';
			
	
	/* Set the Global Constants and Variables. */
	total_constants = set_global_constants(statements,global_constants,statement_number);
		
	total_globals = set_global_variables(statements,global_variables,statement_number);
	
	//print_output(global_constants, total_constants);
	//print_global_vars(global_variables, total_globals);	
	
	/* Total "Possible" Funcion definitions. */
	for(i = 0; i < statement_number; i++)
		if(strlen(statements[i]) > 5)total_functions++;
			
	/* No Functions in the file. */
	if(total_functions == 0){
		fprintf(stderr, "\n No Function Definitions in the File. \n");
		exit(1);
	}	
			
	/* The data structure for holding the function names and their definition. */
	Functions function_list[total_functions];
	
	/* Initialize the structure to empty. */
	for(i = 0; i < total_functions; i++){
		strcpy(function_list[i].name, "");
		strcpy(function_list[i].definition, "");
	}
		
	/* Set the function names and the definition. */
	function_number = set_functions(statements,function_list,statement_number);
	
	/* Print the output. 
    print_output(statements,statement_number);
	print_output(global_constants, total_constants);
	print_global_vars(global_variables, total_globals);
	print_functions(function_list, function_number);
	*/
	//print_global_vars(global_variables, total_globals);
	char done_func[function_number][128];
	int total_done = 0;
	
	for(i = 0; i < function_number; i++)
		for(j = 0; j < 128; j++)
			done_func[i][j] = '\0';
	
	while(1){
	  
		function_found = 0;
		fprintf(stdout,"\n Please enter the name of the Function/Test you want to check or type quit to exit: ");
		fscanf(stdin,"%s", funcs);
		fprintf(stdout, "\n");

		for(j = 0; j < strlen(funcs); j++)lower[j] = tolower(funcs[j]);

		if(strcmp(lower,"quit") == 0){
		  fprintf(stdout,"\n Exiting........done\n\n");
		  return 0;
		}
		else{
		
			i = find_function(function_number, funcs, function_list);
		
			if( i >= 0){
		
				/* Found the function, now work on it. */			
					function_found = 1;
					fprintf(stdout,"\n Function Found. Processing...... \n\n");
					int i5;
					for(i5 = 0; i5 < MAX_NUMBER; i5++){
						strcpy(parameters[i5].type, "");
						strcpy(parameters[i5].vars ,"");
					}
					
					total_params = set_parameters(function_list[i].definition, parameters);
						//print_params(parameters, total_params);
					if( (total_function_statements = set_function_statements(function_list[i].definition,function_statements)) == 0)
					{
						fprintf(stderr,"\n Empty Function Definition. \n");
						fprintf(stdout," Try Another!\n");
						
						/* Reset lower and funcs. */
						for(i = 0; i < VAR_LENGTH; i++){
							lower[i] = '\0';
							funcs[i] = '\0';
						}
						continue ;
					}
					
					total_scoped_statements = set_statement_scopes(function_list[i].definition, function_scoped_statements);					
					
					//print_scoped_statements(function_scoped_statements, total_scoped_statements);
					
					//get the redeclared variable statements.
					total_declared_local_variables = set_declared_local_variables(function_scoped_statements, total_scoped_statements, declared_local_variables,parameters, total_params, global_variables, total_globals, global_constants,total_constants);
					//fprintf(stdout, "\n\n tdss == %d \n\n",total_declared_local_variables);
					//print_Local_variables(declared_local_variables, total_declared_local_variables);
					
					//need to check local redeclarations.......
					
					for(j = 0; j < total_scoped_statements; j++)
					{
						k =  set_dependency(total_dependent_variables,function_scoped_statements[j].statements,function_scoped_statements[j].scope,function_scoped_statements[j].number,total_declared_local_variables,declared_local_variables,dependent_variables,function_list, parameters, global_variables, global_constants );					
						total_dependent_variables = total_dependent_variables + k;
					}
					
					print_dependent_variables(dependent_variables, total_dependent_variables);
					
					strcpy(done_func[total_done++],funcs);
					
					/* Get all the variables the function depends upon. */
					total_variables = set_variables(done_func,total_done,0,function_number,function_list,total_params, parameters,total_globals,global_variables,total_constants,global_constants,total_dependent_variables,dependent_variables,variables);					
					
					int var_found;
										
					for(i = 0; i < total_variables; i++){
						var_found = 0;
						for(j = 0; j < total_unique_variables; j++){
							if( (strcmp(variables[i].name,unique_variables[j].name)) == 0){
								var_found = 1;
								break;
							}
						}
						if(var_found == 1)continue;
						else {
							strcpy(unique_variables[total_unique_variables].name , variables[i].name);
							strcpy(unique_variables[total_unique_variables].type , variables[i].type);
							total_unique_variables++;
						}
					}					
					/* Set the array length for variables. */
					int i6,i7;
					int sub_size;
					for(i6 = 0; i6 < total_unique_variables; i6++){
						if( (findsubstr(unique_variables[i6].type,"*") == 1) && (findsubstr(unique_variables[i6].type,"[") == 1) ){
							strcat(unique_variables[i6].name,strchr(unique_variables[i6].type,'['));
							sub_size = strlen(unique_variables[i6].type) - strlen(strchr(unique_variables[i6].type,'['));
							for(i7 = sub_size; i7 <= strlen(unique_variables[i6].type); i7++){
								unique_variables[i6].type[i7] = '\0';
							}
						}
					}
										
					/* Print the Variables, the Function depends upon. */
					if(total_variables > 0){
						fprintf(stdout, "\n\n Variables the function depends upon: \n\n");
						print_variables(unique_variables,total_unique_variables);					
					}
					else{
						fprintf(stdout,"\n\n No Known Dependency. \n\n");
					}
					
					fprintf(stdout, "\n .......done.\n");
					
						for(j = 0; j < MAX_NUMBER; j++){
							strcpy(variables[j].type , "");
							strcpy(variables[j].name , "");
							strcpy(local_variables[j].type , "");
							strcpy(local_variables[j].name , "");
							strcpy(unique_variables[j].type , "");
							strcpy(unique_variables[j].name , "");			
							strcpy(function_scoped_statements[i].statements,"");
							function_scoped_statements[i].scope = -1;
							function_scoped_statements[i].number = -1;
							strcpy(declared_local_variables[i].type,"");
							strcpy(declared_local_variables[i].name,"");
							declared_local_variables[i].scope = -1;
							declared_local_variables[i].number = -1;
						}
						
						for(j = 0; j < 10; j++)
							for(k = 0; k < 28; k++)
								dependent_variables[j][k] = '\0';

						total_dependent_variables = 0;
						total_variables = 0;
						total_locals = 0;
						total_unique_variables = 0;
			
			}
			for(i = 0; i < function_number; i++)
				for(j = 0; j < 128; j++)
					done_func[i][j] = '\0';
		
			total_done = 0;		
		
			k = 0;
			total_dependent_variables = 0;
				
		}
		/* If no such function, then go back again. */
		if(function_found == 0){
		
			if(strcmp(lower,"quit") == 0){
				fprintf(stdout,"\n Exiting........done\n\n");
				return 0;
			}
		
			fprintf(stderr,"\n No Such Function/Test in this File. \n");
			fprintf(stdout," Try Again!\n");
		}
		
		/* Reset lower and funcs. */
		for(i = 0; i < MAX_LENGTH; i++){
		  lower[i] = '\0';
		  funcs[i] = '\0';
		}

	}/* End While. */

  fprintf(stdout, "\n");
  
  return 0;
}

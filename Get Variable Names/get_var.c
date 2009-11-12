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
	int total_dependent_variables = 0;
	int function_found = 0;
	int total_variables = 0;
	
	char funcs[MAX_LENGTH];
	char lower[MAX_LENGTH];	
	char statements[MAX_NUMBER][MAX_LENGTH];
	char global_constants[MAX_NUMBER][MAX_LENGTH];
  	GlobalVar global_variables[MAX_NUMBER];
	Parameter parameters[MAX_NUMBER];
	Variable variables[MAX_NUMBER];
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
    	for(j =0; j < MAX_LENGTH; j++){
      		statements[i][j] = '\0';
			global_constants[i][j]='\0';      		
			function_statements[i][j] = '\0';
			lower[j] = '\0';
			funcs[j] = '\0';
    	}
	}
	for(i = 0; i < 10; i++)
		for(j = 0; j < 28; j++)
			dependent_variables[i][j] = '\0';
		
	/* Get the input from the file. */
 	if((statement_number = get_input(statements,argv[1])) == -1)exit(1);
	
	/* Set the Global Constants and Variables. */
	total_constants = set_global_constants(statements,global_constants,statement_number);
	total_globals = set_global_variables(statements,global_variables,statement_number);

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

		if(strcmp("quit",lower) == 0){
		  fprintf(stdout,"\n Exiting........done\n\n");
		  return 0;
		}

		i = find_function(function_number, funcs, function_list);
		
		if( i >= 0){
		
			/* Found the function, now work on it. */			
					function_found = 1;
					fprintf(stdout,"\n Function Found. Processing...... \n\n");
					
					total_params = set_parameters(function_list[i].definition, parameters);
										
					if( (total_function_statements = set_function_statements(function_list[i].definition,function_statements)) == 0)
					{
						fprintf(stderr,"\n Empty Function Definition. \n");
						fprintf(stdout," Try Another!\n");
						
						/* Reset lower and funcs. */
						for(i = 0; i < MAX_LENGTH; i++){
							lower[i] = '\0';
							funcs[i] = '\0';
						}
						continue ;
					}
					
					for(j = 0; j < total_function_statements; j++)
					{
						k =  set_dependency(total_dependent_variables,function_statements[j],dependent_variables,function_list, parameters, global_variables, global_constants );					
						total_dependent_variables = total_dependent_variables + k;
					}
					
					strcpy(done_func[total_done++],funcs);
					
					/* Get all the variables the function depends upon. */
					total_variables = set_variables(done_func,total_done,0,function_number,function_list,total_params, parameters,total_globals,global_variables,total_constants,global_constants,total_dependent_variables,dependent_variables,variables);					
					
					/* Print the Variables, the Function depends upon. */
					if(total_variables > 0){
						fprintf(stdout, "\n\n Variables the function depends upon: \n\n");
						print_variables(variables,total_variables);					
					}
					else{
						fprintf(stdout,"\n\n No Known Dependency. \n\n");
					}
					
					fprintf(stdout, "\n .......done.\n");
					
						for(j = 0; j < MAX_NUMBER; j++){
							strcpy(variables[j].type , "");
							strcpy(variables[j].name , "");
						}
						
						for(j = 0; j < 10; j++)
							for(k = 0; k < 28; k++)
								dependent_variables[j][k] = '\0';

						total_dependent_variables = 0;
						total_variables = 0;					
			
		}
		for(i = 0; i < function_number; i++)
			for(j = 0; j < 128; j++)
				done_func[i][j] = '\0';
		
		total_done = 0;		
		
		k = 0;
		total_dependent_variables = 0;
		
		/* If no such function, then go back again. */
		if(function_found == 0){
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

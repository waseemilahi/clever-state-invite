#include "get_var.h"

void print_output(char (*strings)[MAX_LENGTH], int string_number)
{
	int i;

	for(i = 0; i < string_number; i++ )
	    fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(strings[i]),strings[i]);

return ;
}

void print_global_vars(GlobalVar g_vars[], int total)
{
	int i;
	
	for(i = 0; i < total; i++){
		 fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(g_vars[i].type),g_vars[i].type);
		 fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(g_vars[i].vars),g_vars[i].vars);
	}

return ;
}

void print_Local_variables(LocalVar vars[], int total)
{
	int i;
	
	for(i = 0; i < total; i++){
		 fprintf(stdout, "%d. %d. %d. %s  \n\n",vars[i].number,vars[i].scope,strlen(vars[i].type),vars[i].type);
		 fprintf(stdout, "%d. %d. %d. %s  \n\n",vars[i].number,vars[i].scope,strlen(vars[i].name),vars[i].name);
	}

return ;
}

void print_scoped_statements(Scoped_Statements statements[], int total)
{
	int i;
	
	for(i = 0; i < total; i++){
		 fprintf(stdout, "%d. %d. %d. %s  \n\n",statements[i].number,statements[i].scope,strlen(statements[i].statements),statements[i].statements);
	}

return ;
}

void print_dependent_variables(char (*dependent_variables)[28],int total_dependent_variables)
{

	int i;

	for(i = 0; i < total_dependent_variables; i++ )
	    fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(dependent_variables[i]),dependent_variables[i]);
	
	return ;

}

void print_params(Parameter parameters[], int total_params)
{

int i;
	
	for(i = 0; i < total_params; i++){
		 fprintf(stdout, " %d. %d. %s  \n\n",i,strlen(parameters[i].type),parameters[i].type);
		 fprintf(stdout, " %d. %d. %s  \n\n",i,strlen(parameters[i].vars),parameters[i].vars);
	}

return ;

}

void print_variables(Variable variables[], int total_variables)
{

int i;
	
	for(i = 0; i < total_variables; i++){
		if( (strlen(variables[i].type) > 0 ) && (strlen(variables[i].name) > 0)){
			fprintf(stdout, " %d. %d. %s  \n\n",i,strlen(variables[i].type),variables[i].type);
			fprintf(stdout, " %d. %d. %s  \n\n",i,strlen(variables[i].name),variables[i].name);
		}
	}

return ;

}

void print_functions(Functions func_list[], int total)
{
	int i;
	
	for(i = 0; i < total; i++){
		 fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(func_list[i].name),func_list[i].name);
		 fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(func_list[i].definition),func_list[i].definition);
	}

return ;
}


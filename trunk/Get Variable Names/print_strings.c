#include "get_var.h"

void print_output(char (*strings)[MAX_LENGTH], int string_number)
{
	int i;

	for(i = 0; i < string_number; i++ )
	    fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(strings[i]),strings[i]);

return ;
}

void print_global_vars(GlobalVars g_vars[], int total)
{
	int i;
	
	for(i = 0; i < total; i++){
		 fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(g_vars[i].type),g_vars[i].type);
		 fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(g_vars[i].vars),g_vars[i].vars);
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


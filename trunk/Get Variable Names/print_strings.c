#include "get_var.h"

void print_output(char (*strings)[MAX_LENGTH], int string_number)
{
	int i;

	for(i = 0; i < string_number; i++ )
	    fprintf(stdout, "%d. %d. %s  \n\n",i,strlen(strings[i]),strings[i]);

return ;
}


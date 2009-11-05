#ifndef GET_VAR_H
#define GET_VAR_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stddef.h>

# define MAX_LENGTH 256

typedef struct globals {
	char type[1024];
	char vars[1024];
}GlobalVars;

extern int findsubstr(char *string , char *substring);
extern int get_input(char (*statements)[MAX_LENGTH], char *filename);
extern void print_output(char (*strings)[MAX_LENGTH], int string_number);
extern void print_global_vars(GlobalVars g_vars[], int total);
extern int set_global_variables(char (*statements)[MAX_LENGTH],GlobalVars global_variables[], int statement_number);
extern int set_global_constants(char (*statements)[MAX_LENGTH],char (*global_constants)[MAX_LENGTH], int statement_number);

#endif

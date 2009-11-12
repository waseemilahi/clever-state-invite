#ifndef GET_VAR_H
#define GET_VAR_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stddef.h>
# include <ctype.h>

# define MAX_NUMBER 12
# define MAX_LENGTH 2048

typedef struct globals {
	char type[MAX_NUMBER];
	char vars[MAX_NUMBER];
}GlobalVar;

typedef struct params {
	char type[MAX_NUMBER];
	char vars[MAX_NUMBER];
}Parameter;

typedef struct final {
	char type[MAX_NUMBER];
	char name[MAX_NUMBER];
}Variable;

typedef struct funcs{
	char name[MAX_NUMBER];
	char definition[MAX_LENGTH];
}Functions;

extern int findsubstr(char *string , char *substring);
extern int get_input(char (*statements)[MAX_LENGTH], char *filename);
extern void print_output(char (*strings)[MAX_LENGTH], int string_number);
extern void print_dependent_variables(char (*dependent_variables)[28],int total_dependent_variables);
extern void print_global_vars(GlobalVar g_vars[], int total);
extern void print_functions(Functions func_list[], int total);
extern int set_global_variables(char (*statements)[MAX_LENGTH],GlobalVar global_variables[], int statement_number);
extern int set_functions(char (*statements)[MAX_LENGTH],Functions function_list[],int statement_number);
extern int find_function(int function_number,char *funcs, Functions function_list[]);
extern int set_global_constants(char (*statements)[MAX_LENGTH],char (*global_constants)[MAX_LENGTH], int statement_number);
extern int set_parameters(char *definition, Parameter parameters[]);
extern int set_function_statements(char *definition,char (*function_statements)[MAX_LENGTH]);
extern void print_params(Parameter parameters[], int total_params);
extern void print_variables(Variable variables[], int total_variables);
extern int set_dependency(int total_dependent_variables,char *statement,char (*dependent_variables)[28],Functions function_list[],Parameter parameters[],GlobalVar global_variables[],char (*global_constants)[MAX_LENGTH]);
extern char *trimwhitespace(char *str);
extern int set_variables(int total_variables,int function_number, Functions function_list[],int total_params,Parameter parameters[],int total_globals,GlobalVar global_variables[],int total_constants,char (*global_constants)[MAX_LENGTH],int total_dependent_variables,char (*dependent_variables)[28],Variable variables[]);
extern int get_func_vars(char *func,int function_number,int total_globals,int total_constants,char *definition,int total_dependent_variables,char (*dependent_variables)[28],int total_variables,Variable variables[],Functions function_list[],GlobalVar global_variables[],char (*global_constants)[MAX_LENGTH]);

#endif

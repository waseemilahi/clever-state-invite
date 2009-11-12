/* The Test File */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

       #      define     Global_Variable      1
	   
     int xx;
double     xy;

typedef struct params {
	char type[1024];
	char vars[1024];
}Parameter;

Parameter parameters[1024];

int first(int a, double b, char c);
void second(int a, double b, char c);
int third(int d);
void fourth(void);
int fifth(Parameter e);
void sixth();

int first(int a, double b, char c)
{
	int t;
	a = b + c;
	t = a + t;

	return a + t +( b * c);

}

void second(int a, double b, char c)
{
	int t = 128;
	a = 2 * t;
	t = b + c + t;
	fprintf(stdout, "\n T = %d \n", t);

	return ;

}

int third(int d)
{
	int a;
	a = first( d, d, d);
	
  return a;
}

void fourth(void)
{
 if(0 == 1){
 ;
 }
 else {
	return ;
 }
 
  return ;

}

int fifth(Parameter p)
{
  return strlen(p.vars);

}

void sixth()
{
	fourth();
}

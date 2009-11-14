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
	double t = xy;
	int i;
	t = b + c + t;
	fourth();
	third(t);
	for( i = 0; i < xx; i++)
		fprintf(stdout, "\n T = %f \n", t);

	return ;

}

int third(int d)
{
	int a;
	a = first( d, d, d);
	
	second(d,d,a);
	
	fprintf(stderr, "\n Quit \n");
	
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

/* The Test File */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

       #      define     Global_Variable      1
	   
     int xx;
double     xy;

typedef struct params {
	char type[MAX_NUMBER];
	char vars[MAX_NUMBER];
}Parameter;

Parameter parameters[1024];

int first(int a, double b, char c);
void second(int a, double b, char c);
int third(int d);
void fourth(void);
int fifth(int e);
void sixth();

int first(int a, double b, char c)
{
	int t;
	a = b + c;
	t = a + t;

	return a + t +( b * c);

}

void second(int a[1024], struct double b, char c)
{
	int t = 128;
	a = 2 * t;
	t = b + c + t;
	fprintf(stdout, "\n T = %d \n", t);

	return ;

}

int third(int d)
{

  return d + 10;

}

void fourth(void)
{

  return ;

}

int fifth(struct parameter e)
{

  return e - 10;

}

void sixth()
{

}

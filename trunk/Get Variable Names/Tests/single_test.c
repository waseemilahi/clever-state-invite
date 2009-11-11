/* The Test File */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

       #      define     Global_Variable      1
	   
     int xx;
double     xy;

int first(int a, double b, char c);
void second(int a, double b, char c);
void third(int d);
void fourth(void);
int fifth(int e);

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

void third(int d)
{

  return d + 10;

}

void fourth(void)
{

  return ;

}

int fifth(int e)
{

  return e - 10;

}

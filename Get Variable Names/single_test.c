/* The Test File */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int first(int a, double b, char c);
void first(int a, double b, char c);

void first(int a, double b, char c)
{
	int t = 128;
	a = 2 * t;
	t = b + c + t;
 
	return ;

}

int first(int a, double b, char c)
{
	int t;
	a = b + c;
	t = a + t;

	return a + t +( b * c);

}


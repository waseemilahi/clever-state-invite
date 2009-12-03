/* The Test File */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

       #      define     Global_Variable      1
	  
	static unsigned int xx;//,xxx,xxxx,xxxxx,xxxxxx , xz;
	
	volatile unsigned int *ab[10];// , ba;
	
	long int it;
		
double   xy   ;

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
	
	int ta = *(ab[2]);

	return ta + a + t +( b * c);

}

void second(int a, double b, char c)
{
	double t = xy;
	int i,j;
	t = b + c + t;
	++ t;
	//fourth();
	//third(t);
	for( i = 0; i < xx; i++){
		for(j = 0; j < xx; j++){
			int a;
			fprintf(stdout, "\n T = %d \n",  a );
		}
	}
	
	return ;

}

int third(int d)
{
	int a;
	a = first( d, d, d);
	
	char c = 'c';
	second(d,xy,c);
	
	first(d , d , d);
	
	first(xx ,d, xx);
	
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

int seventh(int a, int b)
{
	//xx = b + 2;
	
	int i;
	
	for(i = 0; i < 1; i++){
		int a = 0;
		int b = 1;
		
		if(a == b){
			int (*c);
			int xx = a + b;
			xx = b + 1;
			fprintf(stdout, "\n xx = %d\n",xx);
		}
		
		//int a = 2;
	}
	
	return i;
}

# include <stdio.h>

int f(int a, int b);

int main(){
	
	fprintf(stdout,"\n\n f returns ===>>> %d\n\n",f(1,2));
	
	return 0;
	
}

int f(int a, int b){

	a = b;
	b = a + 2;
	
	if(b == 4){
		a = b + a;
	int a = 0;
		if(a == 0){
			
			b = a;
		}
		
	}
	
	return b + a;

}

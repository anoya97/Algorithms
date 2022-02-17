#include<stdio.h>

// Second Fibonacci function

int fib2(int n){
	int i = 1;
	int j = 0;
	int k;
	for(k = 1; k <= n; k++){
		j = i+j;
		i = j-i;
	}
	return j;
}

main(){
	int x;
	x = fib2(8);
	printf("%d\n",x);
}

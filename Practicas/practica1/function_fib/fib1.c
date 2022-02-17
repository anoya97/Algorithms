#include<stdio.h>


// First Fibonacci function

int fib1(int n){
	if (n < 2)
		return n;
	else
		return fib1(n-1)+fib1(n-2);
}

main(){
	int x;
	x = fib1(8);
	printf("%d\n",x);
}

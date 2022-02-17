#include<stdio.h>
#include<math.h>

int fib3(int n){
	int i = 1;
	int j = 0;
	int k = 0;
	int h = 1;
	int t = 0;
	while (n > 0){
		if ((n % 2) != 0){
			t = j*h;
			j = (i*h)+(j*k)+t;
			i = (i*k)+t;		
		}
		t = pow(h,2);
		h = (2*k*h)+t;
		k = pow(k,2)+t;
		n = n/2;	
	}
	return j;
}

main(){
	int x;
	x = fib3(9);
	printf("%d\n",x);
}

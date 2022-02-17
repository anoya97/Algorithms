#include <stdio.h>
#include <math.h>
#include <sys/time.h>

/* obtiene la hora actual en microsegundos */
double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}


// First Fibonacci function

int fib1(int n){
	if (n < 2)
		return n;
	else
		return fib1(n-1)+fib1(n-2);
}

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

// Third Fibonacci function


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
		t = h*h;
		h = (2*k*h)+t;
		k = k*k +t;
		n = n/2;
	}
	return j;
}

// Function test

void test(){
	int i,f1,f2,f3;
	printf("n\tfib1\tfib2\tfib3\n");
	for(i = 1; i < 21; i++){
		f1 = fib1(i);
		f2 = fib2(i);
		f3 = fib3(i);
		printf("%3d\t%3d\t%3d\t%3d\n",i,f1,f2,f3);
	}
}

// TIMES

void timesfib1(){
	int n, i, k = 100000;
	double t1, t2, t, x, y, z;
	printf("Fibonacci 1\n");
	printf("%12s%15s%15s%15s%15s\n","n","t(n)","t(n)/f(n)","t(n)/g(n)","t(n)/h(n)");
	for(n = 2;n <= 32;n=n*2){
		t1 = microsegundos();
		fib1(n);
		t2 = microsegundos();
		t = t2-t1;

		if (t < 500){
			t1 = microsegundos();
			for(i = 0;i < k;i++)
				fib1(n);
			t2 = microsegundos();
			t = (t2-t1)/k;
		}

		x = t / pow(1.1,n);
		y = t / pow(((1+sqrt(5))/2),n);
		z = t / pow(2,n);
		printf("%12d%15.4f%15.6f%15.6f%15.8f\n",n,t,x,y,z);
	}
}

void timesfib2(){
	int n, i, k = 1000;
	double t1, t2, t, x, y, z;
	printf("Fibonacci 2\n");
	printf("%12s%15s%15s%15s%15s\n","n","t(n)","t(n)/f(n)","t(n)/g(n)","t(n)/h(n)");
	for(n = 1000;n <= 10000000;n=n*10){
		t1 = microsegundos();
		fib2(n);
		t2 = microsegundos();
		t = t2-t1;

		if (t < 500){
			t1 = microsegundos();
			for(i = 0;i < k;i++)
				fib2(n);
			t2 = microsegundos();
			t = (t2-t1)/k;
		}

		x = t / pow(n,0.8);
		y = t / n;
		z = t / (n*log(n));
		printf("%12d%15.3f%15.6f%15.6f%15.6f\n",n,t,x,y,z);
	}
}


void timesfib3(){
	int n, i, k = 10000;
	double t1, t2, t, x, y, z;
	printf("Fibonacci 3\n");
	printf("%12s%15s%15s%15s%15s\n","n","t(n)","t(n)/f(n)","t(n)/g(n)","t(n)/h(n)");
	for(n = 1000;n <= 10000000;n=n*10){
		t1 = microsegundos();
		fib3(n);
		t2 = microsegundos();
		t = t2-t1;

		if (t < 500){
			t1 = microsegundos();
			for(i = 0;i < k;i++)
				fib3(n);
			t2 = microsegundos();
			t = (t2-t1)/k;
		}

		x = t / sqrt(log(n));
		y = t / log(n);
		z = t / pow(n,0.5);
		printf("%12d%15.3f%15.6f%15.6f%15.6f\n",n,t,x,y,z);
	}
}

// main

int main(){
	test();
	printf("\n\n");
	timesfib1();
	printf("\n\n");
    timesfib1();
    printf("\n\n");
    timesfib1();
    printf("\n\n");
	timesfib2();
	printf("\n\n");
    timesfib2();
    printf("\n\n");
    timesfib2();
    printf("\n\n");
	timesfib3();
    printf("\n\n");
    timesfib3();
    printf("\n\n");
    timesfib3();

	return 0;
}


#include<stdio.h>
#include<time.h>
#include<sys/time.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//********************************************************
double microsegundos() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0)
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

//********************************************************
void inicializar_semilla(){
	srand(time(NULL));
}

//********************************************************
void aleatorio(int v[], int n){
	int i, m = 2*n+1;

	for(i = 0; i < n; i++)
		v[i] = (rand() % m) - n;
}

//********************************************************
void ascendente(int v[], int n){
	int i;

	for(i = 0; i < n; i++)
		v[i] = i;
}

//********************************************************
void descendente(int v[], int n){
	int i, x = n;

	for(i = 0; i < n; i++){
		v[i] = x;
		x--;
	}
}

//********************************************************
void mostrar(int v[], int n){
	int i;

	for(i = 0; i < n; i++)
		printf(" %d ",v[i]);
	printf("\n");
}

//********************************************************
void ordenar(int v[], int tam){
	int incr, tmp, j , i;
	//int seguir = 1;

	incr = 797161;

	while (incr){
		incr = (incr-1) /3;
		for (i = incr; i < tam; i++){
			tmp = v[i];
			j = i;
			while ((j-incr >= 0) & (tmp < v[j-incr])){
				v[j] = v[j-incr];
				j = j-incr;
			}
			v[j] = tmp;
		}
	//	if (incr == 0)
	//		seguir = 0;
	}
}

//********************************************************
void test(int v[], int n, void (*metodo)(int[],int)){

	(*metodo)(v,n);
	printf("Ordenacion shell\n");
	mostrar(v,n);
	printf("Ordenando...\n");
	ordenar(v,n);
	mostrar(v,n);
	printf("\n");
}

//********************************************************
void cotas(const char * texto, double * x, double * y, 
			double * z, double t, int n){

	if (strcmp(texto,"aleatorio") == 0){
		*x = t / (pow(n,0.8));
		*y = t / (pow(n,1.2));
		*z = t / (pow(n,2));
	}
	else{
		*x = t / pow(n,1);
		*y = t / (pow(n,1.16));
		*z = t / pow(n,2);
	} 
}

//********************************************************
void times(const char * texto,void (*metodo)(int[],int),
				int k,int ini,int fin){
	int n,i;
	double t1, t2, t, x, y, z, ta, tb;
	char c;
	int v[fin];

	printf("Ordenacion shell con inicializacion %s.\n",texto);
	printf("%12s%15s%15s%15s%15s\n",
			"n","t(n)","t(n)/f(n)","t(n)/g(n)","t(n)/h(n)");

	for(n = ini;n <= fin;n = n*2){
		c = ' ';

		(*metodo)(v,n);	
		t1 = microsegundos();
		ordenar(v,n);
		t2 = microsegundos();
		t = t2 - t1;

		if (t < 500){
			c = '*';
			t1 = microsegundos();
			for(i = 0;i < k;i++){
				(*metodo)(v,n);
				ordenar(v,n);
			}
			t2 = microsegundos();
			ta = (t2 - t1);

			t1 = microsegundos();
			for(i = 0;i < k;i++)
				(*metodo)(v,n);
			t2 = microsegundos();
			tb = (t2 - t1);
			
			t = (ta - tb)/k;
		}
		
		cotas(texto,&x,&y,&z,t,n);
		printf("%12d%c%15.4f%15.6f%15.8f%15.8f\n",n,c,t,x,y,z);
	}
	printf("\n");
}

//********************************************************
int main(){
	int n = 10;
	int v[n];

	//Test	
	inicializar_semilla();
	test(v,n,ascendente);
	test(v,n,descendente);
	test(v,n,aleatorio);
	//Times
	times("aleatorio",aleatorio,100,200,25600);
	times("descendente",descendente,100,200,25600);
	times("ascendente",ascendente,100,200,25600);

	return 0;
}

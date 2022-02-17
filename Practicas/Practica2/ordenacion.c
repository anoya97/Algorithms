#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
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
void ord_ins (int v [], int n){
	int i, x, j;

	for(i = 1;i < n;i++){
		x = v[i];
		j = i-1;
		while ((j >= 0) && (v[j] > x)){
			v[j+1] = v[j];
			j = j-1;
		}
		v[j+1] = x;
	}
}

//********************************************************
void intercambiar(int * x, int * y){
	int aux;

	aux = *x;
	*x = *y;
	*y = aux;
}

//********************************************************
void ord_rap_aux (int v [], int iz, int dr){
	int pivote, i, j;

	if (iz < dr){
		pivote = v[(iz+dr)/2];
		intercambiar(&v[iz],&v[(iz+dr)/2]);
		i = iz+1;
		j = dr;
		while (i <= j){
			while ((i <= dr) && (v[i] < pivote))
				i = i+1;
			while (v[j] > pivote)
				j = j-1;
			if (i <= j){
				intercambiar(&v[i],&v[j]);
				i = i+1;
				j = j-1;
			}
		}
		intercambiar(&v[iz],&v[j]);
		ord_rap_aux(v,iz,j-1);
		ord_rap_aux(v,j+1,dr);
	}
}

//********************************************************
void ord_rap (int v [], int n){
	ord_rap_aux(v,0,n-1);
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
int ordenado(int v[], int n){
	int i;

	for(i = 0; i < n-1; i++)
		if (v[i] <= v[i+1])
			continue;
		else
			return 0;
	return 1;
}

//********************************************************
void mostrar(int v[], int n){
	int i;

	for(i = 0; i < n; i++)
		printf(" %d ",v[i]);
	printf("\n");

	printf("Ordenado? %d\n",ordenado(v,n));
}

//********************************************************
void test(char * texto, char * metodo, int v[], int n,
			void (*tipo)(int[],int), void (*ord)(int[],int)){

	(*tipo)(v,n);
	printf("Ordenacion %s con inicializacion %s.\n",texto,metodo);
	mostrar(v,n);
	printf("Ordenando...\n");
	(*ord)(v,n);
	mostrar(v,n);
	printf("\n");
}

//********************************************************
void cotas(const char * texto, const char * texto2, double * x,
				double * y, double * z, double t, int n){

	if (strcmp(texto,"rapida") == 0){
		*x = t / (pow(n,0.8)*log(n));
		*y = t / (n*log(n));
		*z = t / (pow(n,1.2)*log(n));
	}
	else{
		if(strcmp(texto2,"ascendente") == 0){
				  *x = t / pow(n,0.8);
				  *y = t / n;
				  *z = t / pow(n,1.2);
		}
		else {
				  *x = t / pow(n,1.8);
				  *y = t / pow(n,2);
				  *z = t / pow(n,2.2);
		}
	} 
}

//********************************************************
void times(const char * texto, const char * metodo,void (*tipo)(int[],int),
				void (*ord)(int[],int),int k,int ini,int fin){
	int n,i;
	double t1, t2, t, x, y, z, ta, tb;
	char c;
	int v[fin];

	printf("Ordenacion %s con inicializacion %s.\n",texto,metodo);
	printf("%12s%15s%15s%15s%15s\n",
			"n","t(n)","t(n)/f(n)","t(n)/g(n)","t(n)/h(n)");

	for(n = ini;n <= fin;n = n*2){
		c = ' ';

		(*tipo)(v,n);	
		t1 = microsegundos();
		(*ord)(v,n);
		t2 = microsegundos();
		t = t2 - t1;

		if (t < 500){
			c = '*';
			t1 = microsegundos();
			for(i = 0;i < k;i++){
				(*tipo)(v,n);
				(*ord)(v,n);
			}
			t2 = microsegundos();
			ta = (t2 - t1);

			t1 = microsegundos();
			for(i = 0;i < k;i++)
				(*tipo)(v,n);
			t2 = microsegundos();
			tb = (t2 - t1);
			
			t = (ta - tb)/k;
		}
		
		cotas(texto,metodo,&x,&y,&z,t,n);
		printf("%12d%c%15.4f%15.6f%15.8f%15.8f\n",n,c,t,x,y,z);
	}
	printf("\n");
}

//********************************************************
int main(){
	int n = 10;
	int v[n];
	
	inicializar_semilla();
	//TEST insercion
	test("por insercion","aleatorio",v,n,aleatorio,ord_ins);
	test("por insercion","descendente",v,n,descendente,ord_ins);
	test("por insercion","ascendente",v,n,ascendente,ord_ins);
	//TEST rapida
	test("rapida","aleatorio",v,n,aleatorio,ord_rap);
	test("rapida","descendente",v,n,descendente,ord_rap);
	test("rapida","ascendente",v,n,ascendente,ord_rap);
	//TIMES insercion
	times("por insercion","aleatoria",aleatorio,ord_ins,10,500,32000);
	times("por insercion","descendente",descendente,ord_ins,10,500,32000);
	times("por insercion","ascendente",ascendente,ord_ins,1000,500,32000);
	//TIMES rapida;;
	times("rapida","aleatoria",aleatorio,ord_rap,1,8000,1024000);
	times("rapida","descendente",descendente,ord_rap,10,8000,1024000);
	times("rapida","ascendente",ascendente,ord_rap,10,8000,1024000);

	return 0;
}

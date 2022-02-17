/*Nombre: Jose Joaquin Baz Pena (jose.baz1), Xan Limia García (xan.limia),
Armando Martínez Noya (a.mnoya).
Grupo de prácticas: 4.3.*/

#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

/* obtiene la hora actual en microsegundos */
double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}


void ord_ind (int v[], int n){
    int i, x, j;
    for (i = 1; i < n; i++){
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] >= x){
            v[j+1] = v[j];
            j = j - 1;
        }
        v[j+1] = x;
    }

}

void ord_shell (int v[], int n){
    int incremento, i, tmp, j;
    bool seguir;
    incremento = n;
    do{
        incremento /= 2;
        for(i = incremento; i < n; i++){
            tmp = v[i];
            j = i;
            seguir = true;
            while(j-incremento >= 0 && seguir){
                if(tmp < v[j-incremento]){
                    v[j]= v[j-incremento];
                    j = j - incremento;
                }
                else seguir = false;
            }
            v[j]= tmp;
        }

    }while (incremento != 1);
}

void inicializar_semilla()
{
    srand(time(NULL));
}

void aleatorio(int v[], int n)
{
    /* se generan números pseudoaleatorio entre -n y +n */
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void ascendente(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void descendente(int v[], int n)
{
    int i;
    for (i = n - 1; i >= 0; i--)
        v[i] = n - i;
}

void listarVector(int v[], int n){
    int i;
    printf("[");
    for (i = 0; i < n; i++){
        printf(" %d ", v[i]);
    }
    printf("]\n");
}

bool ordenado(int v[], int n){
    int i;
    for (i = 0; i < n -1; i++){
        if(v[i] > v[i+1])
            return false;
    }
    return true;
}


void tabla(void (*ord)(int v[], int n), void (*inicializacion)(int v[], int n)
		   , char* descripcion, float sub, float ajus, float sobre){
    int v[512000];
    int n, i, k = 1000;
    double t1, t2, t3, t, x, y, z;
    printf("\n%s\n", descripcion);
    printf("%11s%15s%11s%.2f%11s%.2f%11s%.2f\n","n","t(n)","t(n)/n^", sub,
           "t(n)/n^",ajus,"t(n)/n^", sobre);
    t = 0;
    for(n = 500;n <= 512000 && t<1000000;n*=2){
        inicializacion(v, n);
        t1 = microsegundos();
        ord(v, n);
        t2 = microsegundos();
        t = t2-t1;

        if (t < 500) {
            printf("%s%8d", "(*)", n);
            t1 = microsegundos();
            for (i = 0; i < k; i++) {
                inicializacion(v, n);
                ord(v, n);
            }
            t2 = microsegundos();
            for (i = 0; i < k; i++){
                inicializacion(v, n);
            }
            t3 = microsegundos();
            t = ((t2-t1)-(t3-t2))/k;
        }else printf("%11d", n);

        x = t / pow(n, sub);
        y = t / pow(n, ajus);
        z = t / pow(n, sobre);
        printf("%15.3f%15.8f%15.8f%15.8f\n",t,x,y,z);
    }
}

void test(void (*ord)(int v[], int n), void (*inicializacion)(int v[], int n),
		  int n, char* descripcion){
    int v[n];
    inicializacion(v, n);
    printf("%s\n", descripcion);
    listarVector(v, n);
    printf("Ordenado? %d\n", ordenado(v,n));
    ord(v, n);
    listarVector(v, n);
    printf("Ordenado? %d\n\n", ordenado(v, n));
}

void test1(){
    test(ord_shell, aleatorio, 17, 
		 "Ordenación shell con inicializacion aleatoria");
    test(ord_shell, ascendente, 10, 
		 "Ordenación shell con inicializacion ascendente");
    test(ord_shell, descendente, 10, 
		 "Ordenación shell con inicializacion descendente");
    test(ord_ind, aleatorio, 17, 
		 "Ordenación por inserción con inicializacion aleatoria");
    test(ord_ind, ascendente, 10, 
		 "Ordenación por inserción con inicializacion ascendente");
    test(ord_ind, descendente, 10, 
		 "Ordenación por inserción con inicializacion descendente");
}

void tablas(){
    tabla(ord_shell, aleatorio,
		  "Ordenación shell con inicializacion aleatoria", 1.1, 1.2, 1.3);
    tabla(ord_shell, ascendente, 
		  "Ordenación shell con inicializacion ascendente", 0.95, 1.12, 1.2);
    tabla(ord_shell, descendente, 
		  "Ordenación shell con inicializacion descendente", 1, 1.12, 1.2);
    tabla(ord_ind, aleatorio, 
		  "Ordenación por inserción con inicializacion aleatoria", 1.8, 2, 2.2);
    tabla(ord_ind, ascendente, 
		  "Ordenación por inserción con inicializacion ascendente", 0.8, 1, 1.2);
    tabla(ord_ind, descendente, 
		  "Ordenación por inserción con inicializacion descendente", 1.8, 2, 2.2);
}

int main(){
    inicializar_semilla();
    test1();
    tablas();
    return 0;
}

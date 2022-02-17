#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<time.h>
#include<math.h>
#include<string.h>
 
typedef struct{
    int n;
    double time;
    double sub;
    double ajus;
    double sobre;
    double ajusteo;
} info;
 
/*****************************************************************************/
double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
 
/*****************************************************************************/
void inicializar_semilla(){
    srand(time(NULL));
}
 
/*****************************************************************************/
void aleatorio(int v[], int n){
    int i, m = 2*n+1;
 
    for(i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}
 
/*****************************************************************************/
struct nodo {
    int elem;
    int num_repeticiones;
    struct nodo *izq, *der;
};
 
typedef struct nodo *posicion;
typedef struct nodo *arbol;
 
/*****************************************************************************/
static struct nodo *crearnodo(int e) {
 
    struct nodo *p = malloc(sizeof(struct nodo));
    if (p == NULL) {
        printf("memoria agotada\n"); exit(EXIT_FAILURE);
    }
    p->elem = e;
    p->num_repeticiones = 1;
    p->izq = NULL;
    p->der = NULL;
    return p;
}
 
/*****************************************************************************/
arbol insertar(int e, arbol a){
 
    if (a == NULL)
        return crearnodo(e);
    else if (e < a->elem)
        a->izq = insertar(e, a->izq);
    else if (e > a->elem)
        a->der = insertar(e, a->der);
    else
        a->num_repeticiones++;
    return a;
}
 
/*****************************************************************************/
arbol creararbol(){
    return NULL;
}
 
/*****************************************************************************/
int esarbolvacio(arbol a){
    return (a == NULL);
}
 
/*****************************************************************************/
posicion buscar(int n, arbol a){
    posicion p;
 
    if (esarbolvacio(a))
        p = NULL;
    else
    if (n == a->elem)
        p = a;
    else
    if (n < a->elem)
        p = buscar(n,a->izq);
    else
    if (n > a->elem)
        p = buscar(n,a->der);
 
    return p;
}
 
/*****************************************************************************/
arbol eliminararbol(arbol a){
 
    if (a->izq != NULL)
        eliminararbol(a->izq);
    if (a->der != NULL)
        eliminararbol(a->der);
    free(a);
    return NULL;
}
 
/*****************************************************************************/
posicion hijoizquierdo(arbol a){
    return a->izq;
}
 
/*****************************************************************************/
posicion hijoderecho(arbol a){
    return a->der;
}
 
/*****************************************************************************/
int elemento(posicion p){
    return p->elem;
}
 
/*****************************************************************************/
int numerorepeticiones(posicion p){
    return p->num_repeticiones;
}
 
/*****************************************************************************/
static int max(int a, int b){
    return (a>b)?a:b;
}
 
/*****************************************************************************/
int altura(arbol a){
    if(esarbolvacio(a))
        return -1;
    else
        return 1+(max(altura(a->izq),altura(a->der)));
}
 
/*****************************************************************************/
void visualizar(arbol a){
    if(esarbolvacio(a))
        printf("()");
    else{
        if (a->izq != NULL){
            printf("(");
            visualizar(a->izq);
            printf(")");
        }
        printf(" %d ",a->elem);
        if (a->der != NULL){;
            printf("(");
            visualizar(a->der);
            printf(")");
        }
    }
}
 
/*****************************************************************************/
void textoBuscar(int n, arbol a){
    posicion p;
 
    if ((p = buscar(n,a))== NULL)
        printf("Busco el %d y no encuentro nada\n",n);
    else{
        printf("Busco el %d, repetido %d veces\n",
            n,numerorepeticiones(p));
    }
}
 
/*****************************************************************************/
 arbol textoInsertar(int n, arbol a){
    a = insertar(n,a);
    printf("Inserto un %d\n",n);
    return a;
}
 
/*****************************************************************************/
void test(){
    arbol a;
 
    printf("\t********************TEST********************\n");
    a = creararbol();
    printf("Arbol vacio: ");
    visualizar(a);
    printf("\nAltura del arbol: %d\n",altura(a));
 
    a = textoInsertar(3,a);
    a = textoInsertar(1,a);
    a = textoInsertar(2,a);
    a = textoInsertar(5,a);
    a = textoInsertar(4,a);
    a = textoInsertar(5,a);
 
    printf("Arbol: ");
    visualizar(a);
    printf("\nAltura del arbol: %d\n",altura(a));
 
    textoBuscar(1,a);
    textoBuscar(2,a);
    textoBuscar(3,a);
    textoBuscar(4,a);
    textoBuscar(5,a);
    textoBuscar(6,a);
 
    a = eliminararbol(a);
    printf("Borro todos los nodos de la memoria:\n");
    printf("Arbol vacio: ");
    visualizar(a);
    printf("\nAltura del arbol: %d\n",altura(a));
    printf("\n");
}
 
/*****************************************************************************/
int prueba(info datosI[], info datosB[], int tam){
    int i,n,j,k,pos,r;
    double t1,t2,tI,tB;
    arbol a;
    int v[256000];
 
    k = 1; pos = 0; r = 0;
    for(n = 8000;n <= 256000;n = n*2){
 
        aleatorio(v,n);
        a = creararbol();
        t1 = microsegundos();
        for(i = 0;i < n;i++)
            a = insertar(v[i],a);
        t2 = microsegundos();
        tI = t2 - t1;
 
        aleatorio(v,n); 
        t1 = microsegundos();
        for(i = 0;i < n;i++)
            buscar(v[i],a);
        t2 = microsegundos();
        tB = t2 - t1;
 
 
        if (tB < 500){
 
            aleatorio(v,n); 
            t1 = microsegundos();
            for(j = 0;j < k;j++){
                for(i = 0;i < n;i++)
                    buscar(v[i],a);
            }
            t2 = microsegundos();
            tB = (t2 - t1)/k;
        }
        //buscar-insertar O(n*log(n)) teorico
 
        datosI[pos].n = n;
        datosI[pos].time = tI;
        datosI[pos].sub = tI / (pow(n,0.7)*log(n));
        datosI[pos].ajus = tI / (pow(n,1.2)*log(n));
        datosI[pos].ajusteo = tI / (n*log(n));
        datosI[pos].sobre = tI / (pow(n,1.5)*log(n));
        datosB[pos].n = n;
        datosB[pos].time = tB;
        datosB[pos].sub = tB / (pow(n,0.7)*log(n));
        datosB[pos].ajus = tB / (pow(n,1.2)*log(n));
        datosB[pos].ajusteo = tB / (n*log(n));
        datosB[pos].sobre = tB / (pow(n,1.5)*log(n));
        pos++;
        if (pos > tam)
            r = -1;
        a = eliminararbol(a);
    }
    return r;
}
/*****************************************************************************/
void estudio(){
    int tam = 6;
    int i;
    info datosI[tam];
    info datosB[tam];
     
    if (prueba(datosI, datosB, tam) == -1)
            printf("ERROR AL INTRODUCIR LOS DATOS");
    else{
        printf("\t********************TIEMPOS********************\n");
        printf("%12s%15s%15s\n","n","t_ins(n)","t_bus(n)");
        for(i = 0; i < tam; i++){
            printf("%12d%15.f%15.f\n",datosI[i].n,
                datosI[i].time,datosB[i].time);
        }
        printf("\n");
 
        printf("\t********************ESTUDIO********************\n");
        printf("Insercion de n elementos\n");
        printf("%12s%16s%15s%15s%15s%16s\n",
            "n","t(n)","t(n)/f(n)","t(n)/g(n)","t(n)/h(n)","t(n)/g(n)*");
        for(i = 0; i < tam; i++){
            printf("%12d%15.2f%15.4f%15.5f%15.7f%15.5f\n",datosI[i].n,
                datosI[i].time, datosI[i].sub,datosI[i].ajus,
                datosI[i].sobre,datosI[i].ajusteo);
        }
        printf("\n");
 
        printf("Busqueda de n elementos\n");
        printf("%12s%16s%15s%15s%15s%16s\n",
            "n","t(n)","t(n)/f(n)","t(n)/g(n)","t(n)/h(n)","t(n)/g(n)*");
        for(i = 0; i < tam; i++){
            printf("%12d%15.2f%15.4f%15.5f%15.7f%15.5f\n",datosB[i].n,
                datosB[i].time, datosB[i].sub,datosB[i].ajus,
                datosB[i].sobre,datosB[i].ajusteo);
        }
        printf("\n");
    }
}
 
/*****************************************************************************/
int main(){
 
    inicializar_semilla();
    test();
    estudio();
    return 0;
}

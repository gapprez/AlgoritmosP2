#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define UMBRAL 10

void inicializar_semilla() {
    srand(time(NULL));
}

void aleatorio(int v [], int n) {/* se generan números pseudoaleatorio entre -n y +n */
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
}

/* obtiene la hora actual en microsegundos */
double microsegundos(){
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}/* obtiene la hora actual en microsegundos */

void ascendente(int v [], int n) {
    int i;
    for (i=0; i < n; i++)
        v[i] = i;


}

void ord_ins (int v [], int n) {
    int i, j, x;
    for (i=1; i<n; i++) {
        x = v[i];
        j = i-1;
        while (j>=0 && v[j]>x) {
            v[j+1] = v[j];;
            j--;
        }
        v[j+1] = x;
    }
}
int es_ordenado(int v[], int n){
    int i,j;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(!v[i]<=v[j]) return 0;
        }
    }
    return 1;
}
void test(){
    int v[UMBRAL];
    int i;

    inicializar_semilla();
    aleatorio(v, UMBRAL);
    ord_ins(v, UMBRAL);

    for( i = 0; i< UMBRAL-1; i++){
        printf("%d, ",v[i]);
    }
    printf("%d",v[i]);
}

int main() {

test();
}
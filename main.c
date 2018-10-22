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

void descendente (int v[], int n){
	int i;

	for (i = 0; i < n; i++) {
		v[i] = n - i - 1;
	}
}

/*Algoritmos de ordenación*/

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

void intercambiar (int* i, int* j) {
	int aux;
	aux = *i;
	*i = *j;
	*j = aux;
}

void Mediana3(int v[], int i, int j) {
	int k;
	k = (i + j)/2;

	if (v[k] > v[j]) {
		intercambiar(&v[k], &v[j]);
	}
	if (v[k] > v[i]) {
		intercambiar(&v[k],&v[i]);
	}
	if (v[i] > v[j]) {
		intercambiar(&v[i], &v[j]);
	}
}

void OrdenarAux(int v[], int izq, int der) {
	int pivote, i, j;

	if ((izq + UMBRAL) <= der) {
		Mediana3(v, izq, der);

		pivote = v[izq];
		i = izq;
		j = der;

		while (j>i) {
			while (v[i] < pivote) {
				i++;
			}
			while (v[j] > pivote) {
				j--;
			}
			intercambiar(&v[i], &v[j]);
		}

		intercambiar(&v[i], &v[j]);
		intercambiar(&v[izq], &v[j]);
		OrdenarAux(v, izq, j-1);
		OrdenarAux(v, j+1, der);
	}
}

void rapida_aux(int v[], int ini, int n) {
	OrdenarAux(v, ini, n);

	if (UMBRAL > 1) {
		ord_ins(v, n);
	}
}

void ord_rapida(int v[], int n) {
	rapida_aux(v, 0, n-1);
	if (UMBRAL > 1){
		ord_ins(v, n);
	}
}

/*Fin algoritmos de ordenación*/

int es_ordenado(int v[], int n){
    int i;

    for(i = 0; i < n - 2; i++){
    	if (v[i] > v[i+1]) {
			return 0;
    	}
    }

    return 1;
}

void mostrarArray(int v[], int n) {
	int i;

	for (i = 0; i < n - 1; ++i) {
		printf("%d, ", v[i]);
	}
	printf("%d\n", v[i]);
}

struct {
	char* nombre;
	void (*func)(int v[], int nargs);
} ini [] = {
	{"aleatoria",aleatorio},
	{"descendente", descendente},
	{"ascendente", ascendente},
	{NULL, NULL}
}, ord [] = {
		{"por insercion",ord_ins},
		{"rápida", ord_rapida},
		{NULL, NULL}
};

void test(){
    int v[UMBRAL];
    int i, j;

    inicializar_semilla();

	for (j = 0; ord[j].nombre != NULL; j++) {
		for (i = 0; ini[i].nombre != NULL; i++) {
			ini[i].func(v, UMBRAL);
			printf("Ordenación %s con inicializacón %s\n",ord[j].nombre, ini[i].nombre);
			mostrarArray(v, UMBRAL);
			printf("¿ordenado? ");
			if (es_ordenado(v, UMBRAL)) {
				printf("1\n\n");
			} else {
				printf("0\nordenando...\n");
				ord_ins(v, UMBRAL);
				mostrarArray(v, UMBRAL);
				printf("¿ordenado? %d\n\n", es_ordenado(v, UMBRAL));
			}
		}
	}
}

int main() {

	test();
}
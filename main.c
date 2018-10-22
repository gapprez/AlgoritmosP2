#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define UMBRAL 1


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
			i++;
			while (v[i] < pivote) {
				i++;
			}
			j--;
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

void ord_rapida(int v[], int n) {
	OrdenarAux(v, 0, n-1);
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
	int k = 10;
    int v[k];
    int i, j;

    inicializar_semilla();

	for (j = 0; ord[j].func == ord_rapida; j++) {
		for (i = 0; ini[i].nombre != NULL; i++) {
			ini[i].func(v, k);
			printf("Ordenación %s con inicializacón %s\n",ord[j].nombre, ini[i].nombre);
			mostrarArray(v, k);
			printf("¿ordenado? ");
			if (es_ordenado(v, k)) {
				printf("1\n\n");
			} else {
				printf("0\nordenando...\n");
				ord[j].func(v, k);
				mostrarArray(v, k);
				printf("¿ordenado? %d\n\n", es_ordenado(v, k));
			}
		}
	}
}

void complejidad(int v[], void (*ord)(int [], int),
		void (*ini)(int [], int)) {

	double ta, tb, t, ti;
	int k, n;

	printf("%5s\t%5s\t%6s\t%7s\t%8s\n", "n", "t(n)", "t(n)/n^1.8", "t(n)/n^2", "t(n)/n^2.2");
	for (n = 100; n <= 6400; n = n * 2) {
		ini(v, n);
		ta = microsegundos();
		ord(v, n);
		tb = microsegundos();
		t = tb - ta;
		if (t < 500) {
			ta = microsegundos();
			for (k = 0; k < 100; k++) {
				aleatorio(v, n);
				ord_ins(v, n);
			}
			tb = microsegundos();
			t = tb - ta;

			ta = microsegundos();
			for (k = 0; k < 100; k++) {
				aleatorio(v, n);
			}
			tb = microsegundos();

			ti = tb - ta;
			t = (t - ti) / k;
		}
		printf("%5d\t%5f\t%.6f\t%.7f\t%.8f\n", n, t, t / pow(n, 1.8), t / pow(n, 2), t / pow(n, 2.2));
	}
}

void mostrarComplejidad() {
	int *v;
	int j, i;

	v = malloc(1024);
	inicializar_semilla();

	for(j = 0; ord[j].nombre != NULL; j++) {
		for (i = 0; ini[i].nombre != NULL; i++) {
			printf("\n-------------------------------------------------------------\n");
			printf("\nOrdenación %s con inicialización %s\n\n", ord[j].nombre, ini[i].nombre);
			complejidad(v, ord[j].func, ini[i].func);
		}
	}

	free(v);
}

int main() {

	test();
	mostrarComplejidad();
}
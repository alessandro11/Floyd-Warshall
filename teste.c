#include <stdio.h>
#include <malloc.h>
#include "grafo.h"

typedef unsigned int uint;
typedef long int lint;
typedef struct no *no;
typedef struct vertice* heap;

typedef enum __Estado {
	NaoVisitado = 0,
	Visitado
}Estado;

struct no {
  void*	conteudo;
  no	anterior;
  no 	proximo;
};

typedef struct lista *lista;
struct lista {
  unsigned int tamanho;
  no primeiro;
  no sentinela;
};

typedef struct grafo *grafo;
struct grafo {
	uint	nvertices;
	uint	narestas;
	int 	direcionado;
	int 	ponderado;
	lint	diametro;
	char*	nome;
	lista	vertices;
};


int destroi_vertice(void *v);

#ifdef DEBUG

#define UNUSED(x)				(void)(x)

void print_a(vertice, lista);
void print_v(grafo);
void print_vattr(grafo);
void print_vbylista(lista);
void print_heap(heap*);
void print_mat(lista**, grafo);
void print_mat_rev(lista**, grafo);
void print_mat_dist(lint**, uint);

#else

#define print_a(vertice, lista)		(void)0
#define print_v(grafo)				(void)0
#define print_vattr(grafo)			(void)0
#define print_vbylista(lista)		(void)0
#define print_heap(heap)			(void)0
#define print_mat(lista, grafo)		(void)0
#define print_mat_dist(dist_m, grafo)(void)0
#define print_mat_rev(lista, grsfo)	(void)0
#endif /* DEBUG */


//------------------------------------------------------------------------------
int main(int argc, char* argv[]) {

  FILE *fs = fopen(argv[1], "r");
  grafo g = le_grafo(fs);
  fclose(fs);

  if( !g )
    return 1;
	uint i, j;

	lint **dist = (lint**)calloc(g->nvertices, sizeof(lint**));
	for( i=0; i < g->nvertices; i++ ) {
		dist[i] = (lint*)calloc(g->nvertices, sizeof(lint*));
	}

	distancias(dist, g, 'd');
	print_mat_dist(dist, g->nvertices);
	puts("\n");
	distancias(dist, g, ' ');
	print_mat_dist(dist, g->nvertices);

	for( i=0; i < g->nvertices; i++ ) {
		free(dist[i]);
	}
	free(dist);

	fprintf(stderr, "%d\n", direcionado(g));
	fprintf(stderr, "%ld\n", diametro(g));

  printf("nome: %s\n", nome_grafo(g));
  printf("%sdirecionado\n", direcionado(g) ? "" : "não ");
  printf("%sponderado\n", ponderado(g) ? "" : "não ");
  printf("%d vértices\n", numero_vertices(g));
  printf("%d arestas\n", numero_arestas(g));

  escreve_grafo(stdout, g);

  return ! destroi_grafo(g);
}

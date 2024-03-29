/*
 * debug.c
 *
 *  Created on: Nov 6, 2016
 *      Author: m3cool
 */

#include <stdio.h>

/*
 * DO NOT DECLARE IN THE HEADER SINCE NEEDS TO KNOW TYPES vertices, lista and
 * grafo. DO NOT DEVCLARE THIS TYPES IN debug.h, AFTER ALL THIS ARE DUPLICATED
 * CODE AND WILL RISE REDECLARATION BY THE COMPILER.
 */
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
	uint 	nvertices;
	uint 	narestas;
	int		direcionado;
	int		ponderado;
	lint	diametro;
	char*	nome;
	lista	vertices;
};

typedef struct vertice* vertice;
struct vertice {
	char*	nome;
	uint	id;
	lint	distancia;
	Estado	estado;
	vertice anterior;
	vertice proximo;
	lista	vizinhos_sai;
	lista	vizinhos_ent;
};

typedef struct aresta* aresta;
struct aresta {
	int		ponderado;
	lint	peso;
	vertice origem;
	vertice	destino;
};

no primeiro_no(lista l);
no ultimo_no(lista l);

no proximo_no(no n);
void *conteudo(no n);

/*
 * DO NOT DECLARE IN THE HEADER SINCE NEEDS TO KNOW TYPES vertices, lista and
 * grafo. DO NOT DEVCLARE THIS TYPES IN debug.h, AFTER ALL THIS ARE DUPLICATED
 * CODE AND WILL RISE REDECLARATION BY THE COMPILER.
 */
void print_a(vertice, lista);
void print_v(grafo g);
void print_attr(vertice v, lista l);
no anterior_no(no);


/*____________________________________________________________________________*/
void print_v(grafo g) {
	no n;
	struct vertice* v;
	lista l = g->vertices;

	printf("Grafo %s=%p\n", g->nome, g);
	for( n=primeiro_no(l); n->conteudo; n=proximo_no(n) ) {
			v = conteudo(n);
			printf("%u %s=%p\n", v->id, v->nome, v);
			printf("\tV.:\n");
			print_a(v, v->vizinhos_sai);
	}
	fflush(stdout);
}

void print_vbylista(lista l) {
	no n;
	vertice v;

	for( n=primeiro_no(l); n->conteudo; n=proximo_no(n) ) {
		v = conteudo(n);
        fprintf(stderr, "(%s, %s), Estado=%s, Distancia=%ld, possui %u aresta(s).\n",\
        		v->anterior ? v->anterior->nome : "NULL",\
        		v->nome,\
				v->estado == NaoVisitado ? "NaoVisitado" : "Visitado",\
				v->distancia,\
				v->vizinhos_sai->tamanho);

		print_attr(v, v->vizinhos_sai);
	}
}

void print_a(vertice v, lista l) {
    no n;
    struct aresta* a;

    n=primeiro_no(l);
    if( n ) {
        a = conteudo(n);
        fprintf(stderr, "\taresta=%p\n", a);
        fprintf(stderr, "\t(%s=%p, %s=%p)\n", v->nome, v, a->destino->nome, a->destino);
        for( n=proximo_no(n); n->conteudo; n=proximo_no(n) ) {
            a = conteudo(n);
            fprintf(stderr, "\taresta=%p\n", a);
            fprintf(stderr, "\t(%s=%p, %s=%p)\n", v->nome, v, a->destino->nome, a->destino);
        }
    }
}

void print_attr(vertice v, lista l) {
	no n;
	aresta a;

    n=primeiro_no(l);
    if( n ) {
        a = conteudo(n);
        fprintf(stderr, "\t(%s, %s) Peso=%ld\n",\
				a->origem->nome,\
				a->destino->nome,\
				a->peso);
        for( n=proximo_no(n); n->conteudo; n=proximo_no(n) ) {
            a = conteudo(n);
            fprintf(stderr, "\t(%s, %s) Peso=%ld\n",\
					a->origem->nome,\
    				a->destino->nome,\
    				a->peso);
        }
    }

}

void print_vattr(grafo g) {
	no n;
	vertice v;
	lista l = g->vertices;

	printf("Grafo %s=%p\n", g->nome, g);
	for( n=primeiro_no(l); n->conteudo; n=proximo_no(n) ) {
		v = conteudo(n);
        fprintf(stderr, "%s, Estado=%s, Distancia=%ld, possui %u aresta(s).\n",\
        		v->nome,\
				v->estado == NaoVisitado ? "NaoVisitado" : "Visitado",\
				v->distancia,\
				v->vizinhos_sai->tamanho);

		print_attr(v, v->vizinhos_sai);
	}
}

void print_heap(heap *h) {
	unsigned int i = 1;
	heap *p = h+1;

	puts("");
	while( *p ) {
		fprintf(stderr, "%u %s, dist=%ld\n", i++, (*p)->nome, (*p)->distancia);
		p++;
	}
}

const char *busca_nome(unsigned int id, grafo g) {
	const char *p = NULL;
	vertice u;

	for( no n=primeiro_no(g->vertices); n->conteudo && !p; n=proximo_no(n) ) {
		u = conteudo(n);
		if( u->id == id )
			p = u->nome;
	}

	return p;
}

void print_mat(lista **m, grafo g) {
	lista l;
	no n;
	vertice u;
	unsigned int i, j;

	for( i=0; i < g->nvertices; i++ ) {
		for( j=0; j < g->nvertices; j++ ) {
			fprintf(stderr, "(%u %u, %s %s)\n", i, j,\
					busca_nome(i, g), busca_nome(j, g));

			l = m[i][j];
			n = primeiro_no(l);
			if( n->conteudo ) {
				u = conteudo(n);
				fprintf(stderr, "\t%s", u->nome);
				for( n=proximo_no(n); n->conteudo; n=proximo_no(n) ) {
					u = conteudo(n);
					fprintf(stderr, "->%s", u->nome);
				}
				fprintf(stderr, "\n");
//				fprintf(stderr, " distancia = %ld\n", u->distancia);
			}
		}
	}
}

void print_mat_rev(lista **m, grafo g) {
	lista l;
	no n;
	vertice u;
	unsigned int i, j;

	for( i=0; i < g->nvertices; i++ ) {
		for( j=0; j < g->nvertices; j++ ) {
			fprintf(stderr, "(%u %u, %s %s)\n", i, j,\
					busca_nome(i, g), busca_nome(j, g));

			l = m[i][j];
			n = ultimo_no(l);
			if( n && n->conteudo ) {
				u = conteudo(n);
				fprintf(stderr, "\t%s", u->nome);
				for( n=anterior_no(n); n->conteudo; n=anterior_no(n) ) {
					u = conteudo(n);
					fprintf(stderr, "->%s", u->nome);
				}
				fprintf(stderr, "\n");
//				fprintf(stderr, " distancia = %ld\n", u->distancia);
			}
		}
	}
}

void print_mat_v(vertice **m, grafo g) {
	unsigned int i, j;

	for( i=0; i < g->nvertices; i++ ) {
		for( j=0; j < g->nvertices; j++ ) {
			if( !m[i][j] ) {
				fprintf(stderr, "(%u,%u) ", i, j);
				continue;
			}
			fprintf(stderr, "(%u,%u n=%s id=%u) ", i, j,\
					m[i][j]->nome, m[i][j]->id);

		}
		fprintf(stderr, "\n");
	}
}

void print_mat_dist(lint **d, uint size) {
	uint i, j;

	for( i=0; i < size; ++i ) {
		fprintf(stderr, "%ld", d[i][0]);
		for( j=1; j < size; ++j ) {
			fprintf(stderr, " %ld", d[i][j]);
		}
		fprintf(stderr, "\n");
	}
}

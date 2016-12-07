	//https://www.youtube.com/watch?v=gdmfOwyQlcI
	//binary heap
	//http://www.cs.princeton.edu/~wayne/cs423/lectures/heaps-4up.pdf

	uint i, j;

	lint **dist = (lint**)calloc(g->nvertices, sizeof(lint**));
	for( i=0; i < g->nvertices; i++ ) {
		dist[i] = (lint*)calloc(g->nvertices, sizeof(lint*));
	}

	distancias(dist, g, 'd');
	print_mat_dist(dist, g->nvertices);
	distancias(dist, g, ' ');
	print_mat_dist(dist, g->nvertices);

	for( i=0; i < g->nvertices; i++ ) {
		free(dist[i]);
	}
	free(dist);

	fprintf(stderr, "%d\n", direcionado(g));
	fprintf(stderr, "%ld\n", diametro(g));
////////////////
	vertice u;
	vertice v;
	lista T;

	u = busca_vertice("A", g->vertices);
	v = busca_vertice("G", g->vertices);
	fprintf(stderr, "%ld\n", distancia(u, v, g));

	T = caminho_minimo(u, v, g);
	print_vbylista(T);
	destroi_lista(T, NULL);
///////////////////////
	lista **T2;
	uint i, j;
	T2 = (lista**)calloc(g->nvertices, sizeof(lista**));
	lista **p = T2;
	for( no n=primeiro_no(g->vertices); n->conteudo; n=proximo_no(n) )
		*p++ = (lista*)calloc(g->nvertices, sizeof(lista*));

	caminhos_minimos(T2, g, 'd');
	print_mat(T2, g);
	for( int i=0; i < g->nvertices; ++i ) {
		for( int j=0; j < g->nvertices; ++j )
			destroi_lista(T2[i][j], destroi_vertice);
	}
	caminhos_minimos(T2, g, ' ');
	print_mat_rev(T2, g);

	p = T2;
	for( i=0; i < g->nvertices; i++  ) {
		for( j=0; j< g->nvertices; j++ ) {
			destroi_lista(T2[i][j], destroi_vertice);
		}
		free(*p++);
	}
	free(T2);

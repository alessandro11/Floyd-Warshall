lista **caminhos_minimos(lista **c, grafo g, char algoritmo);

A implementação desta função com a busca pelos caminhos mínimos com o algoritmo
Floyd&Warshall constrói a ordem do caminho com a estrutura lista, que pela sua
natureza constrói como uma pilha, ou seja, o no novo sempre vai em head, devido
a isto a ORDEM do camiho fica invertido, então construi a lista duplamete enca-
deada o que permite navegar pelos vértices em orem reversa, logo obtendo o
resultado com a ordem esperado. OBS: foi utilizado a sentinela como head da lista.

		for( no n=ultimo_no(l); n->conteudo; n=anterior_no(n) ) {
			u = conteudo(n);
			...
		} 
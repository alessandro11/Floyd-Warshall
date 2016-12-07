    lista l;
    l = constroi_lista();
    int a=1;
    insere_lista((void*)a++, l);
    insere_lista((void*)a++, l);
    insere_lista((void*)a, l);
    destroi_lista(l, NULL);

    no n;
    void *c;
    for( n=primeiro_no(l); n->conteudo; n=proximo_no(n) ) {
    	c=conteudo(n);
    	fprintf(stderr, "0x%x\n", (uint)(unsigned long)c);
    }
    for( n=ultimo_no(l); n->conteudo; n=anterior_no(n) ) {
    	c=conteudo(n);
    	fprintf(stderr, "0x%x\n", (uint)(unsigned long)c);
    }

    exit(0);

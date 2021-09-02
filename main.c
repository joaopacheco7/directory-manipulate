#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "workTree.h"

int main(){

    Arv* raiz = criaArvore();

    if(inicializaArvore(raiz))
        printf("Inicializada com sucesso \n");

    while(1){
        localizacao(raiz);
        selecionaComando(raiz);
    }

    return 0;
}

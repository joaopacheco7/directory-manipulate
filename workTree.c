#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "workTree.h"

struct no{
    char dado[60];
    struct no *pai;
    struct no *irmao;
    struct no *conteudo;
};

typedef struct no Elemento;
typedef struct no* Arv;

Arv* criaArvore(){
    Arv* raiz = (Arv*) malloc(sizeof(Arv));
    if(raiz != NULL)
        *raiz = NULL;
    Elemento *no = (Elemento*)malloc(sizeof(Elemento));
    strcpy(no->dado, "c:");
    no->conteudo = NULL;
    no->irmao = NULL;
    no->pai = NULL;
    (*raiz) = no;

    return raiz;
}

int criaFilhos(Arv* raiz, char texto[60]){
    if(raiz == NULL)
        return 0;
    if(texto[0] == 0)
        return 0;
    char aux[60];
    int i = 0;
    for(i = 0; i < 60; i++)
        aux[i] = 0;
    memccpy(aux, texto, 47, 60);
    i = 0;
    while(aux[i] != 47)
        i++;
    aux[i] = 0;
    Elemento *verificaIgual = (*raiz)->conteudo;
    Elemento *no;

    if(verificaIgual == NULL){
        no = (Elemento*) malloc(sizeof(Elemento));
        if(no == NULL)
            return 0;
        strcpy(no->dado, aux);
        no->irmao = NULL;
        no->conteudo = NULL;
        no->pai = (*raiz);
        (*raiz)->conteudo = no;
    }else{
        while(verificaIgual != NULL && strcmp(verificaIgual->dado, aux)){
            verificaIgual = verificaIgual->irmao;
        }
        if(verificaIgual == NULL){
            no = (Elemento*) malloc(sizeof(Elemento));
            if(no == NULL)
                return 0;
            strcpy(no->dado, aux);
            no->irmao = (*raiz)->conteudo;
            no->pai = (*raiz);
            (*raiz)->conteudo = no;
        }else{
            no = verificaIgual;
        }
    }
    int tamanho = strlen(aux) + 1;
    for(i = 0; i < 60; i++)
        aux[i] = 0;
    for(i = 0; i < strlen(texto); i++)
        aux[i] = texto[tamanho + i];
    criaFilhos(&no, aux);
    return 1;
}

void liberaArvore(Arv* raiz){
    if((*raiz) == NULL)
        return;
    Elemento *no = *raiz;
    if((no)->irmao != NULL){
        liberaArvore(&((no)->irmao));
    }
    if((no)->conteudo != NULL){
        liberaArvore(&((no)->conteudo));
    }
    free(no);
    return;
}

void comandoLIST(Arv* raiz){
    if((*raiz) == NULL)
        return;
    Elemento *no = (*raiz)->conteudo;
    while(no != NULL){
        printf("%s \n", no->dado);
        no = no->irmao;
    }
}

void comandoCD(Arv* raiz, char diretorio[60]){
    if(*raiz == NULL)
        return;
    if(diretorio[0] == 0)
        return;
    char arquivo[60];
    memccpy(arquivo, diretorio, 46 ,60);
    if(strlen(arquivo) == strlen(diretorio)){
        Elemento *no = (*raiz)->conteudo;

        if(no == NULL)
            return;

        while(no != NULL && strcmp(no->dado, diretorio)){
            no = no->irmao;
        }

        if(no != NULL){
            (*raiz) = no;
            return;
        }else{
            no = (*raiz)->conteudo;
            int ver, cont, i = 0;
            cont = 0;
            printf("Diretorios parecidos:\n");
            while(no != NULL){
                while (diretorio[i] != 0){
                    if (no->dado[i] == diretorio[i]){
                        ver = 1;
                    }else{
                        ver = 0;
                    }
                    i++;
                }
                if (ver == 1){
                    printf("%s\n", no->dado);
                    cont++;
                }
                no = no->irmao;
                i = 0;
                ver = 0;
            }
            if(cont == 0){
                printf("Diretorio nao encontrado.\n");
            }

            return;
        }
    }else{
        int i = 0;
        while(arquivo[i] != 46)
            i++;
        arquivo[i] = '\0';
        printf("%s e um arquivo nao um diretorio \n", arquivo);
    }
}

void localizacao(Arv* raiz){
    if(*raiz == NULL)
        return;

    if(raiz == NULL)
        return;


    Elemento *aux = *raiz;

    if(aux->pai != NULL){
        localizacao(&((*raiz)->pai));
    }

    printf("%s>", aux->dado);
}

void comandoSEARCH(Arv* raiz, char arquivo[60]){
    if(*raiz == NULL)
        return;
    if(arquivo[0] == 0)
        return;

    Elemento *no = *raiz;
    if( !strcmp(no->dado, arquivo)){
        localizacao(raiz);
        return;
    }else{

        if(no->irmao != NULL)
            comandoSEARCH(&((no)->irmao), arquivo);
        if(no->conteudo != NULL)
            comandoSEARCH(&((no)->conteudo), arquivo);
    }
}

void comandoRM(Arv* raiz, char alvo[60]){
    if(*raiz == NULL)
        return;
    if(alvo[0] == 0)
        return;

    Elemento *no = (*raiz)->conteudo;

    if(no != NULL){
        if(!strcmp(no->dado, alvo)){

            (*raiz)->conteudo = (*raiz)->conteudo->irmao;
            if(no->conteudo != NULL){
                Arv* aux = (Arv*) malloc(sizeof(Arv));
                *aux = no->conteudo;
                liberaArvore(aux);
                free(aux);
            }
        }else{
            Elemento *ant = no;
            while(no != NULL && strcmp(no->dado, alvo)){
                ant = no;
                no = no->irmao;
            }
            if(no == NULL)
                return;
            ant->irmao = no->irmao;
            if(no->conteudo != NULL){
                Arv* aux = (Arv*) malloc(sizeof(Arv));
                *aux = no->conteudo;
                liberaArvore(aux);
                free(aux);
            }
        }
        free(no);
    }
}

void comandoMKDIR(Arv* raiz, char inserir[60]){
    if(raiz == NULL)
        return;
    if(inserir[0] == 0)
        return;
    Elemento *no = (*raiz)->conteudo;

    while(no != NULL && strcmp(no->dado, inserir)){
        no = no->irmao;
    }

    if(no != NULL){
        printf("Ja existe este diretorio \n");
    }else{
        Elemento *aux = (Elemento*) malloc(sizeof(Elemento));
        strcpy(aux->dado, inserir);
        aux->irmao = (*raiz)->conteudo;
        aux->pai = *raiz;
        aux->conteudo = NULL;
        (*raiz)->conteudo = aux;
    }
}

void comandoClear(){
    system("cls");
}

void comandoExit(Arv* raiz){
    if(raiz == NULL)
        return;
    if(*raiz == NULL)
        return;

    Elemento *aux = (*raiz);

    while(aux->pai != NULL)
        aux = aux->pai;

    Arv* exclui = (Arv*) malloc(sizeof(Arv));

    *exclui = aux;

    liberaArvore(exclui);

    free(exclui);
    exit(1);
}

int inicializaArvore(Arv* raiz){
    if(raiz == NULL)
        return 0;

    FILE *arq;
    char dir[90];
    int aux;

    arq = fopen("arquivo.txt", "r");

    if(arq != NULL){
        while (!feof(arq)){
            fgets(dir, 90, arq);
            aux = strlen(dir);
            if(dir[aux - 1] == '\n'){
                dir[aux - 1] = 47;
            }else{
                dir[aux] = 47;
                dir[aux + 1] = '\0';
            }
            criaFilhos(raiz, dir);
            for(aux  = 0; aux < 90; aux++)
                dir[aux] = 0;
            aux = 0;
        }
    }else{
        printf("Erro ao abrir o arquivo \n");
        exit(1);
    }

    fclose(arq);

    return 1;
}

void voltaDiretorio(Arv* raiz){
    if(raiz == NULL)
        return;
    if(*raiz == NULL)
        return;

    if((*raiz)->pai != NULL)
        (*raiz) = (*raiz)->pai;
}

void voltaTudo(Arv* raiz){
    if(raiz == NULL)
        return;
    if(*raiz == NULL)
        return;

    while((*raiz)->pai != NULL)
        (*raiz) = (*raiz)->pai;
}

void selecionaComando(Arv*raiz){
    if(raiz == NULL)
        return;
    if(*raiz == NULL)
        return;

    int i, tamanho;
    char comando[30], texto[90], rest[60],novo[60],original[60];
    scanf("%s", texto);
    memccpy(comando, texto, 32, 30);

    i = 0;
    while(comando[i] != 32 && comando[i] != '\0')
            i++;
    if(comando[i] != 32){
    }else{
        comando[i] = '\0';
    }

    tamanho = strlen(comando) + 1;

    if(!strcmp(comando, "cd")){
        for(i = 0; i < strlen(texto); i++)
            rest[i] = texto[tamanho + i];
        if(!strcmp(rest, "user")){
            voltaTudo(raiz);
            return;
        }
        if(!strcmp(rest, "--")){
            voltaDiretorio(raiz);
            return;
        }
        comandoCD(raiz, rest);
        return;
    }

    if(!strcmp(comando, "search")){
        for(i = 0; i < strlen(texto); i++)
            rest[i] = texto[tamanho + i];
        comandoSEARCH(raiz, rest);
        printf("\n");
        return;
    }

    if(!strcmp(comando, "rm")){
        for(i = 0; i < strlen(texto); i++)
            rest[i] = texto[tamanho + i];
        comandoRM(raiz, rest);
        return;
    }

    if(!strcmp(comando, "mkdir")){
        for(i = 0; i < strlen(texto); i++)
            rest[i] = texto[tamanho + i];
        comandoMKDIR(raiz, rest);
        return;
    }

    if(!strcmp(comando, "list")){
        comandoLIST(raiz);
        return;
    }

    if(!strcmp(comando, "clear")){
        comandoClear();
        return;
    }

     if(!strcmp(comando, "exit")){
        comandoExit(raiz);
        return;
    }

     if(!strcmp(comando, "help")){
        FILE *arq;
        char dir[90];

        arq = fopen("ajuda.txt", "r");
        if(arq != NULL){
            while (!feof(arq)){
            fgets(dir, 90, arq);
            printf("%s", dir);
            }
        }
        fclose(arq);
        printf("\n");
        return;
    }

    printf("Comando invalido \n");
    return;
}








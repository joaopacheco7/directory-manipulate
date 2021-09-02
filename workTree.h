typedef struct no Elemento;
typedef struct no* Arv;

Arv* criaArvore();

int criaFilhos(Arv* raiz, char texto[60]);
void liberaArvore(Arv* raiz);
void comandoLIST(Arv* raiz);
void comandoCD(Arv* raiz, char diretorio[60]);
void localizacao(Arv* raiz);
void comandoSEARCH(Arv* raiz, char arquivo[60]);
void comandoRM(Arv* raiz, char alvo[60]);
void comandoMKDIR(Arv* raiz, char inserir[60]);
void comandoClear();
void comandoExit(Arv* raiz);
int inicializaArvore(Arv* raiz);
void selecionaComando(Arv*raiz);
void voltaDiretorio(Arv* raiz);
void voltaTudo(Arv* raiz);

// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Realizado por Francisco Andrade Carvalho - 2019129635

#ifndef UTILS_H
#define UTILS_H


// Inicializa o gerador de numeros aleatorios.
// Esta funcao deve ser chamada apenas uma vez no inicio da execucao do programa
void initRandom();

//Devolve um valor inteiro aleatorio distribuido uniformemente entre [a, b]
int intUniformRnd(int a, int b);

// Devolve o valor 1 com probabilidade prob. Caso contrario, devolve 0
int probEvento(float prob);

// altera a variavel que assiste a detecao de vitória
int altera_tabuleiro_a_jogar(int x, int y, int *p);

// apos cada jogada efetuada, esta é guardada numa lista ligada
void Guarda_jogada();

typedef struct jogo jogada, *pjogada;

struct jogo{
    int posx,posy; // valores em cada no
    char jogador_c;
    pjogada prox; //ponteiro que aponta para o proximo nó
};

// cada vez que esta funcao e chamada, e adicionado um no a lista ligada
pjogada insere(int posx, int posy, int jogador, pjogada p);

//esta funcao preenche a estrutura p
void preenche(int posx, int posy, int jogador, pjogada p);

//recebe o ponteiro para o primeiro elemento da lista ligada e a quantidade de nos a imprimir (de tras para a frente e no maximo 10)
void imprime_lista_ligada(pjogada p,int num,int tam_lista_ligada);

//percorre a lista toda e liberta a memoria um no de cada vez
void liberta_lista_ligada(pjogada p);

void guarda_jogo_bin(pjogada p, int numjogadas);

int abre_ficheiro(char **t,pjogada p);

void exportar_tab_txt(char string[],pjogada p);


#endif /* UTILS_H */

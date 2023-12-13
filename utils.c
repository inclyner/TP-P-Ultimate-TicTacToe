// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Realizado por Francisco Andrade Carvalho - 2019129635
#include "matdin.h"
#include <stdlib.h>
#include <time.h>

#include "utils.h"

void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}

int altera_tabuleiro_a_jogar(int x,int y, int *p){

    if(x==0 || x==3 || x==6)
        p[0] = 0;
    else if(x==1 || x==4 || x==7)
        p[0] = 3;
    else if(x==2 || x==5 || x==8)
        p[0]=6;

    if(y==0 || y==3 || y==6)
        p[1] = 0;
    else if(y==1 || y==4 || y==7)
        p[1] = 3;
    else if(y==2 || y==5 || y==8)
        p[1]=6;

   if(p[0]==0 && p[1]==0)
       return 1;
   else if(p[0]==0 && p[1]==3)
       return 2;
   else if(p[0]==0 && p[1]==6)
       return 3;
   else if(p[0]==3 && p[1]==0)
       return 4;
   else if(p[0]==3 && p[1]==3)
       return 5;
   else if(p[0]==3 && p[1]==6)
       return 6;
   else if(p[0]==6 && p[1]==0)
       return 7;
   else if(p[0]==6 && p[1]==3)
       return 8;
   else if(p[0]==6 && p[1]==6)
       return 9;

   return 0;
}

pjogada insere(int posx, int posy, int jogador, pjogada p){
    pjogada novo, aux;
    novo = malloc(sizeof (jogada)); //aloca espaço para colocar a estrutura jogo
    if(novo==NULL){
        printf("Erro a alocar memoria\n");
        return p;
    }


    if(p==NULL){
        p=novo;
    }else{
        aux=p; // aux = no atual
        while(aux->prox != NULL) //enquanto o nó atual tiver ponteiro para o proximo nó, passar nó a frente
            aux = aux ->prox;
        aux->prox = novo;
    }
    preenche(posx, posy,jogador,novo);
    return p;
}

void preenche(int posx, int posy, int jogador, pjogada p){

    p->posx = posx; //insere valores na estrutura p
    p->posy = posy;
    if(jogador==1){p->jogador_c = 'X';}
    else
        p->jogador_c = 'O';
    p->prox =NULL; // coloca o endereço do proximo no a null (porque nao ha prox no)
}

void imprime_lista_ligada(pjogada p,int num,int tam_lista_ligada ){
    int i=0;
    if(p==NULL){
            printf("Tem de haver pelo menos uma jogada para ver o historico de jogadas");
        }
        pjogada temp;
        temp= p;
        if(tam_lista_ligada>10) {
        for(i=0;i<tam_lista_ligada-10;i++){
            temp=temp->prox;
        }
        for(i=0;i<10-num;i++){
            temp=temp->prox;
        }
        }
        while(temp!=NULL){//iterar pela lista ligada ate chegar ao fim
            printf("\nCoordenada X: %d\nCoordenada Y: %d\nLetra jogada: %c",temp->posx+1,temp->posy+1, temp->jogador_c);
            temp=temp->prox;
        }
}


void liberta_lista_ligada(pjogada p){
    pjogada temp;
    while(p!=NULL){
        temp=p;
        p= temp->prox;
        free(p);
    }
}

void guarda_jogo_bin(pjogada p,int numJogadas){
    FILE* jogo = fopen("jogo.bin","wb"); //w=>write binary
    char aux[1];
    pjogada temp;
    if (jogo==NULL){
        printf("Erro a guardar o ficheiro jogo.bin.");
        return;
    }
        while(p != NULL)
        {
            fwrite(&p, sizeof(pjogada), 1, jogo);
            p = p->prox;
        }
        fclose(jogo);

    /*for(int i=0;i<numJogadas;i++){
        sprintf(aux,"%d",p->posx);
        fwrite(aux,sizeof(char),1,jogo);
        sprintf(aux,"%d",p->posy);
        fwrite(aux,sizeof(char),1,jogo);
        aux[0] = p->jogador_c;
        fwrite(aux,sizeof(char),1,jogo);
        temp=p;
        p= temp->prox;
        printf("guardado: %d",i);
    }*/

    printf("jogo guardado com sucesso!");
    fclose(jogo);
}

int abre_ficheiro(char **t,pjogada p){
    FILE* jogo = fopen("jogo.bin","r");
    char coordx[1],coordy[1];
    int No_jogadas = 0,coord_x,coord_y;
    char jogador[1];
    char aux;
    if(jogo==NULL){
        printf("Erro ao abrir o ficheiro.");
        fclose(jogo);
        return 0;
    }

        do{
            fread(p,sizeof(pjogada),1,jogo);
            setPos(t,p->posx ,p->posy,p->jogador_c);
            No_jogadas++;
            printf("\ncoordx: %d, coordy: %d, jogador: %c\n",coordx,coordy,jogador);

        }while(feof(jogo));
        printf("jogo carregado com sucesso!");
    fclose(jogo);
        return No_jogadas;



}



void exportar_tab_txt(char string[10],pjogada p){
    FILE *tabuleiro;
    tabuleiro = fopen(string,"w");
    char aux[1];

        if(!tabuleiro)
        {
            printf("Nao foi possivel abrir o ficheiro");
            return;
        }
        while(p!=NULL)
        {
            fprintf(tabuleiro,"Linha: %d\nColuna: %d\nJogador: %c\n\n",
                    p->posx, p->posy, p->jogador_c);
            p = p->prox;
        }
        fclose(tabuleiro);
}


/*
// Função main () com alguns exemplos simples de utilizacao das funcoes
int main(){

  int i;

    initRandom();   // esta função só deve ser chamada uma vez

    printf("10 valores aleatorios uniformes entre [4, 10]:\n");
    for(i=0; i<10; i++)
        printf("%d\n", intUniformRnd(4, 100));

    printf(" Probabilidade 0.25 de um evento suceder: \n");
    for(i=0; i<10; i++)
        printf("%d\n", probEvento(0.25));

    return 0;
}
*/
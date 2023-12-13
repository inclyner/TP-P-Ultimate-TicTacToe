// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Realizado por Francisco Andrade Carvalho - 2019129635
#include "matdin.h"


void libertaMat(char** p, int nLin){

    int i;

    for(i=0; i<nLin; i++)
        free(p[i]);
    free(p);
}


char** criaMat(int nLin, int nCol){
    char **p = NULL;
    int i, j;

    p = malloc(sizeof(char*) * nLin);
    if(p == NULL)
        return NULL;

    for(i=0; i<nLin; i++){
        p[i] = malloc(sizeof(char) * nCol);
        if(p[i] == NULL){
            libertaMat(p, i-1);
            return NULL;
        }
        for(j=0; j<nCol; j++)
            p[i][j] = '_';
    }
    return p;
}


void setPos(char **p, int x, int y, char c){
    p[y][x] = c; // trocados o x e y, por estarem ao contrario (para mim faz-me mais sentido que o x seja na horizontal, e o y na vertical)
}


char getPos(char **p, int x, int y){
    return p[x][y];
}


void mostraMat(char **p){
    int i,j;
    int nLin = 9;
    int nCol=9;
    putchar('\n');
    for(i=0; i<nLin; i++){
        for(j=0; j<nCol; j++){
            printf("%c\t", p[i][j]);
            if (j==2 ||j==5){printf("@\t");}
        }
        putchar('\n');
        if(i==2||i==5){
            for(int a = 0;a<nLin +2 ;a++){printf("@\t");
            }putchar('\n');
        }
    }
}

int verifica_vitoria(char **a, int sup_esq[2]){
    char aux;
    int contX=0, contY=0;
    //verif 3 linhas
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            aux =getPos(a,sup_esq[0]+i,sup_esq[1]+j);
            if (aux== '_')
                break;
            else if(aux=='X')
                contX++;
            else if(aux=='O')
                contY++;
        }
        if(contX==3)
            return 1;
        else if (contY==3)
            return 2;
        else{
            contX= 0;
            contY= 0;
        }
    }
    //verif colunas
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            aux =getPos(a,sup_esq[0]+j,sup_esq[1]+i);
            if (aux== '_')
                break;
            else if(aux=='X')
                contX++;
            else if(aux=='O')
                contY++;
        }
        if(contX==3)
            return 1;
        else if (contY==3)
            return 2;
        else{
            contX= 0;
            contY= 0;
        }
        }

        //verif diagonal

    for(int i=0;i<3;i++){
            aux =getPos(a,sup_esq[0]+i,sup_esq[1]+i);
            if (aux== '_')
                break;
            else if(aux=='X')
                contX++;
            else if(aux=='O')
                contY++;
        }
        if(contX==3)
            return 1;
        else if (contY==3)
            return 2;
        else{
            contX= 0;
            contY= 0;
        }

        //verif anti diagonal

    for(int i=0, j=3;i<3;i++,j--){
        aux =getPos(a,sup_esq[0]+j-1,sup_esq[1]+i);
        if (aux== '_')
            break;
        else if(aux=='X')
            contX++;
        else if(aux=='O')
            contY++;
    }
    if(contX==3)
        return 1;
    else if (contY==3)
        return 2;
    else{
        contX= 0;
        contY= 0;
    }
    return 0;
    }


int set_vitoria_no_mini_tabuleiro(int vitoria, int mini_tabuleiro, char ** tabuleiro_vitoria){
        char vencedor;
        int contador=0;
        if(contador==9){return 1;}
    if(vitoria ==1)
        vencedor = 'X';
    else if(vitoria ==2)
        vencedor = 'O';
    switch (mini_tabuleiro) {

        case 1:
            setPos(tabuleiro_vitoria, 0,0,vencedor);
            contador++;
            break;
        case 2:
            setPos(tabuleiro_vitoria, 0,1,vencedor);
            contador++;
            break;
        case 3:
            setPos(tabuleiro_vitoria, 0,2,vencedor);
            contador++;
            break;
        case 4:
            setPos(tabuleiro_vitoria, 1,0,vencedor);
            contador++;
            break;
        case 5:
            setPos(tabuleiro_vitoria, 1,1,vencedor);
            contador++;
            break;
        case 6:
            setPos(tabuleiro_vitoria, 1,2,vencedor);
            contador++;
            break;
        case 7:
            setPos(tabuleiro_vitoria, 2,0,vencedor);
            contador++;
            break;
        case 8:
            setPos(tabuleiro_vitoria, 2,1,vencedor);
            contador++;
            break;
        case 9:
            setPos(tabuleiro_vitoria, 2,2,vencedor);
            contador++;
            break;
        default:
            break;
        }
        return 0;
    }

void preenche_mini_tab(int vitoria,char ** tab, int sup_esq[2] ){

    char vencedor;
    if(vitoria ==1)
        vencedor = 'X';
    else if(vitoria ==2)
        vencedor = 'O';

    for(int i= sup_esq[0];i<= sup_esq[0]+2;i++){
        for(int j= sup_esq[1];j<= sup_esq[1]+2;j++){
            setPos(tab, j, i,vencedor );
        }
    }


}


//void GuardaJogo(char ** tabuleiro, )



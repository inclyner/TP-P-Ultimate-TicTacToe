// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Realizado por Francisco Andrade Carvalho - 2019129635

#ifndef MATDIN_H
#define MATDIN_H

#include <stdlib.h>
#include <stdio.h>

// Liberta uma matriz dinâmica de caracteres com nLin linhas
void libertaMat(char** p, int nLin);

// Cria uma matriz dinâmica de caracteres  com nLin linhas e nCol colunas
// Devolve endereço inicial da matriz
char** criaMat(int nLin, int nCol);

//imprime uma tabela, esta funcao foi adaptada para separar com @ cada tabuleiro do jogo, sendo assim apenas funciona para mostrar uma tabela de 9x9
void mostraMat(char **p);

// Coloca o caracter c na posição (x, y) de uma matriz dinâmica de caracteres
void setPos(char **p, int x, int y, char c);

// Obtém o caracter armazenado na posição (x, y) de uma matriz de caracteres
char getPos(char **p, int x, int y);

// recebe canto superior de cada tabuleiro
// devolve 1 se o jogador 1 ganhou e 2 se o jogador 2 ganhou
int verifica_vitoria(char **a,int sup_esq[2]);

// coloca X ou Y no mini tabuleiro de vitorias
int set_vitoria_no_mini_tabuleiro(int vitoria, int mini_tabuleiro, char ** tabuleiro_vitoria);

//quando é detetada uma vitoria esta funcao preenche todos os lugares to tabuleiro em questao com o caracter do vencedor
void preenche_mini_tab(int vitoria,char ** tab, int sup_esq[2] );

#endif
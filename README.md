
# Ultimate Tic-Tac-Toe

## Overview

This project is an advanced version of the classic Tic-Tac-Toe game. The main differences are that the board is 9x9, representing 9 individual 3x3 games, and the next move is determined by the location of the previous move.

## Data Structures

A single data structure is used to store the x and y positions and the character representing the player for each move. This structure is utilized to maintain a linked list of all the moves made in the game. The `prox` variable is of type `pjogada`, which is a pointer to the next allocated memory space.

```c
typedef struct jogo jogada, *pjogada;

struct jogo {
    int posx, posy;  // position values in each node
    char jogador_c;  // player's character
    pjogada prox;    // pointer to the next node
};

pjogada lista_ligada = NULL;
«

## Functions

- **libertaMat**: Frees a dynamically allocated character matrix.
  
  ```c
  void libertaMat(char** p, int nLin);
  ```

- **criaMat**: Creates a dynamically allocated character matrix with `nLin` lines and `nCol` columns. Returns the initial address of the matrix.
  
  ```c
  char** criaMat(int nLin, int nCol);
  ```

- **mostraMat**: Displays a table. This function is adapted to separate each game board with `@`, and it only works for displaying a 9x9 table.
  
  ```c
  void mostraMat(char **pp);
  ```

- **setPos**: Places the character `c` at position (x, y) in a dynamic character matrix.
  
  ```c
  void setPos(char **pp, int x, int y, char c);
  ```

- **getPos**: Retrieves the character stored at position (x, y) in a dynamic character matrix.
  
  ```c
  char getPos(char **pp, int x, int y);
  ```

- **verifica_vitoria**: Receives the upper left corner of each board and returns 1 if player 1 won and 2 if player 2 won.
  
  ```c
  int verifica_vitoria(char **p, int sup_esq[2]);
  ```

- **set_vitoria_no_mini_tabuleiro**: Places X or O in the mini victory board.
  
  ```c
  int set_vitoria_no_mini_tabuleiro(int vitoria, int mini_tabuleiro, char **tabuleiro_vitoria);
  ```

- **preenche_mini_tab**: When a victory is detected, this function fills all positions in the board in question with the character of the winner.
  
  ```c
  void preenche_mini_tab(int vitoria, char **tab, int sup_esq[2]);
  ```

## General Program Functionality

The program features two tables:
1. The main 9x9 board that the players interact with.
2. The victory board that records the victories of each 3x3 mini-board.

When a player wins in a 3x3 mini-board, their character is recorded in the victory board. The function `verifica_vitoria` checks for victories within each mini-board, given the coordinates of its upper left corner.

## Development Environment

The development environment used was CLion.

## Author

Francisco Andrade Carvalho | 2019129635  
Instituto Superior de Engenharia de Coimbra  
Eng. Informática  
a2019129635@isec.pt  
2020-2021


This README provides a structured and comprehensive overview of the Ultimate Tic-Tac-Toe project, its data structures, functions, general functionality, and development environment.

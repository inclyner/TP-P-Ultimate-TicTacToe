// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2021-2022
// Realizado por Francisco Andrade Carvalho - 2019129635
#include <stdio.h>
#include <string.h>
#include "matdin.h"
#include "utils.h"




int main() {
    char **tabuleiro = criaMat(9, 9);
    char **tabuleiro_de_vitorias = criaMat(3, 3);
    int mini_tabuleiro_atual[2] = {0,0}, vitoria,vitoria_total=0, jogador_atual = 1, resposta_int, coord_x, coord_y, primeira_jogada = 0;
    int mini_tabuleiro_atual_1a9, aux_tabuleiro00[2] = {0, 0};// ambos para reduzir a quantidade de codigo repetido
    int *mini_p = &mini_tabuleiro_atual[0];
    char resposta[10];
    int guarda_jogo, jogocontrabot;
    pjogada lista_ligada = NULL; //ponteiro(aponta para o primeiro elemento da lista, começa NULL porque a lista esta vazia)
    int tam_lista_ligada=0,stop=0; //representa quanta jogadas foram feitas no total
    FILE* fich_jogo = fopen("jogo.bin","r");
    FILE* fich_tabela;

    initRandom();



    if(fich_jogo!=NULL){
       do{
        printf("\nFoi detetado um jogo guardado, deseja carrega-lo?(1-sim,2-nao)\n");
        fgets(resposta, sizeof(resposta), stdin);
        resposta_int = strtol(resposta,NULL,10);
    } while (resposta_int<1 || resposta_int>2);
       if(resposta_int==1){
           tam_lista_ligada = abre_ficheiro(tabuleiro,lista_ligada);
       //verifica vitorias em todos os mini tabuleiros

           for(int i=0;i<9;i=i+3){
               for(int j=0;j<9;j=j+3){
                   mini_tabuleiro_atual[0] = i;
                   mini_tabuleiro_atual[1] = j;
                   vitoria = verifica_vitoria(tabuleiro, mini_tabuleiro_atual);
                   mini_tabuleiro_atual_1a9 = altera_tabuleiro_a_jogar(i, j, mini_p);

                   if (vitoria == 1 || vitoria == 2) {
                       printf("jogador %d ganhou no tabuleiro %d!", vitoria, mini_tabuleiro_atual_1a9);
                       set_vitoria_no_mini_tabuleiro(vitoria, mini_tabuleiro_atual_1a9, tabuleiro_de_vitorias);
                       preenche_mini_tab(vitoria, tabuleiro, mini_tabuleiro_atual);
                       vitoria_total = verifica_vitoria(tabuleiro_de_vitorias, aux_tabuleiro00);
                   }
               }
           }
           primeira_jogada=1;//passa a frente a selecao do mini tabuleiro atual
       }

    }

    // escolha do modo de jogo inicial input verificado
    if(primeira_jogada!=1) {
        do {
            printf("Selecione o modo de jogo\n");
            printf("1-> Jogador contra jogador\n2-> Jogador contra computador\n");
            fgets(resposta, sizeof(resposta), stdin);
            jogocontrabot = strtol(resposta, NULL, 10);
        } while (jogocontrabot != 1 && jogocontrabot != 2);
    }


    //jogo jogador contra jogador
    if(jogocontrabot==1) {
        do {
            while (primeira_jogada != 1) {
                resposta[strcspn(resposta, "\n")] = 0;
                printf("\nEscolha um tabuleiro para jogar:\n1  2  3\n       \n4  5  6\n       \n7  8  9\n");
                fgets(resposta, sizeof(resposta), stdin);
                resposta_int = strtol(resposta, NULL, 10);
                switch (resposta_int) {
                    case 1:
                        mini_tabuleiro_atual[0] = 0;
                        mini_tabuleiro_atual[1] = 0;
                        primeira_jogada = 1;
                        break;
                    case 2:
                        mini_tabuleiro_atual[0] = 3;
                        mini_tabuleiro_atual[1] = 0;
                        primeira_jogada = 1;
                        break;
                    case 3:
                        mini_tabuleiro_atual[0] = 6;
                        mini_tabuleiro_atual[1] = 0;
                        primeira_jogada = 1;
                        break;
                    case 4:
                        mini_tabuleiro_atual[0] = 0;
                        mini_tabuleiro_atual[1] = 3;
                        primeira_jogada = 1;
                        break;
                    case 5:
                        mini_tabuleiro_atual[0] = 3;
                        mini_tabuleiro_atual[1] = 3;
                        primeira_jogada = 1;
                        break;
                    case 6:
                        mini_tabuleiro_atual[0] = 3;
                        mini_tabuleiro_atual[1] = 6;
                        primeira_jogada = 1;
                        break;
                    case 7:
                        mini_tabuleiro_atual[0] = 6;
                        mini_tabuleiro_atual[1] = 0;
                        primeira_jogada = 1;
                        break;
                    case 8:
                        mini_tabuleiro_atual[0] = 6;
                        mini_tabuleiro_atual[1] = 3;
                        primeira_jogada = 1;
                        break;
                    case 9:
                        mini_tabuleiro_atual[0] = 6;
                        mini_tabuleiro_atual[1] = 6;
                        primeira_jogada = 1;
                        break;
                    default:
                        printf("\nintroduza um numero valido.");
                        break;
                }

            }// fim loop da primeira_jogada (selecao do primeiro tabuleiro de jogo)

            printf("\nE a vez do jogador %d!\n", jogador_atual);
            mostraMat(tabuleiro);

            //loop que valida a posicao jogada no tabuleiro --> implementado e testado
            do {
                // loop que valida o input da coordenada x --> implementado e testado
                do {
                    resposta[strcspn(resposta, "\n")] = 0; //fflush(stdin) (mas suportado)
                    printf("\nintroduza a coordenada x:");
                    fgets(resposta, sizeof(resposta), stdin);
                    coord_x = strtol(resposta, NULL, 10) - 1;
                    if (coord_x < mini_tabuleiro_atual[0] || coord_x > mini_tabuleiro_atual[0] + 2)
                        printf("\nintroduza uma coordenada valida (%d-%d)", mini_tabuleiro_atual[0] + 1,
                               mini_tabuleiro_atual[0] + 2 + 1); //adicionado 1 para simplificacao para o utilizado
                } while (coord_x < mini_tabuleiro_atual[0] || coord_x > mini_tabuleiro_atual[0] + 2);

                // loop que valida o input da coordenada y --> implementado e testado
                do {
                    resposta[strcspn(resposta, "\n")] = 0; //fflush(stdin) (mas suportado)
                    printf("\nintroduza a coordenada y:");
                    fgets(resposta, sizeof(resposta), stdin);
                    coord_y = strtol(resposta, NULL, 10) - 1;
                    if (coord_y < mini_tabuleiro_atual[1] || coord_y > mini_tabuleiro_atual[1] + 2)
                        printf("\nintroduza uma coordenada valida (%d-%d)", mini_tabuleiro_atual[1] + 1,
                               mini_tabuleiro_atual[1] + 2 + 1);//adicionado 1 para simplificacao para o utilizador
                } while (coord_y < mini_tabuleiro_atual[1] || coord_y > mini_tabuleiro_atual[1] + 2);

                if (getPos(tabuleiro, coord_x, coord_y) == 'X' ||
                    getPos(tabuleiro, coord_x, coord_y) == 'O') {
                    printf("\nEspaco ocupado por favor tente novamente");
                }
            } while (getPos(tabuleiro, coord_x, coord_y) == 'X' ||
                     getPos(tabuleiro, coord_x, coord_y) == 'O'); //fim loop que valida a posicao jogada no tabuleiro

            if (jogador_atual == 1) // so chega aqui se o jogador introduzir coordenadas validas
            { setPos(tabuleiro, coord_x, coord_y, 'X'); }
            else setPos(tabuleiro, coord_x, coord_y, 'O');


            ////////////// insere jogada no final da lista ligada! ///////////////////
            tam_lista_ligada++;// representa o numero de jogadas total
            lista_ligada = insere(coord_x, coord_y, jogador_atual, lista_ligada);


            mini_tabuleiro_atual_1a9 = altera_tabuleiro_a_jogar(coord_x, coord_y, mini_p);

            //condicao para alternar jogador 1 e 2
            if (jogador_atual == 1)
                jogador_atual = 2;
            else
                jogador_atual = 1;


            vitoria = verifica_vitoria(tabuleiro, mini_tabuleiro_atual);
            if (vitoria == 1 || vitoria == 2) {
                printf("jogador %d ganhou no tabuleiro %d!", vitoria, mini_tabuleiro_atual_1a9);
                set_vitoria_no_mini_tabuleiro(vitoria, mini_tabuleiro_atual_1a9, tabuleiro_de_vitorias);
                preenche_mini_tab(vitoria, tabuleiro, mini_tabuleiro_atual);
                vitoria_total = verifica_vitoria(tabuleiro_de_vitorias, aux_tabuleiro00);
            }




            //////guardar jogadas anteriores ou continuar////////
            do {
                printf("\nSelecione: \nGuardar o jogo ==>1\nVer jogadas anteriores ==> 2\nContinuar a jogar ==> 3\n");
                resposta[strcspn(resposta, "\n")] = 0;
                fgets(resposta, sizeof(resposta), stdin);
                guarda_jogo = strtol(resposta, NULL, 10);
                if (guarda_jogo == 1) {
                    //chama funcao do ficheiro

                    do {
                        printf("deseja continuar o jogo?(escreva 1 se sim, 2 se nao)");
                        resposta[strcspn(resposta, "\n")] = 0;
                        fgets(resposta, sizeof(resposta), stdin);
                        guarda_jogo = strtol(resposta, NULL, 10);

                        guarda_jogo_bin(lista_ligada, tam_lista_ligada);

                    } while ((guarda_jogo != 2 && guarda_jogo != 1));

                } else if (guarda_jogo == 2) {
                    do {
                        printf("\nQuantas jogadas deseja ver? (1-10)");
                        resposta[strcspn(resposta, "\n")] = 0;
                        fgets(resposta, sizeof(resposta), stdin);
                        guarda_jogo = strtol(resposta, NULL, 10);
                        if (guarda_jogo < 0 || guarda_jogo > 10) {
                            printf("\nPor favor introduza um numero de 0 a 10\n");
                        }
                        if (guarda_jogo > tam_lista_ligada)
                            printf("\nAinda so houveram %d jogadas:\n", tam_lista_ligada);

                    } while (guarda_jogo < 1 || guarda_jogo > 10);
                    imprime_lista_ligada(lista_ligada, guarda_jogo, tam_lista_ligada);
                    guarda_jogo = 1;
                } else if (guarda_jogo == 3) { guarda_jogo = 1; }
                else { printf("\nPor favor introduza um valor valido:"); }

            } while (guarda_jogo != 2 && guarda_jogo != 1);

            //condicao do empate max de jogadas e 81, quando o tabueleiro esta cheio o jogo acaba num empate
            if (tam_lista_ligada == 81)vitoria_total = 3;
        } while ((vitoria_total != 1 && vitoria_total != 2 && vitoria_total != 3) &&
                 guarda_jogo == 1); //vitoria_total=1 jogador 1 ganhou, 2 ganhou o jogador 2, 3 ha empate

        if (vitoria_total == 1) { printf("\nParabens!\nJogador 1 ganhou!\n Boa sorte para a proxima jogador 2."); }
        else if (vitoria_total == 2) { printf("\nParabens!\nJogador 2 ganhou!\n Boa sorte para a proxima jogador 1."); }
        else {
            printf("\nHouve um empate!\nAmbos os jogadores perderam!");
        }
    }
    ////////////////////////////jogo contra bot///////////////////
    else{
        do {
            while (primeira_jogada != 1) {
                resposta[strcspn(resposta, "\n")] = 0;
                printf("\nEscolha um tabuleiro para jogar:\n1  2  3\n       \n4  5  6\n       \n7  8  9\n");
                fgets(resposta, sizeof(resposta), stdin);
                resposta_int = strtol(resposta, NULL, 10);
                switch (resposta_int) {
                    case 1:
                        mini_tabuleiro_atual[0] = 0;
                        mini_tabuleiro_atual[1] = 0;
                        primeira_jogada = 1;
                        break;
                    case 2:
                        mini_tabuleiro_atual[0] = 3;
                        mini_tabuleiro_atual[1] = 0;
                        primeira_jogada = 1;
                        break;
                    case 3:
                        mini_tabuleiro_atual[0] = 6;
                        mini_tabuleiro_atual[1] = 0;
                        primeira_jogada = 1;
                        break;
                    case 4:
                        mini_tabuleiro_atual[0] = 0;
                        mini_tabuleiro_atual[1] = 3;
                        primeira_jogada = 1;
                        break;
                    case 5:
                        mini_tabuleiro_atual[0] = 3;
                        mini_tabuleiro_atual[1] = 3;
                        primeira_jogada = 1;
                        break;
                    case 6:
                        mini_tabuleiro_atual[0] = 3;
                        mini_tabuleiro_atual[1] = 6;
                        primeira_jogada = 1;
                        break;
                    case 7:
                        mini_tabuleiro_atual[0] = 6;
                        mini_tabuleiro_atual[1] = 0;
                        primeira_jogada = 1;
                        break;
                    case 8:
                        mini_tabuleiro_atual[0] = 6;
                        mini_tabuleiro_atual[1] = 3;
                        primeira_jogada = 1;
                        break;
                    case 9:
                        mini_tabuleiro_atual[0] = 6;
                        mini_tabuleiro_atual[1] = 6;
                        primeira_jogada = 1;
                        break;
                    default:
                        printf("\nintroduza um numero valido.");
                        break;
                }

            }// fim loop da primeira_jogada (selecao do primeiro tabuleiro de jogo)
            if(jogador_atual==1){printf("\nE a sua vez!\n");}
            mostraMat(tabuleiro);
            if(jogador_atual==1) {
                //loop que valida a posicao jogada no tabuleiro --> implementado e testado
                do {
                    // loop que valida o input da coordenada x --> implementado e testado
                    do {
                        resposta[strcspn(resposta, "\n")] = 0; //fflush(stdin) (mas suportado)
                        printf("\nintroduza a coordenada x:");
                        fgets(resposta, sizeof(resposta), stdin);
                        coord_x = strtol(resposta, NULL, 10) - 1;
                        if (coord_x < mini_tabuleiro_atual[0] || coord_x > mini_tabuleiro_atual[0] + 2)
                            printf("\nintroduza uma coordenada valida (%d-%d)", mini_tabuleiro_atual[0] + 1,
                                   mini_tabuleiro_atual[0] + 2 + 1); //adicionado 1 para simplificacao para o utilizado
                    } while (coord_x < mini_tabuleiro_atual[0] || coord_x > mini_tabuleiro_atual[0] + 2);

                    // loop que valida o input da coordenada y --> implementado e testado
                    do {
                        resposta[strcspn(resposta, "\n")] = 0; //fflush(stdin) (mas suportado)
                        printf("\nintroduza a coordenada y:");
                        fgets(resposta, sizeof(resposta), stdin);
                        coord_y = strtol(resposta, NULL, 10) - 1;
                        if (coord_y < mini_tabuleiro_atual[1] || coord_y > mini_tabuleiro_atual[1] + 2)
                            printf("\nintroduza uma coordenada valida (%d-%d)", mini_tabuleiro_atual[1] + 1,
                                   mini_tabuleiro_atual[1] + 2 + 1);//adicionado 1 para simplificacao para o utilizador
                    } while (coord_y < mini_tabuleiro_atual[1] || coord_y > mini_tabuleiro_atual[1] + 2);

                    if (getPos(tabuleiro, coord_x, coord_y) == 'X' ||
                        getPos(tabuleiro, coord_x, coord_y) == 'O') {
                        printf("\nEspaco ocupado por favor tente novamente");
                    }
                } while (getPos(tabuleiro, coord_x, coord_y) == 'X' ||
                         getPos(tabuleiro, coord_x, coord_y) ==
                         'O'); //fim loop que valida a posicao jogada no tabuleiro
            } //fim do if se o jogador for 1

            if (jogador_atual == 1) // so chega aqui se o jogador introduzir coordenadas validas
            { setPos(tabuleiro, coord_x, coord_y, 'X');
                mini_tabuleiro_atual_1a9 = altera_tabuleiro_a_jogar(coord_x, coord_y, mini_p);}
            else {
                do{
                coord_x= intUniformRnd(mini_tabuleiro_atual[0],mini_tabuleiro_atual[0]+2);
                coord_y= intUniformRnd(mini_tabuleiro_atual[0],mini_tabuleiro_atual[0]+2);
                } while (getPos(tabuleiro, coord_x, coord_y) == 'X' ||
                         getPos(tabuleiro, coord_x, coord_y) == 'O');
                setPos(tabuleiro, coord_x, coord_y, 'O');
                mini_tabuleiro_atual_1a9 = altera_tabuleiro_a_jogar(coord_x, coord_y, mini_p);
            }


            ////////////// insere jogada no final da lista ligada! ///////////////////
            tam_lista_ligada++;// representa o numero de jogadas total
            lista_ligada = insere(coord_x + 1, coord_y + 1, jogador_atual, lista_ligada);


            //condicao para alternar jogador 1 e 2
            if (jogador_atual == 1)
                jogador_atual = 2;
            else
                jogador_atual = 1;


            vitoria = verifica_vitoria(tabuleiro, mini_tabuleiro_atual);
            if (vitoria == 1 || vitoria == 2) {
                printf("jogador %d ganhou no tabuleiro %d!", vitoria, mini_tabuleiro_atual_1a9);
                set_vitoria_no_mini_tabuleiro(vitoria, mini_tabuleiro_atual_1a9, tabuleiro_de_vitorias);
                preenche_mini_tab(vitoria, tabuleiro, mini_tabuleiro_atual);
                vitoria_total = verifica_vitoria(tabuleiro_de_vitorias, aux_tabuleiro00);
            }




            //////guardar jogadas anteriores ou continuar////////
            if(jogador_atual==1) {
                do {
                    printf("\nSelecione: \nGuardar o jogo ==>1\nVer jogadas anteriores ==> 2\nContinuar a jogar ==> 3\n");
                    resposta[strcspn(resposta, "\n")] = 0;
                    fgets(resposta, sizeof(resposta), stdin);
                    guarda_jogo = strtol(resposta, NULL, 10);
                    if (guarda_jogo == 1) {
                        //chama funcao do ficheiro

                        do {
                            printf("deseja continuar o jogo?(escreva 1 se sim, 2 se nao)");
                            resposta[strcspn(resposta, "\n")] = 0;
                            fgets(resposta, sizeof(resposta), stdin);
                            guarda_jogo = strtol(resposta, NULL, 10);

                            guarda_jogo_bin(lista_ligada, tam_lista_ligada);

                        } while ((guarda_jogo != 2 && guarda_jogo != 1));

                    } else if (guarda_jogo == 2) {
                        do {
                            printf("\nQuantas jogadas deseja ver? (1-10)");
                            resposta[strcspn(resposta, "\n")] = 0;
                            fgets(resposta, sizeof(resposta), stdin);
                            guarda_jogo = strtol(resposta, NULL, 10);
                            if (guarda_jogo < 0 || guarda_jogo > 10) {
                                printf("\nPor favor introduza um numero de 0 a 10\n");
                            }
                            if (guarda_jogo > tam_lista_ligada)
                                printf("\nAinda so houveram %d jogadas:\n", tam_lista_ligada);

                        } while (guarda_jogo < 1 || guarda_jogo > 10);
                        imprime_lista_ligada(lista_ligada, guarda_jogo, tam_lista_ligada);
                        guarda_jogo = 1;
                    } else if (guarda_jogo == 3) { guarda_jogo = 1; }
                    else { printf("\nPor favor introduza um valor valido:"); }

                } while (guarda_jogo != 2 && guarda_jogo != 1);
            }
            else{guarda_jogo=1;}

            //condicao do empate max de jogadas e 81, quando o tabueleiro esta cheio o jogo acaba num empate ou quando todos os espacos estiverem preenchidos //ultima parte nao testada
            if (tam_lista_ligada == 81)vitoria_total = 3;
            for(int i=0;i<=8 && stop==0;i++){
                for(int j=0;j<=8 && stop==0;j++){
                    if(getPos(tabuleiro,i,j)=='_') {
                        stop=1;
                    }
                    else if(i==8 &&j ==8){vitoria_total=3;}
                }
            }
            stop=0;
        } while ((vitoria_total != 1 && vitoria_total != 2 && vitoria_total != 3) &&
                 guarda_jogo == 1); //vitoria_total=1 jogador 1 ganhou, 2 ganhou o jogador 2, 3 ha empate

        mostraMat(tabuleiro);
        if (vitoria_total == 1) { printf("\nParabens!\nJogador 1 ganhou!\n Boa sorte para a proxima jogador 2."); }
        else if (vitoria_total == 2) { printf("\nParabens!\nJogador 2 ganhou!\n Boa sorte para a proxima jogador 1."); }
        else if(vitoria_total==3) {
            printf("\nHouve um empate!\nAmbos os jogadores perderam!");
        }
    }
    //////////////////// fim jogo contra bot//////////////////////

    printf("\nEscolha o nome do ficheiro onde quer guardar o tabuleiro:");
    resposta[strcspn(resposta, "\n")] = 0; //fflush(stdin) (mas suportado)
    fgets(resposta, sizeof(resposta), stdin);

    exportar_tab_txt(resposta,lista_ligada);

printf("\n\nObrigado por jogar!");
getchar();

    //liberta memoria
    libertaMat(tabuleiro, 9);
    libertaMat(tabuleiro_de_vitorias, 3);
    liberta_lista_ligada(lista_ligada);
    return 0;
}

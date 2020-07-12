#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tabuleiro.h"
#include "interface.h"

int main(void) {
  //mensagem de inicialização do programa
  printf("\n");
  printf("\033[4m");
  printf("Q");
  printf("\033[4;31m");
  printf("W");
  printf("\033[4;32m");
  printf("I");
  printf("\033[4;33m");
  printf("R");
  printf("\033[4;34m");
  printf("K");
  printf("\033[4;35m");
  printf("L");
  printf("\033[4;36m");
  printf("E");
  printf("\033[0m");
  printf("\n\n");
  //Numero de jogadores
  int num_jog;
  char e[10];
  do{
    printf("Numero de jogadores: ");
    fgets(e, 9, stdin);
    num_jog = atoi(e);
  }while(num_jog < 1 || num_jog > 18);

  //Lista de jogadores alocada dinamicamente
  char **nomes =(char **) malloc(sizeof(char *)*num_jog);
  if(!nomes){
    printf("Problema de alocacao de memoria!");
    exit(1);
  }

  int i = 0;
  for( i = 0; i < num_jog; i++){
    nomes[i] = (char *) malloc(sizeof(char)*20);
    if(!nomes[i]){
    printf("Problema de alocacao de memoria!");
    exit(1);
    }
  }

  //Limpar o buffer
  setbuf(stdin, NULL);

   //Receber os nomes de todos os jogadores
  for( i=0;i<num_jog;i++){
    printf("Nome do jogador %d: ", i+1);
    fgets(nomes[i], 20, stdin);
    for(int k=0;k<20;k++){
      if(nomes[i][k]=='\n'){
        nomes[i][k]='\0';
        break;
      }
    }
  }

  //Habilitar ou nao o modo de trapaca
  int cheatmode;
  do{
  printf("Cheat mode (Sim=1/Nao=0): ");
  fgets(e, 9, stdin);
  cheatmode = atoi(e);
  }while(cheatmode != 0 && cheatmode != 1);
  //Numero inicial de linahs e colunas da matriz
  int n_linhas = 1;
  int n_colunas = 1;
  int *m = &n_linhas;
  int *n = &n_colunas;

  //Alocar o tabuleiro na heap
  Peca **matriz = aloca_tabuleiro(n_linhas, n_colunas);

  //Preencher o tabuleiro com espacos
  fill_tabuleiros(matriz, n_linhas, n_colunas, ' ');

  //Imprimir o tabuleiro em sua configuracao inicial
  print_tabuleiro(matriz, n_linhas, n_colunas);

  //Loop do jogo.
  menu(matriz, m, n, num_jog, nomes, cheatmode);
  
  free(nomes);
  return 0;
}

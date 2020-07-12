#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tabuleiro.h"
#include "time.h"

//Cria todas as combinacoes possiveis de pecas.
Peca* todas_pecas(){
  Peca *matriz = (Peca *) malloc(sizeof(Peca)*108);
  if(matriz==NULL){
    printf("Problema de alocacao de memoria!");
    exit(1);
  }

  int letras[6] = {'A', 'B', 'C', 'D', 'E', 'F'};

  int cores[6] = {'1', '2', '3', '4', '5', '6'};

  int i = 0;
  int j = 0;
  int k = 0;
  int a = 0;

  for(k = 0; k < 3; k++){
    for(i = 0; i < 6; i++){
      for(j = 0; j < 6; j++){
        matriz[a].forma = letras[i];
        matriz[a].cor = cores[j];
        a++;
      }
    }
  }

  return matriz;
}

//Volta as pecas trocadas a pilha de pecas disponiveis.
void retornar_peca(int *usadas, Peca peca){
  Peca *matriz = todas_pecas();
  int i = 0;
  for(i = 0; i < 108; i++){
    if(matriz[i].cor == peca.cor && matriz[i].forma == peca.forma && usadas[i] == 1){
      usadas[i] = 0;
      break;
    }
  }
}

//Escolhe randomicamente uma peca. Retorna a posicao dessa peca no vetor 'usadas', que indexa todas as pecas disponiveis.
int rand_peca(int *usadas){
  srand(time(NULL));
  int i = 0;
  int a = 0;

  int flag;
  do{
    flag = 0;
    a = rand() % 108;
    if(usadas[a]){
      flag = 1;
    }
  }while(flag);
  
  usadas[a]=1;
  return a;
}

//Imprime as pecas de cada jogador.
void print_pecas(Peca *pecas){
  int i;
  for(i = 0; i < 6; i++){
    if(pecas[i].cor != ' ' && pecas[i].forma != ' '){
      cores(pecas[i].cor, pecas[i].forma);
      printf(" ");
    }
  }
  printf("\n");
}

//Ver as pecas que faltam para um jogador, e entrega novas pecas ate o jogador ter 6.
void puxar_pecas(Peca *pecas, int *usadas){

  Peca* matriz = todas_pecas();
  
  int i;

  for(i = 0; i < 6; i++){
    if(pecas[i].forma == ' '){
      pecas[i] = matriz[rand_peca(usadas)];
    }
  }
  
}


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tabuleiro.h"

#define ANSI_COLOR_RED     "\033[0;41m"
#define ANSI_COLOR_GREEN   "\033[0;42m"
#define ANSI_COLOR_ORANGE  "\033[0;43m"
#define ANSI_COLOR_BLUE    "\033[0;44m"
#define ANSI_COLOR_ROXO    "\033[0;45m"
#define ANSI_COLOR_CYAN    "\033[0;46m"
#define ANSI_COLOR_RESET   "\033[0m"

//Aloca o tabuleiro de forma dinamica usando malloc().
Peca** aloca_tabuleiro(int m, int n){

  Peca **matriz = (Peca **) malloc(sizeof(Peca *)*m);
  if(matriz==NULL){
    printf("Problema de alocacao de memoria!");
    exit(1);
  }

  int i;
  int j;

  for(i = 0; i < m; i++){
    matriz[i] = (Peca *) malloc(sizeof(Peca)*n);
    if(matriz[i]==NULL){
      printf("Problema de alocacao de memoria!");
      exit(1);
    }
  }

  for(i = 0; i < m; i++){
    for(j = 0; j < n; j++){
      matriz[i][j].forma = ' ';
      matriz[i][j].cor = ' ';
    }
  }
  
  return matriz;
}

//Imprime uma peca com as cores, usando o numero como identificador de cor.
void cores(char c, char d){

  switch(c){
    case '1':
      printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, d);
      printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, c);
      break;
    case '2':
      printf(ANSI_COLOR_RED "%c" ANSI_COLOR_RESET, d);
      printf(ANSI_COLOR_RED "%c" ANSI_COLOR_RESET, c);
      break;
    case '3':
      printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, d);
      printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, c);
      break;
    case '4':
      printf(ANSI_COLOR_ORANGE "%c" ANSI_COLOR_RESET, d);
      printf(ANSI_COLOR_ORANGE "%c" ANSI_COLOR_RESET, c);
      break;
    case '5':
      printf(ANSI_COLOR_ROXO "%c" ANSI_COLOR_RESET, d);
      printf(ANSI_COLOR_ROXO "%c" ANSI_COLOR_RESET, c);
      break;
    case '6':
      printf(ANSI_COLOR_CYAN "%c" ANSI_COLOR_RESET, d);
      printf(ANSI_COLOR_CYAN "%c" ANSI_COLOR_RESET, c);
      break;
    default:
      printf(" ");
      printf(" ");
      break;
  }
}

//Imprime o tabuleiro
void print_tabuleiro(Peca **matriz, int m, int n){

	printf("\n");
	
	int i, j, k;
	
	printf("   ");

  //Numeros das colunas
	for(k = 0; k < n; k++){
    if(k+1 < 10){
      printf("  %d  ", k);	
    }else{
      printf("  %d  ", k);
    }
	}
	
	printf("\n");
	
	for(i = 0; i < m; i++){

		//Numeros das linhas
		if(i+1 < 10){
		  printf("%d - ", i);
		}else{
		  printf("%d- ", i);
		}

		//Imprime a peca com cores.
		for(j = 0; j < n; j++){
      cores(matriz[i][j].cor, matriz[i][j].forma);
			printf(" | ");
		}
		
		printf("\n");
		
		if(j == 1){
			printf("    ");
		}

		for(k = 0; k <= n; k++){
      if(n!=1){
        printf("-----");
      }else{
        printf("---");
        break;
      }
		  
		}

		printf("\n");
	}
}

//Preenche o tabuleiro com um caracter arbitrario c (em geral espaco).
void fill_tabuleiros(Peca **matriz, int m, int n, char c){

  int i, j;

  for(i = 0; i < m; i++){
    for(j = 0; j < n; j++){
      matriz[i][j].forma = c;
      matriz[i][j].cor = c;
    }
  }

}

//Apos a jogada, redimensiona o tabuleiro, aumentando o numero de linhas e colunas e fazendo shift das pecas ja jogadas
Peca **update_tabuleiro(Peca **matriz, int *n_linhas, int *n_colunas, int **track, int pos){

  int x = track[pos][0];
  int y = track[pos][1];
  int m = *n_linhas; 
  int n = *n_colunas;
  int i, j;

  int expande_cima = 0;
  int expande_esquerda = 0;
  int l_expand = 0;
  int c_expand = 0;
  
  if(x == 0){
    expande_cima = 1;
    l_expand = 1;
    int k;
    for(k = 0; k <= pos; k++){
      (track[k][0])++;
    }
  }

  if(x == m-1){
    l_expand = 1;
  }

  if(y == 0){
    expande_esquerda = 1;
    c_expand = 1;
    int k;
    for(k = 0; k <= pos; k++){
      (track[k][1])++;
    }
  }

  if(y == n-1){
    c_expand = 1;
  }

  if(m == 1 && n == 1){
    l_expand++;
    c_expand++; 
  }

  //Realoca linhas
  if(l_expand){
    matriz = (Peca **) realloc(matriz, sizeof(Peca*)*(m+l_expand));
    if(matriz==NULL){
      printf("Problema de alocacao de memoria!");
      exit(1);
    }
    for(i = 0; i < l_expand; i++){
      matriz[m+i] = (Peca*) malloc(sizeof(Peca)*n);
      if(matriz[m+i]==NULL){
        printf("Problema de alocacao de memoria!");
        exit(1);
      }
    }
    for(i=0;i<l_expand;i++){
      for(j=0;j<n;j++){
        matriz[m+i][j].forma = ' ';
        matriz[m+i][j].cor = ' ';
      }
    }
  }
  m += l_expand;

  //Realoca colunas
  if(c_expand){
    for(i = 0; i < m; i++){
     matriz[i] = (Peca *) realloc(matriz[i], sizeof(Peca)*(n+c_expand));
     if(matriz[i]==NULL){
       printf("Problema de alocacao de memoria!");
        exit(1);
     }
     for(j = 0; j < c_expand; j++){
        matriz[i][n+j].forma = ' ';
        matriz[i][n+j].cor = ' ';
     }
    }
  }
  n += c_expand;


  if(expande_cima){
    int i, j;
    for(i = m-1; i > 0; i--){
      for(j = 0; j < n; j++){
        matriz[i][j] = matriz[i-1][j];
      }
    }
    
    for(i = 0; i < n; i++){
      matriz[0][i].forma = ' ';
      matriz[0][i].cor = ' ';
    } 
  }
  
  if(expande_esquerda){
    for(i = 0; i < m; i++){
      for(j = n-1; j > 0; j--){
        matriz[i][j] = matriz[i][j-1];
      }
    }

    for(i = 0; i < m; i++){
      matriz[i][0].forma = ' ';
      matriz[i][0].cor = ' ';
    }
    
  }

  *n_linhas = m;
  *n_colunas = n;

  return matriz;
}
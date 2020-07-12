#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "tabuleiro.h"
#include "dinamica.h"
#include "pecas.h"

//Pega uma string e retira todas as palavras, retornando uma matriz de strings.
char** get_palavras(char *string, int *num){
  //Quantidade de palavras;
  int count_palavra = 0;
  int a = 0;
  int i = 0;

  //Aloca dinamicamente uma matriz de chars.
  char **palavra = (char **) malloc(sizeof(char*)*11);
  if(!palavra){
    printf("Problema de alocacao de memoria!");
    exit(1);
  }
  for(i = 0; i < 10; i++){
    palavra[i] = (char *) malloc(sizeof(char)*21);
    if(!palavra[i]){
      printf("Problema de alocacao de memoria!");
      exit(1);
    }
  }

  //Caso comece com espacos, avanca-se ate a primeira palavra
  while(string[a] == ' '){
    a++;
  }

  //Enquanto a string nao acabar, retiram-se as palavras
  while(string[a] != '\0'){
    i = 0;
    /*Se o char da posicao a nao for um espaco, coloca-se o caracter em uma string da matriz palavra*/
    while(string[a] != ' ' && string[a] != '\0'){
      palavra[count_palavra][i] = string[a];
      i++;
      a++;
    }
    /*
    Se o char da posicao a for um espaco, avanca-se
    */
    palavra[count_palavra][i] = '\0';
    count_palavra++;
    while(string[a] == ' ' && string[a] != '\0'){
      a++;
    }
  }
  *num = count_palavra;
  return palavra;

}

//Imprimir a tela de jogada invalida.
void jogada_invalida(){
  printf("\n*****************\n");
  printf("Invalid move!");
  printf("\n*****************\n\n");
}

//Efetua uma jogada
Peca** jogada(Peca **matriz, int *m, int *n, Peca n_peca, int *c_x, int *c_y, int *pos, int *linha, int **track, int *flag_concluido){

  //Checa se a posicao escolhida existe no tabuleiro
  if(*c_x >= *m || *c_x < 0 || *c_y >= *n || *c_y < 0){
    jogada_invalida();
    return matriz;
  }

  /*Se for a segunda jogada daquela rodada,
  deve-se verificar se o jogador esta jogando em uma linha ou em uma coluna.
  */
  if(*pos == 1){
    if(ver(matriz, *c_x, *c_y, track, pos, 1)){
      *linha = 1;
    }else if(ver(matriz, *c_x, *c_y, track, pos, 0)){
      *linha = 0;
    }else{
      jogada_invalida();
      return matriz;
    }
  }

  //Se o jogador ja tiver colocado duas pecas na rodada, deve-se verificar se ele esta jogando na mesma linha e coluna da jogada anterior.
  if(*pos > 1){
    if(!ver(matriz, *c_x, *c_y, track, pos, *linha)){
      jogada_invalida();
      return matriz;
    }
  }

  //Checar se a casa esta vazia.
  if(matriz[*c_x][*c_y].forma != ' '){
    jogada_invalida();

  }else{
    matriz[*c_x][*c_y].forma = n_peca.forma;
    matriz[*c_x][*c_y].cor = n_peca.cor;
    /*Checa se as cores e formas das pecas ao redor batem com a peca a ser jogada
    */
    if(check_move(matriz, *c_x, *c_y, *m, *n)){
      track[*pos][0] = *c_x;
      track[*pos][1] = *c_y;
      matriz = update_tabuleiro(matriz, m, n, track, *pos);
      print_tabuleiro(matriz, *m, *n);
      (*pos)++;
      *flag_concluido = 1;
      return matriz;
    }else{
      //Desfazer a jogada, caso seja invalida.
      matriz[*c_x][*c_y].forma = ' ';
      matriz[*c_x][*c_y].cor = ' ';
      jogada_invalida();
    }
  }
  return matriz;
}

//Menu principal do jogo.
void menu(Peca **matriz, int *m, int *n, int num_jog, char **nomes, int cheatmode){
  int pos = 0;
  int x_old = 0;
  int y_old = 0;
  int turno = 0;
  int c_x = 0;
  int c_y = 0;
  int linha = 0;
  int i = 0;
  int j = 0;

  //Vetor que identifica pecas ja usadas.
  int *usadas = (int *) malloc(sizeof(int)*108);
  if(usadas==NULL){
    printf("Problema de alocacao de memoria!");
    exit(1);
  }

  //De inicio, todas as pecas estao disponiveis, entao todas as posicoes recebem 0.
  for(i = 0; i < 108; i++){
    usadas[i] = 0;
  }
  
  //Matriz de pecas que armazena as pecas de cada jogador.
  Peca **pecas = (Peca**) malloc(sizeof(Peca*)*num_jog);
  if(pecas==NULL){
    printf("Problema de alocacao de memoria!");
    exit(1);
  }
  for(i = 0; i < num_jog; i++){
    pecas[i] = (Peca *) malloc(sizeof(Peca)*6);
    if(pecas[i]==NULL){
      printf("Problema de alocacao de memoria!");
      exit(1);
    }
  }
  
  //Zera as pecas de cada jogador.
  for(i = 0; i < num_jog; i++){
    int j;
    for(j = 0; j < 6; j++){
      pecas[i][j].cor = ' ';
      pecas[i][j].forma = ' ';
    }
  }

  //Matriz do tabuleiro.
  Peca **matriz_ = matriz;

  //Vetor que armazena a pontuacao dos jogadores.
  int *pontos = (int *) malloc(num_jog*sizeof(int));
  if(pontos==NULL){
    printf("Problema de alocacao de memoria!");
    exit(1);
  }
  for(int k=0;k<num_jog;k++){
    pontos[k]=0;
  }

  //Matriz que armazena as jogadas dentro de uma rodada.
  int **track = (int **) malloc(sizeof(int *)*6);
  if(track==NULL){
    printf("Problema de alocacao de memoria!");
    exit(1);
  }
  for(i = 0; i < 6; i++){
    track[i] = (int *) malloc(sizeof(int)*2);
    if(track[i]==NULL){
      printf("Problema de alocacao de memoria!");
      exit(1);
    }
    for(j = 0; j < 2; j++){
      track[i][j] = 0;
    }
  }

  //Entrega as pecas a todos os jogadores.
  for(i=0;i<num_jog;i++){
    puxar_pecas(pecas[i], usadas);
  }
  
  while(1){
    //Verificar se o jogo ja acabou.
    fim_de_jogo(usadas, nomes, num_jog, pontos);
    int flag_passar = 0;

    //Menu com as opcoes de cada jogador.
    for(int k=0;k<num_jog;k++){
      printf("Jogador %s (Score: %d): ",nomes[k], pontos[k]);
      print_pecas(pecas[k]);
    }
    printf("===========\n");
    printf("Jogada de %s\n", nomes[turno]);
    printf("Pecas disponiveis: ");
    print_pecas(pecas[turno]);

    //A opcao trocar so esta disponivel na primeira jogada do jogador em uma dada rodada.
    if(!pos){
      printf("opcoes: trocar p1 [p2 p3...] | jogar p1 x y | passar\n");
    }else{
      printf("opcoes: jogar p1 x y | passar\n");
    }

    //Recebe a entrada do jogador.      
    char entrada[40];
    fgets(entrada, 40, stdin);

    //Retira todas as palavras individuais da string.
    int count_palavras = 0;
    char **palavra = get_palavras(entrada, &count_palavras);

    //Primeiro caracter valido (!= ' '), que indica se o jogador ira jogar, passar ou trocar.
    char e = palavra[0][0];

    //Cria todas as opcoes de peca (3*(todas as combinacoes de cores e formas)).
    Peca* todas_as_pecas = todas_pecas();

    //Saber se o jogador vai jogar, passar ou trocar.
    if(e == 'j'){
      Peca peca;
      //Passa-se a letra para maiuscula.
      peca.forma = toupper(palavra[1][0]);
      peca.cor = palavra[1][1];
      int i;
      int flag = 0;

      //Ver se a peca escolhida esta nas opcoes de peca disponiveis, ou se o jogador esta jogando no modo trapaca.
      int flag_concluido = 0;
      for(i = 0; i < 6; i++){
        if(cheatmode == 1){
          if(peca.forma >= 'A' && peca.forma <= 'F' && peca.cor >= '1' && peca.cor <= '6'){
            flag = 1;
          }
        }
        if(peca.forma == pecas[turno][i].forma &&     peca.cor == pecas[turno][i].cor){ 
          flag = 1;
          break;
        }
      }

      if(!flag){
        jogada_invalida();
      }else{
        //Converte as string da posicao para inteiros.
        c_x = atoi(palavra[2]);
        c_y = atoi(palavra[3]);

        //Faz a jogada.
        matriz_ = jogada(matriz_, m, n, peca, &c_x, &c_y, &pos, &linha, track, &flag_concluido);
        if(cheatmode == 1){
          flag_concluido = 0;
        }
        if(flag_concluido){
          pecas[turno][i].forma = ' ';
          pecas[turno][i].cor = ' ';
        }
      }

    }else if(e == 'p'){
      //Caso o usuario queira passar a vez.
      flag_passar = 1;

    }else if(e == 't'  && !pos){
      //Para o usuario poder trocar as pecas, ele nao pode ter jogado nenhuma peca naquela rodada. pos == 0 garante exatamente isso.
      int k;

      //Retira da entrada todas as pecas requisitas e as troca, retornando-as a pilha de pecas restantes.
      int flag = 0;
      for(k = 1; k < count_palavras; k++){
        Peca peca;
        peca.forma = toupper(palavra[k][0]);
        peca.cor = palavra[k][1];
        int i;
        for(i = 0; i < 6; i++){
          if(peca.forma == pecas[turno][i].forma && peca.cor == pecas[turno][i].cor){
            retornar_peca(usadas, pecas[turno][i]);
            pecas[turno][i].forma = ' ';
            pecas[turno][i].cor = ' ';
            flag = 1;
            break;
          }
        }
      }
      if(!flag){
        jogada_invalida();
      }else{
        flag_passar = 1;
      }

    }else{
      jogada_invalida();
      flag_passar = 0;
    }
    
    if(flag_passar==1){
      int pontos_rodada = 0;
      if(pos != 0){
        pontos_rodada = points(matriz_, track, linha, pos, *m, *n);
      }

      //Atribui os pontos da rodada a pontuacao total.
      pontos[turno]+= pontos_rodada;

      // Imprime a tela de final de jogada.
      printf("\n***************\n");
      printf("Pontuacao na rodada: %d\n", pontos_rodada);
      printf("Pontuacao total: %d\n", pontos[turno]);
      printf("***************\n\n");
      pos = 0;

      //Completa as pecas do usuario, ate ele voltar a ter 6.
      puxar_pecas(pecas[turno], usadas);

      //Passa a vez. Caso seja a vez do jogador final, reinicia-se o turno.
      turno++;
      if(turno == num_jog){
        turno = 0;
      }
    }
    free(palavra);
  }
  free(usadas);
  free(nomes);
  free(pontos);
  free(matriz);
  free(pecas);
}
void inicio();
char** get_palavras(char *string, int *num);
Peca** jogada(Peca **matriz, int *m, int *n, Peca n_peca, int *c_x, int *c_y, int *pos, int *linha, int **track, int *flag_concluido);
void menu(Peca **matriz, int *m, int *n, int num_jog, char **nomes, int cheatmode);
void jogada_invalida(Peca **matriz, int m, int n);
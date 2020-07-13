typedef  struct Peca{
    char forma;
    char cor;
} Peca;

Peca** aloca_tabuleiro(int m, int n);
void cores(char c, char d);
void print_tabuleiro(Peca **matriz, int m, int n);
Peca** update_tabuleiro(Peca **matriz, int *n_linhas, int *n_colunas, int **track, int pos);

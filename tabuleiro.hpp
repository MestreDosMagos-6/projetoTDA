#ifndef TABULEIRO_HPP
#define TABULEIRO_HPP

char **criarTabuleiro(int tamanho);
void liberarTabuleiro(char **tab, int tamanho);
void inicializarTabuleiro(char **tab, int tamanho);
void mostrarTabuleiro(char **tab, int tamanho);
bool verificarVitoria(char **tab, int tamanho, char jogador);
bool verificarEmpate(char **tab, int tamanho);

#endif

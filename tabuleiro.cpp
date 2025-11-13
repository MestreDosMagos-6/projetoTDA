#include <iostream>
using namespace std;
#include "tabuleiro.hpp"

char **criarTabuleiro(int tamanho)
{
    char **tab = new char *[tamanho];
    for (int i = 0; i < tamanho; i++)
        tab[i] = new char[tamanho];
    return tab;
}

void liberarTabuleiro(char **tab, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
        delete[] tab[i];
    delete[] tab;
}

void inicializarTabuleiro(char **tab, int tamanho)
{

    if (tamanho == 3)
    {
        char pos = '1';
        for (int i = 0; i < tamanho; i++)
            for (int j = 0; j < tamanho; j++)
                tab[i][j] = pos++;
    }
    else
    {
        char letra = 'A';
        for (int i = 0; i < tamanho; i++)
        {
            for (int j = 0; j < tamanho; j++)
            {
                tab[i][j] = letra++;
            }
        }
    }
}

void mostrarTabuleiro(char **tab, int tamanho)
{
    cout << "\nTabuleiro:\n";
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            cout << " " << tab[i][j] << " ";
            if (j < tamanho - 1)
                cout << "|";
        }
        cout << "\n";
        if (i < tamanho - 1)
        {
            for (int k = 0; k < tamanho; k++)
            {
                cout << "---";
                if (k < tamanho - 1)
                    cout << "+";
            }
            cout << "\n";
        }
    }
    cout << "\n";
}

bool verificarVitoria(char **tab, int tamanho, char jogador)
{
    for (int i = 0; i < tamanho; i++)
    {
        bool linha = true, coluna = true;
        for (int j = 0; j < tamanho; j++)
        {
            if (tab[i][j] != jogador)
                linha = false;
            if (tab[j][i] != jogador)
                coluna = false;
        }
        if (linha || coluna)
            return true;
    }
    bool diag1 = true, diag2 = true;
    for (int i = 0; i < tamanho; i++)
    {
        if (tab[i][i] != jogador)
            diag1 = false;
        if (tab[i][tamanho - 1 - i] != jogador)
            diag2 = false;
    }
    return diag1 || diag2;
}

bool verificarEmpate(char **tab, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
        for (int j = 0; j < tamanho; j++)
            if (tab[i][j] != 'X' && tab[i][j] != 'O')
                return false;
    return true;
}

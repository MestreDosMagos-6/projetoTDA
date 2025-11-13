#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "jogo.hpp"
#include "tabuleiro.hpp"
#include "util.hpp"

using namespace std;

void jogadaJogador(char **tab, int tamanho, char jogador)
{
    string entrada;
    bool valido = false;

    while (!valido)
    {
        cout << "Jogador '" << jogador << "', escolha sua posicao: ";
        cin >> entrada;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Converte para maiuscula caso seja letra
        if (entrada.size() == 1 && isalpha(entrada[0]))
        {
            entrada[0] = toupper(entrada[0]);

            char letra = entrada[0];
            bool achou = false;

            // procura no tabuleiro a letra
            for (int i = 0; i < tamanho; i++)
            {
                for (int j = 0; j < tamanho; j++)
                {
                    if (tab[i][j] == letra)
                    {
                        // verifica se está livre
                        tab[i][j] = jogador;
                        achou = true;
                        valido = true;
                        break;
                    }
                }
                if (achou)
                    break;
            }

            if (!achou)
            {
                cout << "Entrada invalida! Digite uma letra valida do tabuleiro.\n";
            }
        }
        else
        {
            // TRATAR COMO NUMERO (funciona para 3x3)
            int escolha = 0;

            try
            {
                escolha = stoi(entrada);
            }
            catch (...)
            {
                cout << "Entrada invalida! Digite um numero ou uma letra valida.\n";
                continue;
            }

            if (escolha < 1 || escolha > tamanho * tamanho)
            {
                cout << "Posicao fora do intervalo!\n";
                continue;
            }

            int linha = (escolha - 1) / tamanho;
            int coluna = (escolha - 1) % tamanho;

            if (tab[linha][coluna] == 'X' || tab[linha][coluna] == 'O')
            {
                cout << "Posicao ocupada!\n";
            }
            else
            {
                tab[linha][coluna] = jogador;
                valido = true;
            }
        }
    }
}

void jogadaComputador(char **tab, int tamanho, char jogador)
{
    int linha, coluna;
    do
    {
        linha = rand() % tamanho;
        coluna = rand() % tamanho;
    } while (tab[linha][coluna] == 'X' || tab[linha][coluna] == 'O');

    tab[linha][coluna] = jogador;
    cout << "Computador jogou na posicao " << (linha * tamanho + coluna + 1) << "\n";
}

void iniciarJogo()
{
    srand(time(0));

    // ==============================
    //   ESCOLHER TAMANHO DO TABULEIRO
    // ==============================
    int tamanho = 3;
    while (true)
    {
        cout << "Escolha o tamanho do tabuleiro (3, 4 ou 5): ";
        cin >> tamanho;

        if (!cin.fail() && (tamanho == 3 || tamanho == 4 || tamanho == 5))
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }

        cout << "\nValor invalido! Digite 3, 4 ou 5.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    char **tab = criarTabuleiro(tamanho);
    inicializarTabuleiro(tab, tamanho);

    // ==============================
    //   MODO DE JOGO
    // ==============================
    int modo;
    while (true)
    {
        cout << "Escolha modo: 1. PvP  2. PvC: ";
        cin >> modo;

        if (!cin.fail() && (modo == 1 || modo == 2))
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }

        cout << "Entrada invalida! Digite 1 ou 2.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // ==============================
    //   NOMES DOS JOGADORES
    // ==============================
    string jogador1, jogador2;

    cout << "Digite o nome do Jogador X: ";
    getline(cin, jogador1);

    if (modo == 1)
    {
        cout << "Digite o nome do Jogador O: ";
        getline(cin, jogador2);
    }
    else
    {
        jogador2 = "Computador";
    }

    // ==============================
    //       LOOP PRINCIPAL DO JOGO
    // ==============================
    char jogadorAtual = 'X';
    bool fim = false;

    while (!fim)
    {
        mostrarTabuleiro(tab, tamanho);

        if (modo == 1)
        {
            // PvP: ambos humanos
            jogadaJogador(tab, tamanho, jogadorAtual);
        }
        else
        {
            // PvC
            if (jogadorAtual == 'X')
                jogadaJogador(tab, tamanho, 'X'); // humano
            else
                jogadaComputador(tab, tamanho, 'O'); // computador sempre O
        }

        if (verificarVitoria(tab, tamanho, jogadorAtual))
        {
            mostrarTabuleiro(tab, tamanho);

            if (modo == 1)
            {
                // PVP
                string vencedor = (jogadorAtual == 'X') ? jogador1 : jogador2;
                cout << "\n=== VITORIA ===\n";
                cout << "O jogador " << vencedor << " venceu a partida!\n";
                salvarRanking(vencedor, 1);
            }
            else
            {
                // PVC
                if (jogadorAtual == 'X')
                {
                    cout << "\n=== VITORIA ===\n";
                    cout << "Voce venceu!\n";
                    salvarRanking(jogador1, 1);
                }
                else
                {
                    cout << "\n=== DERROTA ===\n";
                    cout << "O computador venceu!\n";
                }
            }

            fim = true;
        }

        else if (verificarEmpate(tab, tamanho))
        {
            mostrarTabuleiro(tab, tamanho);
            cout << "Empate!\n";
            fim = true;
        }

        jogadorAtual = (jogadorAtual == 'X') ? 'O' : 'X';
    }

    liberarTabuleiro(tab, tamanho);
    pausar();
}

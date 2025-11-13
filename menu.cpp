#include <iostream>
#include <limits>
#include "menu.hpp"
#include "jogo.hpp"
#include "util.hpp"
#include "tabuleiro.hpp"

using std::numeric_limits;
using std::streamsize;
using namespace std;

void menu()
{

    int opcao = 0;

    while (true)
    { // menu roda até escolher sair
        limparTela();

        cout << "===== MENU =====\n";
        cout << "1. Jogar\n";
        cout << "2. Ver Ranking\n";
        cout << "3. Creditos\n";
        cout << "4. Sair\n";
        cout << "Escolha uma opcao: ";

        // Tratamento de erro para TEXTO digitado
        if (!(cin >> opcao))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nEntrada invalida! Digite apenas numeros.\n";
            pausar();
            continue;
        }

        // Limpa o ENTER deixado no buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcao)
        {

        case 1:
            iniciarJogo();
            break;

        case 2:
            mostrarRanking();
            break;

        case 3:
            cout << "\n===== CREDITOS =====\n";
            cout << "Eduardo Augusto\n";
            cout << "Aymee Silvestre\n";
            cout << "Joalysson Viana\n";
            cout << "Luiz David\n";
            cout << "Lucas Santana\n";
            cout << "Miguel Luis\n";
            cout << "=====================\n";
            pausar();
            break;

        case 4:
            cout << "Saindo...\n";
            return; // ENCERRA o menu corretamente

        default:
            cout << "Opcao invalida! Digite algo entre 1 e 4.\n";
            pausar();
            break;
        }
    }
}

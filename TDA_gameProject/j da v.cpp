#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

//?
char** criarTabuleiro(int tamanho);
void liberarTabuleiro(char** tab, int tamanho);
void inicializarTabuleiro(char** tab, int tamanho);
void mostrarTabuleiro(char** tab, int tamanho);
bool verificarVitoria(char** tab, int tamanho, char jogador);
bool verificarEmpate(char** tab, int tamanho);
void jogadaJogador(char** tab, int tamanho, char jogador);
void jogadaComputador(char** tab, int tamanho, char jogador);
void limparTela();
void pausar();
void salvarRanking(const string& nome, int pontos);
void mostrarRanking();
void menu();

int main() {
    srand(time(0)); //?
    menu();
    return 0;
}

// Dividir em outro arquivo - 1

char** criarTabuleiro(int tamanho) {
    char** tab = new char*[tamanho];
    for (int i = 0; i < tamanho; i++)
        tab[i] = new char[tamanho];
    return tab;
}

void liberarTabuleiro(char** tab, int tamanho) {
    for (int i = 0; i < tamanho; i++)
        delete[] tab[i];
    delete[] tab;
}

void inicializarTabuleiro(char** tab, int tamanho) {
    char pos = '1';
    for (int i = 0; i < tamanho; i++)
        for (int j = 0; j < tamanho; j++)
            tab[i][j] = pos++;
}

void mostrarTabuleiro(char** tab, int tamanho) {
    cout << "\nTabuleiro:\n";
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            cout << " " << tab[i][j] << " ";
            if (j < tamanho-1) cout << "|";
        }
        cout << "\n";
        if (i < tamanho-1) {
            for (int k = 0; k < tamanho; k++) {
                cout << "---";
                if (k < tamanho-1) cout << "+";
            }
            cout << "\n";
        }
    }
    cout << "\n";
}

bool verificarVitoria(char** tab, int tamanho, char jogador) {
    // checa linhas e colunas
    for (int i = 0; i < tamanho; i++) {
        bool linha = true, coluna = true;
        for (int j = 0; j < tamanho; j++) {
            if (tab[i][j] != jogador) linha = false;
            if (tab[j][i] != jogador) coluna = false;
        }
        if (linha || coluna) return true;
    }
    // checa diagonais
    bool diag1 = true, diag2 = true;
    for (int i = 0; i < tamanho; i++) {
        if (tab[i][i] != jogador) diag1 = false;
        if (tab[i][tamanho-1-i] != jogador) diag2 = false;
    }
    return diag1 || diag2;
}

bool verificarEmpate(char** tab, int tamanho) {
    for (int i = 0; i < tamanho; i++)
        for (int j = 0; j < tamanho; j++)
            if (tab[i][j] != 'X' && tab[i][j] != 'O')
                return false;
    return true;
}

void jogadaJogador(char** tab, int tamanho, char jogador) {
    int escolha;
    bool valido = false;
    while(!valido){
        cout << "Jogador '" << jogador << "', escolha sua posicao (1-" << tamanho*tamanho << "): ";
        cin >> escolha;
        if(cin.fail() || escolha < 1 || escolha > tamanho*tamanho){
            cout << "Entrada invalida!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        int linha = (escolha-1)/tamanho;
        int coluna = (escolha-1)%tamanho;
        if(tab[linha][coluna] == 'X' || tab[linha][coluna] == 'O'){
            cout << "Posicao ocupada!\n";
        } else {
            tab[linha][coluna] = jogador;
            valido = true;
        }
    }
}

void jogadaComputador(char** tab, int tamanho, char jogador) {
    int linha, coluna;
    do {
        linha = rand() % tamanho;
        coluna = rand() % tamanho;
    } while(tab[linha][coluna] == 'X' || tab[linha][coluna] == 'O');
    tab[linha][coluna] = jogador;
    cout << "Computador jogou na posicao " << linha*tamanho + coluna + 1 << "\n";
}
// Dividir em outro arquivo - 1

// Dividir em outro arquivo - 2
void limparTela() {
    system("cls"); // Windows
}

void pausar() {
    cout << "Pressione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void salvarRanking(const string& nome, int pontos){
    ofstream arq("ranking.txt", ios::app);
    arq << nome << " " << pontos << "\n";
    arq.close();
}

void mostrarRanking(){
    ifstream arq("ranking.txt");
    string linha;
    cout << "\n===== RANKING =====\n";
    while(getline(arq, linha)) cout << linha << "\n";
    cout << "==================\n";
    pausar();
}
// Dividir em outro arquivo - 2

// Fica na main
void menu(){
    int opcao;
    do{
        limparTela();
        cout << "===== MENU =====\n";
        cout << "1. Jogar\n2. Ver Ranking\n3. Creditos\n4. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if(opcao == 1){
            int tamanho = 3;
            char** tab = criarTabuleiro(tamanho);
            inicializarTabuleiro(tab, tamanho);

            int modo;
            cout << "Escolha modo: 1. PvP  2. PvC: ";
            cin >> modo;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string nomeJogador;
            cout << "Digite seu nome: ";
            getline(cin, nomeJogador);

            char jogadorAtual = 'X';
            bool fim = false;
            while(!fim){
                mostrarTabuleiro(tab, tamanho);
                if(modo == 1 || jogadorAtual == 'X')
                    jogadaJogador(tab, tamanho, jogadorAtual);
                else
                    jogadaComputador(tab, tamanho, jogadorAtual);

                if(verificarVitoria(tab, tamanho, jogadorAtual)){
                    mostrarTabuleiro(tab, tamanho);
                    cout << "Jogador '" << jogadorAtual << "' venceu!\n";
                    salvarRanking(nomeJogador, 1);
                    fim = true;
                } else if(verificarEmpate(tab, tamanho)){
                    mostrarTabuleiro(tab, tamanho);
                    cout << "Empate!\n";
                    fim = true;
                }

                jogadorAtual = (jogadorAtual=='X')?'O':'X';
            }

            liberarTabuleiro(tab, tamanho);
            pausar();
        }
        else if(opcao==2){
            mostrarRanking();
        }
        else if(opcao==3){
            cout << "\n===== CREDITOS =====\n";
            cout << "Eduardo Augusto\nAymee Silvestre\nJoalysson Viana\nLuiz David\nLucas Santana\n";
            pausar();
        }

    }while(opcao!=4);
}

//Melhorar sistema de salvamento no arquivo, problemas com o pedido de nome, 
//Colocar nome vazio, ao escrever um texto o programa buga, 
//faltou colocar os comentários na parte de cada código
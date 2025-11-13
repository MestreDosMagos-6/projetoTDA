#include <iostream>
#include <fstream>
#include "util.hpp"
#include <limits>
#include <sstream>
#include <vector>

using namespace std;
using std::string;

void limparTela() {
    system("cls");
}

void pausar() {
    cout << "Pressione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void salvarRanking(const string& nome, int pontos) {
    ifstream arqLeitura("ranking.txt");
    string nomeArquivo;
    int pontosArquivo;
    bool encontrado = false;

    vector<pair<string, int>> ranking;

    while (arqLeitura >> nomeArquivo >> pontosArquivo) {
        if (nomeArquivo == nome) {
            pontosArquivo += pontos;
            encontrado = true;
        }
        ranking.push_back({nomeArquivo, pontosArquivo});
    }
    arqLeitura.close();

    if (!encontrado) {
        ranking.push_back({nome, pontos});
    }

    ofstream arqEscrita("ranking.txt", ios::trunc);
    for (auto& entrada : ranking) {
        arqEscrita << entrada.first << " " << entrada.second << "\n";
    }
    arqEscrita.close();
}

void mostrarRanking() {
    ifstream arq("ranking.txt");
    if (!arq) {
        cout << "Nenhum ranking salvo ainda.\n";
        return;
    }
    string linha;
    cout << "\n===== RANKING =====\n";
    while (getline(arq, linha))
        cout << linha << "\n";
    cout << "===================\n";
    pausar();
}

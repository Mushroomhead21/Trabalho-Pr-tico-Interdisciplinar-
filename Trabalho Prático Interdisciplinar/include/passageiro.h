#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

typedef struct {
    int codigo;           // Código único do passageiro
    char nome[100];       // Nome do passageiro
    char endereco[200];   // Endereço do passageiro
    char telefone[20];    // Telefone do passageiro
    char fidelidade[4];       // Fidelidade: 1 para sim, 0 para não
    int pontosFidelidade; // Pontos de fidelidade
} Passageiro;

// Funções para manipulação de passageiros
void cadastrarPassageiro();
int verificarDuplicidade(int codigo);
void salvarPassageiro(Passageiro p);
void listarPassageiros();
void buscarPassageiro();

#endif

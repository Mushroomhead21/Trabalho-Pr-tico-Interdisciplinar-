#ifndef TRIPULACAO_H
#define TRIPULACAO_H

typedef struct {
    int codigo;           // Código único do membro da tripulação
    char nome[100];       // Nome do membro da tripulação
    char telefone[15];    // Telefone do membro
    char cargo[50];       // Cargo do membro (piloto, copiloto, comissario)
} Tripulacao;

// Funções de manipulação de tripulação
int gerarCodigoTripulacao();
void cadastrarTripulacao();
void listarTripulacao();
void salvarTripulacao(Tripulacao t);
void listarTripulacaoPorCargo(const char *cargo);
int verificarDuplicidadeTripulacao(int codigo);
void buscarTripulacao();

#endif

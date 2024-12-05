#ifndef RESERVA_H
#define RESERVA_H

// Estrutura para armazenar a reserva
typedef struct {
    int codigoVoo;          // Código do voo
    char numeroAssento[5];  // Número do assento
    int codigoPassageiro;   // Código do passageiro
    char status[20]; // Exemplo: "Confirmada" ou "Cancelada"
} Reserva;

// Função para listar voos ativos
void listarVoosAtivosParaEscolha();
void listarAssentosDisponiveis(int codigoVoo);
void listarPassageirosParaEscolha();
void reservarAssento();
int verificarAssentoDisponivel(int codigoVoo, char *numeroAssento);
void atualizarPontosFidelidade(int codigoPassageiro);
void listarReservasPorPassageiro(int codigoPassageiro);
void liberarAssento(int codigoVoo, char numeroAssento[5]);

#endif  // RESERVA_H
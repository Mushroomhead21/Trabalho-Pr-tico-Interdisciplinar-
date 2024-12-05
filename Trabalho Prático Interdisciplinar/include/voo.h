#ifndef VOO_H
#define VOO_H


typedef struct {
    int codigo;
    char data[11];
    char hora[6];
    char origem[50];
    char destino[50];
    int codigoAviao;
    int codigoPiloto;
    int codigoCopiloto;
    int codigoComissario; // 0 se não houver
    char status[8]; // "Ativo" ou "Inativo"
    float tarifa;
} Voo;

void cadastrarVoo();
void listarVoos();
void salvarVoo(Voo novoVoo);
void listarVoosAtivosParaEscolha();
#endif // VOO_H
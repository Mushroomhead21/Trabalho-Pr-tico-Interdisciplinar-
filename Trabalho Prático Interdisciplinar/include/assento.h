#ifndef ASSENTO_H
#define ASSENTO_H

typedef struct {
    char numero[5];  // Número do assento (ex: "A1")
    int codigoVoo;   // Código do voo
    char status[10]; // Status do assento ("Livre" por padrão)
} Assento;

void listarVoosAtivosParaEscolha();
void cadastrarAssento();
void listarAssentos(int codigoVoo);
void listarAssentos2(int codigoVoo);
#endif // ASSENTO_H
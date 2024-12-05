#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/assento.h"
#include "../include/voo.h"

#define ASSENTOS_FILE "data/assentos.dat"

// Função para cadastrar um assento
void cadastrarAssento() {
    listarVoosAtivosParaEscolha();

    int codigoVoo;
    char numeroAssento[5];

    // Solicitar código do voo
    printf("Digite o codigo do voo para cadastrar o assento: ");
    scanf("%d", &codigoVoo);
    getchar(); // Limpar o buffer do teclado

    // Solicitar número do assento
    printf("Digite o numero do assento (ex: A1): ");
    fgets(numeroAssento, sizeof(numeroAssento), stdin);
    numeroAssento[strcspn(numeroAssento, "\n")] = '\0'; // Remover newline

    // Preencher e salvar o assento
    Assento assento;
    assento.codigoVoo = codigoVoo;
    strcpy(assento.numero, numeroAssento);
    strcpy(assento.status, "Livre");

    FILE *arquivo = fopen(ASSENTOS_FILE, "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de assentos.\n");
        return;
    }
    fwrite(&assento, sizeof(Assento), 1, arquivo);
    fclose(arquivo);

    printf("Assento cadastrado com sucesso!\n");
}

#define TOTAL_FILE "data/assentos.dat"

void listarAssentos2(int codigoVoo) {
    // Abre o arquivo e lista os assentos do voo selecionado
    FILE *arquivo = fopen("data/assentos.dat", "rb");
    if (arquivo == NULL) {
        printf("Nenhum assento cadastrado.\n");
        return;
    }

    Assento assento;
    printf("\n---- Lista de Assentos (Voo %d) ----\n", codigoVoo);
    int encontrado = 0;

    while (fread(&assento, sizeof(Assento), 1, arquivo)) {
        if (assento.codigoVoo == codigoVoo) {
            encontrado = 1;
            printf("Assento: %s | Status: %s\n", assento.numero, assento.status);
        }
    }

    if (!encontrado) {
        printf("Nenhum assento encontrado para o voo %d.\n", codigoVoo);
    }

    fclose(arquivo);
}
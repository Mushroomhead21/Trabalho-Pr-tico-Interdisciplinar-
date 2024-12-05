#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/assento.h"
#include "../include/voo.h"
#include "../include/reserva.h"
#include "../include/passageiro.h"

#define RESERVAS_FILE "data/reservas.dat"

// Função para listar voos ativos
void listarVoosAtivosParaEscolha() {
    FILE *arquivo = fopen("data/voos.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de voos.\n");
        return;
    }

    Voo voo;
    printf("\n---- Lista de Voos Ativos ----\n");
    while (fread(&voo, sizeof(Voo), 1, arquivo)) {
        if (strcmp(voo.status, "Ativo") == 0) {
            printf("Codigo: %d | Data: %s | Hora: %s | Origem: %s | Destino: %s\n",
                   voo.codigo, voo.data, voo.hora, voo.origem, voo.destino);
        }
    }
    printf("-----------------------------------\n");
    fclose(arquivo);
}

// Função para listar passageiros
void listarPassageirosParaEscolha() {
    FILE *arquivo = fopen("data/passageiros.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de passageiros.\n");
        return;
    }

    Passageiro passageiro;
    printf("\n---- Lista de Passageiros ----\n");
    while (fread(&passageiro, sizeof(Passageiro), 1, arquivo)) {
        printf("Codigo: %d | Nome: %s\n", passageiro.codigo, passageiro.nome);
    }
    printf("-----------------------------------\n");
    fclose(arquivo);
}

// Função para listar assentos disponíveis
void listarAssentosDisponiveis(int codigoVoo) {
    FILE *arquivo = fopen("data/assentos.dat", "rb");
    if (arquivo == NULL) {
        printf("Nenhum assento cadastrado.\n");
        return;
    }

    Assento assento;
    int encontrouAssentoDisponivel = 0;
    printf("\n---- Lista de Assentos Disponiveis (Voo %d) ----\n", codigoVoo);
    while (fread(&assento, sizeof(Assento), 1, arquivo)) {
        if (assento.codigoVoo == codigoVoo && strcmp(assento.status, "Livre") == 0) {
            printf("Assento: %s | Status: %s\n", assento.numero, assento.status);
            encontrouAssentoDisponivel = 1;
        }
    }

    if (!encontrouAssentoDisponivel) {
        printf("Nenhum assento disponivel para o voo %d.\n", codigoVoo);
    }

    fclose(arquivo);
}

// Função para reservar um assento
void reservarAssento() {
    listarVoosAtivosParaEscolha();

    int codigoVoo;
    printf("Digite o codigo do voo para reservar o assento: ");
    scanf("%d", &codigoVoo);

    listarAssentosDisponiveis(codigoVoo);

    char numeroAssento[5];
    printf("Digite o numero do assento para reservar: ");
    scanf("%s", numeroAssento);

    listarPassageirosParaEscolha();

    int codigoPassageiro;
    printf("Digite o codigo do passageiro para reservar o assento: ");
    scanf("%d", &codigoPassageiro);

    // Verificando se o assento está disponível
    FILE *arquivoAssentos = fopen("data/assentos.dat", "rb+");
    if (arquivoAssentos == NULL) {
        printf("Erro ao abrir o arquivo de assentos.\n");
        return;
    }

    Assento assento;
    int assentoReservado = 0;
    while (fread(&assento, sizeof(Assento), 1, arquivoAssentos)) {
        if (assento.codigoVoo == codigoVoo && strcmp(assento.numero, numeroAssento) == 0 && strcmp(assento.status, "Livre") == 0) {
            // Reservando o assento
            strcpy(assento.status, "Reservado");

            // Atualizando o arquivo de assentos
            fseek(arquivoAssentos, -sizeof(Assento), SEEK_CUR);
            fwrite(&assento, sizeof(Assento), 1, arquivoAssentos);
            assentoReservado = 1;
            break;
        }
    }

    if (!assentoReservado) {
        printf("Assento nao disponivel para reserva.\n");
        fclose(arquivoAssentos);
        return;
    }

    // Registrando a reserva
    FILE *arquivoReservas = fopen(RESERVAS_FILE, "ab");
    if (arquivoReservas == NULL) {
        printf("Erro ao abrir o arquivo de reservas.\n");
        fclose(arquivoAssentos);
        return;
    }

    Reserva reserva;
    reserva.codigoVoo = codigoVoo;
    strcpy(reserva.numeroAssento, numeroAssento);
    reserva.codigoPassageiro = codigoPassageiro;
    strcpy(reserva.status, "Confirmada");

    fwrite(&reserva, sizeof(Reserva), 1, arquivoReservas);

    fclose(arquivoAssentos);
    fclose(arquivoReservas);

    printf("Reserva realizada com sucesso!\n");

    atualizarPontosFidelidade(codigoPassageiro);
}

// Função para atualizar os pontos de fidelidade
void atualizarPontosFidelidade(int codigoPassageiro) {
    FILE *arquivoPassageiros = fopen("data/passageiros.dat", "rb+");
    if (arquivoPassageiros == NULL) {
        printf("Erro ao abrir o arquivo de passageiros.\n");
        return;
    }

    Passageiro passageiro;
    int encontrado = 0;
    while (fread(&passageiro, sizeof(Passageiro), 1, arquivoPassageiros)) {
        if (passageiro.codigo == codigoPassageiro) {
            passageiro.pontosFidelidade += 10;
            if (passageiro.pontosFidelidade >= 10) {
                strcpy(passageiro.fidelidade, "Sim");
            }

            fseek(arquivoPassageiros, -sizeof(Passageiro), SEEK_CUR);
            fwrite(&passageiro, sizeof(Passageiro), 1, arquivoPassageiros);
            encontrado = 1;
            break;
        }
    }

    fclose(arquivoPassageiros);

    if (encontrado) {
        printf("Pontos de fidelidade atualizados. Status: %s\n", passageiro.fidelidade);
    } else {
        printf("Passageiro nao encontrado.\n");
    }
}

// Função para listar reservas por passageiro
void listarReservasPorPassageiro(int codigoPassageiro) {
    FILE *arquivoReservas = fopen(RESERVAS_FILE, "rb");
    FILE *arquivoVoos = fopen("data/voos.dat", "rb");

    if (arquivoReservas == NULL || arquivoVoos == NULL) {
        printf("Erro ao abrir os arquivos de reservas ou voos.\n");
        return;
    }

    Reserva reserva;
    Voo voo;
    int encontrado = 0;

    printf("\nVoos reservados pelo passageiro %d:\n", codigoPassageiro);

    while (fread(&reserva, sizeof(Reserva), 1, arquivoReservas)) {
        if (reserva.codigoPassageiro == codigoPassageiro) {
            rewind(arquivoVoos);
            while (fread(&voo, sizeof(Voo), 1, arquivoVoos)) {
                if (voo.codigo == reserva.codigoVoo) {
                    printf("Codigo do Voo: %d\n", voo.codigo);
                    printf("Data: %s | Hora: %s\n", voo.data, voo.hora);
                    printf("Origem: %s | Destino: %s\n", voo.origem, voo.destino);
                    printf("Assento: %s | Status da Reserva: %s\n", reserva.numeroAssento, reserva.status); // Mostra o número do assento
                    printf("---------------------------\n");
                    encontrado = 1;
                    break;
                }
            }
        }
    }

    if (!encontrado) {
        printf("Nenhum voo encontrado para o passageiro %d.\n", codigoPassageiro);
    }

    fclose(arquivoReservas);
    fclose(arquivoVoos);
}

void liberarAssento(int codigoVoo, char numeroAssento[5]) {
    FILE *arquivoAssentos = fopen("data/assentos.dat", "rb+");
    if (arquivoAssentos == NULL) {
        printf("Erro ao abrir o arquivo de assentos.\n");
        return;
    }

    Assento assento;
    int assentoLiberado = 0;
    while (fread(&assento, sizeof(Assento), 1, arquivoAssentos)) {
        if (assento.codigoVoo == codigoVoo && strcmp(assento.numero, numeroAssento) == 0 && strcmp(assento.status, "Reservado") == 0) {
            // Atualiza o status para "Livre"
            strcpy(assento.status, "Livre");

            // Reposiciona o ponteiro e escreve a atualização
            fseek(arquivoAssentos, -sizeof(Assento), SEEK_CUR);
            fwrite(&assento, sizeof(Assento), 1, arquivoAssentos);
            assentoLiberado = 1;
            printf("Assento %s do voo %d liberado com sucesso.\n", numeroAssento, codigoVoo);
            break;
        }
    }

    fclose(arquivoAssentos);

    if (!assentoLiberado) {
        printf("Assento nao encontrado ou ja esta livre.\n");
    }
}

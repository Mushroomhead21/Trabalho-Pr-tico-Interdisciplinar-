#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/voo.h"
#include "../include/tripulacao.h"

// Função para gerar o próximo código de voo (auto-incremento)
int gerarCodigoVoo()
{
    FILE *arquivo = fopen("data/voos.dat", "rb"); // Abrir o arquivo no modo binário de leitura
    if (arquivo == NULL)
    {
        return 1; // Se o arquivo não existir, o primeiro voo terá código 1
    }

    Voo voo;
    int ultimoCodigo = 0;

    // Ler o arquivo até o final para encontrar o último código de voo
    while (fread(&voo, sizeof(Voo), 1, arquivo))
    {
        if (voo.codigo > ultimoCodigo)
        {
            ultimoCodigo = voo.codigo;
        }
    }

    fclose(arquivo);
    return ultimoCodigo + 1; // Retorna o próximo código de voo
}

// Função para cadastrar um voo
int validarData(const char *data) {
    if (strlen(data) != 10) return 0;
    if (data[2] != '/' || data[5] != '/') return 0;
    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && !isdigit(data[i])) return 0;
    }
    int dia = (data[0] - '0') * 10 + (data[1] - '0');
    int mes = (data[3] - '0') * 10 + (data[4] - '0');
    int ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');

    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900 || ano > 2100) return 0;
    return 1;
}

int validarHora(const char *hora) {
    if (strlen(hora) != 5) return 0;
    if (hora[2] != ':') return 0;
    for (int i = 0; i < 5; i++) {
        if (i != 2 && !isdigit(hora[i])) return 0;
    }
    int horas = (hora[0] - '0') * 10 + (hora[1] - '0');
    int minutos = (hora[3] - '0') * 10 + (hora[4] - '0');

    if (horas < 0 || horas > 23 || minutos < 0 || minutos > 59) return 0;
    return 1;
}

void cadastrarVoo() {
    Voo novoVoo;
    novoVoo.codigo = gerarCodigoVoo();

    printf("Codigo do voo gerado: %d\n", novoVoo.codigo);

    // Solicitar e validar a data do voo
    do {
        printf("Digite a data do voo (DD/MM/AAAA): ");
        fgets(novoVoo.data, sizeof(novoVoo.data), stdin);
        novoVoo.data[strcspn(novoVoo.data, "\n")] = '\0'; // Remover newline extra
        

        if (!validarData(novoVoo.data)) {
            printf("Data invalida! Use o formato DD/MM/AAAA.\n");
        }
    } while (!validarData(novoVoo.data));

    // Solicitar e validar a hora do voo
   // Solicitar e validar a hora do voo
    do {
    getchar();
    printf("Digite a hora do voo (HH:MM): ");
    fgets(novoVoo.hora, sizeof(novoVoo.hora), stdin);
    
    // Remover o newline extra (caso o usuário pressione Enter)
    novoVoo.hora[strcspn(novoVoo.hora, "\n")] = '\0'; 

    if (!validarHora(novoVoo.hora)) {
        printf("Hora invalida! Use o formato HH:MM.\n");
    }
    } while (!validarHora(novoVoo.hora)); // Continuar até uma hora válida ser inserida

       // Solicitar e validar a origem
    // Solicitar e validar a origem do voo
    do {
        getchar();
        printf("Digite a origem do voo: ");
        fgets(novoVoo.origem, sizeof(novoVoo.origem), stdin);
        novoVoo.origem[strcspn(novoVoo.origem, "\n")] = '\0';

        if (strlen(novoVoo.origem) == 0) {
            printf("A origem do voo nao pode estar vazia.\n");
        }
    } while (strlen(novoVoo.origem) == 0);

    // Solicitar e validar o destino do voo
    do {
        printf("Digite o destino do voo: ");
        fgets(novoVoo.destino, sizeof(novoVoo.destino), stdin);
        novoVoo.destino[strcspn(novoVoo.destino, "\n")] = '\0';

        if (strlen(novoVoo.destino) == 0) {
            printf("O destino do voo nao pode estar vazio.\n");
        }
    } while (strlen(novoVoo.destino) == 0);

    // Solicitar e validar o código do avião
    do {
        printf("Digite o codigo do aviao: ");
        scanf("%d", &novoVoo.codigoAviao);
        getchar(); // Limpar o buffer após o scanf

        if (novoVoo.codigoAviao <= 0) {
            printf("O codigo do aviao deve ser maior que zero.\n");
        }
    } while (novoVoo.codigoAviao <= 0);

    // Solicitar e validar o código do piloto
    listarTripulacaoPorCargo("Piloto");
    listarTripulacaoPorCargo("piloto");
    do {
        printf("Digite o codigo do piloto: ");
        scanf("%d", &novoVoo.codigoPiloto);
        getchar(); // Limpar o buffer após o scanf

        if (novoVoo.codigoPiloto <= 0) {
            printf("O codigo do piloto deve ser maior que zero.\n");
        }
    } while (novoVoo.codigoPiloto <= 0);

    // Solicitar e validar o código do copiloto
    listarTripulacaoPorCargo("Copiloto");
    listarTripulacaoPorCargo("copiloto");
    do {
        printf("Digite o codigo do copiloto: ");
        scanf("%d", &novoVoo.codigoCopiloto);
        getchar(); // Limpar o buffer após o scanf

        if (novoVoo.codigoCopiloto <= 0) {
            printf("O codigo do copiloto deve ser maior que zero.\n");
        }
    } while (novoVoo.codigoCopiloto <= 0);

    // Solicitar e validar o código do comissário (opcional, pode ser 0)
    listarTripulacaoPorCargo("Comissario");
    listarTripulacaoPorCargo("comissario");
    do {
        printf("Digite o codigo do comissario (0 para pular): ");
        scanf("%d", &novoVoo.codigoComissario);
        getchar(); // Limpar o buffer após o scanf

        if (novoVoo.codigoComissario < 0) {
            printf("O codigo do comissario deve ser zero ou maior.\n");
        }
    } while (novoVoo.codigoComissario < 0);

    // Solicitar e validar a tarifa do voo
    do {
        printf("Digite a tarifa do voo (em reais): ");
        scanf("%f", &novoVoo.tarifa);
        getchar(); // Limpar o buffer após o scanf

        if (novoVoo.tarifa <= 0) {
            printf("A tarifa do voo deve ser maior que zero.\n");
        }
    } while (novoVoo.tarifa <= 0);

    // Definir status do voo
    if (novoVoo.codigoPiloto > 0 && novoVoo.codigoCopiloto > 0) {
        strcpy(novoVoo.status, "Ativo");
    } else {
        strcpy(novoVoo.status, "Inativo");
    }

    // Salvar o voo no arquivo
    salvarVoo(novoVoo);
    printf("Voo cadastrado com sucesso!\n");
}

// Função para listar todos os voos diretamente do arquivo
void listarVoos()
{
    FILE *arquivo = fopen("data/voos.dat", "rb"); // Abrir o arquivo no modo binário de leitura
    if (arquivo == NULL)
    {
        printf("Nenhum voo cadastrado.\n");
        return;
    }

    Voo voo;

    printf("\n---- Lista de Voos ----\n");
    // Ler voos do arquivo um por um
    while (fread(&voo, sizeof(Voo), 1, arquivo))
    {
        printf("Codigo: %d | Data: %s | Hora: %s | Origem: %s | Destino: %s | Codigo Aviao: %d\n",
               voo.codigo, voo.data, voo.hora, voo.origem, voo.destino, voo.codigoAviao);
        printf("Piloto: %d | Copiloto: %d | Comissario: %d | Status: %s | Tarifa: R$%.2f\n",
               voo.codigoPiloto, voo.codigoCopiloto, voo.codigoComissario,
               voo.status, voo.tarifa);
        printf("----------------------------\n");
    }

    fclose(arquivo);
}

// Função para salvar um voo no arquivo
void salvarVoo(Voo novoVoo)
{
    FILE *arquivo = fopen("data/voos.dat", "ab"); // Abrir o arquivo no modo binário de append
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de voos.\n");
        return;
    }

    // Salvar o voo no arquivo
    fwrite(&novoVoo, sizeof(Voo), 1, arquivo);
    fclose(arquivo);
}
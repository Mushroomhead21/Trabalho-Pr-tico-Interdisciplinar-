#include <stdio.h>
#include <string.h>
#include "../include/tripulacao.h"

// Função para verificar se o código do membro da tripulação já existe no arquivo
int verificarDuplicidadeTripulacao(int codigo) {
    FILE *arquivo = fopen("data/tripulacao.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de tripulacao.\n");
        return 0;
    }

    Tripulacao t;
    while (fread(&t, sizeof(Tripulacao), 1, arquivo)) {
        if (t.codigo == codigo) {
            fclose(arquivo);
            return 1; // Já existe um membro com esse código
        }
    }

    fclose(arquivo);
    return 0; // Código não existe
}

// Função para gerar o próximo código da tripulação (auto-incrementado)
int gerarCodigoTripulacao() {
    FILE *arquivo = fopen("data/tripulacao.dat", "rb");
    int ultimoCodigo = 0; // Começar com 0 caso o arquivo ainda não tenha membros

    if (arquivo == NULL) {
        return ultimoCodigo + 1; // Se o arquivo não existir, o código começa em 1
    }

    Tripulacao t;
    while (fread(&t, sizeof(Tripulacao), 1, arquivo)) {
        if (t.codigo > ultimoCodigo) {
            ultimoCodigo = t.codigo; // Atualiza o último código encontrado
        }
    }

    fclose(arquivo);
    return ultimoCodigo + 1; // Retorna o próximo código disponível
}

void cadastrarTripulacao() {
    Tripulacao t;
    int codigo = gerarCodigoTripulacao(); // Gerar código auto-incrementado

    printf("O codigo do membro da tripulacao gerado e: %d\n", codigo);
    t.codigo = codigo;

    // Solicitar o nome do membro da tripulação com verificação
    do {
        printf("Digite o nome do membro da tripulacao: ");
        fgets(t.nome, sizeof(t.nome), stdin);
        t.nome[strcspn(t.nome, "\n")] = '\0'; // Remove o caractere de nova linha

        if (strlen(t.nome) == 0) {
            printf("O nome do membro da tripulacao nao pode estar vazio.\n");
        }
    } while (strlen(t.nome) == 0);

    // Solicitar o telefone do membro da tripulação com verificação
    do {
        printf("Digite o telefone do membro da tripulacao: ");
        fgets(t.telefone, sizeof(t.telefone), stdin);
        t.telefone[strcspn(t.telefone, "\n")] = '\0';

        if (strlen(t.telefone) == 0) {
            printf("O telefone do membro da tripulacao nao pode estar vazio.\n");
        }
    } while (strlen(t.telefone) == 0);

    // Solicitar o cargo do membro da tripulação com verificação
    do {
        printf("Digite o cargo do membro (piloto, copiloto, comissario): ");
        fgets(t.cargo, sizeof(t.cargo), stdin);
        t.cargo[strcspn(t.cargo, "\n")] = '\0';

        if (strlen(t.cargo) == 0) {
            printf("O cargo do membro da tripulacao nao pode estar vazio.\n");
        }
    } while (strlen(t.cargo) == 0);

    // Verificar se já existe um membro com o mesmo código
    if (verificarDuplicidadeTripulacao(codigo)) {
        printf("Erro: Ja existe um membro com esse codigo. O cadastro nao pode ser realizado.\n");
    } else {
        salvarTripulacao(t);
        printf("Membro da tripulacao cadastrado com sucesso!\n");
    }
}

// Função para salvar o membro da tripulação no arquivo
void salvarTripulacao(Tripulacao t) {
    FILE *arquivo = fopen("data/tripulacao.dat", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de tripulacao.\n");
        return;
    }

    fwrite(&t, sizeof(Tripulacao), 1, arquivo);
    fclose(arquivo);
}

// Função para listar os membros da tripulação cadastrados
void listarTripulacao() {
    FILE *arquivo = fopen("data/tripulacao.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de tripulacao.\n");
        return;
    }

    Tripulacao t;
    printf("\nMembros da Tripulacao cadastrados:\n");
    while (fread(&t, sizeof(Tripulacao), 1, arquivo)) {
        printf("Codigo: %d\n", t.codigo);
        printf("Nome: %s\n", t.nome);
        printf("Telefone: %s\n", t.telefone);
        printf("Cargo: %s\n", t.cargo);
        printf("---------------------------\n");
    }

    fclose(arquivo);
}

// Função para listar membros da tripulação por cargo
void listarTripulacaoPorCargo(const char *cargo) {
    FILE *arquivo = fopen("data/tripulacao.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de tripulacao.\n");
        return;
    }

    Tripulacao t;
    printf("\nMembros da Tripulacao com o cargo de %s:\n", cargo);
    while (fread(&t, sizeof(Tripulacao), 1, arquivo)) {
        if (strcmp(t.cargo, cargo) == 0) {
            printf("Codigo: %d | Nome: %s | Cargo: %s | Telefone: %s\n",
                   t.codigo, t.nome, t.cargo, t.telefone);
        }
    }

    fclose(arquivo);
}

// Função para buscar membros da tripulação
void buscarTripulacao() {
    int escolha;
    printf("Buscar Tripulacao por:\n");
    printf("1. Codigo\n");
    printf("2. Nome\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);
    
    FILE *arquivo = fopen("data/tripulacao.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de tripulacao.\n");
        return;
    }

    Tripulacao tripulacao;
    int encontrado = 0;

    if (escolha == 1) {
        int codigo;
        printf("Digite o codigo da tripulacao: ");
        scanf("%d", &codigo);

        while (fread(&tripulacao, sizeof(Tripulacao), 1, arquivo)) {
            if (tripulacao.codigo == codigo) {
                printf("Codigo: %d | Nome: %s | Cargo: %s\n", tripulacao.codigo, tripulacao.nome, tripulacao.cargo);
                encontrado = 1;
                break;
            }
        }
    } else if (escolha == 2) {
        char nome[100];
        printf("Digite o nome da tripulacao: ");
        scanf(" %[^\n]s", nome);  // Lê a string com espaços

        while (fread(&tripulacao, sizeof(Tripulacao), 1, arquivo)) {
            if (strstr(tripulacao.nome, nome) != NULL) {
                printf("Codigo: %d | Nome: %s | Cargo: %s\n", tripulacao.codigo, tripulacao.nome, tripulacao.cargo);
                encontrado = 1;
            }
        }
    } else {
        printf("Opcao invalida!\n");
    }

    if (!encontrado) {
        printf("Tripulacao nao encontrada.\n");
    }

    fclose(arquivo);
}
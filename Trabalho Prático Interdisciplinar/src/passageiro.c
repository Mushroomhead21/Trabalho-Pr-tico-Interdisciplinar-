#include <stdio.h>
#include <string.h>
#include "../include/passageiro.h"

#define PASSAGEIROS_FILE "data/passageiros.dat"

// Função para verificar se o código do passageiro já existe no arquivo
int verificarDuplicidade(int codigo) {
    FILE *arquivo = fopen("data/passageiros.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de passageiros.\n");
        return 0;
    }

    Passageiro p;
    while (fread(&p, sizeof(Passageiro), 1, arquivo)) {
        if (p.codigo == codigo) {
            fclose(arquivo);
            return 1; // Já existe um passageiro com esse código
        }
    }

    fclose(arquivo);
    return 0; // Código não existe
}

// Função para gerar o próximo código do passageiro
int gerarCodigoPassageiro() {
    FILE *arquivo = fopen("data/passageiros.dat", "rb");
    int ultimoCodigo = 0; // Começar com 0 caso o arquivo ainda não tenha passageiros

    if (arquivo == NULL) {
        return ultimoCodigo + 1; // Se o arquivo não existir, o código começa em 1
    }

    Passageiro p;
    while (fread(&p, sizeof(Passageiro), 1, arquivo)) {
        if (p.codigo > ultimoCodigo) {
            ultimoCodigo = p.codigo; // Atualiza o último código encontrado
        }
    }

    fclose(arquivo);
    return ultimoCodigo + 1; // Retorna o próximo código disponível
}

// Função para cadastrar um passageiro
// Função para cadastrar um passageiro
void cadastrarPassageiro() {
    Passageiro p;
    int codigo = gerarCodigoPassageiro(); // Gerar código auto-incrementado

    printf("O codigo do passageiro gerado e: %d\n", codigo);
    p.codigo = codigo;

    // Solicitar o nome do passageiro com verificação
    do {
        printf("Digite o nome do passageiro: ");
        fgets(p.nome, sizeof(p.nome), stdin);
        p.nome[strcspn(p.nome, "\n")] = '\0'; // Remove o caractere de nova linha

        if (strlen(p.nome) == 0) {
            printf("O nome do passageiro nao pode estar vazio.\n");
        }
    } while (strlen(p.nome) == 0);

    // Solicitar o endereço do passageiro com verificação
    do {
        printf("Digite o endereco do passageiro: ");
        fgets(p.endereco, sizeof(p.endereco), stdin);
        p.endereco[strcspn(p.endereco, "\n")] = '\0';

        if (strlen(p.endereco) == 0) {
            printf("O endereco do passageiro nao pode estar vazio.\n");
        }
    } while (strlen(p.endereco) == 0);

    // Solicitar o telefone do passageiro com verificação
    do {
        printf("Digite o telefone do passageiro: ");
        fgets(p.telefone, sizeof(p.telefone), stdin);
        p.telefone[strcspn(p.telefone, "\n")] = '\0';

        if (strlen(p.telefone) == 0) {
            printf("O telefone do passageiro nao pode estar vazio.\n");
        }
    } while (strlen(p.telefone) == 0);

    // Inicializa o passageiro com 0 pontos e fidelidade "Não"
    p.pontosFidelidade = 0;
    strcpy(p.fidelidade, "Nao");

    salvarPassageiro(p);
    printf("Passageiro cadastrado com sucesso!\n");
}

// Função para salvar o passageiro no arquivo
void salvarPassageiro(Passageiro p) {
    FILE *arquivo = fopen("data/passageiros.dat", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de passageiros.\n");
        return;
    }

    // Verificar se o nome está sendo gravado corretamente antes de salvar
    printf("Nome a ser salvo: %s\n", p.nome);  // Verifica o nome antes de salvar

    fwrite(&p, sizeof(Passageiro), 1, arquivo);
    fclose(arquivo);
}

// Função para listar passageiros cadastrados
void listarPassageiros() {
    FILE *arquivo = fopen("data/passageiros.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de passageiros.\n");
        return;
    }

    Passageiro p;
    printf("\nPassageiros cadastrados:\n");
    while (fread(&p, sizeof(Passageiro), 1, arquivo)) {
        // Verificar os dados lidos do arquivo
        printf("Codigo: %d\n", p.codigo);
        printf("Nome: %s\n", p.nome);  // Exibe o nome como foi lido
        printf("Endereco: %s\n", p.endereco);
        printf("Telefone: %s\n", p.telefone);
        printf("Fidelidade: %s\n", p.fidelidade); // Exibe "Sim" ou "Nao"
        printf("Pontos de fidelidade: %d\n", p.pontosFidelidade);
        printf("---------------------------\n");
    }

    fclose(arquivo);
}

// Função para adicionar pontos de fidelidade a um passageiro
void adicionarPontosFidelidade(int codigo) {
    FILE *arquivo = fopen("data/passageiros.dat", "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de passageiros.\n");
        return;
    }

    Passageiro p;
    while (fread(&p, sizeof(Passageiro), 1, arquivo)) {
        if (p.codigo == codigo) {
            p.pontosFidelidade += 10;  // Adiciona 10 pontos de fidelidade

            // Se os pontos forem 10 ou mais, atualiza o status de fidelidade
            if (p.pontosFidelidade >= 10) {
                strcpy(p.fidelidade, "Sim");
            }

            fseek(arquivo, -sizeof(Passageiro), SEEK_CUR);  // Move o ponteiro para o local correto no arquivo
            fwrite(&p, sizeof(Passageiro), 1, arquivo);  // Atualiza os dados do passageiro no arquivo
            printf("Passageiro %d agora tem %d pontos de fidelidade.\n", p.codigo, p.pontosFidelidade);
            fclose(arquivo);
            return;
        }
    }

    printf("Passageiro nao encontrado.\n");
    fclose(arquivo);
}

// Função para buscar passageiros
void buscarPassageiro() {
    int escolha;
    printf("Buscar Passageiro por:\n");
    printf("1. Codigo\n");
    printf("2. Nome\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);
    
    FILE *arquivo = fopen(PASSAGEIROS_FILE, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de passageiros.\n");
        return;
    }

    Passageiro passageiro;
    int encontrado = 0;

    if (escolha == 1) {
        int codigo;
        printf("Digite o codigo do passageiro: ");
        scanf("%d", &codigo);

        while (fread(&passageiro, sizeof(Passageiro), 1, arquivo)) {
            if (passageiro.codigo == codigo) {
                printf("Codigo: %d | Nome: %s | Fidelidade: %s\n", passageiro.codigo, passageiro.nome, passageiro.fidelidade);
                encontrado = 1;
                break;
            }
        }
    } else if (escolha == 2) {
        char nome[100];
        printf("Digite o nome do passageiro: ");
        scanf(" %[^\n]s", nome);  // Lê a string com espaços

        while (fread(&passageiro, sizeof(Passageiro), 1, arquivo)) {
            if (strstr(passageiro.nome, nome) != NULL) {
                printf("Codigo: %d | Nome: %s | Fidelidade: %s\n", passageiro.codigo, passageiro.nome, passageiro.fidelidade);
                encontrado = 1;
            }
        }
    } else {
        printf("Opcao invalida!\n");
    }

    if (!encontrado) {
        printf("Passageiro nao encontrado.\n");
    }

    fclose(arquivo);
}
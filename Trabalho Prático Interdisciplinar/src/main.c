#include <stdio.h>
#include <stdlib.h>
#include "../include/tripulacao.h"
#include "../include/passageiro.h"
#include "../include/voo.h"
#include "../include/assento.h"  // Inclui o cabeçalho de assento
#include "../include/reserva.h"  // Inclui o cabeçalho de reserva

// Função para exibir o menu principal
void exibirMenu() {
    printf("\n----- Sistema de Gerenciamento de Voos -----\n");
    printf("1. Cadastrar Passageiro\n");
    printf("2. Listar Passageiros\n");
    printf("3. Cadastrar Membro da Tripulacao\n");
    printf("4. Listar Membros da Tripulacao\n");
    printf("5. Cadastrar Voo\n");
    printf("6. Listar Voos\n");
    printf("7. Cadastrar Assento\n");
    printf("8. Listar Assentos\n");
    printf("9. Liberar Assento\n");
    printf("10. Realizar Reserva\n"); 
    printf("11. Listar Voos por Passageiro\n");
    printf("12. Buscar Passageiro ou Membro da Tripulacao por Codigo ou Nome\n");
    printf("13. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int opcao;
    int sair = 0;

    while (!sair) {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado após scanf

        switch (opcao) {
            case 1:
                cadastrarPassageiro();
                break;
            case 2:
                listarPassageiros();
                break;
            case 3:
                cadastrarTripulacao();
                break;
            case 4:
                listarTripulacao();
                break;
            case 5:
                cadastrarVoo();
                break;
            case 6:
                listarVoos();
                break;
            case 7:
                cadastrarAssento();  // Função para cadastrar assento
                break;
            case 8:
                listarVoosAtivosParaEscolha();
                printf("Digite o codigo do voo para listar os assentos: ");
                int codigoVoo;
                scanf("%d", &codigoVoo);
                listarAssentos2(codigoVoo);
                break;
            case 9:
                listarVoos();
                printf("Digite o codigo do voo: ");
                scanf("%d", &codigoVoo);
                listarAssentos2(codigoVoo);
                char numeroAssento[5];
                printf("Digite o numero do assento: ");
                scanf("%s", numeroAssento);
                
                liberarAssento(codigoVoo, numeroAssento);
                break;
            case 10:
                reservarAssento();
                break;
            case 11:
                listarPassageiros(); // Exibe os passageiros disponíveis
                printf("Digite o codigo do passageiro: ");
                int codigoPassageiro;
                scanf("%d", &codigoPassageiro);
                listarReservasPorPassageiro(codigoPassageiro);
                break;
            case 12:
                printf("Buscar:\n");
                printf("1. Passageiro\n");
                printf("2. Tripulacao\n");
                printf("Escolha uma opcao: ");
                int tipoBusca;
                scanf("%d", &tipoBusca);

                if (tipoBusca == 1) {
                buscarPassageiro();  // Chama a função de busca de passageiros
                } else if (tipoBusca == 2) {
                buscarTripulacao();  // Chama a função de busca de tripulação
                } else {
                printf("Opcao invalida.\n");
                }
                break;
            case 13:
                sair = 1;
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }

    return 0;
}
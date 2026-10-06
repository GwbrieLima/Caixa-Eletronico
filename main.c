#include <stdio.h>
#include "conta.h"

int main() {
    int opcao;

    do {
        printf("\n========================================\n");
        printf("             CAIXA ELETRONICO\n");
        printf("========================================\n");
        printf("1 - Cadastrar conta\n");
        printf("2 - Consultar conta\n");
        printf("3 - Depositar\n");
        printf("4 - Sacar\n");
        printf("5 - Listar contas\n");
        printf("6 - Sair\n");
        printf("7 - Desativar conta\n");
        printf("8 - Reativar conta\n");
        printf("========================================\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                cadastrarConta();
                break;

            case 2:
                consultarConta();
                break;

            case 3:
                depositar();
                break;

            case 4:
                sacar();
                break;

            case 5:
                listarContas();
                break;

            case 6:
                printf("\nObrigado por utilizar o Caixa Eletronico!\n");
                break;

            case 7:
                alterarStatus(0);
                break;

            case 8:
                alterarStatus(1);
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 6);

    return 0;
}
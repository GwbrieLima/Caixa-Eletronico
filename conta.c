#include <stdio.h>
#include <string.h>
#include "conta.h"

void cadastrarConta() {
    FILE *arquivo;
    Conta conta, aux;

    arquivo = fopen("contas.dat", "ab+");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("\nNumero da conta: ");
    scanf("%d", &conta.numero);

    rewind(arquivo);

    while (fread(&aux, sizeof(Conta), 1, arquivo)) {
        if (aux.numero == conta.numero) {
            printf("Conta ja cadastrada!\n");
            fclose(arquivo);
            return;
        }
    }

    getchar();

    printf("Nome do titular: ");
    fgets(conta.titular, 100, stdin);
    conta.titular[strcspn(conta.titular, "\n")] = '\0';

    printf("CPF: ");
    fgets(conta.cpf, 15, stdin);
    conta.cpf[strcspn(conta.cpf, "\n")] = '\0';

    printf("Saldo inicial: R$ ");
    scanf("%f", &conta.saldo);

    if (conta.saldo < 0) {
        printf("Valor invalido!\n");
        fclose(arquivo);
        return;
    }

    conta.status = 1;

    fseek(arquivo, 0, SEEK_END);
    fwrite(&conta, sizeof(Conta), 1, arquivo);

    printf("Conta cadastrada com sucesso!\n");

    fclose(arquivo);
}

void consultarConta() {
    FILE *arquivo;
    Conta conta;
    int numero;
    int achou = 0;

    arquivo = fopen("contas.dat", "rb");

    if (arquivo == NULL) {
        printf("Nenhuma conta cadastrada!\n");
        return;
    }

    printf("\nDigite o numero da conta: ");
    scanf("%d", &numero);

    while (fread(&conta, sizeof(Conta), 1, arquivo)) {
        if (conta.numero == numero) {
            printf("\n================================\n");
            printf("             CONTA\n");
            printf("================================\n");
            printf("Numero: %d\n", conta.numero);
            printf("Titular: %s\n", conta.titular);
            printf("CPF: %s\n", conta.cpf);
            printf("Saldo: R$ %.2f\n", conta.saldo);

            if (conta.status == 1)
                printf("Status: ATIVA\n");
            else
                printf("Status: INATIVA\n");

            printf("================================\n");

            achou = 1;
            break;
        }
    }

    if (!achou)
        printf("Conta nao encontrada!\n");

    fclose(arquivo);
}

void depositar() {
    FILE *arquivo;
    Conta conta;
    int numero;
    int achou = 0;
    float valor;

    arquivo = fopen("contas.dat", "rb+");

    if (arquivo == NULL) {
        printf("Nenhuma conta cadastrada!\n");
        return;
    }

    printf("\nNumero da conta: ");
    scanf("%d", &numero);

    printf("Valor do deposito: R$ ");
    scanf("%f", &valor);

    if (valor <= 0) {
        printf("Valor invalido!\n");
        fclose(arquivo);
        return;
    }

    while (fread(&conta, sizeof(Conta), 1, arquivo)) {

        if (conta.numero == numero) {
            achou = 1;

            if (conta.status == 0) {
                printf("Conta inativa!\n");
                break;
            }

            conta.saldo += valor;

            fseek(arquivo, -sizeof(Conta), SEEK_CUR);
            fwrite(&conta, sizeof(Conta), 1, arquivo);

            printf("Deposito realizado com sucesso!\n");
            printf("Saldo atual: R$ %.2f\n", conta.saldo);

            break;
        }
    }

    if (!achou)
        printf("Conta nao encontrada!\n");

    fclose(arquivo);
}

void sacar() {
    FILE *arquivo;
    Conta conta;
    int numero;
    int achou = 0;
    float valor;

    arquivo = fopen("contas.dat", "rb+");

    if (arquivo == NULL) {
        printf("Nenhuma conta cadastrada!\n");
        return;
    }

    printf("\nNumero da conta: ");
    scanf("%d", &numero);

    printf("Valor do saque: R$ ");
    scanf("%f", &valor);

    if (valor <= 0) {
        printf("Valor invalido!\n");
        fclose(arquivo);
        return;
    }

    while (fread(&conta, sizeof(Conta), 1, arquivo)) {

        if (conta.numero == numero) {
            achou = 1;

            if (conta.status == 0) {
                printf("Conta inativa!\n");
                break;
            }

            if (valor > conta.saldo) {
                printf("Saldo insuficiente!\n");
                printf("Saldo disponivel: R$ %.2f\n", conta.saldo);
                break;
            }

            conta.saldo -= valor;

            fseek(arquivo, -sizeof(Conta), SEEK_CUR);
            fwrite(&conta, sizeof(Conta), 1, arquivo);

            printf("Saque realizado com sucesso!\n");
            printf("Saldo atual: R$ %.2f\n", conta.saldo);

            break;
        }
    }

    if (!achou)
        printf("Conta nao encontrada!\n");

    fclose(arquivo);
}

void listarContas() {
    FILE *arquivo;
    Conta conta;
    int encontrou = 0;

    arquivo = fopen("contas.dat", "rb");

    if (arquivo == NULL) {
        printf("\nNenhuma conta cadastrada!\n");
        return;
    }

    printf("\n========================================\n");
    printf("          CONTAS CADASTRADAS\n");
    printf("========================================\n");

    while (fread(&conta, sizeof(Conta), 1, arquivo)) {

        printf("Conta: %d\n", conta.numero);
        printf("Titular: %s\n", conta.titular);
        printf("CPF: %s\n", conta.cpf);
        printf("Saldo: R$ %.2f\n", conta.saldo);

        if (conta.status == 1)
            printf("Status: ATIVA\n");
        else
            printf("Status: INATIVA\n");

        printf("----------------------------------------\n");

        encontrou = 1;
    }

    if (!encontrou)
        printf("Nenhuma conta cadastrada!\n");

    fclose(arquivo);
}

void alterarStatus(int status) {
    FILE *arquivo;
    Conta conta;
    int numero;
    int achou = 0;

    arquivo = fopen("contas.dat", "rb+");

    if (arquivo == NULL) {
        printf("Nenhuma conta cadastrada!\n");
        return;
    }

    printf("\nDigite o numero da conta: ");
    scanf("%d", &numero);

    while (fread(&conta, sizeof(Conta), 1, arquivo)) {

        if (conta.numero == numero) {
            achou = 1;

            conta.status = status;

            fseek(arquivo, -sizeof(Conta), SEEK_CUR);
            fwrite(&conta, sizeof(Conta), 1, arquivo);

            if (status == 1)
                printf("Conta reativada com sucesso!\n");
            else
                printf("Conta desativada com sucesso!\n");

            break;
        }
    }

    if (!achou)
        printf("Conta nao encontrada!\n");

    fclose(arquivo);
}
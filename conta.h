#ifndef CONTA_H
#define CONTA_H

typedef struct {
    int numero;
    char titular[100];
    char cpf[15];
    float saldo;
    int status;
} Conta;

void cadastrarConta();
void consultarConta();
void depositar();
void sacar();
void listarContas();
void alterarStatus(int status);

#endif
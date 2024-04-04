#define _GNU_SOURCE
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>

#define FIBER_STACK (1024 * 64)

struct c {
    int saldo;
};

typedef struct c conta;
conta from, to;
int valor;
int direcao;

int transferencia(void *arg) {
    if (direcao == 1 && from.saldo >= valor) {
        from.saldo -= valor;
        to.saldo += valor;
    }
   else if (direcao == - 1 && to.saldo >= valor){
        to.saldo -= valor;
        from.saldo += valor;}
    else {
        printf("Não há fundos para a transação!\n");
        return 0;
    }
    printf("Transferência concluída com sucesso!\n");
    printf("Saldo de c1: %d\n", from.saldo);
    printf("Saldo de c2: %d\n", to.saldo);
    return 0;
}

int main() {
    void *stack;
    pid_t pid;
    int i;
    int num_transacoes = 10; // Número de transações

    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 100;

    printf("\nInsira a direção da transação:\n c1 -> c2 (1)\n c2 -> c1 (-1)\n");
    scanf("%d", &direcao);
    while(abs(direcao) != 1){
        printf("\nInsira um valor válido!\n");
        scanf("%d", &direcao);
    }
    printf("\nInsira o valor a ser transferido:\n");
    scanf("%d", &valor);
    printf("\nInsira a quantidade de transações (máx 100):\n");
    scanf("%d", &num_transacoes);
    while(num_transacoes > 100 || num_transacoes < 0){
        printf("\nInsira um valor válido!\n");
        scanf("%d", &num_transacoes);
    }

    for (i = 0; i < num_transacoes; i++) {
        if (from.saldo < valor) {
            valor = from.saldo;
        }

        stack = malloc(FIBER_STACK);
        if (stack == NULL) {
            perror("malloc: could not allocate stack");
            exit(1);
        }

        pid = clone(transferencia, (char *)stack + FIBER_STACK,
                    SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);
        if (pid == -1) {
            perror("clone");
            exit(2);
        }
    }

    // Esperar pelo término de todos os processos filhos
    for (i = 0; i < num_transacoes; i++) {
        waitpid(-1, NULL, 0);
    }

    free(stack);

    printf("Transferências concluídas e memória liberada.\n");
    printf("\nSaldo final:\nc1 = %d\nc2 = %d\n", from.saldo, to.saldo);
    return 0;
}
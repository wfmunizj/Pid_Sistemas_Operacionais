#define _GNU_SOURCE
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>

#define FIBER_STACK (1024 * 64)

struct c
{
    int saldo;
};

typedef struct c conta;
conta from, to;
int valor;

int transferencia(void *arg)
{
    if (from.saldo >= valor)
    {
        from.saldo -= valor;
        to.saldo += valor;
    }
    else
    {
        to.saldo += from.saldo;
        from.saldo = 0;
    }
    printf("Transferência concluída com sucesso!\n");
    printf("Saldo de c1: %d\n", from.saldo);
    printf("Saldo de c2: %d\n", to.saldo);
    return 0;
}

int main()
{
    void *stack;
    pid_t pid;
    int i;
    int num_transacoes = 10; // Número de transações

    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 100;

    printf("Transferindo 10 para a conta c2\n");
    valor = 10;
    for (i = 0; i < num_transacoes; i++)
    {
        if (from.saldo < valor)
        {
            valor = from.saldo;
        }

        stack = malloc(FIBER_STACK);
        if (stack == NULL)
        {
            perror("malloc: could not allocate stack");
            exit(1);
        }

        pid = clone(transferencia, (char *)stack + FIBER_STACK,
                    SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);
        if (pid == -1)
        {
            perror("clone");
            exit(2);
        }
    }

    // Esperar pelo término de todos os processos filhos
    for (i = 0; i < num_transacoes; i++)
    {
        waitpid(-1, NULL, 0);
    }

    free(stack);

    printf("Transferências concluídas e memória liberada.\n");
    return 0;
}
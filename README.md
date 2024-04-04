# Simulação de Transferência Bancária

Este programa em C simula uma operação de transferência bancária entre duas contas. Ele cria várias threads usando a chamada de sistema `clone`, e cada thread realiza uma operação de transferência de uma conta para outra.

## Como compilar o programa

Para compilar este programa, você precisará de um compilador C instalado em seu sistema. Você pode usar o `gcc`, que é um compilador C comum disponível na maioria das distribuições Linux.

Aqui estão as etapas para compilar o programa:

1. Abra um terminal.
2. Navegue até o diretório que contém o arquivo do programa.
3. Execute o seguinte comando para compilar o programa:

```bash
gcc projeto.c -o projeto
````

Isso irá compilar o programa e criar um executável chamado projeto.

## Como executar o programa
Depois de compilar o programa, você pode executá-lo usando o seguinte comando no terminal:
```bash
./projeto
````

## Como comprovar que os resultados propostos foram alcançados

O programa imprime mensagens no console para indicar o progresso das transferências. Após cada transferência, ele imprime uma mensagem dizendo "Transferência concluída com sucesso!" e mostra os saldos das contas.

Além disso, este programa permite que você escolha a direção da transferência (de `c1` para `c2` ou de `c2` para `c1`), o valor a ser transferido e o número de transações a serem realizadas. Se a conta de origem não tiver fundos suficientes para a transação, o programa imprimirá uma mensagem "Não há fundos para a transação!".

Para verificar se os resultados propostos foram alcançados, você pode fazer o seguinte:

1. Verifique se o saldo da conta de origem é o (valor inicial - o valor total a ser transferido) ou não tem fundos suficientes para a transação após a execução do programa.
2. Verifique se o saldo da conta de destino aumentou pelo valor da transferência multiplicado pelo número de transações.
3. Verifique se o saldo total (soma dos saldos das contas `from` e `to`) permanece o mesmo após todas as transações.

Além disso, você pode ajustar o valor da transferência, a direção da transferência e o número de transações para testar diferentes cenários e verificar se o programa se comporta conforme esperado. 😊

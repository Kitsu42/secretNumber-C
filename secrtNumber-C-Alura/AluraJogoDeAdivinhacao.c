#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  

#define NUMERO_LIMITE 10
/* lembrete de corrigir os caracteres especiais */

bool eUmNumero(const char *str) {
    char *end;
    strtol(str, &end, 10);
    return *end == '\0';
}

void verificaChute(int x, int y, int tentativas) {
    if (x < y) {
        printf("Tente um número maior\n");
    } else if (x > y) {
        printf("Tente um número menor\n");
    } else {
        const char* s = (tentativas > 1) ? "s" : "";
        printf("Parabéns, você acertou com %d tentativa%s!\n", tentativas, s);
    }
}

void esperarPorTecla() {
    printf("Pressione Enter para sair...");
    getchar();
}

void printWithDelay(const char *str, unsigned int delay) {
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = delay * 1000;

    while (*str) {
        putchar(*str++);
        fflush(stdout);
        nanosleep(&ts, NULL);
    }
}

void cabecalho() {
    printWithDelay("******************************************\n", 500);
    printWithDelay("* Bem vindo ao nosso jogo de adivinhação *\n", 50000);
    printWithDelay("******************************************\n", 500);
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "*     Escolha um número entre 1 e %d     *\n", NUMERO_LIMITE);
    printWithDelay(buffer, 50000);
    printWithDelay("******************************************\n\n", 500);
}

void jogar(int secretNumber) {
    char input[100];
    int chute = 0;
    int tentativas = 1;

    while (1) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (eUmNumero(input)) {
            chute = atoi(input);
            verificaChute(chute, secretNumber, tentativas);

            if (chute == secretNumber) {
                break;
            } else {
                printf("Tente novamente: ");
                tentativas++;
            }
        } else {
            printf("Entrada inválida. Por favor, digite um número.\n");
        }
    }
}

int main() {
    srand(time(NULL));
    int secretNumber = (rand() % NUMERO_LIMITE) + 1;

    cabecalho();
    jogar(secretNumber);
    esperarPorTecla();

    return 0;
}
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/* lembrete de corrigir os caracteres especiais */
bool is_number(const char *str) {
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
void cabecalho (){
    printf("******************************************\n");
    printf("* Bem vindo ao nosso jogo de adivinhacao *\n");
    printf("******************************************\n");
    printf("Me diga um numero entre 1 e 10\n");
}

int main() {
    char input[100];
    int chute = 0;
    int tentativas = 1;

    srand(time(NULL));
    int secretNumber = (rand() % 10) + 1;

    cabecalho();

    while (1) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (is_number(input)) {
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

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[80];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;


//Criar salas
Sala* criarSala(const char* nome, Sala* esquerda, Sala* direita) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));

    if (!nova) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    strcpy(nova->nome, nome);
    nova->esquerda = esquerda;
    nova->direita = direita;

    return nova;
}

//Explorar salas
void explorarSalas(Sala* sala) {
    if (sala == NULL) return;

    printf("- %s\n", sala->nome);
    explorarSalas(sala->esquerda);
    explorarSalas(sala->direita);
}


// navegar pelo hall
void navegar_do_hall(Sala* sala) {
    Sala* atual = sala;
    char escolha[8];

    while (atual != NULL) {
        printf("\n Você está em: %s\n", atual->nome);

        // Nó folha → fim
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf(" Sala final alcançada. Fim do caminho.\n");
            break;
        }

        printf("\nEscolha seu caminho:\n");

        if (atual->esquerda)
            printf("  (1) Ir para %s\n", atual->esquerda->nome);
        if (atual->direita)
            printf("  (2) Ir para %s\n", atual->direita->nome);

        printf("\nDigite 1 ou 2: ");
        fgets(escolha, sizeof(escolha), stdin);

        // remover \n
        escolha[strcspn(escolha, "\n")] = '\0';

        if (strcmp(escolha, "1") == 0 && atual->esquerda) {
            atual = atual->esquerda;
        }
        else if (strcmp(escolha, "2") == 0 && atual->direita) {
            atual = atual->direita;
        }
        else {
            printf(" Escolha inválida. Tente novamente.\n");
        }
    }
}



int main() {

    // Salas folha
    Sala* biblioteca = criarSala("Biblioteca", NULL, NULL);
    Sala* cozinha = criarSala("Cozinha", NULL, NULL);
    Sala* jardim = criarSala("Jardim", NULL, NULL);
    Sala* laboratorio = criarSala("Laboratório Secreto", NULL, NULL);

    // Salas intermediárias
    Sala* corredor_norte = criarSala("Corredor Norte", biblioteca, cozinha);
    Sala* corredor_sul   = criarSala("Corredor Sul", jardim, laboratorio);

    // Sala raiz
    Sala* hall = criarSala("Hall de Entrada", corredor_norte, corredor_sul);

    printf("\n=== Estrutura completa da mansão ===\n");
    explorarSalas(hall);

    printf("\n=== Navegação interativa ===\n");
    navegar_do_hall(hall);

    return 0;
}


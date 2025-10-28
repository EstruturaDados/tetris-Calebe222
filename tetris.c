#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5

typedef struct {
    char tipo;
    int id;
} Peca;

Peca fila[TAMANHO_FILA];
int frente = 0;
int tras = 0;
int contador = 0;
int id_counter = 0;

Peca gerarPeca() {
    Peca nova_peca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int n_tipos = sizeof(tipos) / sizeof(tipos[0]);

    nova_peca.tipo = tipos[rand() % n_tipos];
    nova_peca.id = id_counter++;

    return nova_peca;
}

void inicializarFila() {
    frente = 0;
    tras = 0;
    contador = 0;
    for (int i = 0; i < TAMANHO_FILA; i++) {
        fila[tras] = gerarPeca();
        tras = (tras + 1) % TAMANHO_FILA;
        contador++;
    }
}

void visualizarFila() {
    printf("\n--- FILA ATUAL ---\n");
    if (contador == 0) {
        printf("(vazia)\n");
    } else {
        int index = frente;
        for (int i = 0; i < contador; i++) {
            printf("[%d: %c] ", fila[index].id, fila[index].tipo);
            index = (index + 1) % TAMANHO_FILA;
        }
        printf("\n");
    }
    printf("------------------\n");
}

void jogarPeca() {
    if (contador == 0) {
        printf("Fila vazia!\n");
        return;
    }

    Peca p = fila[frente];
    printf("Peça jogada: [%d: %c]\n", p.id, p.tipo);
    frente = (frente + 1) % TAMANHO_FILA;
    contador--;
}

void inserirPeca() {
    if (contador == TAMANHO_FILA) {
        printf("Fila cheia! Não é possível inserir.\n");
        return;
    }
    fila[tras] = gerarPeca();
    printf("Nova peça adicionada: [%d: %c]\n", fila[tras].id, fila[tras].tipo);
    tras = (tras + 1) % TAMANHO_FILA;
    contador++;
}

int main() {
    srand((unsigned)time(NULL));
    int opcao;

    inicializarFila();

    do {
        visualizarFila();

        printf("\n=== MENU ===\n");
        printf("1 - Jogar peça (remover da frente)\n");
        printf("2 - Inserir nova peça\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            // limpar entrada inválida
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                jogarPeca();
                inserirPeca(); // Mantém sempre 5 peças
                break;
            case 2:
                inserirPeca();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}


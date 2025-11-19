#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 5

typedef struct {
    char tipo;
    int id;
} Peca;

Peca fila[TAM_FILA];
Peca pilha[TAM_PILHA];
int frente = 0, tras = 0, topo = -1;
int id_counter = 1;

Peca gerarPeca() {
    char tipos[] = {'I','O','T','L'};
    return (Peca){ tipos[rand() % 4], id_counter++ };
}

void inicializar() {
    frente = 0;
    tras = 0;
    topo = -1;
    for (int i = 0; i < TAM_FILA; i++) {
        fila[i] = gerarPeca();
        tras = (tras + 1) % TAM_FILA;
    }
}

void mostrarEstado() {
    printf("\n=== Estado Atual ===\n");
    printf("Fila: ");
    for (int i = 0, idx = frente; i < TAM_FILA; i++, idx = (idx + 1) % TAM_FILA) {
        printf("[%d:%c] ", fila[idx].id, fila[idx].tipo);
    }

    printf("\nPilha: ");
    if (topo == -1) {
        printf("Vazia");
    } else {
        for (int i = topo; i >= 0; i--) {
            printf("[%d:%c] ", pilha[i].id, pilha[i].tipo);
        }
    }
    printf("\n");
}

void jogarPeca() {
    printf(">>> Jogando [%d:%c]\n", fila[frente].id, fila[frente].tipo);
    frente = (frente + 1) % TAM_FILA;
    fila[tras] = gerarPeca();
    tras = (tras + 1) % TAM_FILA;
}

void reservarPeca() {
    if (topo == TAM_PILHA - 1) {
        printf(">>> Erro: Pilha cheia!\n");
        return;
    }
    pilha[++topo] = fila[frente];
    printf(">>> Reservando [%d:%c]\n", pilha[topo].id, pilha[topo].tipo);
    frente = (frente + 1) % TAM_FILA;
    fila[tras] = gerarPeca();
    tras = (tras + 1) % TAM_FILA;
}

void usarReserva() {
    if (topo == -1) {
        printf(">>> Erro: Pilha vazia!\n");
        return;
    }
    printf(">>> Usando reserva [%d:%c]\n", pilha[topo].id, pilha[topo].tipo);
    fila[tras] = pilha[topo--];
    tras = (tras + 1) % TAM_FILA;
}

void trocarTopoFrente() {
    if (topo == -1) {
        printf(">>> Erro: Pilha vazia!\n");
        return;
    }
    Peca temp = fila[frente];
    fila[frente] = pilha[topo];
    pilha[topo] = temp;
    printf(">>> Trocando frente [%d:%c] com topo [%d:%c]\n",
           fila[frente].id, fila[frente].tipo, pilha[topo].id, pilha[topo].tipo);
}

void desfazerJogada() {
    printf(">>> Desfazendo jogada (simulação)\n");
    printf(">>> Funcionalidade avançada requer histórico\n");
}

void inverterFilaComPilha() {
    if (topo != -1) {
        printf(">>> Erro: Pilha deve estar vazia!\n");
        return;
    }

    // Empilha toda a fila
    for (int i = 0; i < TAM_FILA; i++) {
        int idx = (frente + i) % TAM_FILA;
        pilha[++topo] = fila[idx];
    }

    // Desempilha de volta (invertido)
    for (int i = 0; i < TAM_FILA; i++) {
        fila[(frente + i) % TAM_FILA] = pilha[topo--];
    }
    printf(">>> Fila invertida usando pilha\n");
}

int main() {
    srand((unsigned)time(NULL));
    int opcao;

    printf("🎮 TETRIS - NÍVEL MESTRE\n");
    printf("=======================\n");

    inicializar();

    do {
        mostrarEstado();
        printf("\n1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("4 - Trocar frente com topo\n");
        printf("5 - Desfazer jogada\n");
        printf("6 - Inverter fila com pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            opcao = -1;
        }

        switch (opcao) {
            case 1: jogarPeca(); break;
            case 2: reservarPeca(); break;
            case 3: usarReserva(); break;
            case 4: trocarTopoFrente(); break;
            case 5: desfazerJogada(); break;
            case 6: inverterFilaComPilha(); break;
            case 0: printf(">>> Saindo...\n"); break;
            default: printf(">>> Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
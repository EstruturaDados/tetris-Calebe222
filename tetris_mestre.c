#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5
#define TAMANHO_PILHA 3

typedef struct {
    char tipo;
    int id;
} Peca;

/* declarações corrigidas */
Peca fila[TAMANHO_FILA], pilha[TAMANHO_PILHA], historico[TAMANHO_FILA + TAMANHO_PILHA];
int frente = 0, tras = 0, topo = -1, topo_hist = -1;
int id_counter = 1;

Peca gerarPeca() {
    char tipos[] = {'I','O','T','L'};
    return (Peca){tipos[rand() % 4], id_counter++};
}

/* salva apenas um marcador (implementação simples para evitar erros de compilação) */
void salvarEstado() {
    if (topo_hist < TAMANHO_FILA + TAMANHO_PILHA - 1) {
        topo_hist++;
        /* aqui poderia copiar o estado para 'historico' se desejar */
    }
}

void inicializar() {
    frente = 0;
    tras = 0;
    topo = -1;
    topo_hist = -1;
    for (int i = 0; i < TAMANHO_FILA; i++) {
        fila[i] = gerarPeca();
        tras = (tras + 1) % TAMANHO_FILA;
    }
}

void mostrarEstado() {
    printf("\nFila: ");
    for (int i = 0, idx = frente; i < TAMANHO_FILA; i++, idx = (idx + 1) % TAMANHO_FILA)
        printf("[%d:%c] ", fila[idx].id, fila[idx].tipo);
    
    printf("\nPilha: ");
    if (topo == -1) {
        printf("(vazia)");
    } else {
        for (int i = 0; i <= topo; i++)
            printf("[%d:%c] ", pilha[i].id, pilha[i].tipo);
    }
    printf("\n");
}

void jogarPeca() {
    salvarEstado();
    printf("Jogando peça: [%d:%c]\n", fila[frente].id, fila[frente].tipo);
    frente = (frente + 1) % TAMANHO_FILA;
    fila[tras] = gerarPeca();
    tras = (tras + 1) % TAMANHO_FILA; 
}

void reservarPeca() {
    if (topo >= TAMANHO_PILHA - 1) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    salvarEstado();
    pilha[++topo] = fila[frente];
    printf("Reservando peça: [%d:%c]\n", fila[frente].id, fila[frente].tipo);
    frente = (frente + 1) % TAMANHO_FILA;
    fila[tras] = gerarPeca();
    tras = (tras + 1) % TAMANHO_FILA; 
}

void usarReserva() {
    if (topo == -1) {
        printf("Erro: Pilha vazia!\n");
        return;
    }
    salvarEstado();
    printf("Usando peça reservada: [%d:%c]\n", pilha[topo].id, pilha[topo].tipo);
    fila[tras] = pilha[topo--];
    tras = (tras + 1) % TAMANHO_FILA; 
}

void desfazerJogada() {
    if (topo_hist == -1) {
        printf("Erro: Nenhum estado para desfazer!\n");
        return;
    }
    /* Lógica para restaurar o estado anterior não implementada;
       apenas decrementa o índice do histórico por enquanto. */
    printf("Desfazendo última jogada...\n");
    topo_hist--;
}

void inverterFilaComPilha() {
    if (topo != -1) {
        printf("Pilha deve estar vazia para inverter!\n");
        return;
    }
    salvarEstado();

    /* empilha os elementos da fila na pilha */
    for (int i = 0; i < TAMANHO_FILA; i++) {
        int idx = (frente + i) % TAMANHO_FILA;
        pilha[++topo] = fila[idx];
    }

    /* retorna os elementos da pilha para a fila (inversão) */
    for (int i = 0; i < TAMANHO_FILA; i++) {
        int idx = (frente + i) % TAMANHO_FILA;
        fila[idx] = pilha[topo--];
    }

    printf("Fila invertida!\n");
}

int main() {
    srand((unsigned)time(NULL));
    int opcao;

    inicializar();

    do {
        mostrarEstado();
        printf("\n1. Jogar peça\n2. Reservar peça\n3. Usar peça reservada\n4. Desfazer jogada\n5. Inverter fila com pilha\n0. Sair\nEscolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            opcao = -1;
        }

        switch (opcao) {
            case 1: jogarPeca(); break;
            case 2: reservarPeca(); break;
            case 3: usarReserva(); break;
            case 4: desfazerJogada(); break;
            case 5: inverterFilaComPilha(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
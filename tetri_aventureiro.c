#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANO_FILA 5
#define TAMANHO_PILHA 3

typedef struct {
    char tipo;
    int id;
} Peca;

Peca fila[TAMANO_FILA];
Peca pilha[TAMANHO_PILHA];
int frente = 0;
int tras = 0;
int topo = -1;
int contador_fila = 0;
int id_counter = 0;

Peca gerarPeca() {
    Peca nova_peca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int n_tipos = sizeof(tipos) / sizeof(tipos[0]);

    nova_peca.tipo = tipos[rand() % n_tipos];
    nova_peca.id = id_counter++;

    return nova_peca;
}

void inicializarSistema() {
    for (int i = 0; i < TAMANO_FILA; i++) {
        fila[i] = gerarPeca();
        tras = (tras + 1) % TAMANO_FILA;
        contador_fila++;
    }
}

void visualizarEstado() {
    printf("\n=== ESTADO ATUAL ===\n");

    printf("Fila: ");
    if (contador_fila == 0) {
        printf("Vazia");
    } else {
        int index = frente;
        for (int i = 0; i < contador_fila; i++) {
            printf("[%d:%c] ", fila[index].id, fila[index].tipo);
            index = (index + 1) % TAMANO_FILA;
        }
    }

    printf("\nPilha: ");
    if (topo == -1) {
        printf("Vazia");
    } else {
        for (int i = 0; i <= topo; i++) {
            printf("[%d:%c] ", pilha[i].id, pilha[i].tipo);
        }
    }
    printf("\n===================\n");
}

void jogarPeca() {
    if (contador_fila == 0) {
        printf("Erro: Fila vazia!\n");
        return;
    }

    Peca peca_jogada = fila[frente];
    printf(">>> Jogando peça: [%d:%c]\n", peca_jogada.id, peca_jogada.tipo);

    frente = (frente + 1) % TAMANO_FILA;
    contador_fila--;

    if (contador_fila < TAMANO_FILA) {
        fila[tras] = gerarPeca();
        printf(">>> Nova peça gerada para a fila: [%d:%c]\n", fila[tras].id, fila[tras].tipo);
        tras = (tras + 1) % TAMANO_FILA;
        contador_fila++;
    }
}

void reservarPeca() {
    if (contador_fila == 0) {
        printf("Erro: Nenhuma peça para reservar!\n");
        return;
    }

    if (topo >= TAMANHO_PILHA - 1) {
        printf("Erro: Pilha de reserva cheia! (Máx: %d)\n", TAMANHO_PILHA);
        return;
    }

    Peca peca_reservada = fila[frente];
    topo++;
    pilha[topo] = peca_reservada;

    printf(">>> Reservando peça: [%d:%c]\n", peca_reservada.id, peca_reservada.tipo);

    frente = (frente + 1) % TAMANO_FILA;
    contador_fila--;

    if (contador_fila < TAMANO_FILA) {
        fila[tras] = gerarPeca();
        printf(">>> Nova peça gerada para a fila: [%d:%c]\n", fila[tras].id, fila[tras].tipo);
        tras = (tras + 1) % TAMANO_FILA;
        contador_fila++;
    }
}

void usarPecaReservada() {
    if (topo == -1) {
        printf("Erro: Pilha de reserva vazia!\n");
        return;
    }

    Peca peca_usada = pilha[topo];
    topo--;

    printf(">>> Usando peça reservada: [%d:%c]\n", peca_usada.id, peca_usada.tipo);

    fila[tras] = peca_usada;
    tras = (tras + 1) % TAMANO_FILA;
    contador_fila++;
}

int main() {
    srand((unsigned)time(NULL));
    int opcao;
    
    printf("🎮 TETRIS - Sistema de Fila com Reserva\n");
    printf("=======================================\n");
    
    inicializarSistema();
    
    do {
        visualizarEstado();
        
        printf("\n📋 MENU DE OPÇÕES:\n");
        printf("1 - Jogar peça da fila\n");
        printf("2 - Reservar peça da frente\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair do jogo\n");
        printf("\nEscolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            opcao = -1;
        }
        
        switch (opcao) {
            case 1:
                jogarPeca();
                break;
            case 2:
                reservarPeca();
                break;
            case 3:
                usarPecaReservada();
                break;
            case 0:
                printf("\n🎊 Obrigado por jogar! Até a próxima! 🎊\n");
                break;
            default:
                printf("❌ Opção inválida! Tente novamente.\n");
        }
        
        printf("\n");
        
    } while (opcao != 0);
    
    return 0;
}



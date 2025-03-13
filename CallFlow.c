#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAMADAS 100

typedef struct {
    char numero[15];
    char dia[11]; // Formato: DD/MM/AAAA
    char horario[6]; // Formato: HH:MM
} Chamada;

typedef struct {
    Chamada chamadas[MAX_CHAMADAS];
    int frente;
    int tras;
} FilaChamadas;

void inicializarFila(FilaChamadas *fila) {
    fila->frente = -1;
    fila->tras = -1;
}

int filaVazia(FilaChamadas *fila) {
    return fila->frente == -1;
}

int filaCheia(FilaChamadas *fila) {
    return (fila->tras + 1) % MAX_CHAMADAS == fila->frente;
}

void adicionarChamada(FilaChamadas *fila, Chamada chamada) {
    if (filaCheia(fila)) {
        printf("Erro: Fila de chamadas cheia.\n");
        return;
    }

    if (filaVazia(fila)) {
        fila->frente = 0;
    }

    fila->tras = (fila->tras + 1) % MAX_CHAMADAS;
    fila->chamadas[fila->tras] = chamada;
    printf("Chamada adicionada com sucesso.\n");
}

void removerChamada(FilaChamadas *fila) {
    if (filaVazia(fila)) {
        printf("Erro: Fila de chamadas vazia.\n");
        return;
    }

    if (fila->frente == fila->tras) {
        inicializarFila(fila);
    } else {
        fila->frente = (fila->frente + 1) % MAX_CHAMADAS;
    }
    printf("Chamada removida com sucesso.\n");
}

void listarChamadas(FilaChamadas *fila) {
    if (filaVazia(fila)) {
        printf("Fila de chamadas vazia.\n");
        return;
    }

    printf("Lista de chamadas:\n");
    int i = fila->frente;
    do {
        printf("Número: %s, Dia: %s, Horário: %s\n",
               fila->chamadas[i].numero,
               fila->chamadas[i].dia,
               fila->chamadas[i].horario);
        i = (i + 1) % MAX_CHAMADAS;
    } while (i != (fila->tras + 1) % MAX_CHAMADAS);
}

int main() {
    FilaChamadas fila;
    inicializarFila(&fila);

    int opcao;
    Chamada novaChamada;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar chamada\n");
        printf("2. Remover chamada\n");
        printf("3. Listar chamadas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o número: ");
                scanf("%s", novaChamada.numero);
                printf("Digite o dia (DD/MM/AAAA): ");
                scanf("%s", novaChamada.dia);
                printf("Digite o horário (HH:MM): ");
                scanf("%s", novaChamada.horario);
                adicionarChamada(&fila, novaChamada);
                break;
            case 2:
                removerChamada(&fila);
                break;
            case 3:
                listarChamadas(&fila);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
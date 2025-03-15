#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>

#define MAX_CHAMADAS 100

typedef struct {
    char numero[15];
    char dia[11];
    char horario[6];
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
        mvprintw(LINES - 1, 0, "Erro: Fila de chamadas cheia.");
        refresh();
        getch();
        return;
    }

    if (filaVazia(fila)) {
        fila->frente = 0;
    }

    fila->tras = (fila->tras + 1) % MAX_CHAMADAS;
    fila->chamadas[fila->tras] = chamada;
    mvprintw(LINES - 1, 0, "Chamada adicionada com sucesso.");
    refresh();
    getch();
}

void removerChamada(FilaChamadas *fila) {
    if (filaVazia(fila)) {
        mvprintw(LINES - 1, 0, "Erro: Fila de chamadas vazia.");
        refresh();
        getch();
        return;
    }

    if (fila->frente == fila->tras) {
        inicializarFila(fila);
    } else {
        fila->frente = (fila->frente + 1) % MAX_CHAMADAS;
    }
    mvprintw(LINES - 1, 0, "Chamada removida com sucesso.");
    refresh();
    getch();
}

void listarChamadas(FilaChamadas *fila) {
    if (filaVazia(fila)) {
        mvprintw(LINES - 1, 0, "Fila de chamadas vazia.");
        refresh();
        getch();
        return;
    }

    clear();
    mvprintw(0, 0, "Lista de chamadas:");

    int i = fila->frente;
    int linha = 2;
    do {
        mvprintw(linha, 0, "Número: %s, Dia: %s, Horário: %s",
                 fila->chamadas[i].numero,
                 fila->chamadas[i].dia,
                 fila->chamadas[i].horario);
        i = (i + 1) % MAX_CHAMADAS;
        linha++;
    } while (i != (fila->tras + 1) % MAX_CHAMADAS);

    refresh();
    getch();
}

int main() {
    FilaChamadas fila;
    inicializarFila(&fila);

    initscr();
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));

    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_BLUE, COLOR_BLACK);

    char titulo[] = "CallFlow";
    int linha = LINES / 2 - 1;
    int coluna = COLS / 2 - strlen(titulo) / 2;

    for (int i = 0; i < strlen(titulo); i++) {
        switch (i) {
            case 0: attron(COLOR_PAIR(2)); break;
            case 1: attron(COLOR_PAIR(3)); break;
            case 2: attron(COLOR_PAIR(4)); break;
            case 3: attron(COLOR_PAIR(5)); break;
            case 4: attron(COLOR_PAIR(6)); break;
            case 5: attron(COLOR_PAIR(7)); break;
            case 6: attron(COLOR_PAIR(2)); break;
            case 7: attron(COLOR_PAIR(3)); break;
        }

        mvprintw(linha, coluna + i, "%c", titulo[i]);
        refresh();
        usleep(200000);
    }
    attroff(COLOR_PAIR(2));
    attroff(COLOR_PAIR(3));
    attroff(COLOR_PAIR(4));
    attroff(COLOR_PAIR(5));
    attroff(COLOR_PAIR(6));
    attroff(COLOR_PAIR(7));

    getch();

    int opcao;
    Chamada novaChamada;

    do {
        clear();
        mvprintw(0, 0, "Sistema de Gerenciamento de Chamadas");
        mvprintw(2, 0, "1. Adicionar chamada");
        mvprintw(3, 0, "2. Remover chamada");
        mvprintw(4, 0, "3. Listar chamadas");
        mvprintw(5, 0, "0. Sair");
        mvprintw(7, 0, "Escolha uma opção: ");
        refresh();

        opcao = getch() - '0';

        switch (opcao) {
            case 1:
                clear();
                mvprintw(0, 0, "Digite o número: ");
                getstr(novaChamada.numero);
                mvprintw(1, 0, "Digite o dia (DD/MM/AAAA): ");
                getstr(novaChamada.dia);
                mvprintw(2, 0, "Digite o horário (HH:MM): ");
                getstr(novaChamada.horario);
                adicionarChamada(&fila, novaChamada);
                break;
            case 2:
                removerChamada(&fila);
                break;
            case 3:
                listarChamadas(&fila);
                break;
            case 0:
                break;
            default:
                mvprintw(LINES - 1, 0, "Opção inválida.");
                refresh();
                getch();
        }
    } while (opcao != 0);

    endwin();
    return 0;
}
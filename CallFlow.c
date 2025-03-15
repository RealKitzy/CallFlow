#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h> // Para a função usleep

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

// ... (as outras funções permanecem as mesmas)

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

    // Animação do título "CallFlow"
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
        attroff(COLOR_PAIR(2));
        attroff(COLOR_PAIR(3));
        attroff(COLOR_PAIR(4));
        attroff(COLOR_PAIR(5));
        attroff(COLOR_PAIR(6));
        attroff(COLOR_PAIR(7));
        refresh();
        usleep(200000); // Pausa de 200 milissegundos
    }

    getch();

    // ... (o restante do código permanece o mesmo)

    endwin();
    return 0;
}
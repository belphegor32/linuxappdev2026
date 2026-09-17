#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>


#define DX 7
#define DY 3


int main(int argc, char* argv[]) {
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    WINDOW *frame, *win;
    int c = 0;
    int win_height, win_width;


    file = fopen(argv[1], "r");

    setlocale(LC_ALL, "");

    initscr();
    noecho();
    cbreak();
    printw("%s", argv[1]);
    refresh();

    frame = newwin(LINES - 2*DY, COLS - 2*DX, DY, DX);
    box(frame, 0, 0);
    mvwaddnstr(frame, 0, 2, argv[1], COLS - 2*DX - 4);
    wrefresh(frame);

    win = newwin(LINES - 2*DY - 2, COLS - 2*DX - 2, DY + 1, DX + 1);

    keypad(win, TRUE);
    scrollok(win, TRUE);

    win_height = LINES - 2*DY - 2;
    win_width = COLS - 2*DX - 2;

    
    for (int i =0; i < win_height; i++){
        if(getline(&line, &len, file) == -1){
            break;
        }

        for (int i = 0; line[i] != '\0'; ++i) {
            if (line[i] == '\n' || line[i] == '\r'){
                line[i] = '\0';
                break;
            }
        }

        if (i != 0){
            wprintw(win, "\n");
        }


        // "%.*s" вывести не более win-width-1 символов
        wprintw(win, "%.*s", win_width - 1, line);

    }
    wrefresh(win);

    while((c = wgetch(win)) != 27) {
        if (c != ' '){
            continue;
        }

        if (getline(&line, &len, file) == -1){
            continue;
        }

        for (int i = 0; line[i] != '\0'; ++i) {
            if (line[i] == '\n' || line[i] == '\r'){
                line[i] = '\0';
                break;
            }
        }

        wprintw(win, "\n%.*s", win_width - 1, line);
        wrefresh(win);
    }


    delwin(win);
    delwin(frame);
    free(line);
    fclose(file);
    return 0;
}
#include <ncurses.h>

#include "window.h"

WINDOW *input_window;
WINDOW *comp1;
WINDOW *comp2;
WINDOW *comp3;
WINDOW *comp4;
int count = 0;

int max_x;
int max_y;

void render_title() {
    mvprintw(0, 0, "Space Team");
}

void render_prompt() {
    mvwprintw(input_window, 0, 0, "> ");
    wrefresh(input_window);
}

void render_comps() {
    wborder(comp1, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(comp2, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(comp3, '|', '|', '-', '-', '+', '+', '+', '+');
    wborder(comp4, '|', '|', '-', '-', '+', '+', '+', '+');
    
}

void get_input(char *dest) {
    render_prompt();
    wgetnstr(input_window, dest, 255);
    mvwprintw(input_window, 0, 0, "%*s", max_x, " ");
}

void init_screen() {
    initscr();

    getmaxyx(stdscr, max_y, max_x);
    input_window = newwin(1, max_x, max_y-1, 0);
    comp1 = newwin(max_y / 4 + 2, 2 * max_x / 5 , 3, 3);
    comp2 = newwin(max_y / 4 + 2, 2 * max_x / 5 , 3, (max_x / 2) + 2);
    comp3 = newwin(max_y / 4 + 2, 2 * max_x / 5 , (max_y / 2) , 3);
    comp4 = newwin(max_y / 4 + 2, 2 * max_x / 5 , (max_y / 2) , (max_x / 2) + 2);

    render_title();
    render_prompt();
    render_comps();

    refresh();
    wrefresh(input_window);
    wrefresh(comp1);
    wrefresh(comp2);
    wrefresh(comp3);
    wrefresh(comp4);

}

void clear_screen() {
    //int i;
    //for (i = 2; i < 3; i++) {
    //    move(i, 0);
    //    clrtoeol();
    //}
    move(1, 0);
    clrtoeol();
    move(2,0);
    clrtoeol();
}

void addPanels(char *buffer){
    int x;
    int y;
    WINDOW *mod;
    switch (count){
        case 0:
            mod = comp1;
            count++;
            break;
        case 1:
            mod = comp2;
            count++;
            break;
        case 2:
            mod = comp3;
            count++;
            break;
        case 3:
            mod = comp4;
            count = 0;
            break;
    }
    getyx(mod, y, x);
    mvwprintw(mod, 2, 2, "%s", buffer);
}

void update_screen(int time, char *buffer) {
    int x;
    int y;
    
    getyx(input_window, y, x);
    clear_screen();

    if (time == -1)
        mvprintw(1, 0, "Command: %s", buffer);
    else
        mvprintw(1, 0, "Command: \t\t Time : %s", time);
    
    render_prompt();

    wmove(input_window, y, x);
    refresh();
    wrefresh(input_window);
}



/*
int main() {
    init_screen();
    while (1) {
        char buffer[256] = {};
        get_input(buffer);
        if (*buffer) {
            update_screen(buffer);
        }
    }
}
*/
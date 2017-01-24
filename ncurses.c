#include <ncurses.h>

WINDOW *input_window;
int max_x;
int max_y;

void render_title() {
    mvprintw(0, 0, "Title");
}

void render_prompt() {
    mvwprintw(input_window, 0, 0, "> ");
    wrefresh(input_window);
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

    render_title();
    render_prompt();

    refresh();
    wrefresh(input_window);
}

void clear_screen() {
    int i;
    for (i = 1; i < max_y-2; i++) {
        move(i, 0);
        clrtoeol();
    }
}

void update_screen(char *buffer) {
    int x;
    int y;
    getyx(input_window, y, x);
    clear_screen();

    mvprintw(1, 0, "Input: %s", buffer);
    render_prompt();

    wmove(input_window, y, x);
    refresh();
    wrefresh(input_window);
}

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

#ifndef NCURSES_H
#define NCURSES_H

void render_title();

void render_prompt();

void get_input(char *dest);

void init_screen();

void clear_screen();

void update_screen(char *buffer);




#endif
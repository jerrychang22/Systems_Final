#ifndef WINDOW_H
#define WINDOW_H

void render_title();

void render_prompt();

void render_comps();

void get_input(char *dest);

void init_screen();

void clear_screen();

void addPanels(char *buffer);

void update_screen(int time, char *buffer);

#endif
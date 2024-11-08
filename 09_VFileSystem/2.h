#ifndef 2_H
#define 2_H

#include <curses.h>
#include <dirent.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>

void init_wins();
int read_directory(const char *path, char **files, int *count);
void mainloop();
void print_list(WINDOW *current_window, int current_files_count,
                int current_highlighted, int current_offset,
                char **current_files);

#endif

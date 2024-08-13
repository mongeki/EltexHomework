#include "2.h"

extern WINDOW *left;
extern WINDOW *right;
extern WINDOW *help_window;
extern int rows;
extern int cols;

void init_wins() {
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *)&size);
  rows = size.ws_row - 3;
  cols = size.ws_col - 2;
  left = newwin(rows, cols / 2 - 1, 0, 0);
  right = newwin(rows, cols / 2 - 1, 0, cols / 2);
  help_window = newwin(3, cols, size.ws_row - 3, 0);
}

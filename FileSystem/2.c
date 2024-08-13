#include "2.h"

WINDOW *left;
WINDOW *right;
WINDOW *help_window;
int rows;
int cols;

int main() {
  /* ncurses preparations */
  initscr();
  cbreak();
  curs_set(0);
  refresh();

  /* Left and right windows initialization */
  init_wins();

  /* Helper */
  mvwprintw(help_window, 1, 1, "Switch windows - TAB, Exit - F10");
  wrefresh(help_window);

  /* Main loop */
  mainloop();

  /* Closing program */
  delwin(left);
  delwin(right);
  delwin(help_window);
  refresh();
  endwin();
  exit(EXIT_SUCCESS);
  return 0;
}

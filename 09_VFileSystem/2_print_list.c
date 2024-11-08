#include "2.h"

extern int rows;

void print_list(WINDOW *current_window, int current_files_count,
                int current_highlighted, int current_offset,
                char **current_files) {
  for (int i = 0;
       i < (current_files_count < rows - 2 ? current_files_count : rows - 2);
       ++i) {
    if (i == current_highlighted) {
      wattron(current_window, A_REVERSE);
    }
    mvwprintw(current_window, i + 1, 1, "%s\n",
              current_files[i + current_offset]);
    if (i == current_highlighted) {
      wattroff(current_window, A_REVERSE);
    }
  }
}

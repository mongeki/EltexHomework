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
WINDOW *left;
WINDOW *right;
WINDOW *help_window;
int rows;
int cols;

int main(int argc, char **argv) {
  initscr();
  cbreak();
  curs_set(0);
  refresh();

  init_wins();
  mvwprintw(help_window, 1, 1, "Switch windows - TAB, Exit - F10");
  wrefresh(help_window);
  mainloop();

  delwin(left);
  delwin(right);
  delwin(help_window);
  refresh();
  endwin();
  exit(EXIT_SUCCESS);
  return 0;
}

int read_directory(const char *path, char **files, int *count) {
  for (int i = 0; i < *count; ++i) {
    free(files[i]);
  }
  int newcount = 1;
  files[0] = strdup("/..");
  struct dirent *entry;
  DIR *dp = opendir(path);
  if (dp == NULL) {
    return 1;
  }
  while ((entry = readdir(dp)) != NULL) {
    if (entry->d_type == DT_DIR) {
      if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
        char tmp[1024] = "/";
        files[newcount++] = strdup(strcat(tmp, entry->d_name));
      }
    } else {
      files[newcount++] = strdup(entry->d_name);
    }
  }
  closedir(dp);
  *count = newcount;
  return 0;
}
void mainloop() {
  char lpath[1024] = "";
  char rpath[1024] = "";
  char *lfiles[1024];
  char *rfiles[1024];
  int lfcount = 0;
  int rfcount = 0;
  if (read_directory(".", lfiles, &lfcount) ||
      read_directory(".", rfiles, &rfcount)) {
    exit(1);
  }
  WINDOW *current_window = left;
  char *curpath = lpath;
  char **current_files = lfiles;
  int current_files_count = lfcount;
  int left_highlighted = 0;
  int right_highlighted = 0;
  int current_highlighted = left_highlighted;
  int choice;
  int left_offset = 0;
  int right_offset = 0;
  int current_offset = 0;
  print_list(left, current_files_count, current_highlighted, current_offset,
             current_files);
  print_list(right, current_files_count, current_highlighted, current_offset,
             current_files);
  scrollok(left, TRUE);
  scrollok(right, TRUE);
  while (1) {
    print_list(current_window, current_files_count, current_highlighted,
               current_offset, current_files);
    box(left, 0, 0);
    box(right, 0, 0);
    wrefresh(left);
    wrefresh(right);
    keypad(current_window, true);
    choice = wgetch(current_window);
    switch (choice) {
    case KEY_UP:
      if (current_highlighted > 0) {
        --current_highlighted;
      } else {
        if (current_offset) {
          --current_offset;
        }
      }
      break;
    case KEY_DOWN:
      if (current_highlighted + current_offset < current_files_count - 1) {
        current_highlighted == rows - 3 ? ++current_offset
                                        : ++current_highlighted;
      }
      break;
    case '\t':
      /* Switch windows, awful repeat code, could use pointers */
      if (current_window == left) {
        current_window = right;
        left_highlighted = current_highlighted;
        current_highlighted = right_highlighted;
        current_files = rfiles;
        lfcount = current_files_count;
        current_files_count = rfcount;
        curpath = rpath;
        left_offset = current_offset;
        current_offset = right_offset;
      } else {
        current_window = left;
        right_highlighted = current_highlighted;
        current_highlighted = left_highlighted;
        current_files = lfiles;
        rfcount = current_files_count;
        current_files_count = lfcount;
        curpath = lpath;
        right_offset = current_offset;
        current_offset = left_offset;
      }
      break;

    default:
      break;
    }
    if (choice == 10) {
      if (current_files[current_offset + current_highlighted][0] == '/') {
        if (strcmp(current_files[current_offset + current_highlighted],
                   "/..") == 0 &&
            strlen(curpath) == 0) {
          strcat(curpath, "..");
        } else {
          strcat(curpath, current_files[current_offset + current_highlighted]);
        }
        read_directory(curpath, current_files, &current_files_count);
        wclear(current_window);
        current_highlighted = 0;
        current_offset = 0;
        if (current_window == left) {
          left_highlighted = 0;
        } else {
          right_highlighted = 0;
        }
      }
    } else if (choice == KEY_F(10)) {
      break;
    }
  }
  for (int i = 0; i < rfcount; ++i) {
    free(rfiles[i]);
  }
  for (int i = 0; i < lfcount; ++i) {
    free(lfiles[i]);
  }
}
void init_wins() {
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *)&size);
  rows = size.ws_row - 3;
  cols = size.ws_col - 2;
  left = newwin(rows, cols / 2 - 1, 0, 0);
  right = newwin(rows, cols / 2 - 1, 0, cols / 2);
  help_window = newwin(3, cols, size.ws_row - 3, 0);
}
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

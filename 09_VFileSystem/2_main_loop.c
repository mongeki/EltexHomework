#include "2.h"

extern WINDOW *left;
extern WINDOW *right;
extern WINDOW *help_window;
extern int rows;
extern int cols;

void mainloop() {
  char lpath[1024] = ""; // Relevant path to dir on leftside
  char rpath[1024] = ""; // Relevant path to dir on rightside
  char *lfiles[1024];    // List of files in leftside directory
  char *rfiles[1024];    // List of files in rightside directory

  int lfcount = 0; // Count of files in leftside directory
  int rfcount = 0; // Count of files in rightside directory
  if (read_directory(".", lfiles, &lfcount) ||
      read_directory(".", rfiles, &rfcount)) {
    exit(1);
  }
  WINDOW *current_window = left; // Pointers to the working window attrs
  char *curpath = lpath;
  char **current_files = lfiles;
  int current_files_count = lfcount; // Vars with stored working window attrs
                                     // (should've use pointers too)
  int left_highlighted = 0;
  int right_highlighted = 0;
  int current_highlighted = left_highlighted;
  int choice;
  int left_offset = 0;
  int right_offset = 0;
  int current_offset = 0;

  /* Printing windows */
  print_list(left, current_files_count, current_highlighted, current_offset,
             current_files);
  print_list(right, current_files_count, current_highlighted, current_offset,
             current_files);

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
    case '\t': // Tab button handle
      /* Switch windows, awful repeat code, should've use pointers */
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
    if (choice == 10) { // Enter button handle
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
      if (current_window == left) {
        lfcount = current_files_count;
      } else {
        rfcount = current_files_count;
      }
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

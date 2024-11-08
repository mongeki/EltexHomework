#include "2.h"

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

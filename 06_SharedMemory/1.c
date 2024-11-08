#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EMPTY \
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

struct abonent {
  char name[10];
  char second_name[10];
  char tel[10];
};

void add(struct abonent* phonebook, int index);
void print_all(struct abonent* phonebook, int size);
void print_menu();
void find(struct abonent* phonebook, int size);
int delete_abonent(struct abonent* phonebook, int size);

int main() {
  int size = 0;
  struct abonent* phonebook;
  int not_ended = 1;
  while (not_ended) {
    print_menu();
    int item;
    if (scanf("%d", &item) == 1) {
      switch (item) {
        case 1:
          ++size;
          if (size == 1)
            phonebook = malloc(sizeof(struct abonent) * size);
          else if (size > 1)
            phonebook = realloc(phonebook, sizeof(struct abonent) * size);
          add(phonebook, size);
          break;
        case 2:
          int deleted_count = delete_abonent(phonebook, size);
          size -= deleted_count;
          if (deleted_count)
            phonebook = realloc(phonebook, sizeof(struct abonent) * size);
          break;
        case 3:
          find(phonebook, size);
          break;
        case 4:
          print_all(phonebook, size);
          break;
        case 5:
          not_ended = 0;
          break;
        default:
          break;
      }
    } else {
      int c;
      while ((c = getchar()) != '\n' && c != EOF) {
      }
    }
  }
  if (size) free(phonebook);
  exit(EXIT_SUCCESS);
}

int delete_abonent(struct abonent* phonebook, int size) {
  int deleted_count = 0;
  char to_delete[10];
  printf("Введите имя абонента для удаления\n");
  scanf("%s", to_delete);
  for (int i = 0; i < size; ++i) {
    if (strcmp(phonebook[i].name, to_delete) == 0) {
      for (int j = i; j < size - 1; ++j) {
        strcpy(phonebook[j].name, phonebook[j + 1].name);
        strcpy(phonebook[j].second_name, phonebook[j + 1].second_name);
        strcpy(phonebook[j].tel, phonebook[j + 1].tel);
        --size;
        ++deleted_count;
      }
    }
  }
  printf("Удалено %d совпадений\n", deleted_count);
  return deleted_count;
}

void print_menu() {
  printf(
      "-------------------------\n"
      "1. Добавить абонента\n2. Удалить абонента\n3. Поиск абонентов по "
      "имени\n4. Вывод всех записей\n5. Выход\n"
      "-------------------------\n");
}

void add(struct abonent* phonebook, int index) {
  printf("Введите имя:\n");
  scanf("%s", phonebook[index - 1].name);
  printf("Введите фамилию:\n");
  scanf("%s", phonebook[index - 1].second_name);
  printf("Введите номер телефона:\n");
  scanf("%s", phonebook[index - 1].tel);
  printf("Добавлено\n");
}

void find(struct abonent* phonebook, int size) {
  char str[10];
  int count = 0;
  scanf("%s", str);
  for (int i = 0; i < size; ++i) {
    if (strcmp(str, phonebook[i].name) == 0) {
      printf("%s, %s, %s\n", phonebook[i].name, phonebook[i].second_name,
             phonebook[i].tel);
      ++count;
    }
  }
  printf("Найдено %d совпадений\n", count);
}

void print_all(struct abonent* phonebook, int size) {
  char empty[] = EMPTY;
  for (int i = 0; i < size; ++i) {
    if (strcmp(phonebook[i].name, empty) != 0) {
      printf("%s %s %s\n", phonebook[i].name, phonebook[i].second_name,
             phonebook[i].tel);
    }
  }
  printf("Всего %d абонентов\n", size);
}

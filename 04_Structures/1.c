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

void add(struct abonent* phonebook);
void print_all(struct abonent* phonebook);
void print_menu();
void find(struct abonent* phonebook);
void initialize(struct abonent* phonebook);
int delete (struct abonent* phonebook);

int main() {
  int count = 0;
  struct abonent phonebook[100];
  initialize(phonebook);
  int not_ended = 1;
  while (not_ended) {
    print_menu();
    int item;
    if (scanf("%d", &item) == 1) {
      switch (item) {
        case 1:
          if (count == 100) {
            printf("Overflow\n");
          } else {
            add(phonebook);
            ++count;
          }
          break;
        case 2:
          count -= delete (phonebook);
          break;
        case 3:
          find(phonebook);
          break;
        case 4:
          print_all(phonebook);
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
  exit(EXIT_SUCCESS);
}
int delete (struct abonent* phonebook) {
  int deleted_count = 0;
  char to_delete[10];
  char empty[] = EMPTY;
  printf("Введите имя абонента для удаления\n");
  scanf("%s", to_delete);
  for (int i = 0; i < 100; ++i) {
    if (strcmp(phonebook[i].name, to_delete) == 0) {
      strcpy(phonebook[i].name, empty);
      strcpy(phonebook[i].second_name, empty);
      strcpy(phonebook[i].tel, empty);
      ++deleted_count;
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
void initialize(struct abonent* phonebook) {
  char empty[] = EMPTY;
  for (int i = 0; i < 100; ++i) {
    strcpy(phonebook[i].name, empty);
    strcpy(phonebook[i].second_name, empty);
    strcpy(phonebook[i].tel, empty);
  }
}
void add(struct abonent* phonebook) {
  int i = 0;
  char empty[] = EMPTY;
  for (; i < 100; ++i) {
    if (strcmp(phonebook[i].name, empty) == 0) {
      break;
    }
  }
  printf("Введите имя:\n");
  scanf("%s", phonebook[i].name);
  printf("Введите фамилию:\n");
  scanf("%s", phonebook[i].second_name);
  printf("Введите номер телефона:\n");
  scanf("%s", phonebook[i].tel);
  printf("Добавлено\n");
}
void find(struct abonent* phonebook) {
  char str[10];
  scanf("%s", str);
  for (int i = 0; i < 100; ++i) {
    if (strcmp(str, phonebook[i].name) == 0) {
      printf("%s, %s, %s\n", phonebook[i].name, phonebook[i].second_name,
             phonebook[i].tel);
    }
  }
}
void print_all(struct abonent* phonebook) {
  char empty[] = EMPTY;
  for (int i = 0; i < 100; ++i) {
    if (strcmp(phonebook[i].name, empty) != 0) {
      printf("%s %s %s\n", phonebook[i].name, phonebook[i].second_name,
             phonebook[i].tel);
    }
  }
}

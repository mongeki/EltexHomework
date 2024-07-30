#include <stdio.h>

#include "libcalc.h"

void print_menu();
void get_operands(int* a, int* b);
int main() {
  int choice = 0;
  int a, b;
  while (choice != 5) {
    print_menu();
    if (scanf("%d", &choice) == 1) {
      switch (choice) {
        case 1:
          get_operands(&a, &b);
          printf("Результат = %d\n", add(a, b));
          break;
        case 2:
          get_operands(&a, &b);
          printf("Результат = %d\n", sub(a, b));
          break;
        case 3:
          get_operands(&a, &b);
          printf("Результат = %d\n", mul(a, b));
          break;
        case 4:
          get_operands(&a, &b);
          printf("Результат = %d\n", div(a, b));
          break;
        case 5:
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
  return 0;
}

void print_menu() {
  printf(
      "----------------\n"
      "Выберите пункт\n1. Сложение\n2. Вычитание\n3. Умножение\n4. "
      "Деление\n5. Выход\n"
      "----------------\n");
}
void get_operands(int* a, int* b) {
  printf("Введите 2 целых числа\n");
  while (scanf("%d%d", a, b) != 2) {
    printf("Ведите 2 целых числа\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
  }
}

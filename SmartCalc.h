#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBERS "0123456789"
#define FUNCTIONS "sctlax"
#define SIMPLE "+-*/^"

typedef struct Calculator {
  int data; // Здесь будет хранится информация, если это операция/функция
  double value; // Здесь будет хранится число
  int priority; // Приоритетность(0 - число, 1 - +-, 2 - */mod, 3 - (,), 4 -
                // тригонометрия, логарифм, степень)
  struct Calculator *next; // указатель на след элемент(тк калькулятор - это
                           // список из элемнтов)
} calc;

typedef struct credit_calculator {
  // Вход
  double creditsum; // общая сумма кредита
  double term;      // срок
  double percent;   // процентная ставка
  int type; // 0 - аннуитетный 1 - дифференциальный
  // Выход
  double monthpay[1000]; // ежемесячный платеж
  double overpayment;    // переплата по кредиту
  double total;          // общая выплата
} credit_calc;

typedef struct deposit_calculator {
  // Вход
  double dsum;    // сумма вклада
  double term;    // срок размещения
  double percent; // процентная ставка
  double taxrate; // налоговая ставка
  int period; // периодичность выплат  // 1 - ежемесячная 3 - ежеквартальная 6 -
              // раз в полгода 12 - ежегодная
  int capitalization; // капитализация процентов // 0 - без капитализации // 1 -
                      // с капитализацией процентов
  double replenish_list[100]; // список пополнений
  double withdraw_list[100];  // список снятий
  // Выход
  double apercent; // начисленные проценты
  double taxsum;   // сумма налога
  double total;    // сумма на вкладе к концу срока
} deposit_calc;

void deposit_calculator(deposit_calc *data);
void credit_calculator(credit_calc *data);
int smart_calculator(char *str, double x, double *result);
int check_string(char *str);
int calculation(calc *stack, calc *string, double *result);
int notation(calc *source, calc *stack, calc **string);
void parser(char *str, calc **begin, double x);
void pop(calc **begin);
void insert_to_the_begin(calc **begin, calc *element);
void insert_to_the_end(calc **begin, calc *element);
calc *find_last_element(calc *begin);
calc *create_element(int data, double value, int priority);
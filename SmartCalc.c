#include "SmartCalc.h"

//______________РАБОТА СО СПИСКОМ - ВСПОМОГАТЕЛЬНЫЕ___________//

/**
 * @brief Создаем элемент структуры
 *
 * @param data информация об элементе - 0 - число, иначе - функция/операция
 * @param value если элемент - число, то здесь значение числа
 * @param priority приоритетность элемента
 * 0 - число
 * 1 - +-
 * 2 - * / mod
 * 3 - (,)
 * 4 - sin cos tan arcsin arccos arctan log ln sqrt ^
 * @return calc* элемент типа структуры
 */

calc *create_element(
    int data, double value,
    int priority) { // Выделяем память и заполняем данными элемент списка
  calc *tmp = (calc *)malloc(sizeof(calc));
  if (tmp) {
    tmp->data = data;
    tmp->value = value;
    tmp->priority = priority;
    tmp->next = NULL;
  }

  return tmp;
}

/**
 * @brief Найти последний элемент в списке
 *
 * @param begin указатель на начало
 * @return calc* указатель на последний элемент
 */
calc *
find_last_element(calc *begin) { // Возвращает указатель на последний элемент
  if (begin) {
    while (begin->next) {
      begin = begin->next;
    }
  }

  return begin;
}

/**
 * @brief Вставить элемент в конец списка
 *
 * @param begin указатель на начало списка
 * @param element указатель на элемент, который вставляем
 */
void insert_to_the_end(calc **begin,
                       calc *element) { // Вставка элемента в конец списка
  if (begin) {
    if (*begin) {
      calc *last = find_last_element(*begin);
      last->next = element;
    } else {
      *begin = element;
    }
  }
}

/**
 * @brief Вставить элемент в начало списка
 *
 * @param begin указатель на начало списка
 * @param element указатель на элемент, который вставляем
 */
void insert_to_the_begin(calc **begin,
                         calc *element) { // Вставка элемента перед самым первым
  if (begin) {
    if (*begin && element) {
      element->next = *begin;
      *begin = element;
    } else {
      if (element)
        *begin = element;
    }
  }
}

/**
 * @brief Убрать первый элемент в списке
 *
 * @param begin указатель на первый элемент в списке
 */
void pop(calc **begin) { // Убрать первый элемент
  if (begin) {
    if (*begin) {
      calc *tmp = (*begin)->next;
      free(*begin);
      *begin = tmp;
    }
  }
}

//____________ОСНОВНЫЕ ФУНКЦИИ______________//

/**
 * @brief Парсер строка -> список
 *
 * @param str считанная строка
 * @param begin указатель на начало списка - исходная строка
 * @param x значение x
 */

void parser(char *str, calc **begin,
            double x) { // Создадим список для калькулятора
  int minus = 0;
  int i = 0;
  double value = 0;
  while (str[i] != '\0') {
    if (strchr(NUMBERS, str[i])) {
      value = atof(str + i);
      if (minus == 1) {
        value *= -1;
        minus = 0;
      }

      for (int j = i; strchr("0123456789.", str[j]); j++, i++) {
        continue;
      }

      // Случай, когда после числа идет какая то функция сразу - это умножение
      // пример: 15cos(x) = 15 * cos(x)
      if (strchr(FUNCTIONS, str[i]) || strchr("(", str[i])) {
        insert_to_the_end(begin, create_element('*', 0, 2));
      }

      insert_to_the_end(begin, create_element(0, value, 0));
    }

    if (strchr("x", str[i])) {
      insert_to_the_end(begin, create_element(str[i], x, 0));
    }

    if (strchr("*/", str[i])) {
      insert_to_the_end(begin, create_element(str[i], 0, 2));
    }

    if (strchr("^", str[i])) {
      insert_to_the_end(begin, create_element(str[i], 0, 4));
    }

    if (strchr("+", str[i])) {
      // Случай, когда это первый символ или после открывающей скобки - то
      // опускаем Пример 20 - (+15cos(12) + 17) - 20 или +1345sqrt(x)
      if (strchr("(", str[i - 1]) || i == 0)
        continue;
      insert_to_the_end(begin, create_element(str[i], 0, 1));
    }

    if (strchr("-", str[i])) {
      // Случай, когда это первый символ или после открывающей скобки - то
      // отмечаем флаг Пример -(15cos(x) + 20) или -24 + 16788
      if (strchr("(", str[i - 1]) || i == 0)
        minus = 1;
      else
        insert_to_the_end(begin, create_element(str[i], 0, 1));
    }

    if (strchr("(", str[i])) {
      insert_to_the_end(begin, create_element(str[i], 0, 3));
    }

    if (strchr(")", str[i])) {
      insert_to_the_end(begin, create_element(str[i], 0, 3));
    }

    if (strchr("msctal", str[i])) {
      // printf("%c\n", str[i]);
      if (strncmp(str + i, "ln", 2) == 0) {
        insert_to_the_end(begin, create_element(str[i + 1], 0, 4));
        i += 1;
      } else {
        if (strncmp(str + i, "sqrt", 4) == 0 ||
            strncmp(str + i, "asin", 4) == 0 ||
            strncmp(str + i, "acos", 4) == 0 ||
            strncmp(str + i, "atan", 4) == 0) {
          insert_to_the_end(begin, create_element(str[i + 2], 0, 4));
          i += 3;
        } else {
          if (strncmp(str + i, "sin", 3) == 0 ||
              strncmp(str + i, "cos", 3) == 0 ||
              strncmp(str + i, "tan", 3) == 0 ||
              strncmp(str + i, "log", 3) == 0 ||
              strncmp(str + i, "mod", 3) == 0) {
            if (str[i] == 'm') {
              insert_to_the_end(begin, create_element(str[i], 0, 2));
            } else {
              insert_to_the_end(begin, create_element(str[i], 0, 4));
            }
            i += 2;
          }
        }
      }
    }

    i++;
  }
}

/**
 * @brief Сортировка - польская нотация
 * Перевод из инфиксной записи в обратную поьскую нотацию
 *
 * @param source Исходный список со всеми лесксемами, полученный после парсинга
 * @param stack стек(данные)
 * @param string выходная строка(лексемы)
 * @return int вернет ошибку
 * 0 - нет ошибки, перевод прошел успешно
 * 1 - возвращаем ошибку
 */
int notation(calc *source, calc *stack,
             calc **string) { // source - то, что мы получили после парсинга
                              // stack - стек
                              // string - выходная строка
  int error = 0;
  while (source) {
    if (source->priority == 0) { // число
      insert_to_the_end(string, create_element(source->data, source->value,
                                               source->priority));
    }

    if (source->priority == 4 ||
        source->data == '(') { // функция или открывающая скобка
      insert_to_the_begin(&stack, create_element(source->data, source->value,
                                                 source->priority));
    }

    if (source->priority == 1) {
      while (stack && (stack->priority == 1 || stack->priority == 2)) {
        insert_to_the_end(
            string, create_element(stack->data, stack->value, stack->priority));
        pop(&stack);
      }
      insert_to_the_begin(&stack, create_element(source->data, source->value,
                                                 source->priority));
    }

    if (source->priority == 2) {
      while (stack && (stack->priority == 2)) {
        insert_to_the_end(
            string, create_element(stack->data, stack->value, stack->priority));
        pop(&stack);
      }
      insert_to_the_begin(&stack, create_element(source->data, source->value,
                                                 source->priority));
    }

    if (source->data == ')') {
      while (stack && stack->data != '(') {
        insert_to_the_end(
            string, create_element(stack->data, stack->value, stack->priority));
        pop(&stack);
      }

      if (stack && stack->data == '(') {
        pop(&stack);
      } else {
        error = 1;
      }

      if (stack && stack->priority == 4) {
        insert_to_the_end(
            string, create_element(stack->data, stack->value, stack->priority));
        pop(&stack);
      }
    }

    pop(&source);
  }

  while (stack && stack->data != ')' && stack->data != '(') {
    insert_to_the_end(
        string, create_element(stack->data, stack->value, stack->priority));
    pop(&stack);
  }

  if (stack && (stack->data == '(' || stack->data == ')')) {
    error = 1;
    while (stack) {
      pop(&stack);
    }
  }
  return error;
}

/**
 * @brief Вычисление выражений
 *
 * @param stack Стек со значениями
 * @param string Выходная строка с лексемами(функциями и операциями)
 * @param result Результат вычислений(указатель на него)
 * @return int Ошибка
 * 0 - ошибки нет
 * 2 - деление на 0
 */
int calculation(calc *stack, calc *string, double *result) {
  // double result = 0.0;
  int error = 0;
  while (string) {
    if (string->data == 0 || string->data == 'x') {
      insert_to_the_begin(&stack, create_element(string->data, string->value,
                                                 string->priority));
      pop(&string);
    } // записали в стек ближайшее число

    // Вычисления
    if (string && string->data == '+') {
      stack->next->value += stack->value;
      pop(&stack);
      pop(&string);
    } else {
      if (string && string->data == '-') {
        stack->next->value -= stack->value;
        pop(&stack);
        pop(&string);
      } else {
        if (string && string->data == '*') {
          stack->next->value *= stack->value;
          pop(&stack);
          pop(&string);
        } else {
          if (string && string->data == '/') {
            if (stack->value == 0) {
              error = 2; // деление на 0
              break;
            } else {
              stack->next->value /= stack->value;
              pop(&stack);
              pop(&string);
            }
          } else {
            if (string && string->data == '^') {
              stack->next->value = powf(stack->next->value, stack->value);
              pop(&stack);
              pop(&string);
            } else {
              if (string && string->data == 'm') {
                stack->next->value = fmod(stack->next->value, stack->value);
                pop(&stack);
                pop(&string);
              } else {
                if (string && string->data == 's') {
                  stack->value = sin(stack->value);
                  pop(&string);
                } else {
                  if (string && string->data == 'c') {
                    stack->value = cos(stack->value);
                    pop(&string);
                  } else {
                    if (string && string->data == 't') {
                      stack->value = tan(stack->value);
                      pop(&string);
                    } else {
                      if (string && string->data == 'l') {
                        stack->value = log10(stack->value);
                        pop(&string);
                      } else {
                        if (string && string->data == 'n') {
                          stack->value = log(stack->value);
                          pop(&string);
                        } else {
                          if (string && string->data == 'i') {
                            stack->value = asin(stack->value);
                            pop(&string);
                          } else {
                            if (string && string->data == 'o') {
                              stack->value = acos(stack->value);
                              pop(&string);
                            } else {
                              if (string && string->data == 'a') {
                                stack->value = atan(stack->value);
                                pop(&string);
                              } else {
                                if (string && string->data == 'r') {
                                  stack->value = sqrt(stack->value);
                                  pop(&string);
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    *result = stack->value;
  }
  pop(&stack);
  return error;
}

/**
 * @brief Проверка входной строки на корректность ввода
 *
 * @param str Исходная строка
 * @return int Код ошибки
 * 0 - нет ошибки, строка корректна
 * 1 - ошибка
 */
int check_string(char *str) {
  int flag = 0;
  for (int i = 0; flag == 0 && str[i] != '\0'; i++) {
    if (!strchr("+-*/^mscatlx().0123456789", str[i])) {
      flag = 1;
    } else {
      if (strchr(".", str[i])) {
        if ((!strchr(NUMBERS, str[i - 1]) || !strchr(NUMBERS, str[i + 1]) ||
             !str[i - 1] || !str[i + 1])) {
          flag = 1; // если знак - точка, а по бокам от нее не цифры
        } else {
          int point = 0;
          for (int j = i + 1; strchr(NUMBERS, str[j]) || strchr(".", str[j]);
               j++) {
            if (str[j] == '.') {
              point++;
            }
          }
          if (point) {
            flag = 1;
          } // если во флоат числе больше одной точки
        }
      }

      if (strchr(SIMPLE, str[i]) &&
          ((!strchr("0123456789sctalx(", str[i + 1])) || !str[i - 1] ||
           !str[i + 1])) {
        flag = 1; // printf("4\n");
      } // если после +-*/^ не число или функция(например ++6, 7+--20)

      if (strchr("m", str[i])) {
        if (strstr(str + i, "mod")) {
          i += 2;
          if (!strchr("0123456789x(", str[i + 1]) ||
              !strchr("0123456789x)", str[i - 3]) || !str[i + 1] ||
              !str[i - 3]) {
            flag = 1;
          }
        } else {
          flag = 1;
        }

        // если у нас функция mod - сначала проверяем что функция правильно
        // написана если справа функции мод или слева не числа и не скобки -
        // ошибка
      }

      if (strchr("sctal", str[i])) {
        if (strncmp(str + i, "ln", 2) == 0) {
          i += 1;
        } else {
          if (strncmp(str + i, "sqrt", 4) == 0 ||
              strncmp(str + i, "asin", 4) == 0 ||
              strncmp(str + i, "acos", 4) == 0 ||
              strncmp(str + i, "atan", 4) == 0) {
            i += 3;
          } else {
            if (strncmp(str + i, "sin", 3) == 0 ||
                strncmp(str + i, "cos", 3) == 0 ||
                strncmp(str + i, "tan", 3) == 0 ||
                strncmp(str + i, "log", 3) == 0 ||
                strncmp(str + i, "mod", 3) == 0) {
              i += 2;
            } else {
              flag = 1;
            }
          }
        }

        if (!strchr("0123456789x(", str[i + 1]) || !str[i + 1]) {
          flag = 1;

          // если у нас функция sin cos tan acos asin atan log - сначала
          // проверяем что функция правильно написана если после функции не
          // скобка или не число - ошибка
        }
      }

      if (strchr("(", str[i])) {
        int bracket = 0;
        for (int j = i; str[j] != '\0'; j++) {
          if (str[j] == ')') {
            bracket++;
          }
        }
        if (bracket == 0) {
          flag = 1;
        }
      } // если встречаем открывающую скобку - считаем после нее количество
        // закрывающих - если 0 - ошибка

      if (strchr(")", str[i])) {
        int bracket = 0;
        for (int j = 0; j != i; j++) {
          if (str[j] == '(') {
            bracket++;
          }
        }
        if (bracket == 0) {
          flag = 1;
        }
      } // если встречаем закрывающую скобку скобку - считаем перед ней
        // количество открывающих - если 0 - ошибка
    }
    // printf("%c\n", str[i]);
  }
  return flag;
}

//______________ГЛАВНАЯ ФУНКЦИЯ, КОТОРАЯ ЗАПУСКАЕТ КАЛЬКУЛЯТОР________________//

/**
 * @brief Основная функция, которая запускает калькулятор
 *
 * @param str Входная строка
 * @param x Значение в переменной х
 * @param result Результат вычислений
 * @return int Код ошибки
 * 0 - нет ошибки
 * 1 - Ошибка в парсинге или в нотации
 * 2 - вычислительная ошибка - деление на 0
 */
int smart_calculator(char *str, double x, double *result) {
  calc *source = NULL, *string = NULL, *stack = NULL;
  *result = 0.0;
  int error = check_string(str);
  if (error == 0) {
    parser(str, &source, x);
    error = notation(source, stack, &string);
    if (error == 0) {
      error = calculation(stack, string, result);
      // если error = 2 - делим на 0
    } else {
      while (string) {
        pop(&string);
      }
    }
  }
  return error;
}

//_____________________КРЕДИТНЫЙ
//КАЛЬКУЛЯТОР___________________________________//

/**
 * @brief Кредитный калькулятор
 *
 * @param data Элемент структуры типа credit_calc
 *  Вход
 * double creditsum; // общая сумма кредита
    double term; // срок в месяцах
    double percent; // процентная ставка в процентах
    int type; // 0 - аннуитетный 1 - дифференциальный
    Выход
    double monthpay[1000]; // ежемесячный платеж
    Если аннуитетный платеж - будет только значение в первой ячейке массива
    Если дифференциальный платеж - то будет заполнено несколько элементов
 массива, тк каждый месяц платеж разный double overpayment; // переплата по
 кредиту double total; // общая выплата
 * @return * void
 */
void credit_calculator(credit_calc *data) {
  data->monthpay[0] = 0;
  data->overpayment = 0;
  data->total = 0;
  if (data->type == 0) {
    // Аннуитетный платеж
    // Равные платежи каждый месяц
    double mp = data->percent / (100 * 12); // месячная процентная ставка
    // data->monthpay[0] = data->creditsum * (monthpercent / (1 - powf(1 +
    // monthpercent, - data->term - 1)));
    data->monthpay[0] =
        data->creditsum * (mp + (mp / (powf(1 + mp, data->term) - 1)));
    data->total = data->monthpay[0] * data->term;
    data->overpayment = data->total - data->creditsum;
  } else {
    // Дифференцированный платеж
    // Платежи меняются в течение месяца
    // Часть месячного платежа идет на погашение основного долга
    // Часть месячного платежа идет на оплату процентного долга
    double averageday =
        (31.0 * 7 + 4 * 30.0 + 28.0) / 12.0; // среднее количество дней в месяце
    double md =
        data->creditsum / data->term; // ежемесячное погашение основного долга
    double rest = 0; // остаток задолженности по кредиту
    double pd = 0; // процентный долг
    for (int i = 0; i < data->term; i++) {
      rest = data->creditsum - (md * i);
      pd = rest * data->percent * averageday / (365 * 100);
      data->monthpay[i] = md + pd;
      data->total += data->monthpay[i];
    }
    data->overpayment = data->total - data->creditsum;
  }
}

//_________________________ДЕПОЗИТНЫЙ
//КАЛЬКУЛЯТОР________________________________//

/**
 * @brief Депозитный калькулятор
 *
 * @param data Указатель на элемент структуры типа deposit_credit
 *  Вход
    double dsum; // сумма вклада
    double term; // срок размещения d vtczwf[]
    double percent; // процентная ставка
    double taxrate; // налоговая ставка
    int period; // периодичность выплат
    // 1 - ежемесячная
    3 - ежеквартальная
    6 - раз в полгода
    12 - ежегодная
    int capitalization; // капитализация процентов // 0 - без капитализации // 1
 - с капитализацией процентов double replenish_list[100]; // список пополнений
    double withdraw_list[100]; // список снятий
    Выход
    double apercent; // начисленные проценты
    double taxsum; // сумма налога
    double total; // сумма на вкладе к концу срока
 */
void deposit_calculator(deposit_calc *data) {
  data->apercent = 0;
  data->taxsum = 0;
  data->total = 0;

  for (int i = 0; data->replenish_list[i] != 0; i++) {
    data->dsum +=
        data->replenish_list[i]; // добавили все суммы из списка пополнений
  }

  for (int i = 0; data->withdraw_list[i] != 0; i++) {
    data->dsum -= data->withdraw_list[i]; // убавили все суммы из списка снятий
  }
  double averageday =
      (31.0 * 7 + 4 * 30.0 + 28.0) / 12.0; // среднее количество дней в месяце
  double permon = 0; // начисление процентов за месяц
  if (data->capitalization == 0) {
    // Без капитализации - считаем начисленные проценты
    // Начисленные проценты = (сумма депозита * процентная ставка * среднее
    // количество дней в месяц / (365 * 100))
    for (int i = 0; i < data->term; i++) {
      permon = (data->dsum * data->percent * averageday / (365 * 100));
      data->taxsum += permon * data->taxrate / 100;
      data->apercent += permon;
    }

    data->total = data->dsum;
  } else {
    // С капитализацией процентов
    // Начисленные проценты = ((сумма депозита + процент от капитализации) *
    // процентная ставка * среднее количество дней в месяц / (365 * 100))
    double per = 0; // процент капитализации
    for (int i = 0; i < data->term; i++) {
      if (i % data->period != 0) { // если месяц не является меясцем начисления
                                   // процентов капитализации
        per = data->apercent;
      }
      permon = ((data->dsum + per) * data->percent * averageday / (365 * 100));
      data->taxsum += permon * data->taxrate / 100;
      permon -= permon * data->taxrate / 100;
      data->apercent += permon;
    }

    data->total = data->dsum + data->apercent;
    data->apercent += data->taxsum;
  }
}

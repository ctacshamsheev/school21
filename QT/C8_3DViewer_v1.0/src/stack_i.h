#ifndef SRC_STACK_I_H_
#define SRC_STACK_I_H_

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

typedef struct stack_int
{                    // односвязный список полигонов (плоскостей)
  unsigned int *arr; // массив вершин одного полигона
  unsigned int n;    // количество вершин в одном полигоне
  struct stack_int *next;
} stack_i;

stack_i *stack_i_add_last(stack_i **head, unsigned int n, const unsigned int *arr); // функция добавления полигона в конец списка
stack_i *stack_i_destroy(stack_i **head);                                     // функция очистки списка
int stack_i_get_count(stack_i *head);                                         // возвращает количество элементов в списке

// функции вывода, используются только с консолью, не требуют тестов
void stack_i_output(stack_i *head);                      // функция вывода в консоль i-го полигона
void stack_i_multiset(stack_i *head_f, stack_v *head_v); // функция сопоставления вершин (векторов) и ребер и вывод списком

#endif // SRC_STACK_I_H_

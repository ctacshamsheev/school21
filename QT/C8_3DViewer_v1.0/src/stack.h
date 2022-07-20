#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <stdio.h>
#include <stdlib.h>

#include "s21_matrix.h"

typedef struct stack // односвязный список матриц (векторов)
{
  matrix_t matrix;
  struct stack *next;
} stack_v;

stack_v *stack_add_last(stack_v **head, matrix_t matrix); // функция добавления матрицы (вектора) в конец списка
stack_v *stack_pop(stack_v **head, matrix_t *matrix);     // функция вытаскивания матрицы (вектора) из головы, с удалением из списка
stack_v *stack_destroy(stack_v **head);                   // функция очистки списка из памяти

int stack_get_count(stack_v *head);          // возвращает количество элементов в списке
matrix_t *stack_get_i(stack_v *head, int i); // функция возвращает значение i-го элемента списка, без удаления из него

void stack_fill_matrix_array(stack_v **head_v, int rows, int columns,
                             double *arr); // функция заполняет  матрицу (вектор) из массива arr и кладет в конец списка head_v

void stack_matrix_mult(stack_v **head_v, matrix_t matr_for_mult); // функция умножает каждый элемент списка на матрицу matr_for_mult
void stack_output(stack_v *head);                                 // функция вывода списка в консоль

// stack_v *stack_revers(stack_v **out_stack);
// stack_v *stack_push(stack_v **head, matrix_t matrix);

#endif // SRC_STACK_H_

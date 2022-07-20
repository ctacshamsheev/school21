#include "stack.h"

stack_v *stack_add_last(stack_v **head, matrix_t matrix) {
  stack_v *p = (stack_v *)malloc(sizeof(stack_v));
  p->matrix = matrix;
  p->next = NULL;
  if (*head == NULL) {
    *head = p;
  } else {
    stack_v *ptr = *head;
    while (ptr->next != NULL) {
      ptr = ptr->next;
    }
    ptr->next = p;
  }
  return *head;
}

stack_v *stack_pop(stack_v **head, matrix_t *matrix) {
  if (*head == NULL) {
  } else {
    *matrix = (*head)->matrix;
    stack_v *ptr = *head;
    *head = (*head)->next;
    free(ptr);
  }
  return *head;
}

stack_v *stack_destroy(stack_v **head) {
  stack_v *p = *head;
  while (p != NULL) {
    stack_v *tmp = p;
    p = p->next;
    s21_remove_matrix(&tmp->matrix);
    free(tmp);
  }
  *head = NULL;
  return *head;
}

int stack_get_count(stack_v *head) {
  int count = 0;
  stack_v *ptr = head;
  if (head != NULL) {
    while (ptr != NULL) {
      ptr = ptr->next;
      count++;
    }
  }
  return count;
}

matrix_t *stack_get_i(stack_v *head, int i) {
  stack_v *ptr = head;
  matrix_t *matrix = NULL;
  int tmp_i = 0;
  if (head != NULL) {
    tmp_i = 1;  // отсчет от 1 для .obj
    while (ptr != NULL && tmp_i < i) {
      ptr = ptr->next;
      tmp_i++;
    }
  }
  if (i == tmp_i && i > 0) {
    matrix = &ptr->matrix;
  }
  return matrix;
}

void stack_fill_matrix_array(stack_v **head_v, int rows, int columns,
                             double *arr) {
  matrix_t m = s21_create_matrix(rows, columns);
  matrix_fill_array(&m, arr);
  stack_add_last(head_v, m);
}

void stack_matrix_mult(stack_v **head_v, matrix_t matr_for_mult) {
  stack_v *head = NULL;
  while (*head_v != NULL) {
    matrix_t v;
    stack_pop(head_v, &v);
    stack_add_last(&head, s21_mult_matrix(&matr_for_mult, &v));
    s21_remove_matrix(&v);
  }
  s21_remove_matrix(&matr_for_mult);
  stack_destroy(head_v);
  *head_v = head;
}

void stack_output(stack_v *head) {
  stack_v *ptr = head;
  if (head != NULL) {
    while (ptr != NULL) {
      matrix_print(&ptr->matrix);
      ptr = ptr->next;
    }
  }
  printf("\n");
}

// stack_v* stack_push(stack_v** head, matrix_t matrix) {
//   stack_v* p = (stack_v*)malloc(sizeof(stack_v));
//   p->matrix = matrix;
//   p->next = NULL;
//   if (*head == NULL) {
//     *head = p;
//   } else {
//     stack_v* ptr = *head;
//     *head = p;
//     p->next = ptr;
//   }
//   return *head;
// }

// stack_v* revers_stack(stack_v** in_stack) {
//   stack* out_stack = NULL;
//   while (*in_stack != NULL) {
//     double d = 0;
//     char a = '\0';
//     pop_stack(in_stack, &a, &d);
//     push_stack(&out_stack, a, d);
//   }
//   return out_stack;
// }

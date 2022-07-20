#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <stdlib.h>

typedef struct stack {
  char action;
  double digit;
  struct stack *next;
} stack;

struct stack *push_stack(struct stack **head, char act, double dig);
struct stack *pop_stack(struct stack **head, char *act, double *dig);
struct stack *add_last(struct stack **head, char act, double dig);
struct stack *destroy_stack(struct stack **head);
struct stack *revers_stack(struct stack **out_stack);

#endif  // SRC_STACK_H_

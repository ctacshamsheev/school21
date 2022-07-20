#ifndef SRC_POLISH_NOTATION_H_
#define SRC_POLISH_NOTATION_H_

#include <math.h>
#include <string.h>

#include "stack.h"

#define IN_STACK "("
#define IN_FUNC "sctgqlmabno"
#define IN_OPER "^*/+-sctgqlmabno"

stack *get_polish(stack *input_list);
int get_priority(char c);
double get_stack_value(stack *input_list, double x, int *flag);

#endif  // SRC_POLISH_NOTATION_H_

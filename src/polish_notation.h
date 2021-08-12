#ifndef SRC_POLISH_NOTATION_H_
#define SRC_POLISH_NOTATION_H_

#include <string.h>
#include <math.h>
#include "stack.h"

#define IN_STACK "("
#define IN_FUNC "sctgql"
#define IN_OPER "^*/+-sctgql"

stack * get_polish(stack * input_list);
int get_priority(char c);
double get_stack_value(stack * input_list, double x, int *flag);

#endif  // SRC_POLISH_NOTATION_H_

#ifndef SRC_S21_CALC_H_
#define SRC_S21_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "polish_notation.h"
#include "stack.h"

double get_result(char* input_str, double x);
void output_stack(struct stack* head);

#endif  // SRC_S21_CALC_H_

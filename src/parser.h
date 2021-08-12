#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <stdio.h>
#include <string.h>
#include "stack.h"

#define STR_ALLOW "^+-*/()sincostgctgsqrtlnx01234567890."
#define IS_DIGIT "-0123456789."
#define IS_ACTION "+*/()^"
#define STR_MAX 100

int input(char *str);
int checking_brackets(char *str);
int parse(char *str, stack ** head);
int get_digit(char **str, double *d);
int get_function(char **str, char *ch);

#endif  // SRC_PARSER_H_


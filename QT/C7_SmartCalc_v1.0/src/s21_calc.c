#include "s21_calc.h"

double get_result(char* input_str, double x) {
  stack* head = NULL;
  int l = strlen(input_str);
  input_str[l] = '\n';
  input_str[l + 1] = '\0';
  double ans = NAN;
  if (checking_brackets(input_str) && parse(input_str, &head)) {
    printf("INPUT :");
    output_stack(head);

    stack* out_list = get_polish(head);
    stack* out_stack = revers_stack(&out_list);

    printf("POLISH:");
    output_stack(out_stack);

    int flag = 1;
    ans = get_stack_value(out_stack, x, &flag);
    if (flag) {
      printf("ANSVER: %f\n\n", ans);
    }
    destroy_stack(&head);
    destroy_stack(&out_list);
    destroy_stack(&out_stack);
  } else {
    printf("N/A");
  }
  return ans;
}

void output_stack(struct stack* head) {
  struct stack* ptr = head;
  if (head != NULL) {
    while (ptr != NULL) {
      switch (ptr->action) {
        case 'd':
          printf(" %.1lf", ptr->digit);
          break;
        case 's':
          printf(" sin");
          break;
        case 'c':
          printf(" cos");
          break;
        case 't':
          printf(" tan");
          break;
        case 'g':
          printf(" ctg");
          break;
        case 'q':
          printf(" sqrt");
          break;
        case 'l':
          printf(" log");
          break;
        case 'm':
          printf(" mod");
          break;
        case 'a':
          printf(" asin");
          break;
        case 'b':
          printf(" acos");
          break;
        case 'n':
          printf(" atan");
          break;
        case 'o':
          printf(" log");
          break;
        default:

          printf(" %c", ptr->action);
          break;
      }
      ptr = ptr->next;
    }
  }
  printf("\n");
}

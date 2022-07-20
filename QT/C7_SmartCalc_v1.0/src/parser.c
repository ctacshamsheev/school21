#include "parser.h"

int checking_brackets(char* str) {
  int t = 0;
  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] == '(') {
      t++;
    } else if (str[i] == ')') {
      t--;
      if (t < 0) t = -99999;
    }
  }
  return (t == 0) ? 1 : 0;
}

int get_digit(char** str, double* d) {
  int flag = 1;
  int i = 0;
  int t = 0;
  while (strchr(IS_DIGIT, *(*str + i)) != NULL && flag) {
    if (i > 0 && *(*str + i) == '-') {
      break;
    }
    if (*(*str + i) == '.') {
      t++;
      if (t > 1) {
        flag = 0;
      }
    }
    i++;
  }
  char tmp[STR_MAX] = {'\0'};
  memcpy(tmp, *str, i);
  if (sscanf(tmp, "%lf", d) != 1) {
    flag = 0;
  }
  *str += (i - 1);
  return flag;
}

int get_function(char** str, char* ch) {
  int flag = 1;
  char* lstr = strchr(*str, '(');
  if (lstr != NULL) {
    int len = (int)(lstr - *str);
    if (len > 4) {
      flag = 0;
    } else {
      char tmp[STR_MAX] = {'\0'};
      memcpy(tmp, *str, len);
      if (strcmp(tmp, "sin") == 0) {
        *ch = 's';
      } else if (strcmp(tmp, "cos") == 0) {
        *ch = 'c';
      } else if (strcmp(tmp, "tan") == 0) {
        *ch = 't';
      } else if (strcmp(tmp, "ctg") == 0) {
        *ch = 'g';
      } else if (strcmp(tmp, "sqrt") == 0) {
        *ch = 'q';
      } else if (strcmp(tmp, "ln") == 0) {
        *ch = 'l';
      } else if (strcmp(tmp, "asin") == 0) {
        *ch = 'a';
      } else if (strcmp(tmp, "acos") == 0) {
        *ch = 'b';
      } else if (strcmp(tmp, "atan") == 0) {
        *ch = 'n';
      } else if (strcmp(tmp, "log") == 0) {
        *ch = 'o';
      } else {
        flag = 0;
      }
      *str += (len - 1);
    }
  } else {
    flag = 0;
  }
  return flag;
}

int parse(char* str, stack** head) {
  int flag = 1;
  char ch_m = '\0';
  while (strchr(STR_ALLOW, *str) != NULL && *str > 0 && flag) {
    while (*str == ' ') {
      str++;
    }
    if ((strchr(IS_NEXT, *str) && strchr(IS_NEXT, *(str + 1))) ||
        (*str == '(' && *(str + 1) == ')')) {
      flag = 0;
      break;
    } else if (*str == 'x') {
      add_last(head, 'x', 0);
    } else if (*str == '+' && (ch_m == '\0' || ch_m == '(')) {
    } else if (strchr(IS_ACTION, *str) != NULL && *str != '-') {
      if (*str == 'm' && *(str + 1) == 'o' && *(str + 2) == 'd') {
        add_last(head, *str, 0);
        str++;
        str++;
      } else {
        add_last(head, *str, 0);
      }
    } else if (*str == '-') {
      if (ch_m != '\0' && (strchr(IS_ACTION, ch_m) == NULL || ch_m == ')')) {
        add_last(head, *str, 0);
      } else if (*(str + 1) == 'x') {
        add_last(head, '(', 0);
        add_last(head, 'x', 0);
        add_last(head, '*', 0);
        add_last(head, 'd', -1);
        add_last(head, ')', 0);
        str++;
      } else {
        double d = 0;
        flag = get_digit(&str, &d);
        add_last(head, 'd', d);
      }
    } else if (strchr(IS_DIGIT, *str) != NULL) {
      double d = 0;
      flag = get_digit(&str, &d);
      add_last(head, 'd', d);
    } else if (*str != '\0' && *str != '\n' && (*str >= 'a' && (*str <= 'z'))) {
      char ch = '\0';

      flag = get_function(&str, &ch);
      add_last(head, ch, 0);
    } else if (*str >= ' ' && *str <= '~') {
      flag = 0;
    }
    ch_m = *str;
    str++;
  }
  if (*head == NULL || strchr(IS_NEXT, ch_m)) {
    flag = 0;
  }
  return flag;
}

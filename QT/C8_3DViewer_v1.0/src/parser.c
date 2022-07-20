#include "parser.h"

FILE *is_file_exist(char file_name[]) {
  FILE *fp = NULL;
  if ((fp = fopen(file_name, "r")) == NULL) {
    fprintf(stderr, "s21_%s: %s: No such file or directory\n", "is_file_exist",
            file_name);
  }
  return fp;
}

void get_max(double *max, double a, double b, double c) {
  a = fabs(a);
  b = fabs(b);
  c = fabs(c);
  if (a > *max) *max = a;
  if (b > *max) *max = b;
  if (c > *max) *max = c;
}

int read_file(FILE *fin, stack_v **head_v, stack_i **head_f, double *max) {
  int flag = 1;
  *max = 1;
  if (fin != NULL) {
    char str[MAX_STR];
    while (fgets(str, MAX_STR, fin)) {
      // str - текущая строчка в документе
      if (str[1] == ' ') {
        if (str[0] == 'v') {  // найденная строчка содержит вершины
          double a[4] = {0};
          if (sscanf(str, "v %lf%lf%lf", &a[0], &a[1], &a[2]) == 3) {
            get_max(max, a[0], a[1], a[2]);
            a[3] = 1.0;  // последняя компонента вектора всегда 1, для 3х мерных
                         // объектов
            stack_fill_matrix_array(head_v, 4, 1,
                                    a);  // добавляем вектор 4х1 в список
          }
        } else if (str[0] == 'f') {  // найденная строчка содержит плоскости
          char *saveptr = NULL;                           // for mac cppcheck
          char *istr = strtok_r(str + 2, " ", &saveptr);  // for mac
          // char *istr = strtok(str + 2, " ");

          unsigned int arr[100] = {0};
          // Выделение последующих частей
          unsigned int i = 0;
          while (istr != NULL) {
            if (sscanf(istr, "%u", &arr[i]) == 1) {
              i++;
            } else {
              break;
            }
            // Выделение очередной части строки
            istr = strtok_r(NULL, " ", &saveptr);  // for mac cppcheck
            // istr = strtok(NULL, " ");
          }
          if (i > 2)
            stack_i_add_last(head_f, i, arr);  // добавляем плоскость в список
        }
      }
    }
  } else {
    flag = 0;
  }
  return flag;
}

#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "stack_i.h"

#define MAX_STR 256  // максимальная длина строчки

FILE *is_file_exist(char file_name[]);
// проверка существования файла, возвращает указатель на файл, либо NULL в
// случае ошибки
int read_file(FILE *fin, stack_v **head_v, stack_i **head_f, double *max);
// функция парсинга .obj файла, заполняет список вершин head_v и список
// плоскостей head_v

#endif  // SRC_PARSER_H_

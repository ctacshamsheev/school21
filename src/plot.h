#ifndef SRC_PLOT_H_
#define SRC_PLOT_H_

#include <stdio.h>
#include <math.h>

#define HEIGHT 80
#define WIDTH 25

void clear_frame(char frame[WIDTH][HEIGHT]);
void print_frame(char frame[WIDTH][HEIGHT]);
void frame_add(double data[]);
void main_func(double *data);

#endif  // SRC_PLOT_H_

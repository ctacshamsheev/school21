#include "plot.h"

void clear_frame(char frame[WIDTH][HEIGHT]) {
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			frame[i][j] = '.';
		}
	}
}

void print_frame(char frame[WIDTH][HEIGHT]) {
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			printf("%c", frame[i][j]);
		}
		printf("\n");
	}
}

void frame_add(double data[]) {
	char frame[WIDTH][HEIGHT];
	clear_frame(frame);

	double min = -1;
	double max = 1;
	double dy = (max - min) / (WIDTH - 1);
	for (int i = 0; i < HEIGHT; i++) {
		if (data[i] == data[i]) {
			if (data[i] <= max && data[i] >= min) {
				frame[WIDTH-(int)((round((data[i] - min) / dy)))-1][i] = '*';
			}
		}
	}
	print_frame(frame);
}


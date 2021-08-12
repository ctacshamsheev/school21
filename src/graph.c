#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "stack.h"
#include "parser.h"
#include "plot.h"
#include "polish_notation.h"

int is_contains_x(stack* head);
int graph(stack* out_stack);

int main() {
	char input_str[STR_MAX] = { '\0' };
	stack* head = NULL;
	if (input(input_str) &&
		checking_brackets(input_str) &&
		parse(input_str, &head)) {

		printf("INPUT :");
		output_stack(head);

		stack* out_list = get_polish(head);
		stack* out_stack = revers_stack(&out_list);

		printf("POLISH:");
		output_stack(out_stack);

		if (is_contains_x(out_stack) == 0) {
			int flag = 1;
			double ans = get_stack_value(out_stack, 0, &flag);
			if (flag) {
				printf("ANSVER: %lf\n", ans);
			}
		}

		if (!graph(out_stack)) {
			printf("N/A");
		}
		destroy_stack(&head);
		destroy_stack(&out_list);
		destroy_stack(&out_stack);
	}
	else {
		printf("N/A");
	}
	return 0;
}


int is_contains_x(stack* head) {
	int flag = 0;
	struct stack* ptr = head;
	while (ptr != NULL) {
		if (ptr->action == 'x') {
			flag = 1;
			break;
		}
		ptr = ptr->next;
	}
	return flag;
}

int graph(stack* out_stack) {
	double data[HEIGHT];
	double x = 0;
	double dx = 4 * M_PI / (HEIGHT - 1);
	int flag = 1;
	for (int i = 0; i < HEIGHT && flag; i++) {
		data[i] = get_stack_value(out_stack, x, &flag);
		x += dx;
	}
	if (flag) {
		frame_add(data);
	}
	return flag;
}

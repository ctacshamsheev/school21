#include "polish_notation.h"

int get_priority(char c) {
	int flag = 0;
	switch (c) {
	case 's':
	case 'c':
	case 't':
	case 'g':
	case 'q':
	case 'l':
		flag = 4;
		break;
	case '^':
		flag = 3;
		break;

	case '*':
	case '/':
		flag = 2;
		break;

	case '+':
	case '-':
		flag = 1;
		break;
	}
	return flag;
}

stack* get_polish(stack* input_list) {
	double d = 0; char a = '\0';
	stack* stack_list = NULL; stack* output_list = NULL;
	if (input_list != NULL) {
		stack* ptr = input_list;
		while (ptr != NULL) {
			if (ptr->action == 'd' || ptr->action == 'x') {
				push_stack(&output_list, ptr->action, ptr->digit);
			}
			else if (strchr(IN_STACK, ptr->action) != NULL) {
				push_stack(&stack_list, ptr->action, ptr->digit);
			}
			else if (ptr->action == ')') {
				if (stack_list != NULL) {
					do {
						pop_stack(&stack_list, &a, &d);
						if (a != '(') {
							push_stack(&output_list, a, d);
						}
					} while (a != '(' && stack_list != NULL);
					if (stack_list != NULL && strchr(IN_FUNC, stack_list->action) != NULL) {
						pop_stack(&stack_list, &a, &d);
						push_stack(&output_list, a, d);
					}
				}
			}
			else if (strchr(IN_OPER, ptr->action) != NULL) {
				if (stack_list != NULL) {
					while (stack_list != NULL &&
						get_priority(stack_list->action) >= get_priority(ptr->action)) {
						pop_stack(&stack_list, &a, &d); push_stack(&output_list, a, d);
					}
				}
				push_stack(&stack_list, ptr->action, ptr->digit);
			}
			ptr = ptr->next;
		}
		while (stack_list != NULL) {
			pop_stack(&stack_list, &a, &d); push_stack(&output_list, a, d);
		}
	}
	destroy_stack(&stack_list);
	return output_list;
}

double get_stack_value(stack* input_list, double x, int* flag) {
	stack* stack_list = NULL;
	stack* ptr = input_list;
	double d = 0, d2 = 0, ans = 0;
	char a = '\0';
	while (ptr != NULL) {
		switch (ptr->action) {
		case 'd': ans = ptr->digit; break;
		case 'x': ans = x; break;
		case '+': pop_stack(&stack_list, &a, &d); pop_stack(&stack_list, &a, &d2); ans = (d2 + d); break;
		case '*': pop_stack(&stack_list, &a, &d);  pop_stack(&stack_list, &a, &d2); ans = (d2 * d);  break;
		case '/': pop_stack(&stack_list, &a, &d); pop_stack(&stack_list, &a, &d2); ans = (d2 / d); break;
		case '-': pop_stack(&stack_list, &a, &d); pop_stack(&stack_list, &a, &d2); ans = (d2 - d); break;
		case '^': pop_stack(&stack_list, &a, &d); pop_stack(&stack_list, &a, &d2); ans = (pow(d2, d)); break;
		case 's': pop_stack(&stack_list, &a, &d); ans = (sin(d)); break;
		case 'c': pop_stack(&stack_list, &a, &d); ans = (cos(d));  break;
		case 't': pop_stack(&stack_list, &a, &d); ans = (tan(d));  break;
		case 'g': pop_stack(&stack_list, &a, &d);  break;
		case 'q': pop_stack(&stack_list, &a, &d);
			if (d < 0) * flag = 0;
			ans = (sqrt(d)); break;
		case 'l': pop_stack(&stack_list, &a, &d);
			if (d < 0) * flag = 0;
			ans = (log(d)); break;
		}
		push_stack(&stack_list, 'd', ans);
		ptr = ptr->next;
	}
	double ddd = 0;
	if (stack_list == NULL || stack_list->next != NULL) {
		destroy_stack(&stack_list);
		*flag = 0;
	}
	else {
		ddd = stack_list->digit;
		destroy_stack(&stack_list);
	}
	return ddd;
}
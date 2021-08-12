#include "stack.h"

struct stack* push_stack(struct stack** head, char act, double dig) {
	struct stack* p = (struct stack*) malloc(sizeof(struct stack));
	p->action = act;
	p->digit = dig;
	p->next = NULL;
	if (*head == NULL) {
		*head = p;
	}
	else {
		struct stack* ptr = *head;
		*head = p;
		p->next = ptr;
	}
	return *head;
}

struct stack* add_last(struct stack** head, char act, double dig) {
	if (act != '\0') {
		struct stack* p = (struct stack*) malloc(sizeof(struct stack));
		p->action = act;
		p->digit = dig;
		p->next = NULL;
		if (*head == NULL) {
			*head = p;
		}
		else {
			struct stack* ptr = *head;
			while (ptr->next != NULL) {
				ptr = ptr->next;
			}
			ptr->next = p;
		}
	}
	return *head;
}

struct stack* pop_stack(struct stack** head, char* act, double* dig) {
	if (*head == NULL) {
	}
	else {
		*act = (*head)->action;
		*dig = (*head)->digit;

		struct stack* ptr = *head;
		*head = (*head)->next;
		free(ptr);
	}
	return *head;
}

void output_stack(struct stack* head) {
	struct stack* ptr = head;
	if (head != NULL) {
		while (ptr != NULL) {
			switch (ptr->action) {
			case 'd': printf(" %.1lf", ptr->digit); break;
			case 's': printf(" sin"); break;
			case 'c': printf(" cos");  break;
			case 't': printf(" tan");  break;
			case 'g': printf(" ctg"); break;
			case 'q': printf(" sqrt"); break;
			case 'l': printf(" log"); break;
			default: printf(" %c", ptr->action); break;
			}
			ptr = ptr->next;
		}
	}
	printf("\n");
}

struct stack* destroy_stack(struct stack** head) {
	struct stack* p = *head;
	while (p != NULL) {
		free(p);
		p = p->next;
	}
	*head = NULL;
	return *head;
}

struct stack* revers_stack(struct stack** in_stack) {
	stack* out_stack = NULL;
	while (*in_stack != NULL) {
		double d = 0;
		char a = '\0';
		pop_stack(in_stack, &a, &d);
		push_stack(&out_stack, a, d);
	}
	return out_stack;
}

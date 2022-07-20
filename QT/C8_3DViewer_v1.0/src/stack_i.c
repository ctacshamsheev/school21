#include "stack_i.h"

#include "stack.h"

stack_i *stack_i_add_last(stack_i **head, unsigned int n, const unsigned int *arr) {
  stack_i *p = (stack_i *)malloc(sizeof(stack_i));
  p->n = n;
  p->arr = (unsigned int *)calloc(n, sizeof(unsigned int));
  p->next = NULL;
  for (unsigned int i = 0; i < n; i++) {
    p->arr[i] = arr[i];
  }
  if (*head == NULL) {
    *head = p;
  } else {
    stack_i *ptr = *head;
    while (ptr->next != NULL) {
      ptr = ptr->next;
    }
    ptr->next = p;
  }
  return *head;
}

stack_i *stack_i_destroy(stack_i **head) {
  stack_i *p = *head;
  while (p != NULL) {
    stack_i *tmp = p;
    p = p->next;
    free(tmp->arr);
    free(tmp);
  }
  *head = NULL;
  return *head;
}

int stack_i_get_count(stack_i *head) {
  int count = 0;
  stack_i *ptr = head;
  if (head != NULL) {
    while (ptr != NULL) {
      ptr = ptr->next;
      count++;
    }
  }
  return count;
}

void stack_i_output(stack_i *head) {
  stack_i *ptr = head;
  if (head != NULL) {
    while (ptr != NULL) {
      printf("f[");
      for (unsigned int i = 0; i < ptr->n; i++) {
        if (i != 0) printf(",\t");
        printf("%u", ptr->arr[i]);
      }
      printf("]\n");
      ptr = ptr->next;
    }
  }
  printf("\n");
}

void stack_i_multiset(stack_i *head_f, stack_v *head_v) {
  stack_i *ptr = head_f;
  while (ptr != NULL) {
    printf("f:\n");
    for (unsigned int i = 0; i < ptr->n; i++) {
      matrix_print(stack_get_i(head_v, ptr->arr[i]));
    }
    printf("\n");
    ptr = ptr->next;
  }

  printf("\n");
}

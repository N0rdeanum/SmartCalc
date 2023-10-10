#include "headers/helper.h"

Stack *init(double one) {
  Stack *new_head = malloc(sizeof(Stack));
  new_head->data = one;
  return new_head;
}

Stack *push(Stack *head, double one) {
  Stack *new_head = init(one);
  new_head->next = head;
  return new_head;
}

double top(Stack *head) { return head->data; }

Stack *pop(Stack *head) {
  Stack *new_head = NULL;
  if (head != NULL) {
    new_head = head->next;
    free(head);
  }
  return new_head;
}

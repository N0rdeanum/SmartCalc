#include "headers/helper.h"

#define OK 0
#define ERROR 1

int polish(char *output, const char *input) {
  int index = 0;
  Stack *stack = NULL;
  char str[255] = {0};
  strcpy(str, input);
  int len = strlen(str);
  int status = OK;

  if (brakets_check(str) == 0) {
    for (int i = 0; i < len;) {
      skip_spaces(str, &i);

      if (is_ident(str[i])) {
        while (is_ident(str[i])) {
          output[index++] = str[i++];
        }
        output[index++] = ' ';

      } else if (str[i] == 'x') {
        output[index++] = 'x';
        output[index++] = ' ';
        i++;

      } else if (is_function(str[i])) {
        if (chekFun(&str[i]) == OK) {
          stack = push(stack, chekFunction(&str[i]));
          for (; is_function(str[i]) != '\0'; i++)
            ;

        } else {
          return ERROR;
        }

      } else if (is_operator(str[i])) {
        if ((str[i] == '-') &&
            (i == 0 || (str[i - 1] != ')' && str[i - 1] != 'x' &&
                        !is_ident(str[i - 1])))) {
          str[i] = '~';

        } else if ((str[i] == '+') &&
                   (i == 0 || (str[i - 1] != ')' && str[i - 1] != 'x' &&
                               !is_ident(str[i - 1])))) {
          str[i] = '#';
        } else

          while (stack != NULL && priority(str[i]) <= priority(top(stack))) {
            output[index++] = top(stack);
            stack = pop(stack);
            output[index++] = ' ';
          }

        stack = push(stack, str[i++]);

      } else if (str[i] == o_bracket(str[i])) {
        stack = push(stack, o_bracket(str[i++]));
      } else if (str[i] == c_bracket(str[i])) {
        while (stack != NULL && top(stack) != o_bracket(str[i])) {
          output[index++] = top(stack);
          output[index++] = ' ';
          stack = pop(stack);
        }
        stack = pop(stack);

        if (stack != NULL && is_function(top(stack))) {
          output[index++] = top(stack);
          output[index++] = ' ';
          stack = pop(stack);
        }
        i++;
      }
    }

  } else
    status = ERROR;

  while (stack != NULL) {
    output[index++] = top(stack);
    output[index++] = ' ';
    stack = pop(stack);
  }

  return status;
}

int brakets_check(const char *str) {
  int i = 0, count = 0;
  char prev_char = 0;
  while (*str) {
    if (*str == '(') {
      i++;
      count = 1;
    }
    if (*str == ')' && count == 1 && (prev_char != '(' || prev_char != ')')) {
      i--;
    }
    prev_char = *str;
    str++;
  }
  return i;
}
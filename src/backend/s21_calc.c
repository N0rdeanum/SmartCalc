#include "headers/helper.h"

/*
! ---1 -+-+1
?

*/

int calc(const char *str, double *res, double *x) {
  char output[255] = {0};

  int status = 0;
  status = polish(output, str);
  Stack *stack = NULL;
  double temp = 0.0;
  double op1 = 0.0, op2 = 0.0;

  if (status == OK) {
    for (int i = 0; output[i] != '\0'; i++) {
      skip_spaces(output, &i);

      if (is_ident(output[i]) || output[i] == 'x') {
        char tmp[255] = {0};
        int index = 0;

        if (output[i] == 'x') {
          stack = push(stack, *x);
          i++;
        } else {
          while (is_ident(output[i])) {
            tmp[index++] = output[i++];
          }
          temp = atof(tmp);
          stack = push(stack, temp);
        }
        // status = ERROR;
      } else if (is_operator(output[i]) && output[i] != '~' &&
                 output[i] != '#') {
        if (stack != NULL) {
          op1 = top(stack);
          stack = pop(stack);
        } else
          status = ERROR;

        if (stack != NULL) {
          op2 = top(stack);
          stack = pop(stack);
        } else
          status = ERROR;

        switch (output[i]) {
          case '+':
            stack = push(stack, op1 + op2);
            break;
          case '-':
            stack = push(stack, op2 - op1);
            break;
          case '*':
            stack = push(stack, op1 * op2);
            break;
          case '/':
            stack = push(stack, op2 / op1);
            break;
          case '^':
            stack = push(stack, pow(op1, op2));
            break;
          case '%':
            stack = push(stack, fmod(op2, op1));
            break;
          default:
            status = ERROR;
            break;
        }

        i++;

      } else if (is_function(output[i]) || output[i] == '~' ||
                 output[i] == '#') {
        switch (output[i]) {
          case '~':
            if (output[i] == '~' && stack != NULL) {
              op1 = top(stack);
              stack = pop(stack);
              stack = push(stack, op1 * -1);
            } else
              status = ERROR;
            break;
          case '#':
            if (output[i] == '#') break;
          case 's':
            if (stack != NULL) {
              op1 = top(stack);
              stack = pop(stack);
              stack = push(stack, sin(op1));
            } else
              status = ERROR;
            break;
          case 'c':
            if (stack != NULL) {
              op1 = top(stack);
              stack = pop(stack);
              stack = push(stack, cos(op1));
            } else
              status = ERROR;
            break;
          case 't':
            if (stack != NULL) {
              op1 = top(stack);
              stack = pop(stack);
              stack = push(stack, tan(op1));
            } else
              status = ERROR;
            break;
          case 'A':
            if (stack != NULL) {
              op1 = top(stack);
              stack = pop(stack);
              stack = push(stack, acos(op1));
            } else
              status = ERROR;
            break;
          case 'T':
            if (stack != NULL) {
              op1 = top(stack);
              stack = pop(stack);
              stack = push(stack, atan(op1));
            } else
              status = ERROR;
            break;
          case 'l':
            if (stack != NULL) {
              op1 = top(stack);
              stack = pop(stack);
              stack = push(stack, log(op1));
            } else
              status = ERROR;
            break;
          case 'q':
            if (stack != NULL) {
              op1 = top(stack);
              stack = pop(stack);
              stack = push(stack, sqrt(op1));
            } else
              status = ERROR;
            break;
            break;
          case 'S':
            if (stack != NULL) {
              op1 = top(stack);
              stack = pop(stack);
              stack = push(stack, asin(op1));
            } else
              status = ERROR;
            break;
          case 'g':
            if (stack != NULL) {
              op1 = top(stack);
              stack = pop(stack);
              stack = push(stack, log10(op1));
            } else
              status = ERROR;
            break;
          default:
            break;
        }
        i++;
      } else {
        status = ERROR;
      }
    }
  }

  if (stack != NULL) *res = top(stack);
  stack = pop(stack);

  return status;
}

// int main() {
//   char str[] = "(-5.1+(cos(4+(sqrt(36)))))";

//   double res;
//   double x = 10;
//   int status = 0;

//   status = calc(str, &res, &x);
//   // -5.1+(cos(4+(sqrt(36))))
//   // -(1+x*sin(x))*sin(cos(-(1+x-cos(x))))
//   // "sin*(2*x*x*(1+x))*cos(2x)*(1-x)"
//   // "(1+x*sin(x))*sin(cos(1+x-cos(x)))"
//   // "cos(x-1)*x*cos(x)-sin(x)*sin(1-x*x)"

//   puts(" \033[40m              POLISH хуелиш             \033[0m");
//   puts("------------------------------------------");
//   puts(
//       "|\033[34m-=входная ОПН строка=- \033[0m|\033[34m -=выход=- "
//       "\033[0m     |");
//   puts("------------------------------------------");
//   printf("                 \033[32m%s\033[0m       \n", str);
//   // printf("\033[32m%s\033[0m\n", &str);
//   puts(" \033[40m              ИТОГО                     \033[0m");
//   puts("------------------------------------------");
//   printf("\033[33m                 %f\033[0m\n", res);
//   puts("------------------------------------------");
//   printf("\033[31m           X              %f\033[0m\n", x);
//   printf("\033[34m        STATUS            %d\033[0m\n\n\n\n", status);
// }

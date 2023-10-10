
#include "headers/helper.h"

int is_ident(char c) { return (c >= '0' && c <= '9') || c == '.'; }

int is_function(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int is_operator(char c) { return (strchr("+-/*#~^%", c) != NULL); }

int o_bracket(char c) { return c = '('; }

int c_bracket(char c) { return c = ')'; }

int is_spase(char c) { return (c == ' '); }

int chekFunction(const char *str) {
  if (strncmp(str, "cos", 3) == 0) {
    return 'c';
  } else if (strncmp(str, "sin", 3) == 0) {
    return 's';
  } else if (strncmp(str, "tan", 3) == 0) {
    return 't';
  } else if (strncmp(str, "acos", 4) == 0) {
    return 'A';
  } else if (strncmp(str, "atan", 4) == 0) {
    return 'T';
  } else if (strncmp(str, "sqrt", 4) == 0) {
    return 'q';
  } else if (strncmp(str, "ln", 2) == 0) {
    return 'l';
  } else if (strncmp(str, "asin", 4) == 0) {
    return 'S';
  } else if (strncmp(str, "log", 3) == 0) {
    return 'g';
  } else {
    return ERROR;
  }
  return OK;
}

int chekFun(const char *str) {
  char temp[255] = {0};
  int status = ERROR;

  for (int i = 0; is_function(*str); i++) {
    temp[i] = *str;
    str++;
  }

  if (strcmp(temp, "cos") == 0) {
    status = OK;
  } else if (strcmp(temp, "sin") == 0) {
    status = OK;
  } else if (strcmp(temp, "tan") == 0) {
    status = OK;
  } else if (strcmp(temp, "acos") == 0) {
    status = OK;
  } else if (strcmp(temp, "atan") == 0) {
    status = OK;
  } else if (strcmp(temp, "sqrt") == 0) {
    status = OK;
  } else if (strcmp(temp, "ln") == 0) {
    status = OK;
  } else if (strcmp(temp, "asin") == 0) {
    status = OK;
  } else if (strcmp(temp, "sin") == 0) {
    status = OK;
  } else if (strcmp(temp, "log") == 0)
    status = OK;

  return status;
}

int spaces(char *str) {
  int i = 0;
  int status = OK;
  while (str[i]) {
    if (str[i] == ' ') status = ERROR;
  }
  return status;
}

void skip_spaces(const char *str, int *index) {
  while (str[*index] == ' ') {
    (*index)++;
  }
}

int priority(char c) {
  switch (c) {
    case '#':
    case '~':
      return 5;

    case '^':
    case '%':
      return 4;

    case '*':
    case '/':
      return 3;

    case '+':
    case '-':
      return 2;

    case 's':
    case 'c':
    case 't':
      return 1;
  }
  return 0;
}
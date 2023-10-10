#ifdef __cplusplus
extern "C" {
#endif

#ifndef SRC_BACKEND_HEADERS_HELPER_H_
#define SRC_BACKEND_HEADERS_HELPER_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_calc.h"
#include "s21_polish.h"
#include "s21_stack.h"

#define ERROR 1
#define OK 0
#define UNDEFINED 2

/**
 * @приоритет
 */
int priority(char c);

/**
 * @brief
 * @проверка на числа
 */
int is_ident(char c);

/**
 * @проверка на оператор
 */
int is_operator(char c);

/**
 * @проверка на функцию(sin, cos и т.д)
 */
int is_function(char c);

/**
 * @проверка функйции
 * @возвращает - *ptr
 */
int chekFunction(const char *str);

void skip_spaces(const char *str, int *index);

int o_bracket(char c);
int c_bracket(char c);
int is_spase(char c);
int spaces(char *str);
int chekFun(const char *str);

#endif  // SRC_BACKEND_HEADERS_HELPER_H_

#ifdef __cplusplus
}
#endif

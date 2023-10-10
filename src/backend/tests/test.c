#include <check.h>
#include <stdio.h>

#include "../headers/helper.h"

#define EPS 1e-07
#define EQ_MAX_LENGTH 255

START_TEST(funcWithoutBracket) {
  char *str = "";
  double res = 0;
  int status = 1;
  double x = 5;

  str = "-9+x";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, -4);

  str = "3mod2";
  res = calc(str, &res, &x);
  ck_assert_double_eq(res, 1);

  str = "10+(5%1)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 10);

  str = "5-2";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 3);

  str = "2^2";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 4);

  str = "1/2";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 0.5);
}

START_TEST(funcWithBracket) {
  char *str = "";
  double res = 0;
  int status = 1;
  double x = 5;

  str = "(-9)+(-x)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, -14);

  str = "-(5+5)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, -10);

  str = "-(5-5)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 0);

  str = "-(5*2^2)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, -20);

  str = "-(1/2)*(-5)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 2.5);

  str = "(5+5)+(+5+5)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 20);

  str = "5+5*1+5";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 15);
}

START_TEST(trigFuncWithoutBracket) {
  char *str = "";
  double res = 0;
  int status = 1;
  double x = 1;

  str = "cos(0)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 1);

  str = "sin(0)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 0);

  str = "tan(1)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res - 1.55741 <= EPS, 1);

  str = "sqrt(4+ln(x))";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 2);
}

START_TEST(trigFuncWithBracket) {
  char *str = "";
  double res = 0;
  int status = 1;
  double x = 0;

  str = "-(-acos(x))";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res - 1.5708 <= EPS, 1);

  str = "-asin(0)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 0);

  str = "atan(0)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 0);

  str = "sqrt(4)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 2);

  str = "ln(10)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res - 2.30259 <= EPS, 1);

  str = "log(10)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 1);

  str = "-5.1+(cos(4+(sqrt(36))))";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res + 5.93907 <= EPS, 1);
}

START_TEST(argX) {
  char *str = "";
  double res = 0;
  int status = 0;
  double x = 0;

  str = "-(-acos(x))";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res - 1.5708 <= EPS, 1);

  str = "-asin(x)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 0);

  str = "atan(x)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 0);

  x = 4;
  str = "sqrt(x)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 2);

  x = 10;
  str = "ln(x)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res - 2.30259 <= EPS, 1);

  str = "log(x)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 1);

  x = 4;
  str = "sqrt(4*x)";
  status = calc(str, &res, &x);
  ck_assert_double_eq(res, 4);
}

Suite *Suite_create(void) {
  Suite *s21_SmartCalc = suite_create("s21_SmartCalc");
  TCase *tcase_test = tcase_create("test");
  tcase_add_test(tcase_test, funcWithoutBracket);
  tcase_add_test(tcase_test, funcWithBracket);
  tcase_add_test(tcase_test, trigFuncWithoutBracket);
  tcase_add_test(tcase_test, trigFuncWithBracket);
  tcase_add_test(tcase_test, argX);

  suite_add_tcase(s21_SmartCalc, tcase_test);

  return s21_SmartCalc;
}

int main() {
  Suite *suite = Suite_create();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);

  int failed_count = srunner_ntests_failed(suite_runner);

  srunner_free(suite_runner);

  return (failed_count != 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}

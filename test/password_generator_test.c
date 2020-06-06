#include "../src/password_generator.h"
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

START_TEST(test_case_0) { ck_assert(1); }
END_TEST

Suite *password_generator_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Password Generator");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_case_0);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = password_generator_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

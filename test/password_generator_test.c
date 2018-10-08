#include "../src/password_generator.h"
#include <check.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

START_TEST(test_wrap_printable) {
  char actual[10] = {0x00, 0x01, 0x20, 0x21, 0x7E,
                     0x7F, 0x80, 0xFE, 0xFF, 0x00};
  /* TODO(tom): is this correct? */
  char *expected = "!\"ABAB!AB";

  wrap_printable(actual, 9);
  ck_assert_str_eq(expected, actual);
}
END_TEST

Suite *password_generator_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Password Generator");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_wrap_printable);
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

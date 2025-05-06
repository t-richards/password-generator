#include "../src/password_generator.h"
#include <check.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

START_TEST(test_case_0) {
  // Generate a password with default settings.
  char buf[65] = {0};
  int result = generate_password(buf, 64);

  // Expect the password generation to succeed.
  ck_assert_msg(result == 0, "Password generation failed: %d", result);
  ck_assert_msg(buf[0] != '\0', "Password is empty");
  ck_assert_msg(buf[64] == '\0', "Buffer is not null-terminated");

  // Expect password to have the correct length.
  ck_assert_msg(strlen(buf) == 64, "Password length is incorrect: %zu",
                strlen(buf));

  // Expect all characters to be printable, and not whitespace.
  for (int i = 0; i < 64; i++) {
    char c = buf[i];
    ck_assert_msg(isprint(c), "Character is not printable: %c", c);
    ck_assert_msg(!isspace(c), "Character is whitespace: %c", c);
    ck_assert_msg(c != '\0', "Character is null: %c", c);
  }
}
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

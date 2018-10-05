#include "password_generator.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char *password = NULL;
  int result = -1, retval = 0;
  int password_length = 64;
  int num_passwords = 1;

  if (argc >= 2) {
    password_length = atoi(argv[1]);
  }
  if (argc >= 3) {
    num_passwords = atoi(argv[2]);
  }

  /* Allocate memory */
  password = calloc(1, password_length);
  if (password == NULL) {
    fprintf(stderr, "Failed to allocate memory: %s\n", strerror(errno));
    retval = 1;
    goto cleanup;
  }

  /* Lock the heap-allocated buffer into memory */
  /* This prevents the memory page from swapping to disk */
  result = mlock(password, password_length);
  if (result != 0) {
    fprintf(stderr, "Failed to lock process memory: %s\n", strerror(errno));
    retval = 1;
    goto cleanup;
  }

  /* Happy path: generate and print the password(s)! */
  for (int i = 0; i < num_passwords; i++) {
    /* Generate password */
    result = generate_password(password, password_length);
    if (result < 0) {
      fprintf(stderr, "Failed to generate password: %s\n", strerror(result));
      retval = 1;
      goto cleanup;
    }

    /* Print password(s). */
    /* Omit newline when generating a single password to a non-TTY output */
    if (num_passwords == 1 && !isatty(fileno(stdout))) {
      result = printf("%s", password);
    } else {
      result = puts(password);
    }

    if (result < 0) {
      /* There was an output error, no sense trying to print an error message */
      retval = 1;
      goto cleanup;
    }
  }

cleanup:
  if (password != NULL) {
    explicit_bzero(password, password_length);
    free(password);
    password = NULL;
  }
  return retval;
}

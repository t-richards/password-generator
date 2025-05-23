#include "../apple.h"
#include "../password_generator.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

static int should_show_usage(int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
    if (strncmp("--help", argv[i], 6) == 0) {
      return 1;
    }
    if (strncmp("-h", argv[i], 2) == 0) {
      return 1;
    }
  }

  return 0;
}

static void show_usage(int argc, char *argv[]) {
  printf("Usage:  %s [password_length] [num_passwords]\n", argv[0]);
}

static int generate_and_print(char *password, int password_length,
                              int num_passwords) {
  int result = -1;

  /* Prevent process memory from swapping to disk */
  result = mlockall(MCL_CURRENT | MCL_FUTURE);
  if (result < 0) {
    int errno_sv = errno;
    fprintf(stderr, "Failed to lock process memory: %s\n", strerror(errno_sv));
    return EXIT_FAILURE;
  }

  /* Happy path: generate and print the password(s)! */
  for (int i = 0; i < num_passwords; i++) {
    /* Generate password */
    result = generate_password(password, password_length);
    if (result < 0) {
      int errno_sv = errno;
      fprintf(stderr, "Failed to generate password: %s\n", strerror(errno_sv));
      return EXIT_FAILURE;
    }

    /* Print password */
    if (num_passwords == 1 && !isatty(fileno(stdout))) {
      /* Omit newline when generating a single password to a non-TTY output */
      result = printf("%s", password);
    } else {
      result = puts(password);
    }

    if (result < 0) {
      int errno_sv = errno;
      fprintf(stderr, "Failed writing to stdout: %s\n", strerror(errno_sv));
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  char *password_buf = NULL;
  int password_length = 64;
  int num_passwords = 1;
  int retval = 0;

  /* Check if -h or --help was specified */
  if (should_show_usage(argc, argv)) {
    show_usage(argc, argv);
    return EXIT_SUCCESS;
  }

  /* Parse password length argument, if provided */
  if (argc >= 2) {
    password_length = atoi(argv[1]);
    if (password_length <= 0) {
      fprintf(stderr, "Password length must be greater than zero.\n");
      return EXIT_FAILURE;
    }
  }

  /* Parse number of passwords argument, if provided */
  if (argc >= 3) {
    num_passwords = atoi(argv[2]);
    if (num_passwords <= 0) {
      fprintf(stderr,
              "Number of passwords to generate must be greater than zero.\n");
      return EXIT_FAILURE;
    }
  }

  /* Allocate memory */
  password_buf = calloc(1, password_length + 1);
  if (password_buf == NULL) {
    int errno_sv = errno;
    fprintf(stderr, "Failed to allocate memory: %s\n", strerror(errno_sv));
    return EXIT_FAILURE;
  }

  /* Generate and print passwords */
  retval = generate_and_print(password_buf, password_length, num_passwords);

  /* Cleanup */
  if (password_buf != NULL) {
    explicit_bzero(password_buf, password_length);
    free(password_buf);
    password_buf = NULL;
  }
  return retval;
}

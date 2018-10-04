#include "password_generator.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/random.h>

int main(int argc, char *argv[]) {
  void *buf = NULL;
  int result = -1, retval = 0;
  ssize_t bytes_read = 0;
  int password_length = 64;

  if (argc >= 2) {
    password_length = atoi(argv[1]);
  }

  // Allocate memory
  buf = calloc(1, password_length);
  if (buf == NULL) {
    fprintf(stderr, "Failed to allocate memory: %s\n", strerror(errno));
    retval = 1;
    goto cleanup;
  }

  // Lock the heap-allocated buffer into memory
  // This prevents the memory page swapping to disk
  result = mlock(buf, password_length);
  if (result != 0) {
    fprintf(stderr, "Failed to lock process memory: %s\n", strerror(errno));
    retval = 1;
    goto cleanup;
  }

  // Get random data
  bytes_read = getrandom(buf, password_length, GRND_NONBLOCK);
  if (bytes_read == -1 || bytes_read < password_length) {
    fprintf(stderr, "Failed to read from random source: %s\n", strerror(errno));
    retval = 1;
    goto cleanup;
  }

  // Happy path: print the password!
  result = printf("%s", wrap_printable(buf, password_length));
  if (result < 0) {
    // There was an output error, no sense trying to print an error message
    retval = 1;
    goto cleanup;
  }

cleanup:
  if (buf != NULL) {
    explicit_bzero(buf, password_length);
    buf = NULL;
  }
  return retval;
}

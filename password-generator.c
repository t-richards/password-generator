#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/random.h>

int main(void) {
  void *buf = NULL;
  int result = -1, retval = 0;
  ssize_t bytes_read = 0;

  // TODO(tom): Allow this to be configured on the command line
  int password_length = 32;

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

  // Show the empty buffer
  result = printf("%.*s\n", password_length, buf);
  if (result < 0) {
    // Output error, no sense trying to print an error message
    retval = 1;
    goto cleanup;
  }

  // Get random data
  bytes_read = getrandom(buf, password_length, GRND_RANDOM);
  if (bytes_read == -1) {
    fprintf(stderr, "Failed to read from random source: %s\n", strerror(errno));
    retval = 1;
    goto cleanup;
  }

  // Happy path: print the password!
  // TODO(tom): Convert random nonsense into password. Use wrapping, not
  // clamping.
  result = printf("%.*s\n", password_length, buf);
  if (result < 0) {
    // Output error, no sense trying to print an error message
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

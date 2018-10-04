#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/random.h>

/**
 * Converts the bytes in buf to be printable ASCII characters
 * This is probably bad, needs review and tests
 */
static char *wrap_printable(void *buf, int len) {
  char *data = (char *)buf;

  for (int i = 0; i < len; i++) {
    // Clamp to signed char
    if (data[i] < CHAR_MIN) {
      data[i] = CHAR_MIN;
    } else if (data[i] > CHAR_MAX) {
      data[i] = CHAR_MAX;
    }

    // Wrap the value around the '!' to '~' range
    data[i] = (abs(data[i]) % (0x7E - 0x21 + 1)) + 0x21;
  }

  return data;
}

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

  // Get random data
  bytes_read = getrandom(buf, password_length, GRND_NONBLOCK);
  if (bytes_read == -1 || bytes_read < password_length) {
    fprintf(stderr, "Failed to read from random source: %s\n", strerror(errno));
    retval = 1;
    goto cleanup;
  }

  // Happy path: print the password!
  result = printf("%s\n", wrap_printable(buf, password_length));
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

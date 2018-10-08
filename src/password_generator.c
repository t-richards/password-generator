#include "password_generator.h"
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/random.h>
#include <sys/types.h>

/**
 * Converts the bytes in buf to be printable ASCII characters
 * This needs tests
 */
void wrap_printable(char *buf, int len) {
  char current = 0;

  for (int i = 0; i < len; i++) {
    // Zero out the most significant bit
    current = buf[i] & 0x7F;

    // Wrap the value around the '!' to '~' range
    buf[i] = (current % (0x7E - 0x21 + 1)) + 0x21;
  }
}

/**
 * Generates a password of length len into buf.
 * Returns a negative integer on failure, zero otherwise.
 */
int generate_password(char *buf, int len) {
  ssize_t bytes_read;

  // Draw random bytes from system random facility
  bytes_read = getrandom(buf, len, GRND_NONBLOCK);
  if (bytes_read == -1 || bytes_read < len) {
    return errno;
  }

  // Convert random bytes to printable ASCII
  wrap_printable(buf, len);

  return 0;
}

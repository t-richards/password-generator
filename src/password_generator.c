#include "password_generator.h"
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/random.h>

/**
 * Converts the bytes in buf to be printable ASCII characters
 * This is probably bad, needs review and tests
 */
void wrap_printable(char *buf, int len) {
  for (int i = 0; i < len; i++) {
    // Clamp to signed char
    if (buf[i] < CHAR_MIN) {
      buf[i] = CHAR_MIN;
    } else if (buf[i] > CHAR_MAX) {
      buf[i] = CHAR_MAX;
    }

    // Wrap the value around the '!' to '~' range
    buf[i] = (abs(buf[i]) % (0x7E - 0x21 + 1)) + 0x21;
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

#include "password_generator.h"
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/random.h>

/**
 * Converts the bytes in buf to be printable ASCII characters
 * This is probably bad, needs review and tests
 */
void wrap_printable(void *buf, int len) {
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
}

/**
 * Generates a password of length len into buf.
 * Returns a negative integer on failure, zero otherwise.
 */
int generate_password(char *buf, int len) {
  ssize_t bytes_read;

  // Draw random bytes from system random facility
  bytes_read = getrandom((void *)buf, len, GRND_NONBLOCK);
  if (bytes_read == -1 || bytes_read < len) {
    return errno;
  }

  // Convert random bytes to printable ASCII
  wrap_printable(buf, len);

  return 0;
}

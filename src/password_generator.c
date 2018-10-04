#include "password_generator.h"

/**
 * Converts the bytes in buf to be printable ASCII characters
 * This is probably bad, needs review and tests
 */
char *wrap_printable(void *buf, int len) {
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

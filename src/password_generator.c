#include "password_generator.h"
#include "apple.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include <sys/types.h>

/**
 * Generates a password of length len into buf.
 * Returns a negative integer on failure, zero otherwise.
 */
int generate_password(char *buf, int len) {
  int have = 0;

  while (have < len) {
    /* Draw a random byte from system random facility */
    char current = '\0';
    ssize_t bytes_read = getrandom(&current, 1, GRND_NONBLOCK);
    if (bytes_read != 1) {
      return errno;
    }

    /* Reject the byte if it is not a printable ASCII character */
    if (!isprint(current)) {
      continue;
    }

    buf[have] = current;
    have++;
  }

  /* Terminate with null byte */
  buf[len] = '\0';

  return 0;
}

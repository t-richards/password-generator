#include "password_generator.h"
#include "apple.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include <sys/types.h>

/* Return value for failure */
const int ERR_GENERATE = -1;

/**
 * Generates a password of length len into buf.
 * Note that buf must be at least len + 1 bytes long.
 * Returns -1 on failure, zero otherwise.
 */
int generate_password(char *buf, int len) {
  int have = 0;

  if (len <= 0 || buf == NULL) {
    return ERR_GENERATE;
  }

  while (have < len) {
    /* Draw a random byte from system random facility */
    char current = '\0';
    ssize_t bytes_read = getrandom(&current, 1, GRND_RANDOM);
    if (bytes_read != 1) {
      return ERR_GENERATE;
    }

    /* Reject the byte if it is not a printable ASCII character */
    if (!isprint(current) || isspace(current)) {
      continue;
    }

    buf[have] = current;
    have++;
  }

  /* Terminate with null byte */
  buf[len] = '\0';

  return 0;
}

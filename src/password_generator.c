#include "password_generator.h"
#include "apple.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/random.h>

const int GEN_SUCCESS = 0;
const int GEN_FAILURE = -1;

const int EXCLAMATION = 0x21;
const int TILDE = 0x7E;

/**
 * Generates a password of length len into buf.
 * Note that buf must be at least len + 1 bytes long.
 * Returns -1 on failure, zero otherwise.
 */
int generate_password(char *buf, int len) {
  int have = 0;

  if (len <= 0 || buf == NULL) {
    errno = EINVAL;
    return GEN_FAILURE;
  }

  while (have < len) {
    /* Draw a random byte from system random facility */
    unsigned char current = 0;
    ssize_t bytes_read = getrandom(&current, 1, GRND_RANDOM);
    if (bytes_read != 1) {
      return GEN_FAILURE;
    }

    /* Reject values outside the printable ASCII range */
    if (current < EXCLAMATION || current > TILDE) {
      continue;
    }

    buf[have] = current;
    have++;
  }

  /* Terminate with null byte */
  buf[len] = 0;

  return GEN_SUCCESS;
}

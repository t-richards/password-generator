#ifdef __APPLE__

#include <Security/Security.h>
#include <errno.h>
#include <string.h>

/* compatibility with getrandom */
ssize_t getrandom(void *buf, size_t buflen, unsigned int flags) {
  int result = SecRandomCopyBytes(kSecRandomDefault, buflen, buf);
  if (result == -1) {
    perror("Failed to copy bytes:");
    return result;
  }

  return buflen;
}

/* compatibility with explicit_bzero */
__attribute__((weak)) void __explicit_bzero_hook(void *buf, size_t len) {}

void explicit_bzero(void *buf, size_t len) {
  memset(buf, 0, len);
  __explicit_bzero_hook(buf, len);
}

#endif

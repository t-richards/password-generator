#ifdef __APPLE__

#include <Security/Security.h>
#include <string.h>

/* compatibility with getrandom */
ssize_t getrandom(void *buf, size_t buflen, unsigned int flags) {
  return SecRandomCopyBytes(kSecRandomDefault, buflen, buf);
}

/* compatibility with explicit_bzero */
__attribute__((weak)) void
__explicit_bzero_hook(void *buf, size_t len)
{
}

void
explicit_bzero(void *buf, size_t len)
{
  memset(buf, 0, len);
  __explicit_bzero_hook(buf, len);
}

#endif

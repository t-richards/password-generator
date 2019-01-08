#ifdef __APPLE__
#ifndef PASSWORD_GENERATOR_APPLE_H
#define PASSWORD_GENERATOR_APPLE_H

#include <stddef.h>
#include <unistd.h>

/* getrandom defs */
ssize_t getrandom(void *buf, size_t buflen, unsigned int flags);
#define GRND_NONBLOCK 1
#define GRND_RANDOM 2

/* explicit_bzero defs */
void explicit_bzero(void *buf, size_t len);

#endif /* PASSWORD_GENERATOR_APPLE_H */
#endif /* __APPLE__ */

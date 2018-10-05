#ifndef PASSWORD_GENERATOR_H
#define PASSWORD_GENERATOR_H

/* Convert bytes to ASCII */
void wrap_printable(char *buf, int len);

/* Generate a password of length len */
int generate_password(char *buf, int len);

#endif /* PASSWORD_GENERATOR_H */

# password-generator

A secure, sane-defaults password generator for Unix and GNU/Linux.

## How to know if this password generator is for you

 - You want a password generator which runs on the command line
 - You want a password generator with no dependencies (e.g. gcrypt, openssl)
 - You want a password generator with a small amount of code, so you can read and understand it easily
 - You want a program which fails loudly at the first sign of trouble
 - You trust your kernel's random source, but only when it has been seeded properly

## How to know if this password generator is *NOT* for you

 - You want your passwords to be "pronounceable" or "memorable"
 - You want a password generator with a GUI
 - You prefer to login to your password manager before being able to generate passwords
 - You have an old kernel or C library without the `getrandom` call in it

## Getting started (Docker)

```bash
# Generate one 64-character password
docker run --rm -it ghcr.io/t-richards/password-generator
```

## Getting started (build from source)

```bash
# Build program
make

# Show usage
$ ./password-generator --help
Usage: ./password-generator [password_length] [num_passwords]

# Generate one 64-character password
./password-generator

# Generate 8 32-character passwords
./password-generator 32 8
```

## License

[MIT](./LICENSE).

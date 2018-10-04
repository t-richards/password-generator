# password-generator

[![CircleCI](https://circleci.com/gh/t-richards/password-generator.svg?style=svg)](https://circleci.com/gh/t-richards/password-generator)

A secure, sane-defaults password generator for Unix and GNU/Linux.

## How to know if this password generator is for you

 - You want a password generator which runs on the command line
 - You want a password generator with no dependencies (e.g. gcrypt, openssl)
 - You want the password generator to have a small amount of code, so you can read and understand it easily
 - You want a program which fails loudly at the first sign of trouble
 - You trust your kernel's random source, but only when it has been seeded properly

## How to know if this password generator is *NOT* for you

 - You want your passwords to be "pronounceable" or "memorable"
 - You want a password generator with a GUI

## Getting started

```bash
# Build program
make

# Run program
./password-generator
```

### With Docker

```bash
# Build image
docker build -t trichards/password-generator .

# Run program
docker run --rm -it trichards/password-generator
```

## Roadmap

 - [x] Draw random bytes from the system `getrandom` facility
 - [x] Memory page locking
 - [x] ASCII character output
 - [ ] Command-line flags
 - [ ] Multiple password generation
 - [ ] Security review

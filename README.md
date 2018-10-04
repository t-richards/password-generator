# password-generator

A secure, sane-defaults password generator for Unix and GNU/Linux.

## How to know if this password generator is for you

 - You want a password generator which runs on the command line
 - You want a password generator with no dependencies (e.g. gcrypt, openssl)
 - You want the password generator to have a small amount of code, so you can read and understand it easily
 - You trust your kernel's blocking random source
 - You are willing to WAIT A DANG SECOND for your password to be generated

## How to know if this password generator is *NOT* for you

 - You want your passwords to be "pronounceable" or "memorable"
 - You want a password generator with a GUI
 - You are impatient and want LOTS OF PASSWORDS RIGHT NOW GIMME GIMME

## Getting started

```bash
# Build program
$ make

# Run program
$ ./password-generator
```

## Roadmap

 - [x] Secure random data generation
 - [x] Memory page locking
 - [x] ASCII character output
 - [ ] Command-line flags
 - [ ] Multiple password generation
 - [ ] Security review

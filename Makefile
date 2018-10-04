.PHONY: all
all: password-generator

.PHONY: dist
dist: password-generator
	strip password-generator

.PHONY: clean
clean:
	rm -f password-generator

.PHONY: lint
lint:
	clang-format -i src/password-generator.c

password-generator: src/password-generator.c
	$(CC) $(CFLAGS) -Wall -g -o password-generator src/password-generator.c

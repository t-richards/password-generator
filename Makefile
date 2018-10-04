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
	clang-format -i src/*.{c,h}

password-generator: src/*.c src/*.h
	$(CC) $(CFLAGS) -Wall -g -o password-generator src/password_generator.c src/main.c

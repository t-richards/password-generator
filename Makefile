.PHONY: all
all: password-generator

.PHONY: clean
clean:
	rm -f password-generator

.PHONY: lint
lint:
	clang-format -i password-generator.c

password-generator: password-generator.c
	$(CC) -o password-generator password-generator.c

.PHONY: all
all: password-generator

.PHONY: dist
dist: password-generator
	strip password-generator

.PHONY: clean
clean:
	rm -f password-generator
	rm -f test/password-generator-test

.PHONY: lint
lint:
	clang-format -i src/*.{c,h} test/*.c

.PHONY: test
test: password-generator-test
	test/password-generator-test

password-generator-test: test/*.c
	$(CC) $(CFLAGS) -Wall -g -o test/password-generator-test src/password_generator.c test/password_generator_test.c -lcheck

password-generator: src/*.c src/*.h
	$(CC) $(CFLAGS) -Wall -g -o password-generator src/password_generator.c src/main.c

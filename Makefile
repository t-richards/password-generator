CFLAGS := $(CFLAGS) -Wall -g
TEST_FLAGS := -fprofile-arcs -ftest-coverage -lcheck -lrt -lm
ifeq ($(shell uname),Darwin)
	CFLAGS := $(CFLAGS) -framework Security
endif

.PHONY: all
all: password-generator

.PHONY: dist
dist: password-generator
	strip password-generator

.PHONY: clean
clean:
	rm -f password-generator
	rm -f test/password-generator-test
	rm -f test/*.gcda
	rm -f test/*.gcno

.PHONY: lint
lint:
	clang-format -i **/*.{c,h}

.PHONY: test
test: password-generator-test
	test/password-generator-test

password-generator-test: test/*.c
	$(CC) $(CFLAGS) -o test/password-generator-test src/*.c test/password_generator_test.c $(TEST_FLAGS)

password-generator: src/*.c src/*.h
	$(CC) $(CFLAGS) -o password-generator src/*.c src/cli/main.c

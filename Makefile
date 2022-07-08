CFLAGS := $(CFLAGS) -g
TEST_FLAGS := $(CFLAGS) -fprofile-arcs -ftest-coverage
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
	rm -f *.gcda
	rm -f *.gcno

.PHONY: lint
lint:
	clang-format -i **/*.{c,h}

.PHONY: test
test: password-generator-test
	test/password-generator-test

password-generator-test: test/*.c
	$(CC) $(TEST_FLAGS) -Wall -g -o test/password-generator-test src/*.c test/password_generator_test.c -lcheck

password-generator: src/*.c src/*.h
	$(CC) $(CFLAGS) -Wall -g -o password-generator src/*.c src/cli/main.c

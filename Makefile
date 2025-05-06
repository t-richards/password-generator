CFLAGS := $(CFLAGS) -Wall -g
TEST_FLAGS := $(CFLAGS) -fprofile-arcs -ftest-coverage -lcheck
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
	$(CC) $(TEST_FLAGS) -o test/password-generator-test src/*.c test/password_generator_test.c 

password-generator: src/*.c src/*.h
	$(CC) $(CFLAGS) -o password-generator src/*.c src/cli/main.c

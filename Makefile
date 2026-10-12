CC = gcc
CFLAGS = -fPIC -Wall -Iinclude -Ierrors
OBJ = $(patsubst src/%.c,build/%.o,$(wildcard src/*.c)) build/error.o
MAIN = build/main.o
TEST_BIN = $(patsubst tests/%.c,build/%,$(wildcard tests/test_*.c))
HEADERS = $(wildcard include/*.h errors/*.h)
TEST_FLAGS = -Wall -g -fsanitize=address,undefined -Iinclude -Ierrors # o sanitize detecta memory-leaks

all: lib/libBstatStatic.a lib/libBstatDinamic.so

# -----

lib/libBstatStatic.a: $(OBJ)
	ar rcs $@ $^

lib/libBstatDinamic.so: $(OBJ)
	$(CC) -shared $^ -o $@

# -----

bin/bstat_static: $(MAIN)
	$(CC) $(MAIN) -Llib -lBstatStatic -o $@

bin/bstat_dinamic: $(MAIN)
	$(CC) $(MAIN) -Llib -lBstatDinamic -Wl,-rpath,'$$ORIGIN/../lib' -o $@

# -----

build/%.o: src/%.c $(HEADERS) | build
	$(CC) $(CFLAGS) -c $< -o $@

build/error.o: errors/error.c $(HEADERS) | build
	$(CC) $(CFLAGS) -c $< -o $@

build/main.o: app/main.c $(HEADERS) | build
	$(CC) $(CFLAGS) -c $< -o $@

build/test_%: tests/test_%.c $(OBJ) | build
	$(CC) $(TEST_FLAGS) $^ -o $@

# -----

build:
	mkdir -p build
	mkdir -p bin
	mkdir -p lib

# -----

clean:
	rm -f build/*.o build/test_*
	rm -f lib/*.a lib/*.so
	rm -f bin/bstat_dinamic bin/bstat_static

# -----

run: all
	./bin/bstat_dinamic

# -----

install: bin/bstat_static bin/bstat_dinamic

# -----

test: $(TEST_BIN)
	@for t in $(TEST_BIN); do \
		printf '\033[1;36m================== %s ==================\033[0m\n' $$t; \
		./$$t || exit 1; \
	done

# -----

.PHONY: all clean run install test
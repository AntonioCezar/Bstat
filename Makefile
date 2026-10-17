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
	$(CC) -shared $^ -o $@ -lm

# -----

bin/bstat_static: $(MAIN)
	$(CC) $(MAIN) -Llib -lBstatStatic -o $@ -lm

bin/bstat_dinamic: $(MAIN)
	$(CC) $(MAIN) -Llib -lBstatDinamic -Wl,-rpath,'$$ORIGIN/../lib' -o $@ -lm

# -----

build/%.o: src/%.c $(HEADERS) | build
	$(CC) $(CFLAGS) -c $< -o $@

build/error.o: errors/error.c $(HEADERS) | build
	$(CC) $(CFLAGS) -c $< -o $@

build/main.o: app/main.c $(HEADERS) | build
	$(CC) $(CFLAGS) -c $< -o $@

build/test_%: tests/test_%.c $(OBJ) | build
	$(CC) $(TEST_FLAGS) $^ -o $@ -lm

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

PREFIX ?= /usr/local

install: all bin/bstat_static bin/bstat_dinamic
	install -d $(DESTDIR)$(PREFIX)/lib
	install -d $(DESTDIR)$(PREFIX)/include/Bstat
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m 644 lib/libBstatStatic.a $(DESTDIR)$(PREFIX)/lib/
	install -m 755 lib/libBstatDinamic.so $(DESTDIR)$(PREFIX)/lib/
	install -m 644 include/*.h $(DESTDIR)$(PREFIX)/include/Bstat/
	install -m 755 bin/bstat_dinamic $(DESTDIR)$(PREFIX)/bin/

.PHONY: all clean run install uninstall test

# -----

test: $(TEST_BIN)
	@for t in $(TEST_BIN); do \
		printf '\033[1;36m================== %s ==================\033[0m\n' $$t; \
		./$$t || exit 1; \
	done

# -----

.PHONY: all clean run install test
CC = gcc
CFLAGS = -fPIC -Wall -Iinclude -Ierrors
OBJ = build/transformacao.o build/tendencia.o build/distribuicao.o build/dispersao.o build/dados.o build/error.o
MAIN = build/main.o

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
	$(CC) $(MAIN) -Llib -lBstatDinamic -Wl,-rpath,'$$ORIGIN/build' -o $@

# -----

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/error.o: errors/error.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/main.o: app/main.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# -----

build:
	mkdir -p build
	mkdir -p bin
	mkdir -p lib

# -----

clean:
	rm -f build/*.o
	rm -f lib/*.a lib/*.so
	rm -f bin/bstat_dinamic bin/bstat_static

# -----

run: all
	./bin/bstat_dinamic

# -----

install: bin/bstat_static bin/bstat_dinamic

# -----

test: 

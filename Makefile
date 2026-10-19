# variaveis
CC      := gcc
CFLAGS  := -Wall -Wextra -pedantic -O2 -fPIC -MMD -MP -Iinclude
LDLIBS  := -lm
PREFIX  ?= /usr/local

# encontrando os arquivos
SRCS  := $(wildcard src/*.c)
OBJS  := $(SRCS:src/%.c=build/%.o)
TESTS := $(patsubst tests/%.c,bin/%,$(wildcard tests/test_*.c))

# caminhos das bibliotecas
STATIC := lib/libaudio.a
SHARED := lib/libaudio.so

all: $(STATIC) $(SHARED) bin/app_static bin/app_shared

# pattern rule para transformar qualquer .c em .o
build/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# biblioteca estatica
$(STATIC): $(OBJS)
	@mkdir -p $(@D)
	ar rcs $@ $^

# biblioteca dinamica
$(SHARED): $(OBJS)
	@mkdir -p $(@D)
	$(CC) -shared $^ -o $@ $(LDLIBS)

# aplicacao principal usando a biblioteca estatica
bin/app_static: app/main.c $(STATIC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< $(STATIC) $(LDLIBS) -o $@

# aplicacao principal usando a biblioteca dinamica
bin/app_shared: app/main.c $(SHARED)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -Llib -laudio -Wl,-rpath,'$$ORIGIN/../lib' $(LDLIBS) -o $@

# testes
bin/test_%: tests/test_%.c $(STATIC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -Itests $< $(STATIC) $(LDLIBS) -o $@

test: $(TESTS)
	@for t in $(TESTS); do ./$$t || exit 1; done
	@echo "TODOS OS TESTES PASSARAM"

# execucao, executa o aplicativo com a estatica e com a dinamica
run: bin/app_static bin/app_shared
	./bin/app_static
	./bin/app_shared

# instala a biblioteca no sistema
install: $(STATIC) $(SHARED)
	install -d $(PREFIX)/lib $(PREFIX)/include/audio
	install -m 644 $(STATIC) $(SHARED) $(PREFIX)/lib
	install -m 644 include/*.h $(PREFIX)/include/audio

# limpeza
clean:
	rm -rf build lib bin

# rastreamento de dependencias
-include $(OBJS:.o=.d) $(wildcard bin/*.d)

.PHONY: all run test install clean

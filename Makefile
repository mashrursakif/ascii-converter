CC = gcc
CFLAGS = -Iinclude -Wall -O2

LDFLAGS = -lavformat -lavcodec -lavutil -lswscale -lm

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
TARGET = build/ascii_converter

all: $(TARGET)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

clean:
	rm -rf build

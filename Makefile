CC = gcc
CFLAGS = -Iinclude -Wall -O2

SRC = src/main.c src/image_process.c
OBJ = $(SRC:.c=.o)
TARGET = ascii_converter

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

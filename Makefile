CC = gcc

STD = -std=c99

CFLAGS = $(shell sdl2-config --cflags --libs)

LDFLAGS = -lm

SRC = $(wildcard src/*.c)

TARGET = wireframe

all:
	$(CC) $(SRC) $(STD) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

run:
	./$(TARGET)


clean:
	rm  $(TARGET)



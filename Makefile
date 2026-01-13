CC = gcc

STD = -std=c99

CFLAGS = $(shell sdl2-config --cflags --libs)

LDFLAGS = -lm

SRC = *.c

TARGET = wireframe

all:
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) $(STD) -o $(TARGET)

run:
	./$(TARGET)


clean:
	rm  $(TARGET)



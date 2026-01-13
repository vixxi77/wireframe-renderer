CC = gcc

STD = -std=c99

CFLAGS = $(shell sdl2-config --cflags --libs)

SRC = *.c

TARGET = wireframe

all:
	$(CC) $(CFLAGS) $(SRC) $(STD) -o $(TARGET)

run:
	./$(TARGET)


clean:
	rm  $(TARGET)



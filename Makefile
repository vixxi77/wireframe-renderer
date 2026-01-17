CC = gcc

STD = -std=c99

CFLAGS = -Wall -Wextra $(STD) $(shell sdl2-config --cflags)

LDFLAGS = $(shell sdl2-config --libs) -lm


SRC = $(wildcard src/*.c)

TARGET = wireframe

all: $(TARGET)
	
$(TARGET):
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

run:
	./$(TARGET)


clean:
	rm  $(TARGET)



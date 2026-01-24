CC = gcc

STD = -std=c99

CFLAGS = -Wall -Wextra $(STD) $(shell sdl2-config --cflags) -Iinclude -Imodels

LDFLAGS = $(shell sdl2-config --libs) -lm


SRC = $(wildcard src/*.c)

MODELS = $(wildcard models/*.c)

TARGET = wireframe

all: $(TARGET)
	
$(TARGET):
	$(CC) $(SRC) $(MODELS) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

run:
	./$(TARGET)


clean:
	rm -f $(TARGET)



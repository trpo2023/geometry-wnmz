CC = g++
CFLAGS = -Wall -Werror
TARGET = main
SOURCES = main.cpp utils.cpp

all: clean $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) geometry.txt

clean:
	rm -f $(TARGET); clear;

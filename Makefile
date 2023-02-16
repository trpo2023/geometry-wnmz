CC = g++
CFLAGS = -Wall -Werror
TARGET = main
SOURCES = main.cpp 

all: clean $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) test.txt

clean:
	rm -f $(TARGET); clear;

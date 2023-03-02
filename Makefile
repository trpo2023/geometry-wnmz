CC = g++
CFLAGS = -Wall -Werror
DEPS = -MMD

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

TARGET = main
OBJECTS = $(OBJ_DIR)/main.o $(OBJ_DIR)/utils.o

all: install clean $(TARGET)

install:
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(DEPS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(DEPS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) geometry.txt

clean:
	rm -f $(OBJ_DIR)/*; clear

.PHONY: all clean install
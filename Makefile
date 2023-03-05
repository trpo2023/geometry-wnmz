CC = g++
CFLAGS = -Wall -Werror
DEPS = -MMD

OUT_DIR = bin

TARGET = main
LIB_TARGET = libgeometry
LIB_OUT_NAME = $(LIB_TARGET).a

SRC_DIR = src
OBJ_DIR = obj
LIB_OBJ_DIR = $(OBJ_DIR)/$(LIB_TARGET)
LIB_SRC_DIR = $(SRC_DIR)/$(LIB_TARGET)
LIB_INC_DIR = $(LIB_SRC_DIR)/headers

LIB_OBJECTS = $(LIB_OBJ_DIR)/utils.o \
	$(LIB_OBJ_DIR)/point.o \
	$(LIB_OBJ_DIR)/figure.o \
	$(LIB_OBJ_DIR)/circle.o \
	$(LIB_OBJ_DIR)/triangle.o \
	$(LIB_OBJ_DIR)/parser.o

all: format clean $(OUT_DIR)/$(LIB_OUT_NAME) $(OUT_DIR)/$(TARGET)

$(OUT_DIR)/$(TARGET): $(SRC_DIR)/geometry/main.cpp $(OUT_DIR)/$(LIB_OUT_NAME)
	$(CC) $(CFLAGS) -I$(LIB_INC_DIR) -I$(LIB_SRC_DIR) -L$(OUT_DIR) -lgeometry -o $@ $^

$(OUT_DIR)/$(LIB_OUT_NAME): $(LIB_OBJECTS)
	ar rcs $@ $^

$(LIB_OBJ_DIR)/%.o: $(LIB_SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(DEPS) -I$(LIB_INC_DIR) -c $< -o $@

run: $(OUT_DIR)/$(TARGET)
	./$(OUT_DIR)/$(TARGET) geometry.txt

clean:
	rm -rf $(OBJ_DIR)/geometry/*.{o,d}
	rm -rf $(LIB_OBJ_DIR)/*.{o,d}

format:
	git ls-files *.{cpp,h} | xargs clang-format -i

.PHONY: all run clean format 

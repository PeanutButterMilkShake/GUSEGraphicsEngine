# Compiler and flags
CC = gcc
CXX = g++
CFLAGS = -Iinclude -Wall
CXXFLAGS = -Iinclude -Wall -std=c++17

# Linker flags: link GLFW, OpenGL, GDI32 on Windows
LDFLAGS = -lglfw



# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN = app.exe

# Sources
CPP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
C_SOURCES = $(SRC_DIR)/glad.c

# Objects
OBJ_CPP = $(CPP_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJ_C = $(C_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJ = $(OBJ_CPP) $(OBJ_C)

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN)

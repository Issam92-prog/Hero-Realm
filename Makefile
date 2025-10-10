CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRC_DIR = src
OBJ_DIR = build
BIN = hero_realms

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: all
	./$(BIN)

clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: all clean run

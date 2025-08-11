CXX = g++
CXXFLAXGS = -Ilibraries -Wall -Wextra -g -std=c++17 
LDFLAGS =

CODE_DIR = code
LIB_DIR = libraries
OBJ_DIR = obj
BIN_DIR = bin

SOURCES = $(wildcard $(CODE_DIR)/*.cpp)
OBJECTS = $(patsubst $(CODE_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

ifeq ($(OS),windows_NT)
	EXECUTABLE = $(BIN_DIR)/teenminal.EXECUTABLE
	RM = del /Q /F
	MKDIR_P = if not exist $(@D) mkdir $(@D)
else
	EXECUTABLE = $(BIN_DIR)/teenminal
	RM = rm -F
	MKDIR_P = mkdir -p
endif

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(MKDIR_P)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Teenminal built successfully :) $@"

$(OBJ_DIR)/%.o: $(CODE_DIR)/%.cpp
	@$(MKDIR_P)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	-$(RM) $(EXECUTABLE)
	-$(RM) $(OBJECTS)
	-$(RM) $(OBJECTS:.o=.d)
	@if exist $(OBJ_DIR) rmdir /S /Q $(OBJ_DIR) 2>nul || rm -rf $(OBJ_DIR)

run: all
ifeq ($(OS),windows_NT)
	.\$(EXECUTABLE)
else
	./$(EXECUTABLE)
endif

-include $(OBJECTS:.o=.d)

.PHONY: all clean run


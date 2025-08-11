# Compiler and flags
CXX       = g++
CXXFLAGS  = -Ilibraries -Wall -Wextra -g -std=c++17 -D_HAS_STD_BYTE=0 -DNOMINMAX
LDFLAGS   =

# Directories
CODE_DIR  = codes
LIB_DIR   = libraries
OBJ_DIR   = obj
BIN_DIR   = bin

# Platform-specific settings
ifeq ($(OS),Windows_NT)
	EXECUTABLE = $(BIN_DIR)/teenminal.exe
	RM         = del /Q /F
	MKDIR_P    = if not exist $(@D) mkdir $(@D)
else
	EXECUTABLE = $(BIN_DIR)/teenminal
	RM         = rm -f
	MKDIR_P    = mkdir -p $(@D)
endif

# Source and object files
CODE_SOURCES = $(wildcard $(CODE_DIR)/*.cpp)
LIB_SOURCES  = $(wildcard $(LIB_DIR)/*.cpp)
SOURCES      = $(CODE_SOURCES) $(LIB_SOURCES)

CODE_OBJECTS = $(patsubst $(CODE_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CODE_SOURCES))
LIB_OBJECTS  = $(patsubst $(LIB_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(LIB_SOURCES))
OBJECTS      = $(CODE_OBJECTS) $(LIB_OBJECTS)

# Main target
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(MKDIR_P)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Teenminal built successfully :) -> $@"

# Compile code sources
$(OBJ_DIR)/%.o: $(CODE_DIR)/%.cpp
	@$(MKDIR_P)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Compile library sources
$(OBJ_DIR)/%.o: $(LIB_DIR)/%.cpp
	@$(MKDIR_P)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Cleaning
clean:
	-$(RM) "$(EXECUTABLE)"
	-$(RM) $(OBJ_DIR)\*.o 2>nul || rm -f $(OBJ_DIR)/*.o
	-$(RM) $(OBJ_DIR)\*.d 2>nul || rm -f $(OBJ_DIR)/*.d
	@if exist $(OBJ_DIR) rmdir /S /Q $(OBJ_DIR) 2>nul || rm -rf $(OBJ_DIR)

# Run target
run: all
ifeq ($(OS),Windows_NT)
	$(EXECUTABLE)
else
	./$(EXECUTABLE)
endif

# Include dependency files
-include $(OBJ_DIR)/*.d

.PHONY: all clean run

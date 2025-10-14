# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

# Target executable
TARGET = LinkedListTest

# Source files
SRC = testProgLinkedList.cpp 

# Object files (replace .cpp with .o)
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Rule to build the object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

# Optional: run the program after building
run: $(TARGET)
	./$(TARGET)

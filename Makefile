# Define compiler and flags
CXX := g++
CXXFLAGS := -Wall -g

# Define libraries to link against
LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

# Define the output executable and source files
TARGET := prog1
SRCS := editor.cpp

# Define the default build target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

# Rule to clean up the build
clean:
	rm -f $(TARGET)

# Optional: Add .PHONY to prevent conflicts with files named 'clean' or 'all'
.PHONY: all clean

# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11
# Include directories
INCLUDES = -I.
# Source files
SRCS = ChangeItem.cpp ChangeRequest.cpp control.cpp DatabaseRecord.cpp main.cpp print.cpp ProductRelease.cpp ui.cpp User.cpp
# Object files
OBJS = $(SRCS:.cpp=.o)
# Executable name
EXEC = my_program

# Default target
all: $(EXEC)

# Rule to link the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean

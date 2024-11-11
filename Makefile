# Compiler
CC = clang


# Compiler flags
CFLAGS = -Wall -Wextra -Werror -std=c11

# Source files
SRCS = $(wildcard ./*.c)

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = wheel_database

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
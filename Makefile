# Source code must compile without errors against the c99 standard
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
INCLUDES = -I./include

SRCS = src/*.c
TARGET = tree

# One step compilation
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $@

clean:
	rm -f $(TARGET)

re:
	clean $(TARGET)
.PHONY: clean re

# Source code must compile without errors against the c99 standard
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
INCLUDES = -I./include

SRCS = src/*.c
TARGET = tree

# One step compilation
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) $(LDFLAGS) -o $@

debug-address: CFLAGS += -fsanitize=address -g
debug-address: LDFLAGS += -fsanitize=address
debug-address: $(TARGET)

clean:
	rm -f $(TARGET)

re:
	clean $(TARGET)
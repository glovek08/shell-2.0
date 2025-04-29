CC = gcc
CFLAGS = -Wall -Wextra -g -I. -Iutils
TARGET = shell
SOURCES = shell.c utils/print_prompt.c utils/getcmd.c 
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
		$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(TARGET) $(OBJECTS)

CC = gcc
CFLAGS = -s -Wall -Wextra -O2 -std=c99 -march=native

TARGET = index

SRCS = index.c $(wildcard custom/*.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean 
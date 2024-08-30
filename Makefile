USE_CLANG ?= 0
OPT_LEVEL ?= 2

CC = gcc
ifeq ($(USE_CLANG), 1)
	CC = clang
endif
CFLAGS = -Wall -Wextra -O$(OPT_LEVEL) -pedantic -march=native

TARGET = index

SRCS = $(TARGET).c $(wildcard custom/*.c)
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

allow_core:
	ulimit -c unlimited

run: $(TARGET) allow_core
	./$(TARGET)

time: $(TARGET) allow_core
	bash -c "time ./$(TARGET)"

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean allow_core

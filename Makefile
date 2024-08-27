CXX = gcc
DDEBUG ?= 0
CXXFLAGS = -s -Wall -Wextra -Werror -std=c++17 -O2 -fwhole-program -march=native
TARGET = index
SRCS = $(TARGET).c $(wildcard custom/*.c)
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	objdump -d -t -x -r -Mintel -S -C $(TARGET) > objdump.out

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -O2 -s -fwhole-program -march=native

.PHONY: run
run: $(TARGET)
	ulimit -c unlimited
	./$(TARGET)

.PHONY: debug
debug: $(TARGET)
	gdb -q -tui -ex "b _main" -ex "lay src" -ex "run" ./$(TARGET)

.PHONY: time
time: $(TARGET)
	ulimit -c unlimited
	bash -c "time ./$(TARGET)"

.PHONY: clean
clean:
	rm -rf $(TARGET) objdump.out $(OBJS) core
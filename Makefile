CXX = gcc
DDEBUG ?= 0
CXXFLAGS = -Wall -g -std=c++17 -O2 -fwhole-program -march=native
ifeq ($(DDEBUG), 1)
	CXXFLAGS += -DDEBUG
endif
TARGET = index
SRCS = $(TARGET).c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	objdump -d -t -x -r -Mintel -S -C $(TARGET) > objdump.out

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

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
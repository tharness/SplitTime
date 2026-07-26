all: demo test

SRCS := $(wildcard src/*.cpp)
DEMO_SRCS := main.cpp
HDRS := $(wildcard include/*.hpp)
TEST_SRCS := $(wildcard tests/*.cpp) $(wildcard tests/framework/*)

demo: $(SRCS) $(HDRS) $(DEMO_SRCS)
	mkdir -p bin
	g++ -Iinclude $(SRCS) $(DEMO_SRCS) -o bin/demo

test: $(SRCS) $(TEST_SRCS) $(HDRS)
	mkdir -p bin
	g++ -Iinclude -Itests/framework $(SRCS) $(TEST_SRCS) -o bin/test

clean:
	rm -f bin/*

.PHONY: all clean

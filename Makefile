all: demo test

SRCS := $(wildcard src/*.cpp)
DEMO_SRCS := main.cpp
HDRS := $(wildcard include/*.h)
TEST_SRCS := $(wildcard tests/*.cpp) $(wildcard tests/framework/*)

demo: $(SRCS) $(HDRS) $(DEMO_SRCS)
	mkdir -p bin
	g++ -Iinclude $(SRCS) $(DEMO_SRCS) -o bin/demo

test: $(SRCS) $(TEST_SRCS) $(HDRS)
	mkdir -p bin
	g++ -Iinclude -Itests/framework $(SRCS) $(TEST_SRCS) -o bin/test

arduino_project: $(SRCS) $(HDRS)
	mkdir -p arduino_project
	cp $(SRCS) arduino_project
	cp $(HDRS) arduino_project

clean:
	rm -f bin/*

.PHONY: all clean arduino_project

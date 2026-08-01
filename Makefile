all: test arduino_project

SRCS := $(wildcard src/*.cpp)
ARD_SRCS := $(wildcard arduino_project/*.cpp)
ARD_PROJ := $(wildcard arduino_project/*.ino)
ARD_HDRS := $(wildcard arduino_project/*.h)
HDRS := $(wildcard include/*.h)
TEST_SRCS := $(wildcard tests/*.cpp) $(wildcard tests/framework/*)

test: $(SRCS) $(TEST_SRCS) $(HDRS)
	mkdir -p bin
	g++ -Iinclude -Itests/framework $(SRCS) $(TEST_SRCS) -o bin/test

arduino_project: $(SRCS) $(HDRS)
	mkdir -p arduino_project/SplitTime
	cp $(SRCS) arduino_project/SplitTime
	cp $(HDRS) arduino_project/SplitTime
	cp $(ARD_SRCS) arduino_project/SplitTime
	cp $(ARD_HDRS) arduino_project/SplitTime
	cp $(ARD_PROJ) arduino_project/SplitTime

clean:
	rm -f bin/*

.PHONY: all clean arduino_project

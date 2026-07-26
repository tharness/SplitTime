all: demo test

SRCS := $(wildcard src/*.cpp)
DEMO_SRCS := main.cpp
HDRS := $(wildcard include/*.hpp)
TEST_SRCS := $(wildcard tests/*.cpp) $(wildcard tests/framework/*)

demo: $(SRCS) $(HDRS) $(DEMO_SRCS)
	g++ -Iinclude $(SRCS) $(DEMO_SRCS) -o demo

test: $(SRCS) $(TEST_SRCS) $(HDRS)
	g++ -Iinclude -Itests/framework $(SRCS) $(TEST_SRCS) -o test

clean:
	rm -f demo test

.PHONY: all clean

# SplitTime

SplitTime is a small stopwatch-style application that models its behavior as a state machine. The project is organized around clear state, transition, and action logic, making it straightforward to understand and extend.

## Project layout

- The legacy folder contains the original version of the project and is kept for reference.
- New development should be done at the root level, where the current source files, headers, and tests are located.

## Build with Make

The Makefile provides a simple way to build and test the project:

- make all builds both the demo and test binaries.
- make demo builds the interactive demo into bin/demo.
- make test builds the test executable into bin/test.
- make clean removes the generated files from the bin directory.

## State diagram

The image below shows the state diagram for the project. It describes the states, transitions, and actions used by the application.

![SplitTime state diagram](state_diagram/SplitTime.jpg)

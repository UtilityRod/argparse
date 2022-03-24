CFLAGS = -Wall -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wvla -Wfloat-equal
INCLUDE = -I../include/ -I../argparse/
obj_path := $(dir $(abspath ./obj/.gitkeep))
export CFLAGS
export INCLUDE
export obj_path


.PHONY: all
all: argparse src main

main:
	$(CC) $(CFLAGS) -o main $(wildcard ./obj/*.o)

.PHONY: src
src:
	$(MAKE) -C ./src/

.PHONY: argparse
argparse:
	$(MAKE) -C ./argparse
	
.PHONY: debug
debug: CFLAGS += -g
debug: clean
debug: all

.PHONY: clean
clean:
	$(RM) ./obj/*.o main

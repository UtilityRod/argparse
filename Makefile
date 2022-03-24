CFLAGS = -Wall -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wvla -Wfloat-equal
INCLUDE = -I../include/ -I../argparse/
export CFLAGS
export INCLUDE


.PHONY: all
all: argparse src main

main:
	$(CC) $(CFLAGS) -o main ./obj/argparse.o ./obj/main.o

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

CFLAGS += -Wall -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wvla -Wfloat-equal
CFLAGS += -I./include/

.PHONY: all
all: main

main: main.o argparse.a
	$(CC) $(CFLAGS) -o main ./obj/main.o ./bin/argparse.a
	
main.o: ./src/main.c
	$(CC) $(CFLAGS) -c ./src/main.c -o ./obj/main.o
	
argparse.a: argparse.o
argparse.a: ./bin/argparse.a(./obj/argparse.o)

argparse.o: ./lib/argparse.c
	$(CC) $(CFLAGS) -c ./lib/argparse.c -o ./obj/argparse.o

.PHONY: clean
clean:
	$(RM) ./obj/*.o main ./bin/argparse.a
	
.PHONY: debug
debug: clean
debug: CFLAGS += -g
debug: all

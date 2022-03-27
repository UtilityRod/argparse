sources := $(wildcard *.c)
objects := $(patsubst %.c, %.o, $(sources))
INCLUDE += -I./linked_list

.PHONY: all
all: linked_list $(objects)

.PHONY: linked_list
linked_list:
	$(MAKE) -C ./linked_list

$(objects): %.o: %.c

%.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $(obj_path)$@ -c $^
OBJ=\
	example/add.o\
	example/sub.o\
	example/entry.o

OBJ_TEST=\
	example/add.o\
	example/sub.o\
	src/init.o

.PHONY: all clean

all: calcler test

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_TEST)
	rm -f calcler test

calcler: $(OBJ)
	$(CC) $^ -o $@

test: $(OBJ_TEST)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $< -c -Iinclude -o $@

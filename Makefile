CC=gcc

all: inu

inu: insert-number.c
	$(CC) -o $@ $^

clean:
	rm -f inu

.PHONY: all clean

CFLAGS = -g -Wall -pedantic

all: whither-mmap
.Phony:all

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $^




.Phony: clean
clean:
	rm -f whither-mmap

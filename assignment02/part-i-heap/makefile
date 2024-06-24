CFLAGS = -g -Wall -pedantic


all: wheres-the-heap
.Phony:all

%.o: %.c
	 gcc $(CFLAGS) -c -o $@ $^
	
.Phony: clean
clean:
	rm -f wheres-the-heap

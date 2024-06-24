CFLAGS = -g -Wall -pedantic

all: swap-this swap-this-vm
.Phony:all

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $^

.Phony: clean 
clean: 
	rm -f swap-this

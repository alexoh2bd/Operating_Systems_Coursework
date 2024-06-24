CFLAGS = -g -Wall -pedantic

all: page-size
.Phony:all

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $^

.Phony: clean 
clean: 
	rm -f page-size

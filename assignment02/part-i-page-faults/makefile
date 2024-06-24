CFLAGS = -g -Wall -pedantic

all: page-faults
.Phony:all

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $^

.Phony: clean 
clean: 
	rm -f page-faults

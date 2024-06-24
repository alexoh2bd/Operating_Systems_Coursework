CFLAGS = -g -Wall -pedantic

all: maximum-resident
.Phony:all

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $^

.Phony: clean 
clean: 
	rm -f maximum-resident

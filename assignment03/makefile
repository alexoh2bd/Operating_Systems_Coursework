CFLAGS = -g -WALL -pedantic

all: fs-find fs-cat
.Phony:all

%.o: %.c 
	gcc $(CFLAGS) -c -o $@ $^

.Phony:clean
clean:
	rm -f fs-find fs-cat

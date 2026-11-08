run:
	make clean && make build && ./test
build:
	gcc -fsanitize=address,undefined -g solution.c test.c -o test
clean:
	rm test


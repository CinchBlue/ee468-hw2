all: merge468.c
	gcc -std=c99 -ansi -pthread merge468.c -o merge468

debug: merge468.c
	gcc -std=c99 -ansi -pthread -g -DDEBUG merge468.c -o merge468.debug

clean: ./merge468 ./merge468.debug
	rm ./merge468
	rm ./merge468.debug

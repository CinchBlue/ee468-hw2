all: main.c
	gcc -std=c99 -pthread main.c -o fibonacci

debug: main.c
	gcc -std=c99 -pthread -g -DDEBUG main.c -o fibonacci.debug

clean: ./fibonacci ./fibonacci.debug
	rm ./fibonacci
	rm ./fibonacci.debug

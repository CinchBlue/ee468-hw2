all: main.c
	gcc -std=c99 -pthread main.c -o primes

debug: main.c
	gcc -std=c99 -pthread -g -DDEBUG main.c -o primes.debug

clean: ./primes ./primes.debug
	rm ./primes
	rm ./primes.debug

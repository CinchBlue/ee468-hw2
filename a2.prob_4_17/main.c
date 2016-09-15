#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define BUFFER_SIZE 100

void* generate_fibonacci(void* args);

struct passed_info {
    unsigned long long max;
    unsigned long long arr[100];
};

int main(int argc, char** argv) {
    char buffer[BUFFER_SIZE];

    printf("%s", "Upper limit of primes (max of 100, must be positive): ");

    /* Read from the input, error message and abort if not */
    errno = 0;
    if (!fgets(buffer, sizeof(char)*BUFFER_SIZE, stdin)) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(-1);
    }

    /* Parse the string into max */
    unsigned long long max = 0;
    sscanf(buffer, "%llu", &max);

    #ifdef DEBUG
    printf("max: %llu\n", max);
    #endif /* DEBUG */

    if (max > 100) {
        fprintf(stderr, "%s\n", "error: the maximum number of Fibonacci numbers that can be generated is 100.");
        exit(-1);
    }

    /* Create thread */
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    
    /* Create struct passed_info and run thread. */
    struct passed_info shared_mem;
    shared_mem.max = max;
    pthread_create(&tid, &attr, generate_fibonacci, (void*)&shared_mem);

    #ifdef DEBUG
    printf("thread info: (tid: %04x)\n",
           (unsigned char)tid);
    #endif /* DEBUG */

    /* Wait until it joins. */
    pthread_join(tid, NULL);

    /* Print out the now filled memory up to <max> number of elements. */
    int i = 0;
    for (i = 0; i < max; ++i) {
        printf("#%d: %llu\n", i+1, shared_mem.arr[i]);
    }

    exit(0);
}

void* generate_fibonacci(void* args) {

    #ifdef DEBUG
    printf("%s\n", "Entering generate_fibonacci()");
    #endif /* DEBUG */
    
    unsigned long long max = ((struct passed_info*)(args))->max;     
    unsigned long long* arr = ((struct passed_info*)(args))->arr;

    unsigned long long i = 0;
    unsigned long long last_last_fib_num = 0;
    unsigned long long last_fib_num = 1;

    arr[0] = 1;
    for (i = 1; i < max; ++i) {

        unsigned long long sum = last_last_fib_num + last_fib_num;
        arr[i] = sum;

        last_last_fib_num = last_fib_num;
        last_fib_num = sum;
        
    }


    #ifdef DEBUG
    printf("%s\n", "Exiting generate_fibonacci().");
    #endif /* DEBUG */

    pthread_exit(0);
}

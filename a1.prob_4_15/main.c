#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define BUFFER_SIZE 80

void* primes(void* args);

int main(int argc, char** argv) {
    int i = 0;
    char buffer[BUFFER_SIZE];

    printf("%s", "Upper limit of primes (limit 80 char, must be positive): ");

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

    /* Create thread */
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    
    /* Create and run thread. */
    pthread_create(&tid, &attr, primes, (void*)&max);

    #ifdef DEBUG
    printf("thread info: (tid: %04x)\n",
           (unsigned char)tid);
    #endif /* DEBUG */

    /* Wait until it joins. */
    pthread_join(tid, NULL);

    exit(0);
}

void* primes(void* args) {

    #ifdef DEBUG
    printf("%s\n", "Entering primes()");
    #endif /* DEBUG */
    
    unsigned long long max = *((unsigned long long*)(args)); 
    
    unsigned long long i = 0;

    for (i = 2; i <= max; ++i) {
        unsigned long long divisor = 2;

        bool is_prime = true;
        for (divisor = 2; divisor <= i/2; ++divisor) {
            if (i % divisor == 0) {
                is_prime = false;
                break;
            }
        }

        if (is_prime) {
            printf("%llu\n", i);
        } else {
            continue;
        }
    }

    #ifdef DEBUG
    printf("%s\n", "Exiting primes().");
    #endif /* DEBUG */

    pthread_exit(0);
}

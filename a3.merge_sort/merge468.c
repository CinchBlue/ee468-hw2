/* EE468, HW2:
 * Austin Tasato
 *

/* 
 * This is an implementation of merge sort assuming the
 * data is an array a[] of length N, and N is a power of 2.
 *
 * The main() program uses a function called merge() which
 * merges subarrays in sorted order.  Rewrite the program
 * so that it uses threads to do the merging of the
 * subarrays.  In particular, each call to merge() creates
 * a thread.  
 *
 * The merging is done in a for-loop.  Each
 * pass through the for-loop causes subarrays of the same size
 * to be merged together.  The mergings within a pass should 
 * be done in parallel using one thread per merge. However,
 * the main program must wait for all the threads to complete
 * before doing another pass of the for-loop.  Thus, mergings
 * of subarrays of size 1 can be done in parallel, then
 * mergings of subarrays of size 2 can be done in parallel and
 * so forth.
 *
 * Use the pthread API
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 32 

/* Global variables -- be careful */
int a[N];     /* Array to sort */
int temp[N];  /* Temporary storage */

void genvalues(int n); /* Initializes array a[] */
void prnvalues(int n); /* Prints array a[] */
void merge(int first, int midpt, int last); /* Merges subarrays */

int main() 
{

    int arrsize;     /* Size of subarrays to merge */
    int numarr;      /* Number of subarrays */
    int newarrsize;  /* New subarray size */
    int newnumarr;   /* New number of subarrays */
    int i;
    int first;       /* Parameters used to merge two subarrays */
    int midpt;       /*   The first subarray starts at "first" and ends */ 
    int last;        /*   at "first+midpt-1".  The second subarray starts */
    /*   at "first+midpt" and ends at "last-1" */

    genvalues(N);    /* Initialize a[] with random values */
    printf("Initial values:\n");
    prnvalues(N);    /* Display the values */

    arrsize = 1;

    while (arrsize < N) {
        printf("*** Merging subarrays of size %d\n",arrsize);
        arrsize= 2*arrsize; /* merge subarrays to double subarray size */
        for (i=0; i<N; i+=arrsize) {
            first = i;
            midpt = first +(arrsize/2);
            if (first + arrsize < N) last = first + arrsize;
            else last = N;
            merge(first, midpt, last);
        }
    }

    printf("\nOutput:\n");
    prnvalues(N); /* Display the sorted values */

}

/*
 * Merges subarrays (a[first], ..., a[midpt-1])
 *    and (a[midpt],..., a[last-1]) into
 *    subarray temp[first],..., temp[last-1] in increasing order.
 *    Then it copies temp[first],..., temp[last-1] back into
 *    a[first],..., a[last-1].
 */
void merge(int first, int midpt, int last)
{
    int leftptr;   /* Pointers used in array a[ ] */
    int rightptr;
    int k;         /* pointer used in array temp[ ] */
    int delay;

    /* 
     * Do not delete the next three lines.  They cause the function to
     * delay by a amount that is proportional to the subarray it is merging
     */
    if (last-first > 0) delay = last-first;
    else delay = 1;
    usleep(delay*250000);

    leftptr = first;
    rightptr = midpt; 

    /* Merge values in the two arrays of a[] into temp[] */
    for(k=first; k<last; k++) {
        if (leftptr >= midpt) temp[k] = a[rightptr++];
        else if (rightptr >= last) temp[k] = a[leftptr++];
        else if (a[leftptr] < a[rightptr]) temp[k] = a[leftptr++];
        else if (a[leftptr] >= a[rightptr]) temp[k] = a[rightptr++];
        else printf("There's a bug \n");
    }

    /* Copy temp[] back to a[] */
    for(k=first; k<last; k++) a[k] = temp[k];

}



/*
 * Initializes array a[] with random values.
 */
void genvalues(int n)
{
    int k;
    int i;
    int current; 

    k = 2*n;
    current = 0;
    for (i=0; i<n; i++) {
        current = (current*73 + 19)%k;
        a[i] = current;
    }
}

/*
 * Prints the values in the array a[]
 */
void prnvalues(int n)
{
    int i;
    for (i=0; i<n; i++) {
        printf(" %d ", a[i]);
        if ((i+1)%10 == 0) printf("\n");
    }
    printf("\n");

}



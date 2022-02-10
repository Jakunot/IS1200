
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int counter;

#define COLUMNS 6


void print_numbers(int n) {
    printf("%10d ", n);  // prints numbers with a space of ten

    counter++;

    // since the program increments the value of counter by 1 each time the program prints
    // make sure that it doesn't exceed the COLUMN value which is 6
    //each time it prints 6 prime numbers it starts a new line

    if (counter % COLUMNS == 0 && counter != 0) {
        printf("\n");
    }
}

void print_sieves(int n) {
    int i, j;
    int *numbers = malloc(sizeof(int)*n); //fills the array with a bunch of '1',which assumes that every single number
                                          //is a prime number

    for (i = 0; i <= n; i++) {
        numbers[i-2] = 1;
    }

    for (i = 2; i * i <= n; i++) {       //Loops through all possible primes
        if (numbers[i] == 1) {           //Checks if current number is prime
            for (j = i * i; j <= n; j+= i) {    //marks all multiples of i as not prime
                numbers[j] = 0;
            }
        }
    }

    for (i = 2; i <= n; i++) {           //checks all possible primes
        if (numbers[i] == 1)             //Prints if number is prime
            print_numbers(i);
    }
    free(numbers);
}

int main()
{
    int n = 390000;
    clock_t tic = clock();
    print_sieves(n);
    clock_t toc = clock();
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    union {
        int i;
        char c[sizeof(int)];
    } x;
    x.i = 1;
    if(x.c[0] == 1)
        printf("little-endian\n");
    else    printf("big-endian\n");

    return 0;
}


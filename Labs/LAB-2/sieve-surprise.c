//
// Created by jabku on 2022-02-09.
//

#include <stdio.h>
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
    int distanceCounter = 0;
    int previousPrime = 2;
    int numbers[n];

    for (i = 0; i <= n; i++)  //fill the array with natural numbers upto 105
    {
        numbers[i] = 1;
    }

    for (i = 2; i * i <= n; i++)
    {
        if (numbers[i] == 1)
        {
            for (j = i * i; j <= n; j+= i)
            {
                numbers[j] = 0;
            }
        }
    }
// surprise assignment #1604
// Computes and prints out the number of times there is a distance of (n)
    for (i = 2; i <= n; i++) {
        if (numbers[i] == 1){
            print_numbers(i);
        if(i - previousPrime == 8)  //change value here(n)
            distanceCounter ++;
            previousPrime = i;
        }
    }
    printf("\n \n Number of times there is a distance of given number: %d", distanceCounter);

}

int main()
{
    int n = 105;                   //change number to see how long it takes to compute
    clock_t tic = clock();
    print_sieves(n);
    clock_t toc = clock();
    printf("\n \n Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return 0;
}


// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
/*
int main(int argc, char *argv[]){
    if(argc == 2)
        print_sieves( atoi(argv[1]));
    else
        printf("Please state an integer number.\n");
    return 0;
}
 */
/*
    print-prime.c
    By Jabez Otieno.
    Last modified: 2022-02-10
    This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

int counter = 0; // global variable counter

int is_prime(int n) {
    for (int i = 2; i <= n/2; i++) //prime numbers start at 2, and a prime number is only divisible by itself and 1
    {
        if (n % i == 0) // checks if the value divided by two returns a remainder
        {
            return 0;
        }
    }
    return 1;
}


void print_numbers(int n)
{
    printf("%10d ", n);  // prints numbers with a space of ten

    counter ++;

    // since the program increments the value of counter by 1 each time the program prints
    // make sure that it doesn't exceed the COLUMN value which is 6
    // each time it prints 6 prime numbers it starts a new line

    if(counter % COLUMNS == 0 && counter != 0)
    {
        printf("\n");
    }

}
int main(){
    for(int i = 2; i <= 105; i++)
    {
        if(is_prime(i))
        {
            print_numbers(i);
        }

    }
}
/*
// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
    if(argc == 2)
        print_primes(atoi(argv[1]));
    else
        printf("Please state an interger number.\n");
    return 0;
}
 */



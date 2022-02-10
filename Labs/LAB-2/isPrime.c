#include <stdio.h>
#include <stdbool.h>

int is_prime(int n) {
    for (int i = 2; i <= n / 2; i++) {  // a for loop to check whether a value is a prime number
        if (n % i == 0) {               // program checks if value of n divided by 2 has a remainder
            return false;
        }

    }
    return true;
}

int main(void )
{
    int num;
    printf("Enter any number between 1-100:\n");  //user input to try is different numbers are prime or not
    scanf("%d", &num);
    printf("User input is:\n%d\n", is_prime(num)); // Random number that the user entered
    printf("Original values\n");
    printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
    printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
    printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.

}

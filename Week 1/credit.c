// Tells if a credit card number taken as input is valid by checking its number of digits, 
// the first digits and by using Luhn's algorithm.

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int get_lenght(long num);
int get_digit(long num, int pos);
bool test(long num, int len);

int main (void)
{
    long num; // Stores the number
    int len; // Stores the number of digits

    // Takes the number given as input and calculates its number of digits
    printf("Number: ");
    scanf("%ld", &num);
    len = get_lenght(num);

    // Checks if the number of digits is valid
    if (len != 13 && len != 15 && len != 16){
        printf("INVALID\n");
        return 0;
    }

    // Use Luhn's Algorithm to check the validity of the number
    if (!test(num, len)){
        printf("INVALID\n");
        return 0;
    }

    // Gets the first two digits
    int first_digit = get_digit(num, 1);
    int second_digit = get_digit(num, 2);

    // Check what type of credit card it is
    if (len == 16 && first_digit == 5 && (second_digit >= 1 && second_digit <= 5)){
        printf("MASTERCARD\n");
    }
    else if ((len == 13 || len == 16) && first_digit == 4){
        printf("VISA\n");
    }
    else if (len == 15 && first_digit == 3 && (second_digit == 4 || second_digit == 7)){
        printf("AMEX\n");
    }
    else{
        printf("INVALID\n");
    }

    return 0;
}

int get_lenght(long num){
    int len = 0;
    while (num > 0){
        num /= 10;
        len++;
    }
    return len;
}

int get_digit(long num, int pos){
    long limit = pow(10, pos); // It's important to save limit as a long to avoid integer overflow
    while (num > limit){
        num /= 10;
    }
    num = num % 10;
    return (int) num;
}

bool test(long num, int len){
    int sum1 = 0, sum2 = 0, tmp;
    bool multiply_by_two = false;
    while(len > 0){
        tmp = get_digit(num, len);
        if (multiply_by_two){
            tmp = tmp * 2;
            // If the product has two digits they have to be added separately
            if (tmp > 9){
                int num1 = tmp / 10;
                int num2 = tmp % 10;
                tmp = num1 + num2;
            }
            sum2 = sum2 + tmp;
        }
        else{
            sum1 = sum1 + tmp;
        }
        multiply_by_two = !(multiply_by_two);
        len--;
    }
    return !((sum1 + sum2) % 10); // C counts 0 as false and every other integer as true
}

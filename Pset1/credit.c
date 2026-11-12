#include <stdio.h>

int luhn(long n, int *pc, int *n1, int *n2);

int main(void)
{
    long number;
    int count;
    printf("Number: ");
    while (scanf("%ld", &number) == 1)
    {
        int n1, n2;
        if (luhn(number, &count, &n1, &n2))
        {
            if (count == 13 && n1 == 4){
                printf("VISA\n");
                return 0;
            }
            if (count == 15 && n1 == 3 && (n2 == 4 || n2 == 7)){
                printf("AMEX\n");
                return 0;
            }
            if (count == 16){
                if (n1 == 5 && (n2 == 1 || n2 == 2 || n2 == 3 || n2 == 4 || n2 == 5)){
                    printf("MASTERCARD\n");
                    return 0;
                }
                else if (n1 == 4){
                    printf("VISA\n");
                    return 0;
                }
            }

            printf("INVALID\n");
            return 0;
        }
        else {
            printf("INVALID\n");
            return 0;
        }
        return 0;
    }
}

int luhn(long n, int *pc, int *n1, int *n2)
{
    *pc = 1;
    int sum = 0;
    while (n > 9)
    {
        int temp = n % 10;
        if (n >= 10 && n < 100){ *n2 = temp;}
        n = (n - temp) / 10;
        
        if (*pc % 2 == 1){ sum += temp;}
        else {
            temp *= 2;
            if (temp < 10) { sum += temp;}
            else {
                int temp1 = temp % 10;
                temp = (temp - temp1) / 10;
                sum += temp + temp1;
            }
        }
        (*pc)++;
    }
    *n1 = n;
    if (*pc % 2 == 0){
        n *= 2;
        if (n < 10){ sum += n;}
            else {
                int temp1 = n % 10;
                n = (n - temp1) / 10;
                sum += n + temp1;
            }
    }
    else { sum += n;}
   
    if (sum % 10 == 0){
        return 1;
    }
    else return 0; 
}
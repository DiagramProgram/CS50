#import <stdio.h>
#import <cs50.h>
#include <math.h>

int main(void) {
    long cardnum = get_long("Number: ");

    long ah = cardnum;
    int numdig = 0;

    while (ah != 0) {
        ah /= 10;
        ++numdig;
    }

    long x = 10;
    long mcardnum = cardnum;
    long specialsum = 0;
    long sum = 0;

    for (int s = 0; s < numdig; s++) {
        //printf("it is %li\n", x);
        if (x == 100 || x == 10000 || x == 1000000 || x == 100000000 || x == 10000000000 || x == 1000000000000 || x == 100000000000000 || x == 10000000000000000) {
            long m = mcardnum % x;
            specialsum = ((m*10) / x)*2;
            //printf("%li\n", specialsum);

            if (specialsum > 9) {
                sum += specialsum % 10;
                specialsum -= specialsum % 10;
                sum += specialsum/10;
            } else {
                sum += specialsum;
            }

            mcardnum -= m;
            //printf("%li\n", mcardnum);

        } else {
            long n = mcardnum % x;
            sum += (n*10) / x;

            mcardnum -= n;
            //printf("%li\n", mcardnum);
        }

        x *= 10;
    }
    //printf("%li\n", sum);

    if (sum % 10 != 0) {
        printf("INVALID\n");
    } else if (numdig == 15) {
        long temp1 = cardnum;
        temp1 -= temp1 % 10000000000000;
        if (temp1/10000000000000 == 34 || temp1/10000000000000 == 37) {
            printf("AMEX\n");
        } else {
            printf("INVALID\n");
        }
    } else if (numdig == 13) {
        long temp1 = cardnum;
        temp1 -= temp1 % 100000000000;
        if (temp1/1000000000000 == 4) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else if (numdig == 16) {
        long temp1 = cardnum;
        temp1 -= temp1 % 100000000000000;

        long temp2 = cardnum;
        temp2 -= temp2 % 1000000000000000;

        if (temp1/100000000000000 == 51 || temp1/100000000000000 == 52 || temp1/100000000000000 == 53 || temp1/100000000000000 == 54 || temp1/100000000000000 == 55) {
            printf("MASTERCARD\n");
        } else if (temp2/1000000000000000 == 4) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else {
        printf("INVALID\n");
    }

}
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int num;

    do {
        num = get_int("Height: ");
    } while(num < 1 || num > 8);

    for (int i = 0; i < num; i++) {

        for (int n = num-1; n > i; n--) {
            printf(" ");
        }

        for (int b = 0; b <= i; b++) {
            printf("#");
        }

        printf("  ");

        for (int a = 0; a <= i; a++) {
            printf("#");
        }

        /*for (int s = num-1; s > i; s--) {
            printf(" ");
        }*/

        printf("\n");
    }

}
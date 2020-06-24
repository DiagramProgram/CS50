#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[]) {
    string loweralpha = "abcdefghijklmnopqrstuvwxyz";
    string upperalpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


    if (argc > 2 || argc < 2) {
        printf("Usage: ./substitution key\n");
        return 1;
     } else if (strlen(argv[1]) < 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //string testcode = argv[1];

    for (int s = 0; s < strlen(argv[1]); s++) {
        if ((argv[1][s] < 65 || argv[1][s] > 90) && (argv[1][s] < 97 || argv[1][s] > 122)) {
            return 1;
        }

        int counter = 0;

        for (int ah = 0; ah < strlen(argv[1]); ah++) {
            if (argv[1][s] == argv[1][ah] && counter <= 1) {
                counter += 1;
                //printf("%i", counter);
            }

            if (counter >= 2) {
                return 1;
            }

        }
    }


    string ptext = get_string("plaintext:  ");

    char myarray[strlen(ptext)];

    for (int n = 0; ptext[n] != '\0'; n++) {

        if (ptext[n] >= 65 && ptext[n] <= 90) { //uppercase
            int j = 0;
            while (ptext[n] != upperalpha[j]) {
                j += 1;
            }

            if (argv[1][j] >= 97 && argv[1][j] <= 122) { //check if lowercase & if so, make uppercase
                argv[1][j] -= 32;
            }

            myarray[n] = argv[1][j];

        } else if (ptext[n] >= 97 && ptext[n] <= 122) { //lowercase

            int j = 0;
            while (ptext[n] != loweralpha[j]) {
                j += 1;
            }

            if (argv[1][j] >= 65 && argv[1][j] <= 90) {
                argv[1][j] += 32;
            }

            myarray[n] = argv[1][j];

        } else {

            myarray[n] = ptext[n];

        }
    } //end of for loop

    printf("ciphertext: ");
    for (int x = 0; x < strlen(ptext); x++) {
        printf("%c", myarray[x]);
    }
    printf("\n");

}
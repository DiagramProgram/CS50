#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void) {
    string text = get_string("Text: ");
    int sentences = 0;
    int letters = 0;
    int words = 1;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') { //COUNT NUMBER OF SENTENCES WE HAVE
            sentences ++;
        }

        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122)) { //COUNT NUMBER OF LETTERS
            letters ++;
        }

        if (text[i] == ' ') { //COUNTS NUMBER OF WORDS
            words ++;
        }
    }

    /*printf ("Sentences: %i\n", sentences);
    printf ("Letters: %i\n", letters);
    printf ("Words: %i\n", words);*/

    float lettersperwords = letters*(100.0/words);
    float sentencesperwords = sentences*(100.0/words);

    /*printf ("letters per words: %f\n", lettersperwords);
    printf ("sentence per words: %f\n", sentencesperwords);*/

    float gradelvl = round((0.0588 * lettersperwords) - (0.296 * sentencesperwords) - 15.8);

    if (gradelvl < 1) {
        printf ("Before Grade 1\n");
    } else if (gradelvl >= 16) {
        printf ("Grade 16+\n");
    } else {
        printf ("Grade %.0f\n", gradelvl);
    }
}
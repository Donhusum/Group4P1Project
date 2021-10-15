#include <stdio.h>
#include <string.h>

int main() {

    char StringMan1[30], StringMan2[30];  //Two Char arrays (strings) with capacity to contain 30 chars (a 30 letter string)
    long count = 0, sameWord = 0; //Long is just an int that can contain bigger numbers

    FILE *fileHandler1;
    FILE *fileHandler2; // Two pointers to handle our files

    // We have one of the fileHandler pointers open the first text file, it then checks whether it was successful.
    // If it is not, we get the Error message
    if ((fileHandler1 = fopen("HandInFromStudent.txt", "r")) == NULL) {
        printf("Error, no file \n");
    }

    // A loop that loads the next word from the first text file, and breaks if there are no more words to load (it have reached the end of the file)
    while (fscanf(fileHandler1, "%s", StringMan1) != -1) {

        // The other pointer opens the second file in the same manner that we opened the first one
        if ((fileHandler2 = fopen("OriginalDoc.txt", "r")) == NULL) {
            printf("Error, no file \n");
        }

        //Another loop like the first one
        while (fscanf(fileHandler2, "%s", StringMan2) != -1) {

            // strcmp compares two strings, and returns 0 if they are identical. We then write the identical word and count sameWord one up
            if (strcmp(StringMan2, StringMan1) == 0) {
                printf("%s, are in both docs\n");
                sameWord++;
            }
        }
        count++; // Counts one up every time we have checked a word
        fclose(fileHandler2); // Closes the file, so we can open it again and start over. There must be a better way to do this

    }

    // Prints out the number of words in the file, and tell us how many where identical. 
    printf("Words in the tested document %ld\n", count);
    printf("Words identical %ld\n", sameWord);

    fclose(fileHandler1);
    return 0;
}



//Dette er en comment gg

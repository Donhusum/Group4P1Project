#include <stdio.h>
#include <string.h>

int main() {

    char StringMan1[30], StringMan2[30];
    long count = 0, sameWord = 0;
    int a;

    FILE *fileHandler1;
    FILE *fileHandler2;

    if ((fileHandler1 = fopen(
            "HandInFromStudent.txt",
            "r")) == NULL) {
        printf("Error, no file \n");
    }


    while (fscanf(fileHandler1, "%s", StringMan1) != -1) {
        if ((fileHandler2 = fopen(
                "OriginalDoc.txt",
                "r")) == NULL) {
            printf("Error, no file \n");
        }
        while (fscanf(fileHandler2, "%s", StringMan2) != -1) {
            if (strcmp(StringMan2, StringMan1) == 0) {
                printf("%s, are in both docs\n");
                sameWord++;
            }
            //printf("%d %s \n", count, StringMan1);
            //printf("%d %s \n", count, StringMan2);
        }
        count++;
        fclose(fileHandler2);

    }
    printf("Words in the tested document %d\n", count);
    printf("Words identical %d\n", sameWord);


/*
    if (strcmp(StringMan2, StringMan1)==0)
        printf("2 and 1, They are the same\n");
    else
        printf("2 and 1, They are not the same\n");
*/

    fclose(fileHandler1);
    return 0;
}



//Dette er en comment

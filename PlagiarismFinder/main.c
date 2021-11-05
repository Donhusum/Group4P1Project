#include <stdio.h>
#include <string.h>
#include <ctype.h>

void createWorkFile(FILE *fileIn, FILE *fileOut);

int stringToNumber(char string[]);

int fourFirstStrings(char a[], char b[], char c[], char d[]);

void numberFile(FILE *fileHandler1);

int main() {

    char StringMan1[30], StringMan2[30];  //Two Char arrays (strings) with capacity to contain 30 chars (a 30 letter string)
    long count = 0, sameWord = 0; //Long is just an int that can contain bigger numbers

    FILE *fileHandler1;
    FILE *fileHandler2; // Two pointers to handle our files

    //Opens the original doc, and the copy that we will work with
    //File copier/converter, Copies the original doc into our tester doc, turning uppercase letters into lowercase, and
    // removing non-letter, non-blankspace symbols
    createWorkFile(fileHandler1 = fopen("OriginalDoc.txt", "r"), fileHandler2 = fopen("OriginalDocTester.txt", "w"));

    //A repeat of before, but just with the doc we want to compare.
    createWorkFile(fileHandler1 = fopen("HandInFromStudent.txt", "r"),
                   fileHandler2 = fopen("HandInFromStudentTester.txt", "w"));







/* Simple proof of concept string comparator
 *
    // We have one of the fileHandler pointers open the first text file, it then checks whether it was successful.
    // If it is not, we get the Error message
    if ((fileHandler1 = fopen("HandInFromStudentTester.txt", "r")) == NULL) {
        printf("Error, no file \n");
    }

    // A loop that loads the next word from the first text file, and breaks if there are no more words to load (it have reached the end of the file)
    while (fscanf(fileHandler1, "%s", StringMan1) != -1) {

        // The other pointer opens the second file in the same manner that we opened the first one
        if ((fileHandler2 = fopen("OriginalDocTester.txt", "r")) == NULL) {
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
    */

// Just a tester
    fileHandler1 = fopen("OriginalDocTester.txt", "r");
    numberFile(fileHandler1);
    fclose(fileHandler1);

    int chunkInt1, chunkInt2, chunkInt3;
    fileHandler1 = fopen("NumberFileOrigin.txt", "r");
    while (fscanf(fileHandler1, " %d %d", &chunkInt1, &chunkInt2) != -1)
        printf(" %d %d\n", chunkInt1, chunkInt2);

    //chunkInt3 = getchar();
    //putchar(chunkInt3);


    return 0;
}

// Create workfile function
void createWorkFile(FILE *fileIn, FILE *fileOut) {
    char StringBoy;
    while ((StringBoy = fgetc(fileIn)) != EOF) {
        if (isalpha(StringBoy) != 0 || StringBoy == ' ' || StringBoy == '.') {
            StringBoy = tolower(StringBoy);
            fputc(StringBoy, fileOut);
        }
    }
    fclose(fileIn);
    fclose(fileOut);
}



// Fingerprint function(s)

// Converts a string to a one-digit number
int stringToNumber(char string[]) {
    int sLenght = strlen(string);
    while (sLenght > 9)
        sLenght = sLenght - 10;
    return sLenght;
}

// Generates the chunk number
int fourFirstStrings(char a[], char b[], char c[], char d[]) {
    int i, numb = 0;
    numb = numb + 1000 * stringToNumber(a);
    numb = numb + 100 * stringToNumber(b);
    numb = numb + 10 * stringToNumber(c);
    numb = numb + stringToNumber(d);
    return numb;
}

// converts text to number chunks and puts them into a file
void numberFile(FILE *fileHandler1) {
    FILE *fileHandler2;
    char stringHandler1[40], stringHandler2[40], stringHandler3[40], stringHandler4[40], dotFinder;
    int numberChunk, duplicateChecker, dubVal;
    fileHandler2 = fopen("NumberFileOrigin.txt", "w+");
    while (fscanf(fileHandler1, " %s %s %s %s", stringHandler1, stringHandler2, stringHandler3, stringHandler4) > -1) {
        int len, i, j;

        
        //Fjerner punktummer til sidst
	    len = strlen(stringHandler1);
        for (i=0; i < len; i++){
            if (stringHandler1[i] == '.'){
	            for(j = i; j < len; j++){
                    stringHandler1[j] = stringHandler1[j+1];
                }
	        }
        }





	    len = strlen(stringHandler2);
	    if (stringHandler2[len-1] == '.'){
	        stringHandler2[len-1] = 0;
	    }
	    len = strlen(stringHandler3);
	    if (stringHandler3[len-1] == '.'){
	        stringHandler3[len-1] = 0;
	    }
	    len = strlen(stringHandler4);
	    if (stringHandler4[len-1] == '.'){
	        stringHandler4[len-1] = 0;
	    }
        
        
        
        
        printf(" %s %s %s %s\n", stringHandler1, stringHandler2, stringHandler3, stringHandler4);
        numberChunk = fourFirstStrings(stringHandler1, stringHandler2, stringHandler3, stringHandler4);
        /*
         * while (fscanf(fileHandler2, " %d %d", &duplicateChecker, &dubVal) != -1) {
            if (numberChunk == duplicateChecker) {
                dubVal++;

            }
        }
         */

        fprintf(fileHandler2, " %d %d\n", numberChunk, 1);
        while ((dotFinder = fgetc(fileHandler1)) != EOF) {
            //printf(" %c", dotFinder);
            if (dotFinder == '.') {
                break;
            }
        }
    }
    fclose(fileHandler2);
}


//Dette er en comment gg

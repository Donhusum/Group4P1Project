#include <stdio.h>
#include <string.h>
#include <ctype.h>

void createWorkFile(FILE *fileIn, FILE *fileOut);

int stringToNumber(char string[]);

int fourFirstStrings(char a[], char b[], char c[], char d[]);

void numberFile(FILE *fileHandler1, char location[]);

void numberAccumulator(char location[], int numberChunk);

void periodeRemover(char *dotString);

struct array {
    char string[40];
};

int main() {

    char StringMan1[30], StringMan2[30];  //Two Char arrays (strings) with capacity to contain 30 chars (a 30 letter string)

    FILE *fileHandler1;
    FILE *fileHandler2; // Two pointers to handle our files

    //Opens the original doc, and the copy that we will work with
    //File copier/converter, Copies the original doc into our tester doc, turning uppercase letters into lowercase, and
    // removing non-letter, non-blankspace symbols
    createWorkFile(fileHandler1 = fopen("OriginalDoc.txt", "r"), fileHandler2 = fopen("OriginalDocTester.txt", "w"));

    //A repeat of before, but just with the doc we want to compare.
    createWorkFile(fileHandler1 = fopen("HandInFromStudent.txt", "r"),
                   fileHandler2 = fopen("HandInFromStudentTester.txt", "w"));


// Just a tester
    fileHandler1 = fopen("OriginalDocTester.txt", "r");
    numberFile(fileHandler1, "NumberFileOrigin.txt");
    fclose(fileHandler1);

    fileHandler1 = fopen("HandInFromStudentTester.txt", "r");
    numberFile(fileHandler1, "NumberFileTester.txt");
    fclose(fileHandler1);


    int chunkInt1, chunkInt2, chunkInt3;
    fileHandler1 = fopen("NumberFileOrigin.txt", "r+");

    while (fscanf(fileHandler1, " %d %d", &chunkInt1, &chunkInt2) != EOF) {
        printf(" %d %d\n", chunkInt1, chunkInt2);
    }
    fclose(fileHandler1);

    return 0;
}

// Create workfile function
void createWorkFile(FILE *fileIn, FILE *fileOut) {
    char StringBoy;
    while ((StringBoy = fgetc(fileIn)) != EOF) {
        if (isalpha(StringBoy) != 0 || StringBoy == ' ' || StringBoy == '.' || StringBoy == 'æ' || StringBoy == 'ø' ||
            StringBoy == 'å') {
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
    int numb = 0;
    numb = numb + 1000 * stringToNumber(a);
    numb = numb + 100 * stringToNumber(b);
    numb = numb + 10 * stringToNumber(c);
    numb = numb + stringToNumber(d);
    return numb;
}

// converts text to number chunks and puts them into a file
void numberFile(FILE *fileHandler1, char location[]) {
    FILE *fileHandler2;
    char stringHandler1[40], stringHandler2[40], stringHandler3[40], stringHandler4[40], dotFinder, stringMult[4][40];
    struct array stringObject1;
    int numberChunk, endDot;
    fileHandler2 = fopen(location, "w+");
    while (fscanf(fileHandler1, " %s %s %s %s", stringHandler1, stringHandler2, stringHandler3, stringHandler4) > -1) {
        int len, i, j;

        //Fjerner punktummer til sidst

        //periodeRemover(stringHandler1); Do not currently work!
        len = strlen(stringHandler1);
        for (i = 0; i < len; i++) {
            if (stringHandler1[i] == '.') {
                for (j = i; j < len; j++) {
                    stringHandler1[j] = stringHandler1[j + 1];
                }
            }
        }
        len = strlen(stringHandler2);
        for (i = 0; i < len; i++) {
            if (stringHandler2[i] == '.') {
                for (j = i; j < len; j++) {
                    stringHandler2[j] = stringHandler2[j + 1];
                }
            }
        }
        len = strlen(stringHandler3);
        for (i = 0; i < len; i++) {
            if (stringHandler3[i] == '.') {
                for (j = i; j < len; j++) {
                    stringHandler3[j] = stringHandler3[j + 1];
                }
            }
        }
        len = strlen(stringHandler4);
        for (i = 0; i < len; i++) {
            if (stringHandler4[i] == '.') {
                endDot = 1;
                for (j = i; j < len; j++) {
                    stringHandler4[j] = stringHandler4[j + 1];
                }
            } else {
                endDot = 0;
            }
        }


        printf(" %s %s %s %s\n", stringHandler1, stringHandler2, stringHandler3, stringHandler4);
        numberChunk = fourFirstStrings(stringHandler1, stringHandler2, stringHandler3, stringHandler4);

        numberAccumulator(location, numberChunk);


        //Flytter dotten, medmindre der findes et slutpunktum
        if (!endDot) {
            while ((dotFinder = fgetc(fileHandler1)) != EOF) {
                //printf(" %c", dotFinder);
                if (dotFinder == '.') {
                    break;
                }
            }
        }
    }
    fclose(fileHandler2);
}

// Function that adds the fingerprint to a file, and increases its counter if it is a duplicate
void numberAccumulator(char location[], int numberChunk){
    FILE *fileHandler3;
    int dubVal = 0, duplicateChecker;
    fileHandler3 = fopen(location, "r+");
    while (fscanf(fileHandler3, " %d", &duplicateChecker) != EOF) {
        if (duplicateChecker == numberChunk) {
            fscanf(fileHandler3, " %d", &dubVal);
            fseek(fileHandler3, -2, SEEK_CUR);
            fprintf(fileHandler3, " %d", (dubVal+1));
            fseek(fileHandler3, 0, SEEK_CUR);
            break;
        } else {
            fscanf(fileHandler3, " %d", &duplicateChecker);
        }
        dubVal = 0;
    }
    if (dubVal == 0) {
        fprintf(fileHandler3, " %d %d\n", numberChunk, 1);
    }

    fclose(fileHandler3);
}

// Do currently not work
void periodeRemover(char *dotString) {
    int len, i, j;
    len = strlen(dotString);
    printf(" %c %c %c %c %c %c\n", dotString[0], dotString[1], dotString[2], dotString[3], dotString[4], dotString[5]);
    for (i = 0; i < len; i++) {
        if (dotString[i] == '.') {
            for (j = i; j < len; j++) {
                dotString[j] = dotString[j + 1];
            }
        }
    }
    printf(" %c %c %c %c %c %c\n", dotString[0], dotString[1], dotString[2], dotString[3], dotString[4], dotString[5]);
}





//Dette er en comment gg

//MIN BRANCH
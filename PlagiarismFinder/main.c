#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <dirent.h>

typedef struct {
    int bucket;    // START INDEX i.e. BUCKET NUMBER
    int dubval; // DUBLICATE VALUE
} bucket;

void createWorkFile(char origin[], char subject[]);

int stringToNumber(char string[]);

int fourFirstStrings(char a[][50], int n);

void numberFile(char origin[], char location[], int n);

void numberAccumulator(char location[], bucket buckets[], int n);

void periodeRemover(char *dotString);

void compare(char oriFile[], char testFile[]);

void printNumbers(char location[]);

int inputFile(char originalWorkFile[], char testItFile[]);

int compare_buckets(const void *a, const void *b);

void sort_buckets(bucket buckets[], int n);

int main() {

    char stringMan1[100] = "OriginalWork.txt", stringMan2[100] = "TextToBeTested.txt";
    int n = 4;
    //printf(" Plagiarism Finder: \n\n");

    //n = inputFile(stringMan1, stringMan2);

    //Opens the original doc, and the copy that we will work with
    //File copier/converter, Copies the original doc into our tester doc, turning uppercase letters into lowercase, and
    // removing non-letter, non-blankspace symbols
    createWorkFile(stringMan1, "OriginalDocTester.txt");
    createWorkFile(stringMan2, "HandInFromStudentTester.txt");

    printf(" OriginalWork:\n");
    numberFile("OriginalDocTester.txt", "NumberFileOrigin.txt", n);
    printf(" TextToBeTested:\n");
    numberFile("HandInFromStudentTester.txt", "NumberFileTester.txt", n);


    //printNumbers("NumberFileOrigin.txt");
    //printNumbers("NumberFileTester.txt");

    compare("NumberFileTester.txt", "NumberFileOrigin.txt");
    //compare("NumberFileTester.txt", "NumberFileOrigin.txt");

    remove("OriginalDocTester.txt");
    remove("HandInFromStudentTester.txt");
    remove("NumberFileOrigin.txt");
    remove("NumberFileTester.txt");


    printf("\n You can now close the window \n");
    scanf(" %s", stringMan1);

    return 0;
}

// Create workfile function
void createWorkFile(char origin[], char testFile[]) {
    FILE *fileIn = fopen(origin, "r");
    FILE *fileOut = fopen(testFile, "w");
    if (fileIn == NULL || fileOut == NULL) {
        printf("\n Error reading file %s :", origin);
        perror(" ");
        sleep(5);
        exit(0);
    } else {
        char StringBoy;
        while ((StringBoy = fgetc(fileIn)) != EOF) {
            if (StringBoy == '\n') {
                fputc(' ', fileOut);
            } else if (StringBoy == '!' || StringBoy == '?') {
                fputc('.', fileOut);
            } else if (isalpha(StringBoy) != 0 || StringBoy == ' ' || StringBoy == '.') {
                StringBoy = tolower(StringBoy);
                fputc(StringBoy, fileOut);
            }
        }
        fclose(fileOut);
        fclose(fileIn);
    }
}

// Fingerprint function(s)

// converts text to number chunks and puts them into a file
void numberFile(char origin[], char location[], int n) {
    int i;
    /*int buckets[10000];
    for ( i = 0; i < 10000; ++i) {
        buckets[i]=0;
    }*/
    bucket *buckets =  malloc(sizeof(*buckets) * ((int) pow(10, n)));

    for (i = 0; i < ((int) pow(10, n)); i++) {
        buckets[i].bucket = i;
        buckets[i].dubval = 0;
    }
    FILE *fileHandler1, *fileHandler2;
    char stringHandlerMaster[n][50], dotFinder;
    int numberChunk, end = 0, rewindVal;
    fileHandler1 = fopen(origin, "r");
    fileHandler2 = fopen(location, "w+");
    if (fileHandler1 == NULL || fileHandler2 == NULL) {
        perror("\n Error at numberFile: ");
    } else {
        while (1) {
            for (i = 0; i < n; ++i) {
                if (fscanf(fileHandler1, " %s", stringHandlerMaster[i]) < 1) {
                    end = 1;
                }
            }
            if (end == 1) {
                break;
            }

            //Fjerner punktummer til sidst
            for (i = 0; i < n; ++i) {
                periodeRemover(stringHandlerMaster[i]);
            }
            numberChunk = fourFirstStrings(stringHandlerMaster, n);
            //buckets[numberChunk]++;
            buckets[numberChunk].dubval++;


            // Flytter pointeren til næste punktum.
            for (i = 0; i < n; ++i) {
                rewindVal += (int)strlen(stringHandlerMaster[i]);
            }

            fseek(fileHandler1, -rewindVal, SEEK_CUR);
            while ((dotFinder = fgetc(fileHandler1)) != EOF) {
                if (dotFinder == '.') {
                    break;
                }
            }
            rewindVal = 0;
        }
        fclose(fileHandler1);
        fclose(fileHandler2);
    }
    sort_buckets(buckets, n);
    numberAccumulator(location, buckets, n);
    free(buckets);
}

void sort_buckets(bucket buckets[], int n) {
    qsort(buckets, ((int) pow(10, n)), sizeof(*buckets), compare_buckets);
}

int compare_buckets(const void *a, const void *b) {
    int value1 = ((bucket *) a)->dubval;
    int value2 = ((bucket *) b)->dubval;
    return value2 - value1;
}

// Generates the chunk number
int fourFirstStrings(char a[][50], int n) {
    int numb = 0, i;
    for (i = 0; i < n; ++i) {
        numb = numb * 10 + stringToNumber(a[i]);
    }

    return numb;
}

// Converts a string to a one-digit number
int stringToNumber(char string[]) {
    int sLength = strlen(string);
    while (sLength > 9)
        sLength = sLength - 10;
    return sLength;
}

// Function that adds the fingerprint to a file, and increases its counter if it is a duplicate
void numberAccumulator(char location[], bucket buckets[], int n) {

    FILE *fileHandler3;
    int i;
    fileHandler3 = fopen(location, "w");

    for (i = 0; i < ((int) pow(10, n)); ++i) {
        if (buckets[i].dubval > 0) {
            fprintf(fileHandler3, " %d %d \n", buckets[i].bucket, buckets[i].dubval);
        }
    }
    fclose(fileHandler3);
}

void periodeRemover(char *dotString) {
    int len, i, j;
    len = strlen(dotString);
    for (i = 0; i < len; i++) {
        if (dotString[i] == '.') {
            for (j = i; j < len; j++) {
                dotString[j] = dotString[j + 1];
            }
        }
    }
}

// Function that compare the two hashed files
void compare(char oriFile[], char testFile[]) {
    FILE *orif = fopen(oriFile, "r"), *testf = fopen(testFile, "r");
    if (orif == NULL || testf == NULL) {
        perror("\n Error at compare: ");
    } else {
        int oriNum, testNum, plagCount = 0, testCount = 0;
        while (fscanf(orif, " %d", &oriNum) != EOF) {
            while (fscanf(testf, " %d", &testNum) != EOF) {
                if (oriNum == testNum) {
                    plagCount++;
                }
                fscanf(testf, " %d", &testNum);
            }
            testCount++;
            rewind(testf);
            fscanf(orif, " %d", &oriNum);
        }
        printf(" Number of compared sentences = %d\n "
               "Number of plagiarism hits = %d\n "
               "Percentage plagiarism = %d%%\n",
               testCount, plagCount, 100 * plagCount / testCount);
        int plagPercent = 100 * plagCount / testCount;
        if (plagPercent > 80) {
            printf(" \n Plagiarism score: 4\n Almost definitely plagiarism, most likely the whole text \n");
        } else if (plagPercent > 60) {
            printf(" \n Plagiarism score: 3\n Very high probability of containing plagiarism, most likely several sections\n");
        } else if (plagPercent > 40) {
            printf(" \n Plagiarism score: 2\n High probability of containing plagiarism, can be one or more sections \n");
        } else if (plagPercent > 20) {
            printf(" \n Plagiarism score: 1\n Small chance of plagiarism, might only be a small section \n");
        } else
            printf(" \n Plagiarism score: 0\n No plagiarism or only a few sentences \n");
        fclose(orif);
        fclose(testf);
    }
}


void printNumbers(char location[]) {
    int chunkInt1, chunkInt2;
    FILE *fileHandler1 = fopen(location, "r");
    printf(" \n %s \n\n", location);
    if (fileHandler1 == NULL) {
        perror("\n Error at printNumbers: ");
    } else {
        while (fscanf(fileHandler1, " %d %d", &chunkInt1, &chunkInt2) != EOF) {
            printf(" %d %d\n", chunkInt1, chunkInt2);
        }
        printf("\n");
    }
    fclose(fileHandler1);
}

int inputFile(char originalWorkFile[], char testItFile[]) {
    int n;
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    printf(" Input the file name of the file to be tested (include '.txt'): \n");
    scanf(" %[A-Za-z0-9 ._-!]", testItFile);
    printf("\n Input the file name of the file to it should be tested against (include '.txt'): \n");
    scanf(" %[A-Za-z0-9 ._-!]", originalWorkFile);
    printf("\n Type a number: \n");
    scanf(" %d", &n);
    return n;
}


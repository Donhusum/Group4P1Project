#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>


int main(void)
{
    int WordLen;
    int i;
    int SentenceLen = 4;
    unsigned long SentenceSum;
    char SentenceArray[SentenceLen][20];
    printf("Insert %i word sentence \n", SentenceLen);
    for (i = 0; i < 4; i++)
        scanf("%s", SentenceArray[i]);
    for (i = 0; i < SentenceLen; i++)
        printf("%s ", SentenceArray[i]);
    printf("\n");
//    char *Sentence = (char *) malloc(SentenceLen * sizeof(char));
    for (i = 0; i < SentenceLen; i++)
    {
        int g;
        int sum = 0;
        for (g = 0; g < 4; g++)
        {
            int olehenriksen = SentenceArray[i][g];
            printf("Value of letter nr %i is: %i \n", g, olehenriksen);
        }
        printf("\n");
    }


 
// Plagiarism overview:
// 1. Open 2 files, original and hand-in.
    FILE *fileIn = fopen("origin.txt", "r");
    FILE *fileOut = fopen("output.txt", "w");
    if (fileIn == NULL || fileOut == NULL) 
    {
        perror("\n Error at createWorkFile: ");
    } 
    else 
    {
        char StringBoy;
        while ((StringBoy = fgetc(fileIn)) != EOF) {
            if (StringBoy == '\n')
            {
                fputc(' ',fileOut);
            } 
            else if (isalpha(StringBoy) != 0 || StringBoy == ' ' || StringBoy == '.' ) 
            {
                StringBoy = tolower(StringBoy);
                fputc(StringBoy, fileOut);
            }
        }
        fclose(fileOut);
        fclose(fileIn);
    }
}
//    1.1 Convert the two files into txt files where each sentence is separated by '\n', to be able to read individual lines.
// 2. Convert each word into hashes and put whole hashed sentences into arrays. Remember the line number of the hashed sentence.
// 3. Check each word in each document against each other and +1 to similarity_score for each individual sentence.
// 4. Lav score med formlen (antal_hits_i_n * antal_hits_i_m) / (antal_ord_i_n * antal_ord_i_m)
// 5. put score into 2-dimensional n*m array
// 6. print til csv fil https://www.youtube.com/watch?v=J3j04JrROFo
// 7. Analyser data og fortolk
// 8. ???
// 9. Profit

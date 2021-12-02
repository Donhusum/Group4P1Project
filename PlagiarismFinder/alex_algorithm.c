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
    FILE *fileIn = fopen("original.txt", "r");
    FILE *fileOut = fopen("output.txt", "w");
    if (fileIn == NULL || fileOut == NULL) 
    {
        perror("\n Error at createWorkFile2: ");
        fclose(fileOut);
        fclose(fileIn);
    } 
    else 
    {
        char StringBoy;
        while ((StringBoy = fgetc(fileIn)) != EOF) 
        {
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

    /*
    FILE *fileIn2 = fopen("output.txt", "r");
    
    FILE *fileOut2 = fopen("output2.txt", "w");
    if (fileIn == NULL || fileOut == NULL) 
    {
        perror("\n Error at createWorkFile: ");
        fclose(fileOut2);
        fclose(fileIn2);
    } 
    else 
    {
        char StringBoy;
        char StringBoy2;
        int counter=0;
        while ((StringBoy = fgetc(fileIn2)) != EOF) 
        {
            if(counter =! 0)
                StringBoy2 = fgetc(fileIn2);
            counter++;
            if (StringBoy == ' ' && StringBoy2 == '.')
            {
                fputc('\n',fileOut2);
            }
            else if (StringBoy != NULL) 
            {
                fputc(StringBoy, fileOut2);
            }
        }
        fclose(fileOut2);
        fclose(fileIn2);
    }
    */
    FILE *fileIn2 = fopen("output.txt", "r");
    FILE *fileIn3 = fopen("output.txt", "r");
    FILE *fileOut2 = fopen("output2.txt", "w");
    if (fileIn2 == NULL || fileOut2 == NULL) 
    {
        perror("\n Error at createWorkFile: ");
        fclose(fileOut2);
        fclose(fileIn2);
    } 
    else 
    {
        char StringBoy, dotFinder;
        int DotFinderDelay=0;
        while ((StringBoy = fgetc(fileIn2)) != EOF) 
        {
            if(
                DotFinderDelay != 0)
                dotFinder = fgetc(fileIn3);
            DotFinderDelay++;
            if (StringBoy == ' ' && dotFinder == '.')
            {
                fputc('\n',fileOut2);
            }
            else if (StringBoy != '.') 
            {
                fputc(StringBoy, fileOut2);
            }
        }
        fclose(fileOut2);
        fclose(fileIn2);
    }

    return 0;
}

//      1.1 Convert the two files into txt files where each sentence is separated by '\n', to be able to read individual lines.
//      1.2 To check for abbreviations convert any combination of chars in "original.txt" using fgets()
//          (E.g. 'This is text dr. a.k.a. penis' ===> '52645(This) 32(is) 23535(text) 32545(dr.) 123352(a.k.a.) 2355335(penis))
//          separated by whitespace into hash  and check each hash against database of abbreviations.
//          If abbreviation is found; insert abbreviation without dot/punktum(point) into "output.txt"
//          If abbreviation is not found; instert the word into "output.txt", this will include dots
// 2. Convert each word into hashes and put whole hashed sentences into arrays. Remember the line number of the hashed sentence.
// 3. Check each word in each document against each other and +1 to similarity_score for each individual sentence.
// 4. Lav score med formlen (antal_hits_i_n * antal_hits_i_m) / (antal_ord_i_n * antal_ord_i_m)
// 5. put score into 2-dimensional n*m array
// 6. print til csv fil https://www.youtube.com/watch?v=J3j04JrROFo
// 7. Analyser data og fortolk
// 8. ???
// 9. Profit

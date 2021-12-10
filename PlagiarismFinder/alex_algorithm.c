#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
int RealWordCounter;

int main(void)
{
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
                fputc('\n',fileOut);
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
    FILE *fileIn = fopen("output.txt", "r");
    
    FILE *fileOut = fopen("output2.txt", "w");
    if (fileIn == NULL || fileOut == NULL) 
    {
        perror("\n Error at createWorkFile: ");
        fclose(fileOut);
        fclose(fileIn);
    } 
    else 
    {
        char StringBoy;
        char StringBoy2;
        int counter=0;
        while ((StringBoy = fgetc(fileIn)) != EOF) 
        {
            if(counter =! 0)
                StringBoy2 = fgetc(fileIn);
            counter++;
            if (StringBoy == ' ' && StringBoy2 == '.')
            {
                fputc('\n',fileOut);
            }
            else if (StringBoy != NULL) 
            {
                fputc(StringBoy, fileOut);
            }
        }
        fclose(fileOut);
        fclose(fileIn);
    }
    */
    fileIn = fopen("output.txt", "r");
    FILE *dotFinderFile = fopen("output.txt", "r");
    fileOut = fopen("output2.txt", "w");
    if (fileIn == NULL || fileOut == NULL) 
    {
        perror("\n Error at createWorkFile: ");
        fclose(fileOut);
        fclose(fileIn);
    }
    else
    {
        char StringBoy, dotFinder;
        int DotFinderDelay=0;
        while ((StringBoy = fgetc(fileIn)) != EOF) 
        {
            if(
                DotFinderDelay != 0)
                dotFinder = fgetc(dotFinderFile);
            DotFinderDelay++;
            if (StringBoy == ' ' && dotFinder == '.')
            {
                fputc('\n',fileOut);
            }
            else if (StringBoy != '.') 
            {
                fputc(StringBoy, fileOut);
            }
        }
        fclose(fileOut);
        fclose(fileIn);
        fclose(dotFinderFile);
    }

//
//  This code opens the final outputtext and counts the words in it. Using isspace to check if a char is a space and checks the previous symbol to determine if
//  the space marked the end of a word or is just space.
//
    fileIn = fopen("output2.txt", "rb+");
    int wordcounter=1;
    char symbol;
    printf("\n Symbols are: \n");
    while((symbol=fgetc(fileIn))!= EOF)
    {   
        printf("%c", symbol);
        if(isspace(symbol))
        {
            fseek(fileIn, -2, SEEK_CUR);
            symbol=fgetc(fileIn);
            if(isspace(symbol))
            {
                symbol = ' ';
            }
            if(isspace(symbol) == 0)
            {   
                wordcounter++;
            }
            symbol=fgetc(fileIn);
        }
    }
    RealWordCounter=wordcounter;
    printf("\n Word count: %i\n", RealWordCounter);
    fclose(fileIn);





    FILE *fileFormatted = fopen("output2.txt", "r");
    FILE *testoutput = fopen("testoutput.txt", "w");
    char str1[200];
    char newString[50][50]; 
    int j,ctr;
    int df=1;
    while (fgets(str1, sizeof str1, fileFormatted) != NULL) 
    {
        printf("%i. str1 = \"%s\"",df, str1);
        j=0; 
        ctr=0;
        int i=0;
        for(i=0;i<=(strlen(str1));i++)
        {
            // if space or NULL found, assign NULL into newString[ctr]
            if(str1[i]==' '||str1[i]=='\0')
            {
                newString[ctr][j]='\0';
                ctr++;  //for next word
                j=0;    //for next word, init index to 0
            }
            else
            {
                newString[ctr][j]=str1[i];
                j++;
            }
        }
        df++;
        fwrite(str1, sizeof(char), sizeof(str1), testoutput);
    }
    fclose(fileFormatted);
    fclose(testoutput);








    int WordLen;
    int SentenceLen = 4;
    unsigned long SentenceSum;
    char SentenceArray[SentenceLen][30];
//    char *Sentence = (char *) malloc(SentenceLen * sizeof(char));
    int i;
    for (i = 0; i < SentenceLen; i++)
    {
        int g;
        int sum = 0;
        for (g = 0; g < 4; g++)
        {
            int olehenriksen = SentenceArray[i][g];
            printf("\nValue of letter nr %i is: %i \n", g, olehenriksen);
        }
        printf("\n");
    }
    /*
//copied from https://www.w3resource.com/c-programming-exercises/string/c-string-exercise-31.php
    char str1[100];
    char newString[10][10]; 
    int i,j,ctr;
       printf("\n\n Split string by space into words :\n");
       printf("---------------------------------------\n");    
 
    printf(" Input  a string : ");
    fgets(str1, sizeof str1, stdin);	
 
    j=0; ctr=0;
    for(i=0;i<=(strlen(str1));i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if(str1[i]==' '||str1[i]=='\0')
        {
            newString[ctr][j]='\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            newString[ctr][j]=str1[i];
            j++;
        }
    }
    printf("ctr is now %i \n", ctr);
    printf("\n Strings or words after split by space are :\n");
    for(i=0;i < ctr;i++)
        printf(" %s\n",newString[i]);
    */
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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int main(void)
{
    int WordLen;
    int i;
    int sentenceLen = 4;
    unsigned long SentenceSum;
    char SentenceArray[sentenceLen][20];
    printf("Insert %i word sentence \n", sentenceLen);
    for (i = 0; i < 4; i++)
        scanf("%s", SentenceArray[i]);
    for (i = 0; i < sentenceLen; i++)
        printf("%s ", SentenceArray[i]);
    printf("\n");
//    char *Sentence = (char *) malloc(sentenceLen * sizeof(char));
    for (i = 0; i < sentenceLen; i++)
    {
        int g;
        int sum = 0;
        int WordLen;
        
        for (g = 0; g < 4; g++)
        {
            int olehenriksen = SentenceArray[i][g];
            printf("Value of letter nr %i is: %i \n", (g+1), olehenriksen);
        }
        printf("\n");
    }
    return 0;
}
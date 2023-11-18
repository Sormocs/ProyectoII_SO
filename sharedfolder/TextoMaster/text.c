#include <stdio.h>
#include <stdlib.h>
#include "../Encriptado/ROT13.h"
#include <string.h>

#define MAX_WORD_LENGTH 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

char* findTrendWord(char* filename) {

  	FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    char word[MAX_WORD_LENGTH];
    WordCount *wordCounts = NULL;
    int wordCountsSize = 0;

    while (fscanf(file, "%99s", word) == 1) {
        int found = 0;
        for (int i = 0; i < wordCountsSize; ++i) {
            if (strcmp(wordCounts[i].word, word) == 0) {
                wordCounts[i].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            wordCountsSize++;
            wordCounts = realloc(wordCounts, wordCountsSize * sizeof(WordCount));
            strcpy(wordCounts[wordCountsSize - 1].word, word);
            wordCounts[wordCountsSize - 1].count = 1;
        }
    }

    fclose(file);

    if (wordCountsSize == 0) {
        printf("No words found in the file.\n");
        free(wordCounts);
        return NULL;
    }

    int maxCountIndex = 0;
    for (int i = 1; i < wordCountsSize; ++i) {
        if (wordCounts[i].count > wordCounts[maxCountIndex].count) {
            maxCountIndex = i;
        }
    }

    char *mostRepeatedWord = strdup(wordCounts[maxCountIndex].word);
    free(wordCounts);

    return mostRepeatedWord;
}


//int main() {

//    divideFile();
    //printf(findTrendWord("outputB.txt"));
//    char* trend = findTrendWord("input.txt");
//    if (trend) {
//        printf("Trend word is: %s\n", trend);
//    } else {
//        printf("No trend word found\n");
//    }
    
    

//    printf("Files divided into outputA.txt and outputB.txt.\n");

//    return 0;
//}


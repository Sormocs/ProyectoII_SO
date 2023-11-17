//
// Created by marko on 11/13/2023.
//

#ifndef TEXT_H
#define TEXT_H

#define MAX_WORD_LENGTH 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

char* findTrendWord(char* filename);

#endif //TEXT_H

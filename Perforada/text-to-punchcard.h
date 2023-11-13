//
// Created by marko on 11/13/2023.
//

#ifndef PROYECTO_2_TEXT_TO_PUNCHCARD_H
#define PROYECTO_2_TEXT_TO_PUNCHCARD_H

#define MAX_POSITIONS 115

typedef struct {
    char character;
    int* numbers;
    int numNumbers;
} CharInfo;

void addNumber(CharInfo charInfo[], char ch, int number);

int* getNumbers(CharInfo charInfo[], char ch, int index, int* numNumbers);

typedef struct {
    char character;
    int* numbers;
    int numNumbers;
} CharacterNumbers;


CharacterNumbers* getCharacterNumbersForWord(CharInfo charInfo1[], CharInfo charInfo2[], const char* word, int index, int* totalCharacters);

void initializeCharacterNumbers(CharInfo charInfo[], int set);

#endif //PROYECTO_2_TEXT_TO_PUNCHCARD_H

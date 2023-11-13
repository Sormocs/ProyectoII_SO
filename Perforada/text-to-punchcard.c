// matrix_parser.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text-to-punchcard.h"

void addNumber(CharInfo charInfo[], char ch, int number) {
    for (int i = 0; i < MAX_POSITIONS; ++i) {
        if (charInfo[i].character == '\0') {
            charInfo[i].character = ch;
            charInfo[i].numNumbers = 0;
            charInfo[i].numbers = NULL;
        }

        // Añadir numero acá
        if (charInfo[i].character == ch && charInfo[i].numNumbers < MAX_POSITIONS) {
            charInfo[i].numbers = (int*)realloc(charInfo[i].numbers, sizeof(int) * (charInfo[i].numNumbers + 1));
            if (charInfo[i].numbers == NULL) {
                // Handle memory allocation error

            }

            charInfo[i].numbers[charInfo[i].numNumbers] = number;
            charInfo[i].numNumbers++;
            break;
        }
    }
}

int* getNumbers(CharInfo charInfo[], char ch, int index, int* numNumbers) {
    for (int i = 0; i < MAX_POSITIONS; ++i) {
        if (charInfo[i].character == ch) {
            *numNumbers = charInfo[i].numNumbers;

            int* numbers = (int*)malloc(sizeof(int) * (*numNumbers));
            if (numbers == NULL) {
                *numNumbers = 0;
                return NULL;
            }

            for (int j = 0; j < charInfo[i].numNumbers; ++j) {
                numbers[j] = charInfo[i].numbers[j];
            }

            return numbers;
        }
    }

    *numNumbers = 0;
    return NULL;
}

CharacterNumbers* getCharacterNumbersForWord(CharInfo charInfo1[], CharInfo charInfo2[], const char* word, int index, int* totalCharacters) {
    int wordLength = strlen(word);

    CharInfo* selectedCharInfo = (index == 1) ? charInfo1 : charInfo2;

    CharacterNumbers* characterNumbersArray = (CharacterNumbers*)malloc(sizeof(CharacterNumbers) * wordLength);
    if (characterNumbersArray == NULL) {
        // Handle memory allocation error
        *totalCharacters = 0;
        return NULL;
    }

    *totalCharacters = 0;

    for (int i = 0; i < wordLength; ++i) {
        char currentChar = word[i];
        int numCharNumbers;
        int* charNumbers = getNumbers(selectedCharInfo, currentChar, index, &numCharNumbers);

        if (charNumbers != NULL) {
            int* numbers = (int*)malloc(sizeof(int) * numCharNumbers);
            if (numbers == NULL) {
                // Handle memory allocation error
                free(charNumbers);
                return NULL;
            }

            for (int j = 0; j < numCharNumbers; ++j) {
                numbers[j] = charNumbers[j];
            }

            characterNumbersArray[*totalCharacters].character = currentChar;
            characterNumbersArray[*totalCharacters].numbers = numbers;
            characterNumbersArray[*totalCharacters].numNumbers = numCharNumbers;

            (*totalCharacters)++;

            free(charNumbers);
        }
    }

    return characterNumbersArray;
}

void initializeCharacterNumbers(CharInfo charInfo[], int set) {
    for (int i = 0; i < MAX_POSITIONS; ++i) {
        charInfo[i].character = '\0';
        charInfo[i].numNumbers = 0;

        charInfo[i].numbers = (int*)malloc(sizeof(int) * MAX_POSITIONS);
        if (charInfo[i].numbers == NULL) {
            // Handle memory allocation error
        }
    }

    switch (set) {
        case 1:
            addNumber(charInfo, '&', 0);
            addNumber(charInfo, '-', 1);
            addNumber(charInfo, '0', 2);
            addNumber(charInfo, '1', 3);
            addNumber(charInfo, '2', 4);
            addNumber(charInfo, '3', 5);
            addNumber(charInfo, '4', 6);
            addNumber(charInfo, '5', 7);
            addNumber(charInfo, '6', 8);
            addNumber(charInfo, '7', 9);
            addNumber(charInfo, '8', 10);
            addNumber(charInfo, '9', 11);
            addNumber(charInfo, 'a', 0);
            addNumber(charInfo, 'b', 0);
            addNumber(charInfo, 'c', 0);
            addNumber(charInfo, 'd', 0);
            addNumber(charInfo, 'e', 0);
            addNumber(charInfo, 'f', 0);
            addNumber(charInfo, 'g', 0);
            addNumber(charInfo, 'h', 0);
            addNumber(charInfo, 'i', 0);
            addNumber(charInfo, 'a', 3);
            addNumber(charInfo, 'b', 4);
            addNumber(charInfo, 'c', 5);
            addNumber(charInfo, 'd', 6);
            addNumber(charInfo, 'e', 7);
            addNumber(charInfo, 'f', 8);
            addNumber(charInfo, 'g', 9);
            addNumber(charInfo, 'h', 10);
            addNumber(charInfo, 'i', 11);
            addNumber(charInfo, 'j', 1);
            addNumber(charInfo, 'k', 1);
            addNumber(charInfo, 'l', 1);
            addNumber(charInfo, 'm', 1);
            addNumber(charInfo, 'n', 1);
            addNumber(charInfo, 'o', 1);
            addNumber(charInfo, 'p', 1);
            addNumber(charInfo, 'q', 1);
            addNumber(charInfo, 'r', 1);
            addNumber(charInfo, 'j', 3);
            addNumber(charInfo, 'k', 4);
            addNumber(charInfo, 'l', 5);
            addNumber(charInfo, 'm', 6);
            addNumber(charInfo, 'n', 7);
            addNumber(charInfo, 'o', 8);
            addNumber(charInfo, 'p', 9);
            addNumber(charInfo, 'q', 10);
            addNumber(charInfo, 'r', 11);
            addNumber(charInfo, '/', 2);
            addNumber(charInfo, 's', 2);
            addNumber(charInfo, 't', 2);
            addNumber(charInfo, 'u', 2);
            addNumber(charInfo, 'v', 2);
            addNumber(charInfo, 'x', 2);
            addNumber(charInfo, 'y', 2);
            addNumber(charInfo, 'z', 2);
            addNumber(charInfo, '/', 3);
            addNumber(charInfo, 's', 4);
            addNumber(charInfo, 't', 5);
            addNumber(charInfo, 'u', 6);
            addNumber(charInfo, 'v', 7);
            addNumber(charInfo, 'w', 8);
            addNumber(charInfo, 'x', 9);
            addNumber(charInfo, 'y', 10);
            addNumber(charInfo, 'z', 11);

            //addNumber(charInfo, '¢', 0);
            addNumber(charInfo, '.', 0);
            addNumber(charInfo, '<', 0);
            addNumber(charInfo, '(', 0);
            addNumber(charInfo, '+', 0);
            addNumber(charInfo, '|', 0);
            //addNumber(charInfo, '¢', 5);
            addNumber(charInfo, '.', 6);
            addNumber(charInfo, '<', 7);
            addNumber(charInfo, '(', 8);
            addNumber(charInfo, '+', 9);
            addNumber(charInfo, '|', 10);
            //addNumber(charInfo, '¢', 11);
            addNumber(charInfo, '.', 11);
            addNumber(charInfo, '<', 11);
            addNumber(charInfo, '(', 11);
            addNumber(charInfo, '+', 11);
            addNumber(charInfo, '|', 11);

            addNumber(charInfo, '!', 1);
            addNumber(charInfo, '$', 1);
            addNumber(charInfo, '*', 1);
            addNumber(charInfo, ')', 1);
            addNumber(charInfo, ';', 1);
            //addNumber(charInfo, '¬', 1);
            addNumber(charInfo, '!', 5);
            addNumber(charInfo, '$', 6);
            addNumber(charInfo, '*', 7);
            addNumber(charInfo, ')', 8);
            addNumber(charInfo, ';', 9);
            //addNumber(charInfo, '¬', 10);
            addNumber(charInfo, '!', 11);
            addNumber(charInfo, '$', 11);
            addNumber(charInfo, '*', 11);
            addNumber(charInfo, ')', 11);
            addNumber(charInfo, ';', 11);
            //addNumber(charInfo, '¬', 11);

            addNumber(charInfo, ',', 2);
            addNumber(charInfo, '%', 2);
            addNumber(charInfo, '_', 2);
            addNumber(charInfo, '>', 2);
            addNumber(charInfo, '?', 2);
            addNumber(charInfo, ',', 6);
            addNumber(charInfo, '%', 7);
            addNumber(charInfo, '_', 8);
            addNumber(charInfo, '>', 9);
            addNumber(charInfo, '?', 10);
            addNumber(charInfo, ',', 11);
            addNumber(charInfo, '%', 11);
            addNumber(charInfo, '_', 11);
            addNumber(charInfo, '>', 11);
            addNumber(charInfo, '?', 11);

            addNumber(charInfo, ':', 5);
            addNumber(charInfo, '#', 6);
            addNumber(charInfo, '@', 7);
            addNumber(charInfo, '\'', 8);
            addNumber(charInfo, '=', 9);
            addNumber(charInfo, '"', 10);
            addNumber(charInfo, ':', 11);
            addNumber(charInfo, '#', 11);
            addNumber(charInfo, '@', 11);
            addNumber(charInfo, '\'', 11);
            addNumber(charInfo, '=', 11);
            addNumber(charInfo, '"', 11);
            break;
        case 2:
            addNumber(charInfo, '-', 1);
            addNumber(charInfo, '0', 2);
            addNumber(charInfo, '1', 3);
            addNumber(charInfo, '2', 4);
            addNumber(charInfo, '3', 5);
            addNumber(charInfo, '4', 6);
            addNumber(charInfo, '5', 7);
            addNumber(charInfo, '6', 8);
            addNumber(charInfo, '7', 9);
            addNumber(charInfo, '8', 10);
            addNumber(charInfo, '9', 11);
            addNumber(charInfo, 'a', 0);
            addNumber(charInfo, 'b', 0);
            addNumber(charInfo, 'c', 0);
            addNumber(charInfo, 'd', 0);
            addNumber(charInfo, 'e', 0);
            addNumber(charInfo, 'f', 0);
            addNumber(charInfo, 'g', 0);
            addNumber(charInfo, 'h', 0);
            addNumber(charInfo, 'i', 0);
            addNumber(charInfo, 'a', 3);
            addNumber(charInfo, 'b', 4);
            addNumber(charInfo, 'c', 5);
            addNumber(charInfo, 'd', 6);
            addNumber(charInfo, 'e', 7);
            addNumber(charInfo, 'f', 8);
            addNumber(charInfo, 'g', 9);
            addNumber(charInfo, 'h', 10);
            addNumber(charInfo, 'i', 11);
            addNumber(charInfo, 'j', 1);
            addNumber(charInfo, 'k', 1);
            addNumber(charInfo, 'l', 1);
            addNumber(charInfo, 'm', 1);
            addNumber(charInfo, 'n', 1);
            addNumber(charInfo, 'o', 1);
            addNumber(charInfo, 'p', 1);
            addNumber(charInfo, 'q', 1);
            addNumber(charInfo, 'r', 1);
            addNumber(charInfo, 'j', 3);
            addNumber(charInfo, 'k', 4);
            addNumber(charInfo, 'l', 5);
            addNumber(charInfo, 'm', 6);
            addNumber(charInfo, 'n', 7);
            addNumber(charInfo, 'o', 8);
            addNumber(charInfo, 'p', 9);
            addNumber(charInfo, 'q', 10);
            addNumber(charInfo, 'r', 11);
            addNumber(charInfo, '/', 2);
            addNumber(charInfo, 's', 2);
            addNumber(charInfo, 't', 2);
            addNumber(charInfo, 'u', 2);
            addNumber(charInfo, 'v', 2);
            addNumber(charInfo, 'x', 2);
            addNumber(charInfo, 'y', 2);
            addNumber(charInfo, 'z', 2);
            addNumber(charInfo, '/', 3);
            addNumber(charInfo, 's', 4);
            addNumber(charInfo, 't', 5);
            addNumber(charInfo, 'u', 6);
            addNumber(charInfo, 'v', 7);
            addNumber(charInfo, 'w', 8);
            addNumber(charInfo, 'x', 9);
            addNumber(charInfo, 'y', 10);
            addNumber(charInfo, 'z', 11);

            addNumber(charInfo, '.', 0);
            addNumber(charInfo, '.', 6);
            addNumber(charInfo, '.', 11);

            addNumber(charInfo, '$', 1);
            addNumber(charInfo, '$', 6);
            addNumber(charInfo, '$', 11);

            addNumber(charInfo, ',', 2);
            addNumber(charInfo, ',', 6);
            addNumber(charInfo, ',', 11);

            break;
        default:
            break;
    }
}
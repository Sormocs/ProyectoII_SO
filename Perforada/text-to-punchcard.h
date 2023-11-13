//
// Created by marko on 11/13/2023.
//

#ifndef PROYECTO_2_TEXT_TO_PUNCHCARD_H
#define PROYECTO_2_TEXT_TO_PUNCHCARD_H

#define MAX_POSITIONS 115

// Define a structure to store character information
typedef struct {
    char character;
    int* numbers;
    int numNumbers;
} CharInfo;

// Function to add a number for a character
void addNumber(CharInfo charInfo[], char ch, int number);

// Function to get numbers for a character and structure index
int* getNumbers(CharInfo charInfo[], char ch, int index, int* numNumbers);

// Structure to store character and associated numbers
typedef struct {
    char character;
    int* numbers;
    int numNumbers;
} CharacterNumbers;

// Function to get numbers for a word and structure index
CharacterNumbers* getCharacterNumbersForWord(CharInfo charInfo1[], CharInfo charInfo2[], const char* word, int index, int* totalCharacters);


void initializeCharacterNumbers(CharInfo charInfo[], int set);

#endif //PROYECTO_2_TEXT_TO_PUNCHCARD_H

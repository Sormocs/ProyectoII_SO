#include "text-to-punchcard.h"
#include <stdio.h>
#include <stdlib.h>
#include "Encriptado/ROT13.h"

int main() {
    char message[] = "Hello, World!";

    printf("Original Message: %s\n", message);

    applyROT13(message);

    printf("Encrypted Message: %s\n", message);

    applyROT13(message);

    printf("Original Message: %s\n", message);

    return 0;
}

//int main() {
//    // Initialize character information arrays for two structures
//    CharInfo charInfo1[MAX_POSITIONS];
//    CharInfo charInfo2[MAX_POSITIONS];
//
//    for (int i = 0; i < MAX_POSITIONS; ++i) {
//        charInfo1[i].character = '\0';
//        charInfo1[i].numNumbers = 0;
//        charInfo1[i].numbers = NULL;
//
//        charInfo2[i].character = '\0';
//        charInfo2[i].numNumbers = 0;
//        charInfo2[i].numbers = NULL;
//    }
//
//    // Call the functions to initialize character numbers for each structure
//    initializeCharacterNumbers(charInfo1, 1);
//    initializeCharacterNumbers(charInfo2, 2);
//
//    // Example usage
//    const char* word = "pipilacha";
//    int totalCharacters;
//
//    // Specify the index of the desired structure (1 or 2)
//    int structureIndex = 1;
//    CharacterNumbers* characterNumbersArray = getCharacterNumbersForWord(charInfo1, charInfo2, word, structureIndex, &totalCharacters);
//
//    if (characterNumbersArray != NULL) {
//        printf("Character and Numbers for '%s' (Structure %d):\n", word, structureIndex);
//        for (int i = 0; i < totalCharacters; ++i) {
//            printf("Character: %c\n", characterNumbersArray[i].character);
//            printf("Numbers: ");
//            for (int j = 0; j < characterNumbersArray[i].numNumbers; ++j) {
//                printf("%d ", characterNumbersArray[i].numbers[j]);
//            }
//            printf("\n\n");
//
//            // Free the allocated memory for numbers
//            free(characterNumbersArray[i].numbers);
//        }
//
//        // Free the allocated memory for the array of CharacterNumbers
//        free(characterNumbersArray);
//    } else {
//        printf("Character and Numbers not found.\n");
//    }
//
//    return 0;
//}
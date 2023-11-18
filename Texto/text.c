#include <stdio.h>
#include <stdlib.h>
#include "../Encriptado/ROT13.h"
#include <string.h>

#define MAX_WORD_LENGTH 100

void divideFile() {
    const char *inputFileName = "Texto/bible.txt";
    const char *outputFile1 = "Texto/outputA.txt";
    const char *outputFile2 = "Texto/outputB.txt";

    FILE *inputFile, *outputFileA, *outputFileB;
    char buffer[1024];
    size_t fileSize, halfSize;

    // Open the input file
    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    // Get the size of the file
    fseek(inputFile, 0, SEEK_END);
    fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    // Calculate half the size
    halfSize = fileSize / 2;

    // Open the output files
    outputFileA = fopen(outputFile1, "w");
    if (outputFileA == NULL) {
        perror("Error opening output file A");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    outputFileB = fopen(outputFile2, "w");
    if (outputFileB == NULL) {
        perror("Error opening output file B");
        fclose(inputFile);
        fclose(outputFileA);
        exit(EXIT_FAILURE);
    }

    // Read the first half of the file and write to output file A
    while (ftell(inputFile) < halfSize && fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        applyROT13(buffer);
        fputs(buffer, outputFileA);
    }

    // Read the second half of the file and write to output file B
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        fputs(buffer, outputFileB);
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFileA);
    fclose(outputFileB);

    // Print the character count
    printf("Character count in the input file: %zu\n", fileSize);
}


char* findTrendWord(char* filename) {

  // Open file
  FILE* file = fopen(filename, "r");
  if (!file) {
    return NULL;
  }

  // Track word counts
  char words[100][20];
  int counts[100] = {0};

  // Read words from file
  char word[20];
  while (fscanf(file, "%s", word) == 1) {
    int i;
    for (i = 0; i < 100; i++) {
      if (strcmp(words[i], word) == 0) {
        counts[i]++;
        break;
      }
      if (strlen(words[i]) == 0) {
        strcpy(words[i], word);
        counts[i]++;
        break;
      }
    }
  }

  // Find word with max count
  int maxIndex = 0;
  for (int i = 1; i < 100; i++) {
    if (counts[i] > counts[maxIndex]) {
      maxIndex = i;
    }
  }

  // Return trend word
  char* trendWord = words[maxIndex];
  return trendWord;
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


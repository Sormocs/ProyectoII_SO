//#include "Texto/text.h"
#include "Encriptado/ROT13.h"
#include "LibraryMaster/library.h"
#include <stdio.h>
#include <stdlib.h>

void divideFile() {
    const char *inputFileName = "/home/sergio/Desktop/sharedfolder/TextoMaster/bible.txt";
    const char *outputFile1 = "/home/sergio/Desktop/sharedfolder/TextoMaster/outputA.txt";
    const char *outputFile2 = "/home/sergio/Desktop/sharedfolder/TextoMaster/outputB.txt";

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


int main() {
    divideFile();
    


    // mpirun command as a string
    char cmd[100] = "mpirun --hostfile /etc/hosts -np 1 /home/curso/Desktop/sharedfolder/slave_file";

    // Run command
    int result = system(cmd);

    // Check result
    if (result == -1) {
      perror("system() failed");
      exit(EXIT_FAILURE);
    } else if (result != 0) {
      fprintf(stderr, "mpirun returned %d\n", result);
      exit(EXIT_FAILURE);
    }

	printf("mpirun command executed successfully\n");
	
	pipilacha();

    return 0;

}

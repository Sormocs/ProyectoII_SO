# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
#include "Texto/text.h"
#include "Encriptado/ROT13.h"
#include <string.h>

int main ( int argc, char *argv[] ){
	
	int rank, size, len;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_library_version(version, &len);
	
	const char *file_path = "/home/curso/Desktop/sharedfolder/TextoMaster/outputA.txt";


    FILE *file = fopen(file_path, "r");
    
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Seek to the end of the file to get its size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);  // Rewind to the beginning

    // Loop through each character in the file and apply ROT13
    for (long i = 0; i < file_size; i++) {
        char current_char;
        fread(&current_char, 1, 1, file);
        applyROT13(&current_char);
        fseek(file, i, SEEK_SET);
        //fwrite(&current_char, 1, 1, file);
    }

    // Close the file
    fclose(file);

    
    
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

  // Return trend word
  	int maxIndex = 0;
	for (int i = 1; i < 100; i++) {
  	if (counts[i] > counts[maxIndex]) {
    maxIndex = i;
  	}
  }
  
  	char* trendWord = malloc(strlen(words[maxIndex]) + 1); // +1 for null terminator
  	//trendWord = "Jesus";
	strcpy(trendWord, words[maxIndex]);
    

    //char* trend = findTrendWord("/home/curso/Desktop/sharedfolder/Texto/outputA.txt");
    if (trendWord) {
        printf("Trend word is: %s\n", trendWord);
    } else {
        printf("No trend word found\n");
    }  
    
	
	MPI_Finalize();	
			
	return 0;
}

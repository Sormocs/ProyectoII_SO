# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>
//#include "Texto/text.h"
//#include "Encriptado/ROT13.h"
#include <string.h>

#define NUM_WORDS 8192
#define WORD_LENGTH 24

void applyROT13(char* message) {
  char* ptr = message;
  while (*ptr != '\0') {
    char c = *ptr;
    if ((c >= 'a' && c <= 'z')) {
      *ptr = (((c - 'a') + 13) % 26) + 'a';
    }
    else if ((c >= 'A' && c <= 'Z')) {
      *ptr = (((c - 'A') + 13) % 26) + 'A';
    }
    ptr++;
  }
}

int main ( int argc, char *argv[] ){
	
	int rank, size, len;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_library_version(version, &len);
	
	const char *file_path = "/home/curso/Desktop/sharedfolder/TextoMaster/outputA.txt";

	//const char* file_path = "./sharedfolder/TextoMaster/outputA.txt";
  // const char* file_path = "./Texto/outputB.txt";

  FILE* file = fopen(file_path, "rb");

  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  // Seek to the end of the file to get its size
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);  // Rewind to the beginning

  char decrypted_buffer[file_size + 1];

  int current_char;  // Use int to handle EOF
  long index = 0;
  while ((current_char = fgetc(file)) != EOF) {
    if (index < file_size) {
      applyROT13((char*)&current_char);

      if (
        current_char != '.' && current_char != ',' && current_char != ';' &&
        current_char != ':' && current_char != '!' && current_char != '?' &&
        current_char != '-' && current_char != '(' && current_char != ')'
        ) {
        decrypted_buffer[index++] = current_char;
      }
    }
  }

  decrypted_buffer[index] = '\0';

  fclose(file);

  // Track word counts
  char words[NUM_WORDS][WORD_LENGTH];
  int counts[NUM_WORDS] = { 0 };

  memset(words, '\0', sizeof(words));

  // Read words from buffer
  char word[WORD_LENGTH];
  long read_chars = 0;
  long offset = 0;

  while (sscanf(decrypted_buffer + offset, "%24s%n", word, &read_chars) == 1) {
    for (int i = 0; i < NUM_WORDS; i++) {
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

    // Update the offset
    offset += read_chars;

    // Check if we've reached the end of the string
    if (offset >= strlen(decrypted_buffer)) {
      break;
    }
  }

  index = 0;
  int maxIndex = 0;
  while (strlen(words[index]) > 0) {
    //printf("Word: %s, Count: %d\n", words[index], counts[index]);
    if (counts[index] > counts[maxIndex]) {
      maxIndex = index;
    }

    index++;
  }

  char trendWord[sizeof(words[maxIndex]) + 1];
  strcpy(trendWord, words[maxIndex]);

  if (trendWord) {
    printf("Trend word is: %s with %ld repetitions.\n", trendWord, counts[maxIndex]);
  }
  else {
    printf("No trend word found\n");
  }
    
	
	MPI_Finalize();	
			
	return 0;
}

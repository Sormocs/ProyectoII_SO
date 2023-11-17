#include "Texto/text.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LibraryMaster/library.h"

#define NUM_WORDS 8192
#define WORD_LENGTH 24


int main() {
    divideFile();


    // mpirun command as a string
    //char cmd[100] = "mpirun --hostfile /etc/hosts -np 1 /home/curso/Desktop/sharedfolder/client_file";

    // Run command
    //int result = system(cmd);

    // Check result
    //if (result == -1) {
    //  perror("system() failed");
    //  exit(EXIT_FAILURE);
    //} else if (result != 0) {
    //  fprintf(stderr, "mpirun returned %d\n", result);
    //  exit(EXIT_FAILURE);
    //}

	printf("mpirun command executed successfully\n");
	
	const char* file_path = "./sharedfolder/TextoMaster/outputB.txt";
  // const char* file_path = "./Texto/outputB.txt";

  FILE* file = fopen(file_path, "rb+");

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
    printf("Word: %s, Count: %d\n", words[index], counts[index]);
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
  
  pipilacha(trendWord);

    return 0;

}

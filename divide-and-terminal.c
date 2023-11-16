#include "Texto/text.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    divideFile();


    // mpirun command as a string
    char cmd[100] = "mpirun --hostfile /etc/hosts -np 1 /home/curso/Desktop/sharedfolder/client_file";

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

    return 0;

}

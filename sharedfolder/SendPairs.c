#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Library/library.h"

int main(){

	FILE *file = fopen("pairs.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    char pair[32];  // Adjust the size as needed
    while (fgets(pair, sizeof(pair), file) != NULL) {
        // Remove newline character at the end
        size_t len = strlen(pair);
        if (len > 0 && pair[len - 1] == '\n') {
            pair[len - 1] = '\0';
        }

        // Process each pair
        send_data(pair);
        sleep(0.8);
    }
    
    fclose(file);

}

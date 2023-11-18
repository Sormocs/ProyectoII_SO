#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stddef.h>
#include "library.h"
#include "text-to-punchcard.h"

#define SERIAL_PORT_0 "/dev/ttyACM0"
#define SERIAL_PORT_1 "/dev/ttyACM1"

int open_serial_port() {


    int serial_port = open(SERIAL_PORT_0, O_RDWR);
    if (serial_port == -1) {
    // Try opening secondary serial port
    serial_port = open(SERIAL_PORT_1, O_RDWR);
    
    	if (serial_port == -1) {
      		perror("Error opening serial ports");
      		exit(EXIT_FAILURE);
    	}	
  	}

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    if (tcgetattr(serial_port, &tty) != 0) {
        perror("Error from tcgetattr");
        exit(EXIT_FAILURE);
    }

    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        perror("Error from tcsetattr");
        exit(EXIT_FAILURE);
    }

    return serial_port;
}

void send_data(const char *data) {

	int serial_port = open_serial_port();	
	
    write(serial_port, data, strlen(data));
    
    close(serial_port);

}

void read_data(char *buffer, size_t buffer_size) {


	int serial_port = open_serial_port();
	
    int bytes_read = read(serial_port, buffer, buffer_size - 1);
    if (bytes_read == -1) {
        perror("Error reading from serial port");
        exit(EXIT_FAILURE);
    }

    buffer[bytes_read] = '\0'; // Null-terminate the string
    
    close(serial_port);
}

void pipilacha() {

	CharInfo charInfo1[MAX_POSITIONS];

	CharInfo charInfo2[MAX_POSITIONS];

	for (int i = 0; i < MAX_POSITIONS; ++i) {

		charInfo1[i].character = '\0';
		charInfo1[i].numNumbers = 0; 
		charInfo1[i].numbers = NULL;
		charInfo2[i].character = '\0';
		charInfo2[i].numNumbers = 0;
		charInfo2[i].numbers = NULL;

	}

	initializeCharacterNumbers(charInfo1, 1);
	initializeCharacterNumbers(charInfo2, 2);
	const char* word = "abcdefg";
	int totalCharacters;
	int structureIndex = 1;
	CharacterNumbers* characterNumbersArray = getCharacterNumbersForWord(charInfo1, charInfo2, word, structureIndex, &totalCharacters);

	if (characterNumbersArray != NULL) {
		for (int i = 0; i < totalCharacters; ++i) {
			for (int j = 0; j < characterNumbersArray[i].numNumbers; ++j) {
				char pair[32];
      			snprintf(pair, sizeof(pair), "(%d, %d)", i, characterNumbersArray[i].numbers[j]);
      			
      			printf("%s", pair);	
      			send_data(pair);
      			
				
			}

			printf("\n\n");
			free(characterNumbersArray[i].numbers);
		
		}
		free(characterNumbersArray);
		
	} else {

			printf("Character and Numbers not found.\n");

	}


}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stddef.h>
#include "library.h"
#include "text-to-punchcard.h"

#define SERIAL_PORT_0 "/dev/ch341"
#define SERIAL_PORT_1 "/dev/ttyACM1"

int open_serial_port() {

	const char port = "/dev/ttyACM0";
    int serial_port = open(port, O_RDWR | O_NOCTTY | O_SYNC);
    
    if (serial_port == -1) {
        perror("Error opening serial port");
        exit(EXIT_FAILURE);
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    if (tcgetattr(serial_port, &tty) != 0) {
        perror("Error from tcgetattr");
        close(serial_port);
        exit(EXIT_FAILURE);
    }

    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CS8;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 5;

    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        perror("Error from tcsetattr");
        close(serial_port);
        exit(EXIT_FAILURE);
    }

    return serial_port;
}

void send_data(const char *message) {

	const char *port = "/dev/ttyACM0";
	int fd = open(port, O_RDWR | O_NOCTTY | O_SYNC);
    
    if (fd == -1) {
        perror("Error opening serial port");
        exit(EXIT_FAILURE);
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    if (tcgetattr(fd, &tty) != 0) {
        perror("Error from tcgetattr");
        close(fd);
        exit(EXIT_FAILURE);
    }

    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CS8;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 5;

    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("Error from tcsetattr");
        close(fd);
        exit(EXIT_FAILURE);
    }

    write(fd, message, strlen(message));

    close(fd);

    printf("Message '%s' sent successfully.\n", message);

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

void pipilacha(char* word) {

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
	//const char* word = "abcdefg";
	printf("Word: %s\n",word);
	int totalCharacters;
	int structureIndex = 1;
	CharacterNumbers* characterNumbersArray = getCharacterNumbersForWord(charInfo1, charInfo2, word, structureIndex, &totalCharacters);
	
	FILE *file = fopen("pairs.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

	if (characterNumbersArray != NULL) {
		for (int i = 0; i < totalCharacters; ++i) {
		printf("%ld", totalCharacters);
		printf("Character: %c\n", characterNumbersArray[i].character);
			for (int j = 0; j < characterNumbersArray[i].numNumbers; ++j) {
				char pair[32];
      			snprintf(pair, sizeof(pair), "(%d,%d)\n", i, characterNumbersArray[i].numbers[j]);
      			
      			printf("%s", pair);	
      			//send_data(pair);
      			fputs(pair,file);
				
			}

			printf("\n\n");
			//free(characterNumbersArray[i].numbers);
		
		}
		free(characterNumbersArray);
		fclose(file);
		
	} else {

			printf("Character and Numbers not found.\n");

	}


}


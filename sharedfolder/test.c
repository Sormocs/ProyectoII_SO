#include <stdlib.h>
#include <stdio.h>
//#include "LibraryMaster/library.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

void send_message(const char *port, const char *message) {
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

int main() {
    // Replace "/dev/ttyACM0" with the actual path of your ttyACM0 device
    const char *ttyACM0_path = "/dev/ttyACM0";

    // Replace "Hello, Arduino!" with the message you want to send
    const char *message_to_send = "Hello, Arduino!";

    send_message(ttyACM0_path, message_to_send);

    return 0;
}


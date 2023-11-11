#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#define SERIAL_PORT "/dev/ttyACM1"

int open_serial_port() {
    int serial_port = open(SERIAL_PORT, O_RDWR);
    if (serial_port == -1) {
        perror("Error opening serial port");
        exit(EXIT_FAILURE);
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

void send_data(int serial_port, const char *data) {
    write(serial_port, data, strlen(data));
}

void read_data(int serial_port, char *buffer, int buffer_size) {
    int bytes_read = read(serial_port, buffer, buffer_size - 1);
    if (bytes_read == -1) {
        perror("Error reading from serial port");
        exit(EXIT_FAILURE);
    }

    buffer[bytes_read] = '\0'; // Null-terminate the string
}

int main() {
    int serial_port = open_serial_port();

    // Example: sending data
    const char *data_to_send = "Hello, Arduino!";
    send_data(serial_port, data_to_send);
    printf("Sent: %s\n", data_to_send);

    // Example: reading data
    char buffer[256];
    read_data(serial_port, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);

    close(serial_port);

    return 0;
}


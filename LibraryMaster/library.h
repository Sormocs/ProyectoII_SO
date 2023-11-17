// library.h

#ifndef LIBRARY_H
#define LIBRARY_H

#include <stddef.h>

//Open serial port
int open_serial_port();
// Function to send data over a serial port
void send_data(const char *message);

// Function to read data from a serial port into a buffer
void read_data(char *buffer, size_t buffer_size);

void pipilacha(char* word);

#endif // LIBRARY_H

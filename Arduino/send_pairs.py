import serial
import time

# Establish a connection with the Arduino
arduino = serial.Serial('/dev/ttyACM0', 9600) # Replace 'COM3' with your Arduino's port
time.sleep(2) # Wait for the connection to settle

# Send a string
arduino.write(b'c')

for column in range(24):
    for row in range(16):
        arduino.write('({row},{column})'.format(row=row, column=column).encode())
        


# Close the connection
arduino.close()

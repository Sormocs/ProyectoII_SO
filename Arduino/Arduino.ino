#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::DR1CR1RR0_HW 

#define PIN_CLK 13
#define PIN_DIN 11
#define PIN_CS 10

#define MAX_DEVICES 6

MD_MAX72XX matrix_driver = MD_MAX72XX(HARDWARE_TYPE, PIN_DIN, PIN_CLK, PIN_CS, MAX_DEVICES);

uint8_t get_row_mask(uint8_t row) {
	switch (row)
	{
		case 0: return 0b00000001;
		case 1: return 0b00000010;
		case 2: return 0b00000100;
		case 3: return 0b00001000;
		case 4: return 0b00010000;
		case 5: return 0b00100000;
		case 6: return 0b01000000;
		case 7: return 0b10000000;
		default: return 0b00000000;
	}
}

void clear_matrix() {
	for(uint8_t display_id = 0; display_id < 6; display_id++){
		for(uint8_t column = 0; column < 8; column++) {
			const uint8_t column_state = matrix_driver.getColumn(display_id, column % 8);
			matrix_driver.setColumn(display_id, column % 8, 0b00000000);
		}
	}
}

void turn_on_pixel(uint8_t row, uint8_t column){
	const uint8_t display_id = (row / 8) + (column / 8) + 2*(row > 7); 

	const uint8_t column_state = matrix_driver.getColumn(display_id, column % 8);
	const uint8_t column_mask = get_row_mask(row - 8 * (row > 7));

	matrix_driver.setColumn(display_id, column % 8, column_state | column_mask);
}

void test(){
	for(uint8_t column = 0; column < 24; column++) {
		for(uint8_t row = 0; row < 16; row++){
			turn_on_pixel(row, column);
		}
  }

	delay(100);
	
	clear_matrix();

 	delay(100);
}

void setup(){
  matrix_driver.begin();
  matrix_driver.clear();
  matrix_driver.control(MD_MAX72XX::INTENSITY, 1);

  Serial.begin(9600);
}


char column[3];
char row[3];

uint8_t row_index = 0;
uint8_t column_index = 0;

bool reading_row = false;
bool reading_column = false;

void loop(){
  while(Serial.available() > 0){
    char character = Serial.read();
		
		if(character == 'c'){
			clear_matrix();
			continue;
		}

		if(character == '('){
			reading_row = true;
      continue;
		}

		if(reading_row){
			if(character == ','){
				row[row_index] = '\0';
				row_index = 0;

				reading_row = false;
				reading_column = true;
			} 
			else{
				row[row_index] = character;
				row_index++;
			}

      continue;
		}

		if(reading_column){
			if(character == ')'){
				column[column_index] = '\0';
				column_index = 0;

				reading_column = false;

				Serial.println(atoi(row));
				Serial.println(atoi(column));
				turn_on_pixel(atoi(row), atoi(column));
			} 
			else {
				column[column_index] = character;
				column_index++;
			}
		} 
  }
}

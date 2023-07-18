/*
 * KEYPAD.c
 *
 * Created: 11/18/2022 12:25:16 AM
 *  Author: AhmedMabrouk
 */ 


#include "KEYPAD.h"
#include "LCD.h"
extern uint32_t timer0_value_ms;

uint8_t const KEYPAD_matrix[] = {
	'7','8','9','/',
	'4','5','6','*',
	'1','2','3','-',
	'c','0','=','+'
};


/*****************************************************************************
* Function Name: KEYPAD_init
* Purpose      : Initializing Keypad
* Parameters   : void
* Return value : void
*****************************************************************************/
void KEYPAD_init(void) {
	INIT_KEYPAD_PINS();
}


/*****************************************************************************
* Function Name: KEYPAD_read
* Purpose      : Read value from keypad
* Parameters   : void
* Return value : Character
*****************************************************************************/
int8_t KEYPAD_read(void) {
	K4(0);K5(1);K6(1);K7(1);
	if(K0() == 0) return KEYPAD_matrix[0];
	if(K1() == 0) return KEYPAD_matrix[1];
	if(K2() == 0) return KEYPAD_matrix[2];
	if(K3() == 0) return KEYPAD_matrix[3];
	_delay_ms(5);
	
	K4(1);K5(0);K6(1);K7(1);
	if(K0() == 0) return KEYPAD_matrix[4];
	if(K1() == 0) return KEYPAD_matrix[5];
	if(K2() == 0) return KEYPAD_matrix[6];
	if(K3() == 0) return KEYPAD_matrix[7];
	_delay_ms(5);
	
	K4(1);K5(1);K6(0);K7(1);
	if(K0() == 0) return KEYPAD_matrix[8];
	if(K1() == 0) return KEYPAD_matrix[9];
	if(K2() == 0) return KEYPAD_matrix[10];
	if(K3() == 0) return KEYPAD_matrix[11];
	_delay_ms(5);
	
	K4(1);K5(1);K6(1);K7(0);
	if(K0() == 0) return KEYPAD_matrix[12];
	if(K1() == 0) return KEYPAD_matrix[13];
	if(K2() == 0) return KEYPAD_matrix[14];
	if(K3() == 0) return KEYPAD_matrix[15];
	_delay_ms(5);
	
	
	
	return -1;
}

/*****************************************************************************
* Function Name: KEYPAD_get_key
* Purpose      : Read value from keypad and return it
* Parameters   : void
* Return value : Character
*****************************************************************************/
uint8_t KEYPAD_get_key(void) {
	uint8_t KEY;
	
	while(KEYPAD_read() == -1) {}
	KEY = KEYPAD_read();
	while(KEYPAD_read() != -1) {}
	
	return KEY;
}

/*****************************************************************************
* Function Name: KEYPAD_get_key_timer
* Purpose      : Read value from keypad and return it within 500ms
* Parameters   : void
* Return value : Character
*****************************************************************************/
uint8_t KEYPAD_get_key_timer(void) {
	uint8_t KEY;
	
	timer0_value_ms = 0;
	while ((KEYPAD_read() == -1) && (timer0_value_ms <= 500)) {}
	KEY = KEYPAD_read();
	while (KEYPAD_read() != -1) {}
	
	return KEY;
}

/*****************************************************************************
* Function Name: KEYPAD_get_char
* Purpose      : Read character from keypad and return it
* Parameters   : void
* Return value : Character
*****************************************************************************/
uint8_t KEYPAD_get_char(void) {
	uint8_t KEY;
	
	timer0_value_ms = 0;
	while ((KEYPAD_read() == -1) && (timer0_value_ms <= 500)) {}
	KEY = KEYPAD_read();
	while (KEYPAD_read() != -1) {}
	
	switch (KEY) {
		case '1' : return 'a';
		case '2' : return 'd';
		case '3' : return 'g';
		case '4' : return 'j';
		case '5' : return 'm';
		case '6' : return 'p';
		case '7' : return 's';
		case '8' : return 'v';
		case '9' : return 'y';
		case 'c' : return 'C';
		case '0' : return ' ';
		default  : return  0 ;
	}
}


/*****************************************************************************
* Function Name: KEYPAD_get_charachter
* Purpose      : Read character from keypad and return it
* Parameters   : void
* Return value : Character
*****************************************************************************/
uint8_t KEYPAD_get_charachter(void) {
	uint8_t RETURNED_KEY, LAST_KEY, KEY, count;
	LAST_KEY = KEYPAD_get_char();
	while (LAST_KEY == 0) {
		LAST_KEY = KEYPAD_get_char();
	}
	RETURNED_KEY = LAST_KEY;
	
	if (RETURNED_KEY == 'C') {
		return 'C';
	} else if (RETURNED_KEY == ' ') {
		return ' ';
	}
	LCD_write_char(RETURNED_KEY);
	
	count = 0;
	while (count < 2) {
		timer0_value_ms = 0;
		while (timer0_value_ms < 500) {
			KEY = KEYPAD_get_char();
			if (KEY == LAST_KEY) {
				LCD_write_command(0x10);
				if (count == 0) {
					RETURNED_KEY = KEY+1;
					LCD_write_char(RETURNED_KEY);
				} else if (count == 1) {
					RETURNED_KEY = KEY+2;
					LCD_write_char(RETURNED_KEY);
				}
				break;
			} else if (KEY != 0) {
				RETURNED_KEY = KEY;
				LCD_write_char(RETURNED_KEY);
				count = 2;
				break;
			}
		}
		count++;
	}
	
	return RETURNED_KEY;
}
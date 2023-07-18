/*
 * Project.c
 *
 * Created: 12/1/2022 7:37:11 PM
 * Author : AhmedMabrouk
 */ 

#include "std_macros.h"
#include "LCD_cfg.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "timer0.h"

#define HOURS_ADD 1
#define MINS_ADD 2

extern uint32_t timer0_value_ms;

int main(void)
{
	
	LCD_init();
	KEYPAD_init();
	timer0_free_init();	
	timer0_free_start();
	
	uint8_t KEY;
	
    while (1) 
    {
		
		KEY = KEYPAD_get_charachter();
		if (KEY == 'C') {
			LCD_write_command(0x10);
			LCD_write_char(' ');
			LCD_write_command(0x10);
		} else if (KEY == ' ') {
			LCD_write_char(' ');
		}
		
    }
	
}

// 16Mhz, CC = 64/16 = 4 usec, Tov = 250*4 usec = 1 msec

ISR(TIMER0_COMP_vect) {
	timer0_value_ms ++;
}

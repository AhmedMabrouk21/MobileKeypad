/*
 * LCD.h
 *
 * Created: 11/17/2022 6:29:47 PM
 *  Author: AhmedMabrouk
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "std_macros.h"

void LCD_init(void);
void LCD_write_command(uint8_t);
void LCD_write_char(uint8_t);
void LCD_write_string(uint8_t *);
void LCD_write_number(uint32_t);
void LCD_pos_xy(uint8_t x, uint8_t y);

#endif /* LCD_H_ */
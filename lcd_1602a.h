/*
 * lcd_1602a.h
 *
 *  Created on: Jul 27, 2022
 *      Author: FJRR
 */

#ifndef LCD_1602A_H_
#define LCD_1602A_H_
#include "main.h"

void lcd_init(void);
void lcd_write_char(char Data);
void lcd_cmd (unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_write_num(int num);
void lcd_write_string(char* str);
void lcd_clear(void);
void lcd_set_cursor(unsigned char r, unsigned char c);
void lcd_shift(short int dir);
void lcd_write_float(float num);
#endif /* LCD_1602A_H_ */

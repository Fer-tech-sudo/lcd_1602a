/*
 * lcd_1602a.c
 *
 *  Created on: Jul 27, 2022
 *      Author: FJRR
 */
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

void lcd_data(unsigned char data){
	if (data & 1) HAL_GPIO_WritePin(GPIOB,D4_Pin,GPIO_PIN_SET);
		else HAL_GPIO_WritePin(GPIOB,D4_Pin,GPIO_PIN_RESET);

	if (data & 2) HAL_GPIO_WritePin(GPIOB,D5_Pin,GPIO_PIN_SET);
		else HAL_GPIO_WritePin(GPIOB,D5_Pin,GPIO_PIN_RESET);

	if (data & 4) HAL_GPIO_WritePin(GPIOB,D6_Pin,GPIO_PIN_SET);
		else HAL_GPIO_WritePin(GPIOB,D6_Pin,GPIO_PIN_RESET);

	if (data & 8) HAL_GPIO_WritePin(GPIOB,D7_Pin,GPIO_PIN_SET);
		else HAL_GPIO_WritePin(GPIOB,D7_Pin,GPIO_PIN_RESET);

}

void lcd_cmd (unsigned char cmd){
	HAL_GPIO_WritePin(GPIOB,RS_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,E_Pin,GPIO_PIN_RESET);
	lcd_data(cmd);
	HAL_GPIO_WritePin(GPIOB,E_Pin,GPIO_PIN_SET);
	HAL_Delay(4);
	HAL_GPIO_WritePin(GPIOB,E_Pin,GPIO_PIN_RESET);
}

////////////////////////InitLCD
void lcd_init(void){
	lcd_cmd(0x00);
	HAL_Delay(30);
	lcd_cmd(0x03);
	HAL_Delay(5);
	lcd_cmd(0x03);
	HAL_Delay(5);
	lcd_cmd(0x03);
	lcd_cmd(0x02);
	lcd_cmd(0x02);
	//define the use of 2 rows, use 0x08 to use only 1
	lcd_cmd(0x0C);
	lcd_cmd(0x00);
	lcd_cmd(0x0C);
	lcd_cmd(0x00);
	lcd_cmd(0x06);
}
// Function that writes a character in the LCD
//Delay is very important, refer to datasheet to ensure
//min time of delay. It is governed by the Enable pin time width

void lcd_write_char(char Data)
{
  char Low4,High4;
  Low4 = Data & 0x0F;
  High4 = Data & 0xF0;
  HAL_GPIO_WritePin(GPIOB,RS_Pin,GPIO_PIN_SET);
  lcd_data(High4>>4);
  HAL_GPIO_WritePin(GPIOB,E_Pin,GPIO_PIN_SET);
  HAL_Delay(1);
  HAL_GPIO_WritePin(GPIOB,E_Pin,GPIO_PIN_RESET);
  HAL_Delay(1);
  lcd_data(Low4);
  HAL_GPIO_WritePin(GPIOB,E_Pin,GPIO_PIN_SET);
  HAL_Delay(1);
  HAL_GPIO_WritePin(GPIOB,E_Pin,GPIO_PIN_RESET);
  HAL_Delay(1);
}
/// Write string in LCD
void lcd_write_string(char* str){

	for (int i = 0;str[i]!='\0';i++) lcd_write_char(str[i]);

}

//Write a Integer number

void lcd_write_num(int num){

	int dec=0,cent=0,mil=0;

	dec=num/10;
	cent=dec/10;
	mil=cent/10;
	if (num<0) {
		lcd_write_char('-');
		num = -1*num;
	}


	if (num<100 && num>9){
		lcd_write_char(dec%10+'0');
	}else if (num<1000 && num>99){
		lcd_write_char(cent%10+'0');
		lcd_write_char(dec%10+'0');
	}else if (num<6000 && num > 999){
		lcd_write_char(mil%10+'0');
		lcd_write_char(cent%10+'0');
		lcd_write_char(dec%10+'0');
	}
	lcd_write_char(num%10+'0');

}


void lcd_clear(void)
{
  lcd_cmd(0);
  lcd_cmd(1);
}




void lcd_set_cursor(unsigned char r, unsigned char c)
{
  unsigned char Temp,Low4,High4;
  if(r == 1)
  {
    Temp = 0x80 + c - 1; //0x80 is used to move the cursor
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    lcd_cmd(High4);
    lcd_cmd(Low4);
  }
  if(r == 2)
  {
    Temp = 0xC0 + c - 1;
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    lcd_cmd(High4);
    lcd_cmd(Low4);
  }
}



void lcd_shift(short int dir)
{
	if(dir == 1){
	  lcd_cmd(0x01);
	  lcd_cmd(0x0C);
	}else if(dir==2){
		lcd_cmd(0x01);
		lcd_cmd(0x08);
	}
}


void lcd_write_float(float num){

	int dec=0;
	if (num<0) {
			lcd_write_char('-');
			num = -1*num;
		}
	lcd_write_num((int)num);

	lcd_write_char('.');

	num = (num-(int)num) *100;

	lcd_write_num((int)num);

}


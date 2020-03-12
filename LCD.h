/*
 * LCD.h
 *
 *  Created on: Feb 27, 2020
 *      Author: PI
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_



//clear all the LCD display
#define CLR_DISPLAY 0x01

//return the cursor to 1st option
#define RETURN_HOME 0x02

//increment the cursor and shift it to right
#define ENTRY_MODE 0x06

//display on and cursor on
#define DISP_ON_CON 0x0E

//display on only
#define DISP_ON 0x0C

//display on and cursor on and blink
#define DISP_ON_CBON 0x0F

//shift cursor right
#define SHIFT_C_RIGHT 0x14

//shift cursor left
#define SHIFT_C_LEFT 0x10

//use 8 input bits D0~D7 and display in 2 lines
#define I8BIT_2LINE 0x38

//use 4 input bits only D4~D7 (send most sign. bits then least sign. ones) and display 1 line
#define I4BIT_2LINE 0x28

#define Row0 0x00
#define Row1 0x40
#define Col0 0x00
#define Col1 0x01
#define Col2 0x02
#define Col3 0x03
#define Col4 0x04
#define Col5 0x05
#define Col6 0x06
#define Col7 0x07
#define Col8 0x08
#define Col9 0x09
#define Col10 0x0A00
#define Col11 0x0B
#define Col12 0x0C
#define Col13 0x0D
#define Col14 0x0E
#define Col15 0x0A


void LCD_Init_8BIT(u8 Disp_mode);
void LCD_SendData(u8 Data);
void LCD_SendCommand(u8 Inst);
void LCD_GoToXY(u8 Row, u8 Col);
void LCD_SendStr(u8* ptrStr);
void LCD_WriteNum(u16 num);


#define Data_0 B0
#define Data_1 B1
#define Data_2 B2
#define Data_3 B3
#define Data_4 B4
#define Data_5 B5
#define Data_6 B6
#define Data_7 B7
#define RS E0
#define RW E1
#define E E2



#endif /* INC_LCD_H_ */

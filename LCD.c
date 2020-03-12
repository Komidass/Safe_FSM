#include  "types.h"
#include  "BIT_MATH.h"
#include "DIO.h"
#include  "LCD.h"
#include <stdbool.h>
#include  <stdint.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
void LCD_SendCommand(u8 Inst) {


        DIO_SetPinValue(RS, LOW);
        DIO_SetPinValue(RW, LOW);
        DIO_SetPinValue(E, HIGH);
        DIO_SetPinValue(LCD_u8_D0_Pin,GET_BIT(Inst,0));
        DIO_SetPinValue(LCD_u8_D1_Pin,GET_BIT(Inst,1));
        DIO_SetPinValue(LCD_u8_D2_Pin,GET_BIT(Inst,2));
        DIO_SetPinValue(LCD_u8_D3_Pin,GET_BIT(Inst,3));
        DIO_SetPinValue(LCD_u8_D4_Pin,GET_BIT(Inst,4));
        DIO_SetPinValue(LCD_u8_D5_Pin,GET_BIT(Inst,5));
        DIO_SetPinValue(LCD_u8_D6_Pin,GET_BIT(Inst,6));
        DIO_SetPinValue(LCD_u8_D7_Pin,GET_BIT(Inst,7));
        DIO_SetPinValue(E, LOW);
       // _delay_ms(5);
        SysCtlDelay(16000000 /(3*200));

        DIO_SetPinValue(E, HIGH);

}
void LCD_SendData(u8 Data)
{
    DIO_PinInit(RS);
    DIO_PinInit(RW);
    DIO_PinInit(E);
    DIO_PinInit(LCD_u8_D0_Pin);
    DIO_PinInit(LCD_u8_D1_Pin);
    DIO_PinInit(LCD_u8_D2_Pin);
    DIO_PinInit(LCD_u8_D3_Pin);
    DIO_PinInit(LCD_u8_D4_Pin);
    DIO_PinInit(LCD_u8_D5_Pin);
    DIO_PinInit(LCD_u8_D6_Pin);
    DIO_PinInit(LCD_u8_D7_Pin);
    DIO_SetPinValue(RS, HIGH);
    DIO_SetPinValue(RW, LOW);
    DIO_SetPinValue(E, HIGH);
    DIO_SetPinValue(LCD_u8_D0_Pin,GET_BIT(Data,0));
    DIO_SetPinValue(LCD_u8_D1_Pin,GET_BIT(Data,1));
    DIO_SetPinValue(LCD_u8_D2_Pin,GET_BIT(Data,2));
    DIO_SetPinValue(LCD_u8_D3_Pin,GET_BIT(Data,3));
    DIO_SetPinValue(LCD_u8_D4_Pin,GET_BIT(Data,4));
    DIO_SetPinValue(LCD_u8_D5_Pin,GET_BIT(Data,5));
    DIO_SetPinValue(LCD_u8_D6_Pin,GET_BIT(Data,6));
    DIO_SetPinValue(LCD_u8_D7_Pin,GET_BIT(Data,7));
    DIO_SetPinValue(E, LOW);
    //_delay_ms(5);
    SysCtlDelay(16000000 /(3*200));

    DIO_SetPinValue(E, HIGH);
}



void LCD_GoToXY(u8 Row, u8 Col)
{
    u8 inst ;


    if (Row==0)
            inst = 0x80;
        else if (Row==1)
            inst = 0xC0;
        if (Col<16)
            inst += Col;



    LCD_SendCommand(inst);
}



void LCD_SendStr(u8* ptrStr)
{// edit with gotoxy so that it can write a long string on the 2 lines
    u8 i;
    for(i=0; ptrStr[i] != '\0'; i++)
    {
        LCD_SendData(ptrStr[i]);
    }
}

void LCD_WriteNum(u16 num)
{
    if(num > 10000)
    {
        LCD_SendData((num/10000)+'0');
        num -= (num/10000)*10000;
        LCD_SendData((num/1000)+'0');
        num -= (num/1000)*1000;
        LCD_SendData((num/100)+'0');
        num -= (num/100)*100;
        LCD_SendData((num/10)+'0');
        num -= (num/10)*10;
        LCD_SendData((num)+'0');
        return ;
    }
    if(num > 1000)
    {
        LCD_SendData((num/1000)+'0');
        num -= (num/1000)*1000;
        LCD_SendData((num/100)+'0');
        num -= (num/100)*100;
        LCD_SendData((num/10)+'0');
        num -= (num/10)*10;
        LCD_SendData((num)+'0');
        return ;
    }
    if(num > 100)
    {
        LCD_SendData((num/100)+'0');
        num -= (num/100)*100;
        LCD_SendData((num/10)+'0');
        num -= (num/10)*10;
        LCD_SendData((num)+'0');
        return ;
    }
    if(num > 10)
    {
        LCD_SendData((num/10)+'0');
        num -= (num/10)*10;
        LCD_SendData((num)+'0');
        return ;
    }
    LCD_SendData((num)+'0');
    return ;

}

void LCD_Init_8BIT(u8 Disp_mode)
{

    SysCtlDelay(16000000 /(3));
    LCD_SendCommand(I8BIT_2LINE);
    SysCtlDelay(16000000 /(3*200));
    LCD_SendCommand(Disp_mode);
    SysCtlDelay(16000000 /(3*200));
    LCD_SendCommand(CLR_DISPLAY);
    SysCtlDelay(16000000 /(3*200));
    LCD_SendCommand(ENTRY_MODE);
    DIO_SetPinDirection(RS,OUTPUT);
    DIO_SetPinDirection(RW,OUTPUT);
    DIO_SetPinDirection(E,OUTPUT);
    DIO_SetPinDirection(LCD_u8_D0_Pin,OUTPUT);
    DIO_SetPinDirection(LCD_u8_D1_Pin,OUTPUT);
    DIO_SetPinDirection(LCD_u8_D2_Pin,OUTPUT);
    DIO_SetPinDirection(LCD_u8_D3_Pin,OUTPUT);
    DIO_SetPinDirection(LCD_u8_D4_Pin,OUTPUT);
    DIO_SetPinDirection(LCD_u8_D5_Pin,OUTPUT);
    DIO_SetPinDirection(LCD_u8_D6_Pin,OUTPUT);
    DIO_SetPinDirection(LCD_u8_D7_Pin,OUTPUT);
    //LCD_SendCommand(CLR_DISPLAY);
}




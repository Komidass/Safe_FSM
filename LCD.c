#include  "types.h"
#include "BIT_MATH.h"
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
   //     DIO_SetPortValue(Data_Port, Inst);
      /*  for(i=0;i<8;i++)
        {
            DIO_SetPinValue(Data_0+i, GET_BIT(Inst,i));
        }
        */
        DIO_SetPinValue(Data_0, GET_BIT(Inst,0));
        DIO_SetPinValue(Data_1, GET_BIT(Inst,1));
        DIO_SetPinValue(Data_2, GET_BIT(Inst,2));
        DIO_SetPinValue(Data_3, GET_BIT(Inst,3));
        DIO_SetPinValue(Data_4, GET_BIT(Inst,4));
        DIO_SetPinValue(Data_5, GET_BIT(Inst,5));
        DIO_SetPinValue(Data_6, GET_BIT(Inst,6));
        DIO_SetPinValue(Data_7, GET_BIT(Inst,7));
        DIO_SetPinValue(E, LOW);
       // _delay_ms(5);
        SysCtlDelay(16000000 /(3*200));

        DIO_SetPinValue( E, HIGH);

}
void LCD_SendData(u8 Data)
{

    DIO_SetPinValue(RS, HIGH);
    DIO_SetPinValue(RW, LOW);
    DIO_SetPinValue(E, HIGH);
   // DIO_SetPortValue(Data_Port, Data);
   /* for(i=0;i<8;i++)
    {
        DIO_SetPinValue(Data_0+i, GET_BIT(Data,i));
    }*/
    DIO_SetPinValue(Data_0, GET_BIT(Data,0));
    DIO_SetPinValue(Data_1, GET_BIT(Data,1));
    DIO_SetPinValue(Data_2, GET_BIT(Data,2));
    DIO_SetPinValue(Data_3, GET_BIT(Data,3));
    DIO_SetPinValue(Data_4, GET_BIT(Data,4));
    DIO_SetPinValue(Data_5, GET_BIT(Data,5));
    DIO_SetPinValue(Data_6, GET_BIT(Data,6));
    DIO_SetPinValue(Data_7, GET_BIT(Data,7));
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
        if(i == 16) LCD_GoToXY(1,0);
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


}




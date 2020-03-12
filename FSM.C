/*
 * FSM.C
 *
 *  Created on: Mar 10, 2020
 *      Author: thomas
 */

#include "types.h"
#include"BIT_MATH.h"
#include "DIO_REG.h"
#include "DIO.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "EEPROM.h"
#include "LCD.h"
#include "KBD_interface.h"
#include"FSM.h"



State Three_Stars_Pressed_Handler(void)
{

    if(NextState == Unlocked_NoPass) return Enter_Pass_To_Lock;
    if(NextState == Locked) return Enter_Pass_To_Unlock;
    if(NextState == Unlocked_Pass) return Locked;

}

State Three_Hashes_Pressed_Handler(void)
{
    return Enter_Pass_To_Reset;
}

State Correct_Password_Handler(void)
{
    if(NextState == Enter_Pass_To_Unlock) return Unlocked_Pass;
    if(NextState == Enter_Pass_To_Reset) return Unlocked_NoPass;
}

State Incorrect_Password_Handler(void)
{
    if(NextState == Enter_Pass_To_Unlock) return Locked;
    if(NextState == Enter_Pass_To_Reset)  return Locked;
}

void ReadState(void)
{
    static u8 No_Of_Stars = 0;
    static u8 No_Of_Hashes = 0;
    if(pressed == '*')
    {
        SysCtlDelay(16000000 /(3*3));
        LCD_SendData('*');
        No_Of_Stars++;
    }
    if(No_Of_Stars == 3)
    {

        SET_BIT(Event_Reg,Three_Stars_Pressed);
        No_Of_Stars = 0;
    }
    else
    {
        CLR_BIT(Event_Reg,Three_Stars_Pressed);
    }
//////////////////////////////////////////////////////

    if(pressed == '#')
    {
        SysCtlDelay(16000000 /(3*3));
        LCD_SendData('#');
        No_Of_Hashes++;
    }
    if(No_Of_Hashes == 3)
    {
        SET_BIT(Event_Reg,Three_Hashes_Pressed);
        No_Of_Hashes = 0;
    }
    else
    {
        CLR_BIT(Event_Reg,Three_Hashes_Pressed);
    }
//////////////////////////////////////////////////////

    if((Unlock_Error == NO_ERROR)&&(Lock_State == EEPROM_UNLOCKED))
        {
        SET_BIT(Event_Reg,Correct_Password);
        }
    else
    {
        CLR_BIT(Event_Reg,Correct_Password);
    }

}

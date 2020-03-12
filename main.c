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
#include "FSM.h"

u8 keys[16];
u8 pressed;
u8 Init_Error;
u8 Set_Password_Error;
u8 Lock_Error;
u8 Unlock_Error;
u8 Lock_State;
State NextState = Unlocked_NoPass;
volatile u32 Event_Reg;

int main () {

    DIO_PortInit(PORTA_);
    DIO_PortInit(PORTE_);
    DIO_PortInit(PORTB_);
    DIO_SetPortDirection(PORTB_, 0b00001111);
    DIO_SetPortDirection(PORTA_, 0b11111000);
    DIO_SetPortDirection(PORTE_, 0b00111111);
    Init_Error = EEPROM_Init();
    LCD_Init_8BIT(DISP_ON_CBON);
    KBD_u8Initialize(PORTB_);
    LCD_SendCommand(CLR_DISPLAY);
    u8 Pass_Counter = 0;
    u32 password = 0x00;
    u8  One_Time_FLag = 1;
    EEPROM_Mass_Erase();
    while(1)
    {
        KBD_u8GetKeyPadState(keys);
        pressed = KBD_keys_map(keys);
        ReadState();

        switch(NextState)
        {
        case Unlocked_NoPass:
        {

            if(GET_BIT(Event_Reg,Three_Stars_Pressed))
            {
               LCD_SendCommand(CLR_DISPLAY);
               LCD_SendStr("Set Password:");
               SysCtlDelay(16000000*2 /(3));
               LCD_SendCommand(CLR_DISPLAY);
               NextState = Three_Stars_Pressed_Handler();
               One_Time_FLag = 1;
            }
        }
        break;
        case Enter_Pass_To_Lock:
        {
            if(pressed != 0xff)
                  {
                      password |= ((0x00|pressed) << Pass_Counter*8);
                      Pass_Counter++;
                      LCD_SendData(pressed);
                      SysCtlDelay(16000000 /(3*3));
                  }
            if (Pass_Counter==4)
            {
                LCD_SendCommand(CLR_DISPLAY);
                Set_Password_Error = EEPROM_Set_Password(&password);
                Lock_Error = EEPROM_Lock();
                Lock_State = EEPROM_Get_Lock_State();
                if(Lock_State == EEPROM_LOCKED) LCD_SendStr("LOCKED");
                else LCD_SendStr("LOCK ERROR");
                SysCtlDelay(16000000*2 /(3));
                LCD_SendCommand(CLR_DISPLAY);
                Pass_Counter = 0;
                password = 0x00;
            }
            if((Lock_State == EEPROM_LOCKED)&&(Set_Password_Error == NO_ERROR)&&(Lock_Error == NO_ERROR))
            {
                NextState = Locked;
                One_Time_FLag = 1;
            }
        }break;
        case Locked:
        {
            if(GET_BIT(Event_Reg,Three_Stars_Pressed))
            {
                LCD_SendCommand(CLR_DISPLAY);
                LCD_SendStr("Enter Password:");
                SysCtlDelay(16000000*2 /(3));
                LCD_SendCommand(CLR_DISPLAY);
                NextState = Three_Stars_Pressed_Handler();
                One_Time_FLag = 1;
            }
            if(GET_BIT(Event_Reg,Three_Hashes_Pressed))
            {
                LCD_SendCommand(CLR_DISPLAY);
                LCD_SendStr("Enter Password:");
                SysCtlDelay(16000000*2 /(3));
                LCD_SendCommand(CLR_DISPLAY);
                NextState = Three_Hashes_Pressed_Handler();
                One_Time_FLag = 1;
            }
        }break;
        case Enter_Pass_To_Unlock:
        {
            if(pressed != 0xff)
                  {
                      password |= ((0x00|pressed) << Pass_Counter*8);
                      Pass_Counter++;
                      LCD_SendData(pressed);
                      SysCtlDelay(16000000 /(3*3));
                  }
            if (Pass_Counter==4)
            {
                LCD_SendCommand(CLR_DISPLAY);
                Unlock_Error = EEPROM_Unlock(&password);
                Lock_State = EEPROM_Get_Lock_State();
                Pass_Counter = 0;
                password = 0x00;
                if((Lock_State == EEPROM_UNLOCKED)&&(Unlock_Error == NO_ERROR)) {
                         LCD_SendStr("UNLOCKED");
                         SysCtlDelay(16000000*2 /(3));
                         LCD_SendCommand(CLR_DISPLAY);
                         NextState = Correct_Password_Handler();
                     }
                else
                {
                    LCD_SendStr("UNLOCKE ERROR");
                    SysCtlDelay(16000000*2 /(3));
                    LCD_SendCommand(CLR_DISPLAY);
                    NextState = Incorrect_Password_Handler();
                }
            }

        }break;
        case Unlocked_Pass:
        {
            if(GET_BIT(Event_Reg,Three_Stars_Pressed))
            {
                Lock_Error = EEPROM_Lock();
                if(Lock_Error == NO_ERROR)
                {
                    LCD_SendCommand(CLR_DISPLAY);
                    LCD_SendStr("LOCKED");
                    SysCtlDelay(16000000*2 /(3));
                    LCD_SendCommand(CLR_DISPLAY);
                    NextState = Locked;
                }
            }
        }break;
        case Enter_Pass_To_Reset:
        {
            if(pressed != 0xff)
                              {
                                  password |= ((0x00|pressed) << Pass_Counter*8);
                                  Pass_Counter++;
                                  LCD_SendData(pressed);
                                  SysCtlDelay(16000000 /(3*3));
                              }
                        if (Pass_Counter==4)
                        {
                            LCD_SendCommand(CLR_DISPLAY);
                            Unlock_Error = EEPROM_Unlock(&password);
                            Lock_State = EEPROM_Get_Lock_State();
                            Pass_Counter = 0;
                            password = 0x00;
                            if((Lock_State == EEPROM_UNLOCKED)&&(Unlock_Error == NO_ERROR)) {
                                     LCD_SendStr("RESET SUCCESS");
                                     SysCtlDelay(16000000*2 /(3));
                                     LCD_SendCommand(CLR_DISPLAY);
                                     EEPROM_Mass_Erase();
                                     NextState = Correct_Password_Handler();
                                 }
                            else
                            {
                                LCD_SendStr("RESET ERROR");
                                SysCtlDelay(16000000*2 /(3));
                                LCD_SendCommand(CLR_DISPLAY);
                                NextState = Incorrect_Password_Handler();
                            }
                        }

        }break;
        }

    }
    return 0;
}


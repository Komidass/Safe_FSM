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
#include "FSM_1.h"


u8 keys[16];
u8 pressed;
u8 Init_Error;
u8 Set_Password_Error;
u8 Lock_Error;
u8 Unlock_Error;
u8 Lock_State;
State NextState;
volatile u32 Event_Reg;
u32 State_EEPROM;


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
    u8 pass_flash_counter;
    u8 EEPROM_Write_Error;
    u8 EEPROM_Read_Error = EEPROM_READ(&State_EEPROM, 2, 0, 1);
    NextState = Unlocked_NoPass;
    EEPROM_Mass_Erase();
    u32 LastState;
    while(1)
    {
        State_EEPROM = NextState;
        if (LastState != NextState) EEPROM_Write_Error = EEPROM_Write(&State_EEPROM, 2, 0, 1);
        KBD_u8GetKeyPadState(keys);
        pressed = KBD_keys_map(keys);
        ReadState();

        switch(NextState)
        {
        case Unlocked_NoPass:
        {
            if(One_Time_FLag)
            {
                LCD_SendCommand(CLR_DISPLAY);
                LCD_SendStr("Press  ***      to Set password");
                while(pressed == 0xff)
                {
                    KBD_u8GetKeyPadState(keys);
                    pressed = KBD_keys_map(keys);
                }
                LCD_SendCommand(CLR_DISPLAY);
                One_Time_FLag = 0;
            }

            if(GET_BIT(Event_Reg,Three_Stars_Pressed))
            {
               LastState = NextState;
               NextState = Three_Stars_Pressed_Handler();
               One_Time_FLag = 1;
            }
        }
        break;
        case Enter_Pass_To_Lock:
        {

            if(One_Time_FLag)
            {
                LCD_SendCommand(CLR_DISPLAY);
                LCD_SendStr("Enter Password to lock");
                while(pressed == 0xff)
                {
                    KBD_u8GetKeyPadState(keys);
                    pressed = KBD_keys_map(keys);
                }
                LCD_SendCommand(CLR_DISPLAY);
                One_Time_FLag = 0;
            }
            if(pressed != 0xff)
                  {
                      password |= ((0x00|pressed) << Pass_Counter*8);
                      Pass_Counter++;
                      LCD_SendData(pressed);
                      SysCtlDelay(16000000 /(3*3));
                      SysCtlDelay(16000000 /(3*6));
                      LCD_SendCommand(CLR_DISPLAY);
                      for(pass_flash_counter = 0; pass_flash_counter<Pass_Counter; pass_flash_counter++)
                      {
                          LCD_SendData('*');
                      }

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
                LastState = NextState;
                NextState = Locked;
                One_Time_FLag = 1;
            }
        }break;
        case Locked:
        {
            if(One_Time_FLag)
            {
                LCD_SendCommand(CLR_DISPLAY);
                LCD_SendStr("***: Unlock");
                LCD_GoToXY(1, 0);
                LCD_SendStr("###: Reset pass");
                while(pressed == 0xff)
                {
                    KBD_u8GetKeyPadState(keys);
                    pressed = KBD_keys_map(keys);
                }
                LCD_SendCommand(CLR_DISPLAY);
                One_Time_FLag = 0;
            }
            if(GET_BIT(Event_Reg,Three_Stars_Pressed))
            {
                LastState = NextState;
                NextState = Three_Stars_Pressed_Handler();
                One_Time_FLag = 1;
            }
            if(GET_BIT(Event_Reg,Three_Hashes_Pressed))
            {
                LastState = NextState;
                NextState = Three_Hashes_Pressed_Handler();
                One_Time_FLag = 1;
            }
        }break;
        case Enter_Pass_To_Unlock:
        {
            if(One_Time_FLag)
            {
                LCD_SendCommand(CLR_DISPLAY);
                LCD_SendStr("Enter password to unlock");
                while(pressed == 0xff)
                {
                    KBD_u8GetKeyPadState(keys);
                    pressed = KBD_keys_map(keys);
                }
                LCD_SendCommand(CLR_DISPLAY);
                One_Time_FLag = 0;
            }
            if(pressed != 0xff)
                  {
                      password |= ((0x00|pressed) << Pass_Counter*8);
                      Pass_Counter++;
                      LCD_SendData(pressed);
                      SysCtlDelay(16000000 /(3*3));
                      SysCtlDelay(16000000 /(3*6));
                      LCD_SendCommand(CLR_DISPLAY);
                      for(pass_flash_counter = 0; pass_flash_counter<Pass_Counter; pass_flash_counter++)
                      {
                          LCD_SendData('*');
                      }
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
                         LastState = NextState;
                         NextState = Correct_Password_Handler();
                         One_Time_FLag = 1;
                     }
                else
                {
                    LCD_SendStr("UNLOCKE ERROR");
                    SysCtlDelay(16000000*2 /(3));
                    LCD_SendCommand(CLR_DISPLAY);
                    LastState = NextState;
                    NextState = Incorrect_Password_Handler();
                    One_Time_FLag = 1;
                }
            }

        }break;
        case Unlocked_Pass:
        {
            if(One_Time_FLag)
            {
                LCD_SendCommand(CLR_DISPLAY);
                LCD_SendStr("***: Lock");
                while(pressed == 0xff)
                {
                    KBD_u8GetKeyPadState(keys);
                    pressed = KBD_keys_map(keys);
                }
                LCD_SendCommand(CLR_DISPLAY);
                One_Time_FLag = 0;
            }
            if(GET_BIT(Event_Reg,Three_Stars_Pressed))
            {
                Lock_Error = EEPROM_Lock();
                if(Lock_Error == NO_ERROR)
                {
                    LCD_SendCommand(CLR_DISPLAY);
                    LCD_SendStr("LOCKED");
                    SysCtlDelay(16000000*2 /(3));
                    LCD_SendCommand(CLR_DISPLAY);
                    LastState = NextState;
                    NextState = Locked;
                    One_Time_FLag = 1;
                }
            }
        }break;
        case Enter_Pass_To_Reset:
        {
            if(One_Time_FLag)
            {
                LCD_SendCommand(CLR_DISPLAY);
                LCD_SendStr("Enter Password to reset");
                SysCtlDelay(16000000*2 /(3));
                while(pressed == 0xff)
                {
                    KBD_u8GetKeyPadState(keys);
                    pressed = KBD_keys_map(keys);
                }
                LCD_SendCommand(CLR_DISPLAY);
                One_Time_FLag = 0;
            }
            if(pressed != 0xff)
                              {
                                  password |= ((0x00|pressed) << Pass_Counter*8);
                                  Pass_Counter++;
                                  LCD_SendData(pressed);
                                  SysCtlDelay(16000000 /(3*3));
                                  SysCtlDelay(16000000 /(3*6));
                                  LCD_SendCommand(CLR_DISPLAY);
                                  for(pass_flash_counter = 0; pass_flash_counter<Pass_Counter; pass_flash_counter++)
                                  {
                                      LCD_SendData('*');
                                  }
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
                                     LastState = NextState;
                                     NextState = Correct_Password_Handler();
                                     One_Time_FLag = 1;
                                 }
                            else
                            {
                                LCD_SendStr("RESET ERROR");
                                SysCtlDelay(16000000*2 /(3));
                                LCD_SendCommand(CLR_DISPLAY);
                                LastState = NextState;
                                NextState = Incorrect_Password_Handler();
                                One_Time_FLag = 1;
                            }
                        }

        }break;
        }

    }
    return 0;
}


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
int main () {

    DIO_PortInit(PORTA_);
    DIO_PortInit(PORTE_);
    DIO_PortInit(PORTB_);
    DIO_SetPortDirection(PORTB_, 0b00001111);
    DIO_SetPortDirection(PORTA_, 0b11111000);
    DIO_SetPortDirection(PORTE_, 0b00111111);
    LCD_Init_8BIT(DISP_ON_CBON);
    KBD_u8Initialize(PORTB_);
    u8 keys[16];
    u8 pressed;
    LCD_SendCommand(CLR_DISPLAY);
    while(1)
    {
        KBD_u8GetKeyPadState(keys);
        pressed = KBD_keys_map(keys);
        if(pressed != 0xff)
        {
            if(pressed == 'C')
            {
                SysCtlDelay(16000000 /(3*3));
                LCD_SendCommand(CLR_DISPLAY);
            }
            else
            {
                LCD_SendData(pressed);
                SysCtlDelay(16000000 /(3*3));
            }

        }

    }

return 0;
}


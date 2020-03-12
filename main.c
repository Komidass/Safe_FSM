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

    DIO_PortInit(PORTB_);
    DIO_PortInit(PORTE_);
  //  DIO_SetPortDirection(PORTB_, 0b00001111);
    DIO_SetPortDirection(PORTE_, 0xff);
    KBD_u8Initialize(PORTB_);
    u8 keys[16];
    u8 pressed;
    u32 password = 0x00;
    u8 i = 0;
    while(1)
    {
        KBD_u8GetKeyPadState(keys);
        pressed = KBD_keys_map(keys);

        if(pressed != 0xff)
              {
                  password |= ((0x00|pressed) << i*8);
                  i++;
                  DIO_SetPortValue(PORTE_ , 0xff);
                  SysCtlDelay(16000000 /(3));
              }
        else {
            DIO_SetPortValue(PORTE_ , 0x00);
        }
        if (i==4)
        {
            i = 0;
            password = 0x00;
        }
    }

return 0;
}


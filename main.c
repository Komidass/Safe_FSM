#include "types.h"
#include"BIT_MATH.h"
#include "DIO_REG.h"
#include "DIO.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "LCD.h"
#include "EEPROM.h"
#include "KBD_interface.h"
int main () {
u8 error_Init_state = EEPROM_Init();
u32 pass = 0x78945612;
u32 pass2 = 0x45644564;
//u8 error_Set_pass = EEPROM_Set_Password(&pass);
//u8 error_lock = EEPROM_Lock();
u8 unlocked = EEPROM_Unlock(&pass);
u8 Lock_State = EEPROM_Get_Lock_State();
// if (EEPROM_Get_Lock_State() == LOCKED) DIO_SetPinValue(F1, HIGH);
// if (EEPROM_Get_Lock_State() == UNLOCKED) DIO_SetPinValue(F1, LOW);
    while(1)
    {

    }
return 0;
}
/* DIO_PortInit(PORTB_);
 DIO_SetPortDirection(PORTB_, 0xff);
 DIO_SetPortValue(PORTB_, 0x40);
 */

 /*DIO_SetPortDirection(PORTE_, 0x07);
 DIO_SetPortDirection(PORTB_, 0xff);
 LCD_SendCommand(CLR_DISPLAY);
 */
/*  LCD_Init_8BIT(DISP_ON_CBON);
 LCD_SendStr("My Tiva-c loves ");
 LCD_GoToXY(1, 0);
 LCD_SendStr("YOUUUUUUUUUUUU ");
*/
/*      if(key != 0xff)
      {
          password |= ((0x00|key) << i*8);
          i++;
      }
      */

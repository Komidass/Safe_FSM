/*******************************************************/
/* Author  : Bishoy Medhat                             */
/* Version : V1.0                                      */
/* Date    : 26 FEB 2019                               */
/*******************************************************/
/* Description                                         */
/* ------------                                        */
/* This file has the implementation of both private and*/
/* public function corresponding to Keypad module      */
/*******************************************************/

#include "types.h"
#include"BIT_MATH.h"
#include "DIO_REG.h"
#include "DIO.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "KBD_config.h"
#include "KBD_interface.h"
#include "KBD_private.h"



u8 KBD_u8GetKeyPadState(u8* Copy_Au8KeysState/*[KBD_u8_KEYS_NB]*/)
{
	u8 LOCAL_u8ColIndex = 0;
	u8 LOCAL_u8RowIndex = 0;
	
	u8 Local_u8CurrentPinValue=0;
	u8 Local_u8KeyIndex=0;
	
	// check on Activation type
	#if KBD_u8_ACTIVATION_TYPE==KBD_u8_ACTIVE_COL
		for(LOCAL_u8ColIndex = 0; LOCAL_u8ColIndex < KBD_u8_COL; LOCAL_u8ColIndex ++ )
		{
			//activate current col
			#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
				DIO_SetPinValue(KBD_Au8ColsPins[LOCAL_u8ColIndex], LOW);
			#else
				DIO_SetPinValue(KBD_Au8ColsPins[LOCAL_u8ColIndex], HIGH);
			#endif
			
			//Check on active ROW
			
			for(LOCAL_u8RowIndex = 0; LOCAL_u8RowIndex < KBD_u8_ROWS; LOCAL_u8RowIndex ++)
			{
			    Local_u8CurrentPinValue = DIO_GetPinValue(KBD_Au8ColsPins[LOCAL_u8ColIndex]);
				
				Local_u8KeyIndex = LOCAL_u8ColIndex + (LOCAL_u8RowIndex*KBD_u8_COL);
				
				if(Local_u8CurrentPinValue == HIGH)
				{
					#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
					//Not Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_NOT_PRESSED;
					#else
					//Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_PRESSED;
					#endif
				}else
				{
					#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
					//Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_PRESSED;
					#else
					//Not Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_NOT_PRESSED;
					#endif
				}
			}
			#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
				DIO_SetPinValue(KBD_Au8ColsPins[LOCAL_u8ColIndex], HIGH);
			#else
				DIO_SetPinValue(KBD_Au8ColsPins[LOCAL_u8ColIndex], LOW);
			#endif
		}
	#else
		for(LOCAL_u8RowIndex = 0; LOCAL_u8RowIndex < KBD_u8_ROWS; LOCAL_u8RowIndex ++)
		{
			//activate current row
			#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
				DIO_SetPinValue(KBD_Au8RowsPins[LOCAL_u8RowIndex], LOW);
			#else
				DIO_SetPinValue(KBD_Au8RowsPins[LOCAL_u8RowIndex], HIGH);
			#endif
			
			//Check on active COL
			
			for(LOCAL_u8ColIndex = 0; LOCAL_u8ColIndex < KBD_u8_COL; LOCAL_u8ColIndex ++ )
			{
				//(KBD_Au8ColsPins[LOCAL_u8ColIndex], &Local_u8CurrentPinValue);
				Local_u8CurrentPinValue = DIO_GetPinValue(KBD_Au8ColsPins[LOCAL_u8ColIndex);
				Local_u8KeyIndex = LOCAL_u8RowIndex + (LOCAL_u8ColIndex*KBD_u8_ROWS);
				
				if(Local_u8CurrentPinValue == HIGH)
				{
					#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
					//Not Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_NOT_PRESSED;
					#else
					//Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_PRESSED;
					#endif
				}else
				{
					#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
					//Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_PRESSED;
					#else
					//Not Pressed
						Copy_Au8KeysState[Local_u8KeyIndex]= KBD_u8_NOT_PRESSED;
					#endif
				}
			}
			#if KBD_u8_CONNECTION_TYPE==KBD_u8_CON_PULLUP
				DIO_SetPinValue(KBD_Au8RowsPins[LOCAL_u8RowIndex], HIGH);
			#else
				DIO_SetPinValue(KBD_Au8RowsPins[LOCAL_u8RowIndex], LOW);
			#endif
		}

	#endif

}
void KBD_u8Initialize(void) //initialize keypad active col pull up with Row 4 to be the the 8th pin in the port and col 4 to the 1st pin
	{
            u32 i;
		    DIO_PinInit(output0);
            DIO_PinInit(output1);
            DIO_PinInit(output2);
            DIO_PinInit(output3);
            DIO_PinInit(input0);
            DIO_PinInit(input1);
            DIO_PinInit(input2);
            DIO_PinInit(input3);
			DIO_SetPinDirection(output0, OUTPUT);
            DIO_SetPinDirection(output1, OUTPUT);
            DIO_SetPinDirection(output2, OUTPUT);
            DIO_SetPinDirection(output3, OUTPUT);
            DIO_SetPinDirection(input0, INPUT);
            DIO_SetPinDirection(input1, INPUT);
            DIO_SetPinDirection(input2, INPUT);
            DIO_SetPinDirection(input3, INPUT);
			DIO_Pull_Pin_Up(input0);
			DIO_Pull_Pin_Up(input1);
			DIO_Pull_Pin_Up(input2);
			DIO_Pull_Pin_Up(input3);
			for (i=0;i<4;i++)
			{
				KBD_Au8RowsPins[i] = input0 + i;
				KBD_Au8ColsPins[i] = output3 - i;
			}

	}

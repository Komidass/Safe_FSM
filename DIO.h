/*
 * DIO.h
 *
 *  Created on: Feb 26, 2020
 *      Author: PI
 */

#ifndef INC_DIO_H_
#define INC_DIO_H_

/* Port Defines */
#define PORTA_   0
#define PORTB_   1
#define PORTC_   2
#define PORTD_   3
#define PORTE_   4
#define PORTF_   5

/* PIN Defines */
#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7

/* PIN Directions */
#define INPUT  0
#define OUTPUT 1

/* PIN Value Options */
#define HIGH   1
#define LOW    0

enum Pins{
            A0,
            A1,
            A2,
            A3,
            A4,
            A5,
            A6,
            A7,
            B0,
            B1,
            B2,
            B3,
            B4,
            B5,
            B6,
            B7,
            C0,
            C1,
            C2,
            C3,
            C4,
            C5,
            C6,
            C7,
            D0,
            D1,
            D2,
            D3,
            D4,
            D5,
            D6,
            D7,
            E0,
            E1,
            E2,
            E3,
            E4,
            E5,
            E6,
            E7,
            F0,
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
};

void DIO_SetPortDirection (u8 u8PortId, u8 u8PortDir) ;
void DIO_PinInit(u8 PinId);
void DIO_PortInit (u8 u8PortId);
void DIO_Pull_Pin_Up (u8 PinId);
void DIO_Pull_Pin_Down (u8 PinId);
void DIO_SetPinDirection (u8 PinId, u8 u8PinDirCopy);
void DIO_SetPinValue(u8 PinId,u8 PinValue);
u8 DIO_GetPinValue(u8 PinId) ;
void DIO_SetPortValue (u8 u8PortId, u8 u8PortVal) ;



#endif /* INC_DIO_H_ */

/*******************************************************/
/* Author  : Bishoy Medhat                             */
/* Version : V1.0                                      */
/* Date    : 26 FEB 2019                               */
/*******************************************************/
/* Description                                         */
/* ------------                                        */
/* This file defines the configuration parameters for  */
/* Keypad Component                                    */
/*******************************************************/

/* Comment: Header file guard                          */
#ifndef KBD_CONFIG_H
#define KBD_CONFIG_H

#define KBD_u8_ROWS		4
#define KBD_u8_COL		4

#define KBD_u8_ACTIVATION_TYPE	KBD_u8_ACTIVE_COL
#define KBD_u8_CONNECTION_TYPE	KBD_u8_CON_PULLUP


u8 KBD_Au8RowsPins[KBD_u8_ROWS];

u8 KBD_Au8ColsPins[KBD_u8_COL];
#endif

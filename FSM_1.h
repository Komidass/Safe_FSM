/*
 * FSM_1.h
 *
 *  Created on: Mar 11, 2020
 *      Author: tho
 */

#ifndef FSM_1_H_
#define FSM_1_H_



extern volatile u32 Event_Reg;


typedef enum
{
    Unlocked_NoPass,
    Enter_Pass_To_Lock,
    Locked,
    Enter_Pass_To_Unlock,
    Unlocked_Pass,
    Enter_Pass_To_Reset,
} State;
extern State NextState;

enum Events
{
    Three_Stars_Pressed,
    Three_Hashes_Pressed,
    Correct_Password,
    Incorrect_Password,

};

void ReadState(void);
State Three_Stars_Pressed_Handler(void);
State Three_Hashes_Pressed_Handler(void);
State Correct_Password_Handler(void);
State Incorrect_Password_Handler(void);




#endif /* FSM_1_H_ */

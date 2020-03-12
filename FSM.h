/*
 * FSM.h
 *
 *  Created on: Mar 10, 2020
 *      Author: thomas
 */

#ifndef FSM_H_
#define FSM_H_


 //u8    No_Of_Stars = 0;
 //u8    No_Of_Hashes = 0;
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


#endif /* FSM_H_ */

#include  "types.h"
#include  "BIT_MATH.h"
#include "DIO.h"
#include "DIO_REG.h"


volatile u32* DIO_OutRegisters [6] = {GPIO_PORTA_DATA_REG,GPIO_PORTB_DATA_REG,GPIO_PORTC_DATA_REG,GPIO_PORTD_DATA_REG,GPIO_PORTE_DATA_REG ,GPIO_PORTF_DATA_REG};

volatile u32* DIO_DirRegisters [6] = {GPIO_PORTA_DIR_REG , GPIO_PORTB_DIR_REG , GPIO_PORTC_DIR_REG , GPIO_PORTD_DIR_REG, GPIO_PORTE_DIR_REG , GPIO_PORTF_DIR_REG};

volatile u32* DIO_AfselRegisters [6] = {GPIO_PORTA_AFSEL_REG , GPIO_PORTB_AFSEL_REG ,GPIO_PORTC_AFSEL_REG, GPIO_PORTD_AFSEL_REG, GPIO_PORTE_AFSEL_REG, GPIO_PORTF_AFSEL_REG};

volatile u32* DIO_DEN_Registers [6] = {GPIO_PORTA_DEN_REG,GPIO_PORTB_DEN_REG , GPIO_PORTC_DEN_REG , GPIO_PORTD_DEN_REG , GPIO_PORTE_DEN_REG , GPIO_PORTF_DEN_REG};

volatile u32* DIO_Lock_Registers [6] = {GPIO_PORTA_LOCK_REG,GPIO_PORTB_LOCK_REG,GPIO_PORTC_LOCK_REG,GPIO_PORTD_LOCK_REG,GPIO_PORTE_LOCK_REG,GPIO_PORTF_LOCK_REG};

volatile u32* DIO_Commit_Registers [6] = {GPIO_PORTA_CR_REG,GPIO_PORTB_CR_REG,GPIO_PORTC_CR_REG,GPIO_PORTD_CR_REG,GPIO_PORTE_CR_REG,GPIO_PORTF_CR_REG};
volatile u32* DIO_Amsel_Registers [6] = {GPIO_PORTA_AMSEL_REG , GPIO_PORTB_AMSEL_REG , GPIO_PORTC_AMSEL_REG , GPIO_PORTD_AMSEL_REG , GPIO_PORTE_AMSEL_REG , GPIO_PORTF_AMSEL_REG};

volatile u32* DIO_Port_Control_Registers [6] = {GPIO_PORTA_PCTL_REG,GPIO_PORTB_PCTL_REG,GPIO_PORTC_PCTL_REG,GPIO_PORTD_PCTL_REG,GPIO_PORTE_PCTL_REG,GPIO_PORTF_PCTL_REG};

volatile u32* DIO_Port_Pull_Up [6] = {GPIO_PORTA_PUR_REG , GPIO_PORTB_PUR_REG , GPIO_PORTC_PUR_REG , GPIO_PORTD_PUR_REG , GPIO_PORTE_PUR_REG , GPIO_PORTF_PUR_REG};

volatile u32* DIO_Port_Pull_Down [6] = {GPIO_PORTA_PDR_REG , GPIO_PORTB_PDR_REG , GPIO_PORTC_PDR_REG , GPIO_PORTD_PDR_REG , GPIO_PORTE_PDR_REG , GPIO_PORTF_PDR_REG};




void DIO_PortInit (u8 u8PortId){

    // connect the selected Port to the clock
        SET_BIT(*SYSCTL_RCGCGPIO_REG,u8PortId);
        // unlock the Port
        *DIO_Lock_Registers[u8PortId] = 0x4C4F434B;
        //commit registers
        *DIO_Commit_Registers [u8PortId] = 0xff;
        // digital enable
        *DIO_DEN_Registers[u8PortId] = 0xff;
        // not analog
         *DIO_Amsel_Registers[u8PortId] = 0x00;
}

void DIO_PinInit(u8 PinId)
{
    u8 PortId = PinId/8;
    u8 Pin = PinId%8;
    SET_BIT(*SYSCTL_RCGCGPIO_REG,PortId);
    SET_BIT(*DIO_Commit_Registers[PortId],Pin);
    SET_BIT(*DIO_DEN_Registers[PortId],Pin);
    CLR_BIT(*DIO_Amsel_Registers[PortId],Pin);
}
void DIO_SetPortDirection (u8 u8PortId, u8 u8PortDir) {

    //set the direction
    *DIO_DirRegisters[u8PortId] = u8PortDir;
    // alternative selcet for the port
    *DIO_AfselRegisters[u8PortId] = 0x00;

    // control reg
    *DIO_Port_Control_Registers[u8PortId] = 0x00;

}


void DIO_SetPortValue (u8 u8PortId, u8 u8PortVal) {

    *DIO_OutRegisters [u8PortId] = u8PortVal;
}



void DIO_Pull_Pin_Up (u8 PinId){
    u8 PortId = PinId/8;
    u8 Pin = PinId%8;
    SET_BIT(*DIO_Port_Pull_Up[PortId],Pin);

}


void DIO_Pull_Pin_Down (u8 PinId){
    u8 PortId = PinId/8;
    u8 Pin = PinId%8;
    SET_BIT(*DIO_Port_Pull_Down[PortId],Pin);

}

void DIO_SetPinDirection (u8 PinId, u8 u8PinDirCopy){

    u8 PortId = PinId/8;
    u8 Pin = PinId%8;
            if ( u8PinDirCopy == OUTPUT )
                {
                SET_BIT(*DIO_DirRegisters[PortId],Pin);
                }

            if ( u8PinDirCopy == INPUT )
                {
                CLR_BIT(*DIO_DirRegisters[PortId],Pin);
                }
}

void DIO_SetPinValue(u8 PinId,u8 PinValue) {

u8 PortId = PinId/8;
u8 Pin = PinId%8;
if (PinValue == HIGH) SET_BIT(*DIO_OutRegisters [PortId],Pin);
if (PinValue == LOW) CLR_BIT(*DIO_OutRegisters [PortId],Pin);
}

u8 DIO_GetPinValue(u8 PinId)
{
    u8 PortId = PinId/8;
    u8 Pin = PinId%8;
    u8 u8ResultLocal= GET_BIT(*DIO_OutRegisters[PortId],Pin);

return u8ResultLocal;

}


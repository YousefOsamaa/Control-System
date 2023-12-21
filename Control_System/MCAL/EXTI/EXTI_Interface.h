/*
 * EXTI_Interface.h
 *
 * Created: 12/21/23 1:38:59 AM
 *  Author: joo
 */ 

#include <avr/io.h>

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


void EXTI_Init()
{
    /*Initiazlizing INT0 */
    EICRA |= (3 <<  0); //CHoosing Sense Level as rising
    EIMSK |= (1 << 0); //Enabling INT1 (PIE)

}



#endif /* EXTI_INTERFACE_H_ */
/*
 * IncFile1.h
 *
 * Created: 12/19/23 4:22:34 AM
 *  Author: 
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#include "../../LIB/LSTD.h"

#define SREG (*(volatile u8_t*)(0x5F))

void SREG_EnableGIE()
{
    SREG |= ( 1<< 7);
}

void SREG_DisableGIE()
{
    SREG &= ~( 1<< 7);
}



#endif /* INCFILE1_H_ */

#ifndef DC_INTERFACE_H_
#define DC_INTERFACE_H_

/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/

#include "../../LIB/LBIT_MATH.h"
#include "../../LIB/LSTD.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include <avr/interrupt.h>

/***************************************************************************************************/
/*                                        Important macros                                         */
/***************************************************************************************************/

#define ENC_PORT			(PORTC)
#define A_Phase				(PIN1)
#define B_Phase				(PIN2)
#define Z_Signal			(PIN3)
 
static s16_t  motorPosition=0;
/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/

void encoderMotor_init()
{
	mdio_setPinStatus(ENC_PORT,A_Phase,INPUT_PULL_DOWN);
	mdio_setPinStatus(ENC_PORT,A_Phase,INPUT_PULL_DOWN);
	mdio_setPinStatus(ENC_PORT,Z_Signal,INPUT_PULL_DOWN);
	return;
}

s16_t ret_Encoder_Value()
{
	return motorPosition;
}


/***************************************************************************************************/
/*													ISR                                   */
/***************************************************************************************************/

ISR (INT0_vect)
{
	u8_t temp;
	//We need to read the other pin of the encoder which will be either 1 or 0 depending on the direction
	mdio_getPinValue(ENC_PORT,A_Phase,&temp);

	if (temp == 1) //CW direction
	{
		motorPosition++;
	}
	else //else, it is zero... -> CCW direction
	{
		motorPosition--;
	}


}


#endif /* DC_INTERFACE_H_ */
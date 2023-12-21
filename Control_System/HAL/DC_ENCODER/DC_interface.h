
#ifndef DC_INTERFACE_H_
#define DC_INTERFACE_H_

/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/

#include "../../LIB/LBIT_MATH.h"
#include "../../LIB/LSTD.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../HAL/H_BRIDGE/H_Bridge.h"
#include <avr/interrupt.h>

/***************************************************************************************************/
/*                                        Important macros                                         */
/***************************************************************************************************/

#define ENC_PORT			(PORTD)
#define A_Phase				(PIN4)
#define B_Phase				(PIN2)
#define Z_Signal			(PIN3)   /*NOT USED UNTIL NOW*/


#define Max_RPM					(210)
#define Gear_Ratio				(515)
#define Pulses_Per_Rev_Shaft    (1)
#define Pulses_Per_Rev_Gear     (Pulses_Per_Rev_Shaft*Gear_Ratio)

//PID parameters - tuned by the user
float proportional = 1.35; //k_p = 0.5
float integral = 0.00005; //k_i = 3
float derivative = 0.01; //k_d = 1
float controlSignal = 0; //u - Also called as process variable (PV) 
static u8_t Target;
static int  motorPosition=0;
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

void setTarget(u8_t t)
{
	Target=t;
	return;
}
u8_t getTarget()
{
	return Target;
}

/*TO BE MODIFIED BECAUSE THIS MUST BE DONE AS INTERRUPT OR DO IT WITH PID CALCULATION WHICH I THINK WOULD BE BETTER*/
/*THIS FUNCTION IS WRONG TILL NOW*/
void start_Motor()
{
	u8_t Pulses=0;
	f32_t temp=360/Target;
	u8_t temp2;
	temp=Pulses_Per_Rev_Gear/temp;
	H_Bridge_SetMode(CW);
	while(motorPosition < Pulses_Per_Rev_Shaft)
	{
		mdio_getPinValue(ENC_PORT,A_Phase,&temp2);
		if(temp2==1)
		Pulses++;
		
	}
	H_Bridge_SetMode(OFF);
	return;
}
void calculate_PID()
{
	 int errorValue = motorPosition - Target; //Current position - target position (or setpoint)
	 controlSignal = (proportional * errorValue)
	 return;
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
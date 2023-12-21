/*
 * H_Bridge.h
 *
 * Created: 12/19/2023 1:57:18 AM
 *  Author: OWNER
 */ 


#ifndef H_BRIDGE_H_
#define H_BRIDGE_H_
/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/

#include "../../MCAL/DIO/DIO_interface.h"
#include "../../LIB/LBIT_MATH.h"
#include "../../LIB/LSTD.h"

/***************************************************************************************************/
/*                                        Important macros                                         */
/***************************************************************************************************/

/*Setting H Bridge Modes*/
#define  CW   (0)
#define  CCW  (1)
#define  OFF  (2)

/*Setting H Bridge Port,Enable, and inputs*/
#define H_PORT  (PORTD)
#define IN1     (PIN0)
#define IN2     (PIN1)
#define EN      (PIN6)

u8_t Dir_Status;
/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/


/**
 * @brief This function is responsible for initializing H Bridge
 * 
 * @param au8_port 
 * @param au8_pin 
 * @param au8_status 
 */
void H_Bridge_init()
{
	
	mdio_setPinStatus(H_PORT,IN1,OUTPUT);
	mdio_setPinStatus(H_PORT,IN2,OUTPUT);
	Dir_Status=OFF;
	
	return;
}

/**
 * @brief This function is responsible for setting Mode of H Bridge
 * 
 * @param au8_port 
 * @param au8_pin 
 * @param au8_status 
 */
void H_Bridge_SetMode(u8_t Mode)
{
	switch (Mode)
	{
		
	
	case CW:
	mdio_setPinValue(H_PORT,IN1,HIGH);
	mdio_setPinValue(H_PORT,IN2,LOW);
	Dir_Status=CW;
	
	break;
	
	case CCW:
	mdio_setPinValue(H_PORT,IN1,LOW);
	mdio_setPinValue(H_PORT,IN2,HIGH);
	Dir_Status=CCW;
	break;
	
	case OFF:
	mdio_setPinValue(H_PORT,IN1,LOW);
	mdio_setPinValue(H_PORT,IN2,LOW);
	Dir_Status=OFF;
	break;
	
	default:
	break;
	
	
	}
	return;
}


void Speed_Control(u8_t Duty)
{
	Generate_PWM_Signal(Duty);
	
}

u8_t Toggle_Direction()
{
	
	if(Dir_Status==CW){
	H_Bridge_SetMode(CCW);

			}
	else if(Dir_Status==CCW)
	{
		
	H_Bridge_SetMode(CW);

    }
	else
	Dir_Status=OFF;
}
#endif /* H_BRIDGE_H_ */
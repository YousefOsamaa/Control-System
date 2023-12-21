/**
 * @file    MDIO_private.h
 * @author  
 * @brief   This file contains private information related to DIO module
 * @version 1.0
 * @date    
 * 
 * 
 */



#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "../../LIB/LSTD.h"
/***************************************************************************************************/
/*                                         DIO Registers                                           */
/***************************************************************************************************/

/*PORTB registers*/
#define MDIO_PORTB_ADDRESS                   ((volatile u8_t*)(0x25))
#define MDIO_DDRB_ADDRESS                    ((volatile u8_t*)(0x24))
#define MDIO_PINB_ADDRESS                    ((volatile u8_t*)(0x23))

/*PORTC registers*/
#define MDIO_PORTC_ADDRESS                   ((volatile u8_t*)(0x28))
#define MDIO_DDRC_ADDRESS                    ((volatile u8_t*)(0x27))
#define MDIO_PINC_ADDRESS                    ((volatile u8_t*)(0x26))

/*PORTD registers*/
#define MDIO_PORTD_ADDRESS                   ((volatile u8_t*)(0x2B))
#define MDIO_DDRD_ADDRESS                    ((volatile u8_t*)(0x2A))
#define MDIO_PIND_ADDRESS                    ((volatile u8_t*)(0x29))


/***************************************************************************************************/
/*                                         Interfacing macros                                      */
/***************************************************************************************************/

/*DIO Ports*/

#define PORTB          (0)  
#define PORTC          (1)  
#define PORTD          (2) 

/*DIO Pins*/                           //AVAILABLE PINS

#define PIN0           (0b00000001)     //B,C,D
#define PIN1           (0b00000010)     //B,C,D
#define PIN2           (0b00000100)     //B,C,D
#define PIN3           (0b00001000)     //B,C,D
#define PIN4           (0b00010000)     //B,C,D
#define PIN5           (0b00100000)     //B,C,D
#define PIN6           (0b01000000)     //D
#define PIN7           (0b10000000)     //D


/*DIO Pins' status*/
#define INPUT_PULL_DOWN    (0)
#define INPUT_PULLUP       (1)
#define OUTPUT             (2)

/*DIO Pins' values*/
#define LOW            (0)
#define HIGH           (1)

/***************************************************************************************************/
/*                                        Functions' prototypes                                    */
/***************************************************************************************************/

/**
 * @brief This function is responsible for setting the DIO pins status (Input/Output)
 * 
 * @param au8_port 
 * @param au8_pin 
 * @param au8_status 
 */
void mdio_setPinStatus(u8_t au8_port, u8_t au8_pin, u8_t au8_status);

/**
 * @brief This function is responsible for setting the DIO pins value (High/Low)
 * 
 * @param au8_port 
 * @param au8_pin 
 * @param au8_value 
 */
void mdio_setPinValue(u8_t au8_port, u8_t au8_pin, u8_t au8_value);

/**
 * @brief This function is responsible for toggling the DIO pins value (High -> Low/Low -> High)
 * 
 * @param au8_port 
 * @param au8_pin 
 */
void mdio_togglePinValue(u8_t au8_port, u8_t au8_pin);

/**
 * @brief This function is responsible for getting the DIO pin value (High/Low)
 * 
 * @param au8_port 
 * @param au8_pin 
 * @param pu8_pinValue 
 */
void mdio_getPinValue(u8_t au8_port, u8_t au8_pin, u8_t* pu8_pinValue);

#endif /*__MDIO_INTERFACE_H__*/



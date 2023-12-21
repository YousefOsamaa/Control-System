
/* Brief:Control System Project. There are 2 modes.
First one is the speed control mode. The second
one is Position control. Both the speed and position are
controlled through potentiometer. 

 Authors: Ali Saeed,Youssef Osama,Mohamed Saeed,Ziad Ragaie,Kareem el Farsy

*/

/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/

#define F_CPU   16000000UL
#include <avr/io.h>
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#include "MCAL/TIMER/Timer_interface.h"
#include "LIB/LSTD.h"
#include "MCAL/ADC/ADC_interface.h"
#include "HAL/LCD/LCD.h"
#include "MCAL/SREG/SREG_Interface.h"
#include "HAL/H_Bridge/H_Bridge.h"
#include <stdlib.h>
#include <util/delay.h>
#include "HAL/DC_ENCODER/DC_interface.h"
#include "MCAL/EXTI/EXTI_Interface.h"

/***************************************************************************************************/
/*                                        Important Variables & Macros                                */
/***************************************************************************************************/

u16_t MotorSpeed;

// Variable to tell main that the button is pressed (and debounced).
// Main will clear it after a detected button press.
volatile u8_t button_down;

#define Max_RPM    (210)
#define Gear_Ratio (515)
#define BUTTON_PIN PIND
#define BUTTON_MASK (1<<PD3)

/***************************************************************************************************/
/*                                        Important Functions                                         */
/***************************************************************************************************/

static void debounce(void)
{
	// Counter for number of equal states
	static uint8_t count = 0;
	// Keeps track of current (debounced) state
	static uint8_t button_state = 0;
	// Check if button is high or low for the moment
	uint8_t current_state = (~BUTTON_PIN & BUTTON_MASK) != 0;
	if (current_state != button_state) {
		// Button state is about to be changed, increase counter
		count++;
		if (count >= 4) {
			// The button have not bounced for four checks, change state
			button_state = current_state;
			// If the button was pressed (not released), tell main so
			if (current_state != 0) {
				button_down = 1;
			}
			count = 0;
		}
	}
	else {
		// Reset counter
		count = 0;
	}
}


/***************************************************************************************************/
/*                                               Main                                         */
/***************************************************************************************************/

int main(void)
{
    u16_t Text[10];
    
	ADC_init();
   
	H_Bridge_init();
	
	H_Bridge_SetMode(CCW);
	

	mdio_setPinStatus(PORTD,PIN2,INPUT_PULL_DOWN);

	mdio_setPinStatus(PORTD,PIN3,INPUT_PULLUP);

	Timer_init();
   
    LCD_Init();
	int rpm;

	EXTI_Init();

	// Enabling Interrupts
	SREG_EnableGIE();
    while (1)
    {
		debounce();
	    if(button_down)
		{
		Toggle_Direction();
		button_down=0;
		}
	    ADC_startConversion(&MotorSpeed ,ADC_CHANNEL_0);
	    sprintf(Text,"%d",MotorSpeed);
	    
	    Generate_PWM_Signal(MotorSpeed/50.0);
	    
	    LCD_GoToXY(0,0);		
	    sprintf(Text,"%d",ret_Encoder_Value());
		LCD_PutStr(Text);
		
	 }



}
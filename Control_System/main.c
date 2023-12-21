
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
int Pos_Degrees;
// Variable to tell main that the button is pressed (and debounced).
// Main will clear it after a detected button press.
volatile u8_t button_down;



#define BUTTON_PIN PIND
#define BUTTON_MASK				(1<<PD3)
#define SELECT_MODE				(0)
#define SPEED_MODE				(1)
#define POSITION_MODE			(2)
#define PRESSED                 (1)
#define RELEASED                (0)
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
/*                                               Main                                             */
/***************************************************************************************************/

int main(void)
{
	
	/*INITIALZINNG PROGRAM FUNCTIONS*/
	u8_t mode=SELECT_MODE;
	mdio_setPinStatus(PORTC,PIN1,INPUT_PULL_DOWN);
	mdio_setPinStatus(PORTC,PIN2,INPUT_PULL_DOWN);
    u16_t Text[10];
	char Text_Position[3];
	ADC_init();
	H_Bridge_init();
	H_Bridge_SetMode(OFF);
	mdio_setPinStatus(PORTD,PIN2,INPUT_PULL_DOWN);
	mdio_setPinStatus(PORTD,PIN3,INPUT_PULLUP);
	Timer_init();
    LCD_Init();
	int rpm;
	EXTI_Init();
	// Enabling Interrupts
	SREG_EnableGIE();
	
	/*ENETRING SUPERLOOP*/
    while (1)
    {
		/*USER INPUT FOR SYSTEM MODE*/
		if(mode==SELECT_MODE)
		{
			mode=SPEED_MODE;
			
			/*STUCK IN LOOP UNTIL USER CONFIRM*/
			while(!(PINC & 1<<2))
			{
				LCD_GoToXY(0,0);
				LCD_PutStr("WELCOME :)");
				LCD_GoToXY(1,0);
				LCD_PutStr("SELECT:");
				
				/*CHECKING IF SPEED MODE*/
				if(mode==SPEED_MODE)
				{
					
					/*TOGGLING TO POSITION MODE IF BUTTON PRESSED*/
					if(PINC & 1<<1)
					{
						mode=POSITION_MODE;
						LCD_PutStr("Position");
						_delay_ms(50);
					}
					
					/*ELSE STAY SPEED CONTROL*/
					else
					{
						mode=SPEED_MODE;
						LCD_PutStr("Speed");
					}
				}
				
				/*IF NOT SPEED MODE,POSITION CONTROL MODE*/
				else
				{
					/*TOGGLING TO SPEED MODE IF BUTTON PRESSED*/
					if(PINC & 1<<1)
					{
						mode=SPEED_MODE;
						LCD_PutStr("Speed");
						LCD_PutStr("   ");
						_delay_ms(50);
					}
					/*ELSE STAY POSITION CONTROL*/
					else
					{
						mode=POSITION_MODE;
						LCD_PutStr("Position");
					}
					
				}
				
				
			}
			/*CLEARING WELCOME SCREEN AND INITIALZING MOTOR*/
			H_Bridge_SetMode(CW);
			LCD_Clear();
		}
		
		/*CHECKING IF MODE= SPEED CONTROL*/
		if(mode==SPEED_MODE)
		{
			/*CHECKING IF USER WANTS TO GET BACK TO SELECT MODE*/
			if(PINC & 1<<1)
			{
				mode=SELECT_MODE;
				H_Bridge_SetMode(OFF);
			}
			else
			{
				/*ENTERED SPEED MODE*/
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
		
		/*CHECKING IF MODE= POSITION CONTROL MODE*/
		else
		{
			/*CHECKING IF USER WANTS TO RETURN TO MENU*/
			if(PINC & 1<<1)
			{
				mode=SELECT_MODE;
				H_Bridge_SetMode(OFF);
			}
			/*ENTERED POSITION CONTROL*/
			H_Bridge_SetMode(OFF);
			ADC_startConversion(&Pos_Degrees ,ADC_CHANNEL_0);
			Pos_Degrees = (Pos_Degrees*360.0)/5000.0;
			setTarget(Pos_Degrees);
			LCD_GoToXY(0,0);
			LCD_PutStr("Target:");
			sprintf(Text,"%d",Pos_Degrees);
			LCD_PutStr(Text);
			LCD_GoToXY(1,0);
			LCD_PutStr("Confirm ???");
			debounce();
			if(button_down)
			{
				LCD_Clear();
				start_Motor();
				button_down=0;
			}
			
		}
		
	 }



}
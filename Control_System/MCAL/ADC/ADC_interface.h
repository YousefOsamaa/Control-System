/*
 * ADC_interface.h
 *
 * Created: 12/19/2023 1:27:35 AM
 *  Author: OWNER
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/***************************************************************************************************/
/*                                             Includes                                            */
/***************************************************************************************************/

#include "../../LIB/LBIT_MATH.h"
#include "../../LIB/LSTD.h"

/***************************************************************************************************/
/*                                        Important macros                                         */
/***************************************************************************************************/

#define step    (5000.0/1024.0)
#define ADC_CHANNEL_0  (0)

/***************************************************************************************************/
/*                                       Functions' definitions                                    */
/***************************************************************************************************/

void ADC_init()
{
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // highest prescaler 128
	ADMUX |= (0<<REFS1) | (1<<REFS0); // Voltage Reference Vcc
	ADMUX |= (0<<MUX2)|(0<<MUX1)|(0<<MUX0); // First ADC pin
	ADCSRA |= (1<<ADEN); // Enabling the ADC Functionality

	return;
}

void ADC_startConversion(u16_t* var,u8_t channel)
{
	
	ADCSRA |= (1<<ADIF); //Writing on ADIF clears the flag for the next conversion.
	ADCSRA |= (1<<ADSC); //starting conversion again to always convert new voltage data
	while  (!(ADCSRA & (1<<ADIF) )); // waiting until conversion is complete
	ADCSRA |= (1<<ADIF); //Writing on ADIF clears the flag for the next conversion.
	*var = ADC * step; //10bit value saved in ADCH&L is multiplied by step value is saved to variable.
	
	return;
}


#endif /* ADC_INTERFACE_H_ */
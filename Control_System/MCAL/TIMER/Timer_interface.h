/*
 * Timer_interface.h
 *
 * Created: 12/19/2023 1:35:21 AM
 *  Author: OWNER
 */ 


#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

/***************************************************************************************************/
/*                                        Functions' definitions                                         */
/***************************************************************************************************/

 
void Timer_init()
{
	SET_BIT(DDRD,6);
	TCCR0A |=0b10000001;  /*USING NON INVERTING PHASE CORRECT MODE*/
	TCCR0B |= (1<<CS02) | (1<<CS00); /*PRESCALER : 1024*/
	OCR0A=0.5*155;  /*INITIALIZING DUTY WITH 50%*/
	
	return;
}

void Generate_PWM_Signal(u8_t Duty)
{
	OCR0A = Duty*255/100;
	
	return;
}










#endif /* TIMER_INTERFACE_H_ */
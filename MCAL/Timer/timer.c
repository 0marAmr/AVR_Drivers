
#include <avr/io.h>

#include "timer.h"

static uint8 PWM_getDutyCycle(const uint8 duty_cycle_percentage);


static uint8 PWM_getDutyCycle(const uint8 duty_cycle_percentage){
	return (((uint16)duty_cycle_percentage * TIMER0_MAX_COUNT)/100);
}

void PWM_timer0Start(uint8 duty_cycle){
	TCNT0 = 0; //Set Timer Initial value

	OCR0  = PWM_getDutyCycle(duty_cycle); // Set Compare Value

	DDRB  = DDRB | (1<<PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}

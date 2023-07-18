/*
 * timer0.c
 *
 * Created: 12/1/2022 11:03:21 PM
 *  Author: AhmedMabrouk
 */ 

#include "timer0.h"

uint32_t timer0_value_ms;

void timer0_free_init(void) {
	TCCR0 |= (1<<FOC0) | (1<<WGM01) | (1<<CS00) | (1<<CS01);    // 64 prescaler, CTC mode
	OCR0   = 250;												// set compare value to adjust 1 ms for every interrupt
}

void timer0_free_start(void) {
	SETBIT(TIMSK, OCIE0);						// enable compare match interrupt for ctc mode
	SETBIT(SREG,7);								// enable global interrupt
	timer0_value_ms = 0;						// set initial value for timer = 0
}

void timer0_free_end(void) {
	CLRBIT(TIMSK, OCIE0);						// disable compare match interrupt for ctc mode
	CLRBIT(SREG,7);								// disable global interrupt
}

void timer0_normal_init(void) {
	TCCR0 |= (1<<FOC0) | (1<<CS00) | (1<<CS02);				 // normal mode, 1024 prescaler
	SETBIT(TIMSK,TOIE0);									 // enable overflow interrupt for normal mode
	SETBIT(SREG,7);											 // enable global interrupt
}

void timer0_CTC_init(uint8_t max) {
	TCCR0 |= (1<<FOC0) | (1<<WGM01) | (1<<CS00) | (1<<CS01); // 64 prescaler, CTC mode
	OCR0   = max;										   	 // set compare value
	TIMSK |= (1<<OCIE0);									 // enable compare match interrupt for ctc mode
	SETBIT(SREG,7);											 // enable global interrupt
}

void timer0_frea_gen_init(uint8_t max) {
	SETBIT(DDRB,3);
	TCCR0 |= (1<<FOC0) | (1<<WGM01) | (1<<COM00) | (1<<CS00) | (1<<CS02); // CTC mode, 1024 prescaler
	OCR0   = max;
}

void timer0_PWM_init(void) {
	SETBIT(DDRB,3);
	TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00); // PWM mode, non-inverting, no prescaler
}

void timer0_PWM_Duty(uint8_t duty) {
	OCR0 = duty*2.55;
}
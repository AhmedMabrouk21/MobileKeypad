/*
 * timer0.h
 *
 * Created: 12/1/2022 11:02:50 PM
 *  Author: AhmedMabrouk
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include "std_macros.h"
void timer0_free_init(void);
void timer0_free_start(void);
void timer0_free_end(void);
void timer0_normal_init(void);
void timer0_CTC_init(uint8_t);
void timer0_frea_gen_init(uint8_t);
void timer0_PWM_init(void);
void timer0_PWM_Duty(uint8_t duty);


#endif /* TIMER0_H_ */
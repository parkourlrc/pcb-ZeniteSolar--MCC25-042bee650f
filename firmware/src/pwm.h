#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#ifndef PWM_H
#define PWM_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include"conf.h"

#ifdef MACHINE_ON
#include "machine.h"
#endif



// // pwm macros
#define set_pwm_duty_cycle(d)       OCR1A = d      //!< apply duty cycle 'd'
#define set_pwm_off()               OCR1A = 0;     //!< d = 0

#ifndef PWM_DDR
#define PWM_DDR DDRB
#endif
#ifndef PWM
#define PWM PB1
#endif


#ifndef INITIAL_D
#define INITIAL_D      0
#endif

#ifndef PWM_PRESCALE
#define PWM_PRESCALE    1
#endif  
#define PWM_CLK_DIVIDER_VALUE           10 // TODO

// Equations for mode 14 (Fast PWM with TOP in ICR1)
// At 100 kHz with F_CPU = 16 MHz, ICR1 = PWM_TOP = 159 (16000000 / 100000 - 1)
#define PWM_TOP 159
#define PWM_RESOLUTION log10(PWM_TOP +1)/log10(2)
#define PWM_D_MAX   ((uint16_t)(0.95f * PWM_TOP))
#define PWM_D_MIN   ((uint16_t)(0.25f * PWM_TOP))
void pwm_init(void);
void pwm_compute(void);
void pwm_reset(void);
#endif /* ifndef PWM_H */
#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#ifndef MACHINE_H
#define MACHINE_H 

#include <avr/io.h>
#include <avr/wdt.h>
#include"conf.h"

// #ifdef USART_ON
// #include "usart.h"
// #endif
#ifdef ADC_ON
#include "adc.h"
#endif

//DEFINIÇÕES DE MEDIDAS (TENSÕES E CORRENTES REAIS)
#define MAXIMUM_PANEL_CURRENT 10.0f //10A
#define MAXIMUM_PANEL_VOLTAGE 21.0f // 21V
#define MAXIMUM_BATT_VOLTAGE 50.0f // 50V
#define MINIMUM_BATT_VOLTAGE 28.0f //28V
#define MINIMUM_PANEL_VOLTAGE 9.0f //9V

// LIMITES EM CONVERSÃO DIRETA DO ADC (0 a 1023) PARA CHECAGEM RÁPIDA
// Ipanel:  I = 0.032923627 * ADC - 16.62932491 => ADC = (I + 16.62932491) / 0.032923627
#define ADC_MAX_PANEL_CURRENT   809    // ~10.0 A
// Vpanel:  V = 0.020717284 * ADC - 0.057896889 => ADC = (V + 0.057896889) / 0.020717284
#define ADC_MAX_PANEL_VOLTAGE   1016   // ~21.0 V
#define ADC_MIN_PANEL_VOLTAGE   437    // ~9.0 V
// Vbatt:   V = 0.066479683 * ADC - 0.156185641 => ADC = (V + 0.156185641) / 0.066479683
#define ADC_MAX_BATT_VOLTAGE    634    // ~42,0 V
#define ADC_MIN_BATT_VOLTAGE    363    // ~24.0 V

//DEFINIÇÕES GERAIS
#define LED PC5
#define LED_DDR DDRC
#define LED_PORT PORTC
#define ENABLE_DRIVER PB3
#define ENABLE_DRIVER_DDR DDRB
#define ENABLE_DRIVER_PORT PORTB

extern volatile uint8_t machine_clk;
extern uint8_t total_errors;   // Contagem de ERROS

typedef enum state_machine{
    STATE_INITIALIZING,
    STATE_RUNNING,
    STATE_ERROR,
} state_machine_t;

extern volatile state_machine_t state_machine;

typedef struct control{
    uint16_t    D;              // value converted from 0 to TOP
    uint8_t  sweep_done;
    float    i_panel[2];              // value of panel current in AMPS
    float    v_panel[2];              // value of panel voltage in VOLTS
	float	v_batt[2];			// value of battery voltage in VOLTS
	float	pi[2];			// value of power in WATTS

}control_t;

extern volatile control_t control;

typedef union error_flags{
    struct{
        uint8_t     overcurrent :1;
        uint8_t     overvoltage :1;
		uint8_t		undervoltage:1;
		uint8_t		overvolt_panel:1;
		uint8_t		undervolt_panel:1;
    };
    uint8_t   all;
}error_flags_t;
extern volatile error_flags_t error_flags;

void machine_init(void);
void check_buffers(void);
void check_electrical_limits_adc(uint16_t raw_i_panel, uint16_t raw_v_panel, uint16_t raw_v_batt);
void read_and_check_adcs(void);
void clr_EN_driver(void);
void set_EN_driver(void);
void set_LED(void);
void task_initializing(void);
void task_running(void);
void task_error(void);
void machine_run(void);

//control.i_panel = ma_adc0(void);
//control.v_panel = ma_adc1(void);
//control.v_batt = ma_adc2(void);

#endif /* ifndef MACHINE_H */
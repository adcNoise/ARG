#ifndef LED_H
#define LED_H

#include "stm32g0xx_hal.h"
#include "Periphery.h"

/*
typedef enum {
	GREEN_LED_ALARM	= 0,	// Не горит когда активен красный светодиод
	GREEN_LED_READY,		// Горит на постоянку - ситема готова
	GREEN_LED_OIL_PUMP,		//
	GREEN_LED_OIL_HEAT,		//
	GREEN_LED_IGNITION,		//
	GREEN_LED_1ST,			//
	GREEN_LED_2ST			//
	
}GREEN_LED;

typedef enum {
	RED_LED_READY	= 0,	// Не горит когда активен зелёный светодиод
	RED_LED_ALARM			// 
} RED_LED;

extern RED_LED 		RedLED;
extern GREEN_LED 	GreenLED;
*/
extern void LED_Indicator(void);
#endif
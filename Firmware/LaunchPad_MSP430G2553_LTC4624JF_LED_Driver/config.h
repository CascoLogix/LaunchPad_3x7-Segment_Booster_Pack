#ifndef LAUNCHPAD_MSP430G2553_LTC4624JF_LED_DRIVER_CONFIG_H_
#define LAUNCHPAD_MSP430G2553_LTC4624JF_LED_DRIVER_CONFIG_H_

#include <msp430g2553.h>


#define DIGIT_TIME	125
#define ONE_SECOND	31250


#define LED_MUX			P2OUT
#define LED_MUX_EN		P2DIR
#define LED_SEGMENTS	P1OUT


#endif /*LAUNCHPAD_MSP430G2553_LTC4624JF_LED_DRIVER_CONFIG_H_*/
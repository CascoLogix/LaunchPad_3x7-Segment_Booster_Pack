//******************************************************************************
//  MSP430G2xx2 Demo - Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and TA_0 ISR. Toggles every
//  50000 SMCLK cycles. SMCLK provides clock source for TACLK.
//  During the TA_0 ISR, P1.0 is toggled and 50000 clock cycles are added to
//  CCR0. TA_0 ISR is triggered every 50000 cycles. CPU is normally off and
//  used only during TA_ISR.
//  ACLK = n/a, MCLK = SMCLK = TACLK = default DCO
//
//           MSP430G2xx2
//         ---------------
//     /|\|            XIN|-
//      | |               |
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
//
//  D. Dang
//  Texas Instruments Inc.
//  December 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************


#include <msp430g2452.h>
#include "config.h"
#include "Drivers\LTC4624JF\LTC4624JF.h"
#include <stdint.h>


void initMSP430(void);


extern void DisplaySegments(void);
extern void WriteToDisplay(uint8_t alphaNumeric, uint8_t anode);
extern void TestDisplay(void);
extern void ClearDisplay(void);
extern void TestAnode(uint8_t anode);
extern void ClearAnode(uint8_t anode);


uint8_t sec, min;
uint8_t display_Data[NUM_DIGITS];

void main(void)
{
	sec = 0;									// Initialize sec to 0
	min = 0;									// Initialize min to 0
   	WriteToDisplay(0, DIGIT_1);					// Initialize digit 1
   	WriteToDisplay(0, DIGIT_2);					// Initialize digit 2
   	WriteToDisplay(0, DIGIT_3);					// Initialize digit 3
   	WriteToDisplay(':', L_GROUP);				// Display colon
	initMSP430();
	_BIS_SR(LPM0_bits + GIE);					// Enter LPM0 w/ interrupt
}


void initMSP430(void)
{
	WDTCTL = WDTPW + WDTHOLD;					// Stop WDT
	
	P1DIR = 0xFF;								// P1.0 & P1.6 output
	P2DIR = BIT0|BIT1|BIT2|BIT3|BIT4|BIT5;		// P2.0 through P2.5 output
	
	CCTL0 = CCIE;								// CCR0 interrupt enabled
	CCTL1 = CCIE;
	CCR0 = ONE_SECOND;
	CCR1 = DIGIT_TIME;
    BCSCTL2 |= DIVS0|DIVS1;						// Setup divider for SMCLK/8
	//TACTL = TASSEL_2 + MC_2;					// SMCLK, contmode
	TACTL = TASSEL_2 + MC_2 + ID1;				// SMCLK, contmode
}


// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A_CCR0 (void)
{
    if (++sec > 59)						//count seconds, up to one minute
    {
        sec = 0;                        //reset seconds and ...
        if (++min > 9)					//count miutes, up to one hour
            min = 0;                    //reset minutes and ...
    }
    
    display_Data[DIGIT_3] = sec%10;
    display_Data[DIGIT_2] = sec/10;
    display_Data[DIGIT_1] = min;
    
    uint8_t i;
    
    for(i = 0; i < NUM_DIGITS; i++)
    	WriteToDisplay(display_Data[i], i);
    
    CCR0 += ONE_SECOND;						// Setup next IRQ

}


// Timer A0 interrupt service routine
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TimerA_CCR1 (void)
{
	switch(TA0IV)
	{
		case  2:                          		// CCR1
		{
    		DisplaySegments();
			CCR1 += DIGIT_TIME;
			break;
		}
			
		case  4: 
			break;                          	// CCR2 not used
		
		case 10: 								// overflow
            break;
	}
}


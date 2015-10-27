

#include <config.h>
#include <LTC4624JF.h>
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
	
	TACCTL0 = CCIE;								// CCR0 interrupt enabled
	TACCTL1 = CCIE;
	TACCR0 = ONE_SECOND;
	TACCR1 = DIGIT_TIME;
    BCSCTL2 |= DIVS0|DIVS1;						// Setup divider for SMCLK/8
	//TACTL = TASSEL_2 + MC_2;					// SMCLK, contmode
	TACTL = TASSEL_2 + MC_2 + ID1;				// SMCLK, contmode
}


// Timer A0 interrupt service routine
//#pragma vector=TIMERA0_VECTOR		// MSP430F2618
#pragma vector=TIMER0_A0_VECTOR		// MSP430G2452, MSP430G2553
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
    
    TACCR0 += ONE_SECOND;						// Setup next IRQ

}


// Timer A0 interrupt service routine
//#pragma vector=TIMERA1_VECTOR		// MSP430F2618
#pragma vector=TIMER0_A1_VECTOR		// MSP430G2452, MSP430G2553
__interrupt void TimerA_CCR1 (void)
{
	switch(TA0IV)
	{
		case  2:                          		// CCR1
		{
    		DisplaySegments();
			TACCR1 += DIGIT_TIME;
			break;
		}
			
		case  4: 
			break;                          	// CCR2 not used
		
		case 10: 								// overflow
            break;
	}
}


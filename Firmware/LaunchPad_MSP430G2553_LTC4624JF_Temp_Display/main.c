

#include <config.h>
#include <LTC4624JF.h>
#include <stdint.h>


#define ADCDeltaOn       3                  // ~ 2 Deg C delta for LED on


void initMSP430(void);
void kickstartADC10(void);


static unsigned int FirstADCVal;            // holds 1st ADC result
uint8_t display_Data[NUM_DIGITS];


void main(void)
{
	kickstartADC10();
	
   	WriteToDisplay(0, DIGIT_1);					// Initialize digit 1
   	WriteToDisplay(0, DIGIT_2);					// Initialize digit 2
   	WriteToDisplay(0, DIGIT_3);					// Initialize digit 3
   	WriteToDisplay(255, L_GROUP);
	initMSP430();
	_BIS_SR(LPM0_bits + GIE);					// Enter LPM0 w/ interrupt
}


void initMSP430(void)
{
	WDTCTL = WDTPW + WDTHOLD;					// Stop WDT
	
	P1DIR = 0xFF;								// P1.0 & P1.6 output
	P2DIR = BIT0|BIT1|BIT2|BIT3|BIT4|BIT5;		// P2.0 through P2.5 output
	
	TA1CCTL1 = CCIE;
	TA1CCR1 = DIGIT_TIME;
    BCSCTL2 |= DIVS0|DIVS1;						// Setup divider for SMCLK/8
	TA1CTL = TASSEL_2 + MC_2 + ID1;				// SMCLK, contmode
}


void kickstartADC10(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog
  ADC10CTL1 = ADC10DIV_3 + INCH_10 + SHS_1 + CONSEQ_2;  // TA trig., rpt, A10
  ADC10CTL0 = SREF_1 + ADC10SHT_3 + REF2_5V + ADC10IE + REFON + ADC10ON;
  __enable_interrupt();                     // Enable interrupts.
  TA0CCR0 = 30;                             // Delay to allow Ref to settle
  TA0CCTL0 |= CCIE;                         // Compare-mode interrupt.
  TA0CTL = TASSEL_2 | MC_1;                 // TACLK = SMCLK, Up mode.
  LPM0;                                     // Wait for delay.
  TA0CCTL0 &= ~CCIE;                        // Disable timer Interrupt
  __disable_interrupt();
  ADC10CTL0 |= ENC;
  TA0CCTL1 = OUTMOD_4;                      // Toggle on EQU1 (TAR = 0)
  TA0CTL = TASSEL_2 + MC_2;                 // SMCLK, cont-mode
  while (!(ADC10IFG & ADC10CTL0));          // First conversion?
  FirstADCVal = ADC10MEM;                   // Read out 1st ADC value
  P1OUT = 0x00;                             // Clear P1
  P1DIR = 0x01;                             // P1.0 as output
}


#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
  if (ADC10MEM >= FirstADCVal + ADCDeltaOn)
    P1OUT |= 0x01;                          // LED on
  else
    P1OUT &= ~0x01;                         // LED off
    
  WriteToDisplay((ADC10MEM & 0x0F), DIGIT_3);
  
  if(ADC10MEM > 15)
	WriteToDisplay(((ADC10MEM >> 4) & 0x0F), DIGIT_2);
  else
    ClearAnode(DIGIT_2);
    
  if(ADC10MEM > 255)
	WriteToDisplay(((ADC10MEM >> 8) & 0x0F), DIGIT_1);
  else
    ClearAnode(DIGIT_1);
}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void ta0_isr(void)
{
  TA0CTL = 0;
  LPM0_EXIT;                                // Exit LPM0 on return
}


// Timer A0 interrupt service routine
//#pragma vector=TIMERA1_VECTOR		// MSP430F2618
#pragma vector=TIMER1_A1_VECTOR		// MSP430G2452, MSP430G2553
__interrupt void TimerA_CCR1 (void)
{
	switch(TA1IV)
	{
		case  2:                          		// CCR1
		{
    		DisplaySegments();
			TA1CCR1 += DIGIT_TIME;
			break;
		}
			
		case  4: 
			break;                          	// CCR2 not used
		
		case 10: 								// overflow
            break;
	}
}

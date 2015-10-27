#ifndef LTC4624JF_H_
#define LTC4624JF_H_


// Includes
#include <config.h>
#include <stdint.h>


// Defines
#define _COMMON_ANODE_

#define NUM_DIGITS 		3
#define NUM_ANODES		4

#define MAX_DECIMAL		10
#define MAX_HEXADECIMAL	16

#define ANODE_1			0
#define ANODE_2			1
#define ANODE_3			2
#define ANODE_4			3

#define DIGIT_1			ANODE_1
#define DIGIT_2			ANODE_2
#define DIGIT_3			ANODE_3
#define L_GROUP			ANODE_4

#define SEG_A			(1 << 0)
#define SEG_B			(1 << 1)
#define SEG_C			(1 << 2)
#define SEG_D			(1 << 3)
#define SEG_E			(1 << 4)
#define SEG_F			(1 << 5)
#define SEG_G			(1 << 6)
#define SEG_DP			(1 << 7)

#define SEG_L1			SEG_A
#define SEG_L2			SEG_B
#define SEG_L3			SEG_C


extern void WriteToDisplay(uint8_t alphaNumeric, uint8_t anode);
extern void TestDisplay(void);
extern void ClearDisplay(void);
extern void TestAnode(uint8_t anode);
extern void ClearAnode(uint8_t anode);
extern void DisplaySegments(void);
extern uint8_t DecimalNumLookup(uint8_t number);
extern uint8_t HexNumLookup(uint8_t number);
extern uint8_t AlphaLookup(char ascii);
extern void DPOn(uint8_t anode);
extern void DPOff(uint8_t anode);


extern uint8_t codedDataArray[NUM_ANODES];				// stores the active segments for each digit
extern uint8_t anode;									// local variable to select which anode is active
extern uint8_t testMode;								// local flag to activate/deactivate test mode


#endif /*LTC4624JF_H_*/

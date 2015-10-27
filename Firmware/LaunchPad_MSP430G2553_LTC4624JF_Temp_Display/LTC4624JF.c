


#include <LTC4624JF.h>


uint8_t codedDataArray[NUM_ANODES];				// stores the active segments for each digit
uint8_t anode;									// local variable to select which anode is active
uint8_t testMode;								// local flag to activate/deactivate test mode


/***********************************************************************************
 * 
 * Constant array to store the active segments which create the corresponding 
 * decimal or hexadecimal number.
 * 
 **********************************************************************************/
const uint8_t num_map[] = 
{
	SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F,		// 0
	SEG_B|SEG_C,								// 1
	SEG_A|SEG_B|SEG_E|SEG_D|SEG_G,				// 2
	SEG_A|SEG_B|SEG_C|SEG_D|SEG_G,				// 3
	SEG_B|SEG_C|SEG_F|SEG_G,					// 4
	SEG_A|SEG_C|SEG_D|SEG_F|SEG_G,				// 5
	SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G,		// 6
	SEG_A|SEG_B|SEG_C,							// 7
	SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G,	// 8
	SEG_A|SEG_B|SEG_C|SEG_F|SEG_G,				// 9
	SEG_A|SEG_C|SEG_E|SEG_F|SEG_G,				// A
	SEG_C|SEG_D|SEG_E|SEG_F|SEG_G,				// b
	SEG_A|SEG_D|SEG_E|SEG_F,					// C
	SEG_B|SEG_C|SEG_D|SEG_E|SEG_G,				// d
	SEG_A|SEG_D|SEG_E|SEG_F|SEG_G,				// E
	SEG_A|SEG_E|SEG_F|SEG_G						// F
};	


/***********************************************************************************
 * 
 * Constant array to store the active segments which create the corresponding 
 * character.
 * 
 **********************************************************************************/
const uint8_t char_map[] = 
{
	SEG_A|SEG_C|SEG_E|SEG_F|SEG_G,				// 'A'
	SEG_C|SEG_D|SEG_E|SEG_F|SEG_G,				// 'b'
	SEG_A|SEG_D|SEG_E|SEG_F,					// 'C'
	SEG_B|SEG_C|SEG_D|SEG_E|SEG_G,				// 'd'
	SEG_A|SEG_D|SEG_E|SEG_F|SEG_G,				// 'E'
	SEG_A|SEG_E|SEG_F|SEG_G,					// 'F'
	SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G,		// 'g'
	SEG_C|SEG_E|SEG_F|SEG_G,					// 'h'
	SEG_B|SEG_C,								// 'i'
	SEG_B|SEG_C|SEG_D|SEG_E,					// 'J'
	SEG_D|SEG_E|SEG_F,							// 'L'
	SEG_C|SEG_E|SEG_G,							// 'n'
	SEG_C|SEG_D|SEG_E|SEG_G,					// 'o'
	SEG_A|SEG_B|SEG_E|SEG_F|SEG_G,				// 'P'
	SEG_A|SEG_B|SEG_C|SEG_F|SEG_G,				// 'q'
	SEG_E|SEG_G,								// 'r'
	SEG_A|SEG_C|SEG_D|SEG_F|SEG_G,				// 'S'
	SEG_D|SEG_E|SEG_F|SEG_G,					// 't'
	SEG_C|SEG_D|SEG_E,							// 'u'
	SEG_B|SEG_C|SEG_D|SEG_F|SEG_G,				// 'y'	
	SEG_D,										// '_'
	SEG_G,										// '-'
	SEG_DP,										// '.'
	SEG_L1|SEG_L2,								// ':'
	SEG_L3										// degrees symbol
};


/***********************************************************************************
 * 
 * Function name: WriteToDisplay(alphaNumeric, anode)
 * 
 * Scope: global
 * 
 * Parameters:
 * 		alphaNumeric - can be either a number 0x00 thru 0x0F, or an ASCII-coded 
 * 			character (note: not all characters are supported).
 * 		anode - must be in range: zero <= anode <= NUM_ANODES
 * 
 * Description:
 * 		WriteToDisplay handles writing the alphanumeric character to the display.  
 * The resulting segment data is written to codedDataArray[], which is used in a 
 * separate scan loop.  
 * 
 * Only certain characters are supported.  Unsupported 
 * characters will result in a blank digit (all segments off).
 * 
 * Attempting to write to an invalid anode (i.e. anode >= NUM_ANODES) will result 
 * in no change in that digit from the previous state.
 *   
 **********************************************************************************/
void WriteToDisplay(uint8_t alphaNumeric, uint8_t anode)
{
	if(anode < NUM_ANODES)
	{
		if(alphaNumeric < MAX_DECIMAL)
			codedDataArray[anode] = (codedDataArray[anode] & SEG_DP) | ~DecimalNumLookup(alphaNumeric);
		else if(alphaNumeric < MAX_HEXADECIMAL)
			codedDataArray[anode] = (codedDataArray[anode] & SEG_DP) | ~HexNumLookup(alphaNumeric);
		else
			codedDataArray[anode] = (codedDataArray[anode] & SEG_DP) | ~AlphaLookup(alphaNumeric);
		
		testMode &= ~(1<<anode);	// Deactivate test mode for specified anode
	}
}


/***********************************************************************************
 * 
 * Function name: TestDisplay()
 * 
 * Scope: global
 * 
 * Parameters:
 * 		none
 * 
 * Description:
 * 		TestDisplay() turns on all segments for all anodes.  
 * 
 **********************************************************************************/
void TestDisplay(void)
{
	testMode = (1<<ANODE_1)|(1<<ANODE_2)|(1<<ANODE_3)|(1<<ANODE_4);
}


/***********************************************************************************
 * 
 * Function name: ClearDisplay()
 * 
 * Scope: global
 * 
 * Parameters:
 * 		none
 * 
 * Description:
 * 		ClearDisplay() turns off all segments for all anodes.  
 * 
 **********************************************************************************/
void ClearDisplay(void)
{
	codedDataArray[0] = 0xFF;
	codedDataArray[1] = 0xFF;
	codedDataArray[2] = 0xFF;
	codedDataArray[3] = 0xFF;
}


/***********************************************************************************
 * 
 * Function name: TestAnode(anode)
 * 
 * Scope: global
 * 
 * Parameters:
 * 		anode - must be in range: zero <= anode <= NUM_ANODES
 * 
 * Description:
 * 		TestAnode() turns on all segments for the anode specified.  
 * 
 **********************************************************************************/
void TestAnode(uint8_t anode)
{
	testMode = (1<<anode);
}


/***********************************************************************************
 * 
 * Function name: ClearAnode(anode)
 * 
 * Scope: global
 * 
 * Parameters:
 * 		anode - must be in range: zero <= anode <= NUM_ANODES
 * 
 * Description:
 * 		ClearAnode() turns off all segments for the anode specified.  
 * 
 **********************************************************************************/
void ClearAnode(uint8_t anode)
{
	codedDataArray[anode] = 0xFF;
}


/***********************************************************************************
 * 
 * Function name: DisplaySegments(void)
 * 
 * Scope: global
 * 
 * Parameters:
 * 		none
 * 
 * Description:
 * 		DisplaySegments is used in a scan loop where each call increments to the 
 * next digit and updates the active segments according to the control data in 
 * codedDataArray[].  
 *   
 **********************************************************************************/
void DisplaySegments(void)
{
	uint8_t temp;
	
	if(anode >= NUM_ANODES)
		anode = 0;
	
	if(testMode & (1<<anode))
	{
		LED_MUX &= 0xF0;
		LED_SEGMENTS = 0x00;												// Enable all segments
		temp = LED_MUX & ~((1<<ANODE_1)|(1<<ANODE_2)|(1<<ANODE_3)|(1<<ANODE_4));	// Clear digit enable bits
		LED_MUX = temp | (1<<anode);										// Set appropriate digit enable bit
	}
	
	else
	{
		if(anode < NUM_DIGITS)
		{
			LED_MUX &= 0xF0;
			LED_SEGMENTS = codedDataArray[anode];								// Enable digit segments
			temp = LED_MUX & ~((1<<ANODE_1)|(1<<ANODE_2)|(1<<ANODE_3)|(1<<ANODE_4));	// Clear digit enable bits
			LED_MUX = temp | (1<<anode);										// Set appropriate digit enable bit
		}
		
		else
		{
			LED_MUX &= 0xF0;
			LED_SEGMENTS = codedDataArray[anode];								// Enable digit segments
			temp = LED_MUX & ~((1<<ANODE_1)|(1<<ANODE_2)|(1<<ANODE_3)|(1<<ANODE_4));	// Clear digit enable bits
			LED_MUX = temp | (1<<anode);										// Set appropriate digit enable bit
		}
	}
	
	anode++;	
}


/***********************************************************************************
 * 
 * Function name: DecimalNumLookup(number)
 * 
 * Scope: local
 * 
 * Parameters:
 * 		number - must be in range: 0 <= number <= 9
 * 
 * Return:
 * 		uint8_t - active segments which create the corresponding decimal number 
 * from lookup table.
 * 
 * Description:
 * 		DecimalNumLookup will return the segment data corresponding to the decimal
 * number passed to the function.  A zero is returned for any data outside the 
 * valid range, which effectively turns off all 7 segments. 
 * 
 **********************************************************************************/
uint8_t DecimalNumLookup(uint8_t number)
{
	if(number < MAX_DECIMAL)
	{
		return num_map[number];
	}
	
	else
		return 0;
}


/***********************************************************************************
 * 
 * Function name: HexNumLookup(number)
 * 
 * Scope: local
 * 
 * Parameters:
 * 		number - must be in range: 0x00 <= number <= 0x0F
 * 
 * Return:
 * 		uint8_t - active segments which create the corresponding hexadecimal 
 * 			number from lookup table.
 * 
 * Description:
 * 		HexNumLookup will return the segment data corresponding to the hexadecimal
 * number passed to the function.  A zero is returned for any data outside the 
 * valid range, which effectively turns off all 7 segments. 
 * 
 **********************************************************************************/
uint8_t HexNumLookup(uint8_t number)
{
	if(number < MAX_HEXADECIMAL)
	{
		return num_map[number];
	}

	else
		return 0;
}


/***********************************************************************************
 * 
 * Function name: AlphaLookup(ascii)
 * 
 * Scope: local
 * 
 * Parameters:
 * 		ascii - ASCII-coded character (note: not all characters are supported)
 * 
 * Return:
 * 		uint8_t - active segments which create the corresponding alphanumeric 
 * 			character from lookup table.
 * 
 * Description:
 * 		AlphaLookup returns the segment data corresponding to the ASCII-coded
 * character passed to the function.  Only certain alphanumeric characters are 
 * supported due to the type of display.  A zero is returned for any unsupported
 * characters, which effectively turns off all 7 segments. 
 * 
 **********************************************************************************/
uint8_t AlphaLookup(char ascii)
{
	switch(ascii)
	{
		case '0': return num_map[0];
		case '1': return num_map[1];
		case '2': return num_map[2];
		case '3': return num_map[3];
		case '4': return num_map[4];
		case '5': return num_map[5];
		case '6': return num_map[6];
		case '7': return num_map[7];
		case '8': return num_map[8];
		case '9': return num_map[9];
		case 'A': return char_map[0];
		case 'b': return char_map[1];
		case 'C': return char_map[2];
		case 'd': return char_map[3];
		case 'E': return char_map[4];
		case 'F': return char_map[5];
		case 'g': return char_map[6];
		case 'h': return char_map[7];
		case 'i': return char_map[8];
		case 'J': return char_map[9];
		case 'L': return char_map[10];
		case 'n': return char_map[11];
		case 'o': return char_map[12];
		case 'P': return char_map[13];
		case 'q': return char_map[14];
		case 'r': return char_map[15];
		case 'S': return char_map[16];
		case 't': return char_map[17];
		case 'u': return char_map[18];
		case 'y': return char_map[19];
		case '_': return char_map[20];
		case '-': return char_map[21];
		case '.': return char_map[22];
		case ':': return char_map[23];
		case 167: return char_map[24];
		default: return 0;
	}
}


extern void DPOn(uint8_t anode)
{
	codedDataArray[anode] &= ~SEG_DP;
}


extern void DPOff(uint8_t anode)
{
	codedDataArray[anode] |= SEG_DP;
}

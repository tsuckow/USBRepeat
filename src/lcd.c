#include "lcd.h"

#include <plib.h>

#define delay(ms) (ms*1000 / 256)

void lcdCommand( uint8_t cmd );
void lcdWrite(uint8_t page, uint8_t column);

//! Local display bitmap for manipulating parts of pages
uint8_t display[8][128];

//
// Functions
//

void initLCD()
{
	//No commands for 40ms
	OpenTimer2( T2_PS_1_256 | T2_ON, delay( 40 ) );

	//Start Reset
	mPORTAClearBits( 1 << 3 );
	mPORTASetPinsDigitalOut( 1 << 3 );

	//Prep
	mPMPOpen(
		PMP_ON |
		PMP_TTL |
		PMP_READ_WRITE_EN |
		PMP_WRITE_POL_LO |
		PMP_READ_POL_LO,
		PMP_MODE_MASTER1 |
		PMP_WAIT_BEG_4 |
		PMP_WAIT_MID_15 |
		PMP_WAIT_END_4,
		PMP_PEN_0,
		PMP_INT_OFF
	);

	//Wake Up!
	while( !mT2GetIntFlag() );
	CloseTimer2();
	mT2ClearIntFlag();
	
	//End Reset
	mPORTASetBits( 1 << 3 );
	
	//No Commands for 39us
	OpenTimer2( T2_PS_1_256 | T2_ON, delay( 40 ) );
	//Wake Up!
	while( !mT2GetIntFlag() );
	CloseTimer2();
	mT2ClearIntFlag();
	
    lcdCommand(LCD_ON);

    //Best boot 5-1-05
    lcdCommand(0xA3); //LCD Bias (A2 A3) - First Choice
    lcdCommand(0x2F); //Turn on internal power control
    lcdCommand(0x26); //Pseudo-Contrast 7 = dark 6 = OK - First Choice

    lcdCommand(0x81); //Set contrast
    lcdCommand(40);//The Contrast (30 to 54 - Recommeneded)

    lcdCommand(0xC8); //Flip screen on the horizontal to match with the vertical software invertion
    
    lcdClear();    
}

//Writes byte to selected page
void lcdWrite(uint8_t page, uint8_t column)
{
   	// make sure column and page are within bounds
   	page %= 9;
   	column %= 128;
   	
	// set column  MSB
	lcdCommand(0x10 | ((127 - column) >> 4));
	// set column LSB
	lcdCommand(0x0F & (127 - column));
	
	// set page
	lcdCommand(0xB0 |(0x0F & (7-page)));
	
    //Data write
    PMPSetAddress(1); 
    PMPMasterWrite( display[page][column] ); //Reverse Vertical Axis
}

void lcdSetGlyph( uint8_t on, uint8_t column )
{
	// set column  MSB
	lcdCommand(0x10 | ((127 - column) >> 4));
	// set column LSB
	lcdCommand(0x0F & (127 - column));
	
	// set page
	lcdCommand(0xB0 | 8);
	
    //Data write
    PMPSetAddress(1); 
    PMPMasterWrite( on );
}

void lcdCommand( uint8_t cmd )
{
	PMPSetAddress(0);
	PMPMasterWrite( cmd );
}

void lcdClear()
{
	int p, c;
	for(p=0;p<8;++p)
    {
	    for(c=0;c<128;++c)
	    {
	    	display[p][c] = 0x00;
			lcdWrite(p,c);
		}
	}
	
	for(c=0;c<128;++c)
	{
		lcdSetGlyph(0x00,c);
	}	
}

lcdPaint( uint8_t top, uint8_t right, uint8_t bottom, uint8_t left )
{
	int p, c;
	for(p=top;p<bottom;++p)
    {
	    for(c=left;c<right;++c) 
		lcdWrite(p,c);
	}
}	

void lcdSetPixel( uint8_t val, uint8_t x, uint8_t y )
{
	uint8_t p = y/8;
	uint8_t value = display[p][x] & ~(0x01 << (7-y%8)) | ((val & 0x01) << (7-y%8));
	display[p][x] = value;
	lcdWrite(p,x);
}

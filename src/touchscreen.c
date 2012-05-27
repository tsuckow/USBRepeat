#include "touchscreen.h"

#include <plib.h>

#define SAMPLE_TIME 500

//TS1 G6
//TS2 B0
//TS3 B1
//TS4 G7

// To read touch screen x, drive TS1 high and TS3 low and read TS4 or TS2
// get touch screen x
//TS1(0);    // 0 is bit clear (High), 1 is set (Low), 2 is input
//TS2(2);
//TS3(1);
//TS4(2);
//adc_x = adc_TS2();
	
// vice versa for the y reading. (Except that this is inverted)
// get touch screen y
//TS1(2);
//TS2(1);
//TS3(2);
//TS4(0);
//adc_y = adc_TS3();

uint16_t tsX()
{
	//TS4 Float
	mPORTGSetPinsDigitalIn(1<<7);	
	//TS2 READ
	mPORTBSetPinsDigitalIn(1<<0);
	
	//TS1 HIGH
	mPORTGSetBits(1<<6);
	mPORTGSetPinsDigitalOut(1<<6);
	//TS3 LOW
	mPORTBClearBits(1<<1);
	mPORTBSetPinsDigitalOut(1<<1);
	
	//Do Read
	CloseADC10();
	OpenADC10(
		ADC_MODULE_ON | ADC_IDLE_CONTINUE | ADC_FORMAT_INTG | ADC_CLK_MANUAL |  ADC_AUTO_SAMPLING_OFF,
        ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_1 |  ADC_BUF_16,
        ADC_CONV_CLK_INTERNAL_RC,
        ENABLE_AN0_ANA,
        SKIP_SCAN_ALL
    );
    SetChanADC10(ADC_CH0_POS_SAMPLEA_AN0);

	mAD1ClearIntFlag();    
    AcquireADC10();
    int i;
	for(i=0;i<SAMPLE_TIME;++i);
	ConvertADC10();
		
	while ( ! mAD1GetIntFlag() ) {}
	// wait for the first conversion to complete so there will be vaild data in ADC result registers
        
	uint16_t value;
	value = ReadADC10(0);//Read Buffer
	
	return value;
}	

uint16_t tsY()
{
	//TS1 Float
	mPORTGSetPinsDigitalIn(1<<6);	
	//TS3 READ
	mPORTBSetPinsDigitalIn(1<<1);
	
	//TS4 LOW
	mPORTGClearBits(1<<7);
	mPORTGSetPinsDigitalOut(1<<7);
	//TS2 HIGH
	mPORTBSetBits(1<<0);
	mPORTBSetPinsDigitalOut(1<<0);
	
	//Do Read
	CloseADC10();
	OpenADC10(
		ADC_MODULE_ON | ADC_IDLE_CONTINUE | ADC_FORMAT_INTG | ADC_CLK_MANUAL |  ADC_AUTO_SAMPLING_OFF,
        ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_1 |  ADC_BUF_16,
        ADC_CONV_CLK_INTERNAL_RC,
        ENABLE_AN1_ANA,
        SKIP_SCAN_ALL
    );
    SetChanADC10(ADC_CH0_POS_SAMPLEA_AN1);

	mAD1ClearIntFlag();    
    AcquireADC10();
    int i;
	for(i=0;i<SAMPLE_TIME;++i);
	ConvertADC10();
		
	while ( ! mAD1GetIntFlag() ) {}
	// wait for the first conversion to complete so there will be vaild data in ADC result registers
        
	uint16_t value;
	value = ReadADC10(0);//Read Buffer
	
	return value;
}	

//
//Thermostat
//
//#include <p32xxxx.h>
#include <plib.h>
//#include "led.h"
#include "HardwareProfile.h"
#include "lcd.h"
#include "touchscreen.h"

#pragma config POSCMOD=XT, FNOSC=PRIPLL, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1
#pragma config FPBDIV = DIV_2, FWDTEN=OFF, CP=OFF, BWP=OFF
#pragma config UPLLEN   = ON   // USB PLL Enabled
#pragma config UPLLIDIV = DIV_2// USB PLL Input Divider

void drawCursor( int x, int y )
{
	int z;
	for(z=0;z<3;++z)
	{
		lcdSetPixel(1,x-1+z,y);
		lcdSetPixel(1,x,y-1+z);
	}
}	
volatile static unsigned int OneMSTimer;
int main()
{
	//Configure the system for 80MHz
	long const FREQ = 80000000L;
	SYSTEMConfig(FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE );
	
	initLCD(); //Shares LED and switch pins
        lcdClear();
//	initTS();
	

            AD1PCFG = 0xFFFF;

//	The USB specifications require that USB peripheral devices must never source
//	current onto the Vbus pin.  Additionally, USB peripherals should not source
//	current on D+ or D- when the host/hub is not actively powering the Vbus line.
//	When designing a self powered (as opposed to bus powered) USB peripheral
//	device, the firmware should make sure not to turn on the USB module and D+
//	or D- pull up resistor unless Vbus is actively powered.  Therefore, the
//	firmware needs some means to detect when Vbus is being powered by the host.
//	A 5V tolerant I/O pin can be connected to Vbus (through a resistor), and
// 	can be used to detect when Vbus is high (host actively powering), or low
//	(host is shut down or otherwise not supplying power).  The USB firmware
// 	can then periodically poll this I/O pin to know when it is okay to turn on
//	the USB module/D+/D- pull up resistor.  When designing a purely bus powered
//	peripheral device, it is not possible to source current on D+ or D- when the
//	host is not actively providing power on Vbus. Therefore, implementing this
//	bus sense feature is optional.  This firmware can be made to use this bus
//	sense feature by making sure "USE_USB_BUS_SENSE_IO" has been defined in the
//	HardwareProfile.h file.
    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif

//	If the host PC sends a GetStatus (device) request, the firmware must respond
//	and let the host know if the USB peripheral device is currently bus powered
//	or self powered.  See chapter 9 in the official USB specifications for details
//	regarding this request.  If the peripheral device is capable of being both
//	self and bus powered, it should not return a hard coded value for this request.
//	Instead, firmware should check if it is currently self or bus powered, and
//	respond accordingly.  If the hardware has been configured like demonstrated
//	on the PICDEM FS USB Demo Board, an I/O pin can be polled to determine the
//	currently selected power source.  On the PICDEM FS USB Demo Board, "RA2"
//	is used for	this purpose.  If using this feature, make sure "USE_SELF_POWER_SENSE_IO"
//	has been defined in HardwareProfile.h, and that an appropriate I/O pin has been mapped
//	to it in HardwareProfile.h.
    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;	// See HardwareProfile.h
    #endif

    // Let compile time pre-processor calculate the CORE_TICK_PERIOD
#define SYS_FREQ 				(80000000L)
#define TOGGLES_PER_SEC			1000
#define CORE_TICK_RATE	       (SYS_FREQ/2/TOGGLES_PER_SEC)
    // Decriments every 1 ms.

// Open up the core timer at our 1ms rate
	OpenCoreTimer(CORE_TICK_RATE);

    // set up the core timer interrupt with a prioirty of 2 and zero sub-priority
	mConfigIntCoreTimer((CT_INT_ON | CT_INT_PRIOR_2 | CT_INT_SUB_PRIOR_0));


    USBDeviceInit();

        USBDeviceAttach();
}

void __ISR(_CORE_TIMER_VECTOR, ipl2) CoreTimerHandler(void)
{
    // clear the interrupt flag
    mCTClearIntFlag();

    static int status = 1;
lcdSetGlyph(status++,LCD_GLYPH_CLOCK);

	if (OneMSTimer)
	{
            
		OneMSTimer--;
	}

    // update the period
    UpdateCoreTimer(CORE_TICK_RATE);
}
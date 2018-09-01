//*************************************************************
//************************************************************* 
// =====================================
// =====================================
void PortInit(void)
{
	PORTA=0B11110001;
	TRISA=0b00100011;
	PORTB=0B11010011;
	TRISB=0b00000001;
	PORTC=0B11111110;
	TRISC=0b10011100;
}

// =====================================
// =====================================
void initMcu(void)
{
	OSCCON=0x61; //4Mhz, internalOSC (0x71: is 8Mhz, Internal OSC)
	WdtPrescaler();
	PortInit();
	Tmr1Resetting();
	Tmr1Control_init();
	Tmr1On();
	initA2d(); // see also halA2d.h
}//End of initialize. Init_Async_(); Init_SSP_(); //subfunction head process.

// =====================================
// =====================================
void bShutdownPORT(void)
{
	PORTA=0B11110111;
	TRISA=0b00100011;
	PORTB=0B11010111;
	TRISB=0b00000001;
	PORTC=0B11000100;
	TRISC=0b10000100;
}

// =====================================
// =====================================
void aShutdownMCU(void)
{
	// Function shutdown
	TXREG = ')'; do{}while(!TRMT);
	TXREG = 0x0D; do{}while(!TRMT);
	TXREG = 0x0A; do{}while(!TRMT);
	DeassertTmr1INT();
	Tmr1Off();

	// Mcu shutdown
	bShutdownPORT();
	INTCON=0;

}//End of initialize. Init_Async_(); Init_SSP_(); //subfunction head process.

/*********************/
/* end of the file   */
/*********************/


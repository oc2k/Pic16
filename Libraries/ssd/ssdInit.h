//*************************************************************
//************************************************************* 

#ifndef _ssdInitial_H
#define _ssdInitial_H

//======================================
//(1) define constant parameter
//(2) file register defined
//(3) system flag
//======================================
// -sys- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//======================================
//(4) hardware defination
//======================================
// PLM#
//-- RA ---------------
//(1)RA0 -- A2D BATTERY MEASUREMENT
//(2)RA1 -- A2D REFERENCE VOLTAGE MEASUREMENT
//(3)RA2 -- IsHwDev1VCC
//(4)RA3 -- IsHwTestFREQ
//(5)RA4 -- IsHwDev2VCC
//(6)RA5 -- _IsHwDev1DR
//(7)RA6 -- NA
//(8)RA7 -- NA

//-- RB ---------------
//(1)RB0 -- *, INT INTERRUPT SERVICE
//(2)RB1 -- IsHwAntVCC, ANT Power control
//(3)RB2 -- IsHwAntRESET, ANT Reset control
//(4)RB3 -- IsHwPwrVCC, DC/DC control
//(5)RB4 -- IsHwUartSelUSB, UART TX selection
//(6)RB5 -- IsHwRefVoltASSERT, Reference voltage control
//(7)RB6 -- SPARE
//(8)RB7 -- SPARE

//-- RC ---------------
//(1)RC0 -- IsAntSuspendASSERTED, ANT SUSPEND CONTROL
//(2)RC1 -- IsAntSleepASSERTED, ANT SLEEP CONTROL
//(3)RC2 -- _IsHwAntRtsAGREE, ANT RTS
//(4)RC3 -- SCL (I2CM)
//(5)RC4 -- SDA (I2CM)
//(6)RC5 -- IsHwGsINT
//(7)RC6 -- TX (SCI)
//(8)RC7 -- RX (SCI)

//======================================
//(5) Macro defined
//======================================
#define aSsdSLEEP() \
	__SLEEP(); __NOP();

//======================================
//(6) Function defination
//======================================
	void PortInit(void);
	void initMcu(void);
	void bShutdownPORT(void);
	void aShutdownMCU(void);
//	void aSsdSLEEP(void);

//======================================
// (7) Initial Process
//======================================
//##############################################################################################
//System Timer, watchdogtimer, ... setting
//##############################################################################################

//------------------------------------------------------------------------
//(1)Scaler for watchdog | Option_REG: RBPU(0),INTEDG(0)INT--|__,T0CS(0)Internal,T0SE(0)T0CKI__|--
//                         Option_REG: PSA(1)ForWdt,PS[2..0]Scaler
enum WdtPre	{WdtPre1 = 0x8, WdtPre2 = 0x9, WdtPre4 = 0xA, WdtPre8 = 0xB, \
	         WdtPre16 = 0xC,WdtPre32 = 0xD, WdtPre64 = 0xE, WdtPre128 = 0xF};
#define WdtPrescaler() OPTION = WdtPre128;
#define WdtSleepPrescaler() OPTION = WdtPre8;
enum T0Pre	{T0Pre2 = 0x0, T0Pre4 = 0x1, T0Pre8 = 0x2, T0Pre16 = 0x3, \
	         T0Pre32 = 0x4,T0Pre64 = 0x5, T0Pre128 = 0x6, T0Pre256 = 0x7};
#define Tmr0Prescaler() OPTION = WDTPRE128;
//Pic16F88x Special for Wdt operation, But no time try
enum WdtPs	{WdtPs32  = 1,WdtPs64  = 3,WdtPs128 = 5,WdtPs256 = 9,\
	         WdtPs512 = 11,WdtPs1k  = 13,WdtPs2k  = 15,WdtPs4k  = 17,\
	         WdtPs8k  = 19,WdtPs16k = 21,WdtPs32k = 23,WdtPs64k = 25};
#define WdtControlReg()	WDTCON = WdtPs64k
//------------------------------------------------------------------------
//(2)MCU option setting
//enum TPRE	{PRE2 = 0x0, PRE4 = 0x1, PRE8 = 0x2, PRE16 = 0x3,\
//			 PRE32 = 0x4,PRE64 = 0x5, PRE128 = 0x6, PRE256 = 0x7};
//#define	PRE		4						// prescaler value 
//#define	RATE	1000	    			// .909 ms per loop (RATE=1/TMR0)
//#define	TMRDIVIDE	(FOSC/PRE/RATE/4)	// division ratio - must be < 256 [125]
//#define TMRoption_Init() (OPTION = PRE4) //(OPTION = PRE4, TMR0 = -TMRDIVIDE+5)
//#define TMRoption_() (TMR0 = -TMRDIVIDE+5)
/**/
static volatile unsigned int	TMR1HL	@ 0x0E;

#define	T1RATE	1000 //1000
enum Tmr1PrescaleOn	{T1PRE1 = 0x4, T1PRE2 = 0x14, T1PRE4 = 0x24, T1PRE8 = 0x34};
#define	T1Prescale	1						// prescaler value 
#define	Tmr1Divide	(UINT)(FOSC/4/T1Prescale/T1RATE)	// division ratio - must be < 256 [125]

// Tmr1 offset adjust in baseline
#define Tmr1Offset	0x20  // -- Measure main board LED frequence is 500Hz
// -- Done --
#define Tmr1Control_init() (T1CON = T1PRE1)//, TMR1L = -Tmr1Divide)
#define Tmr1Resetting() (TMR1HL = (UINT)(-Tmr1Divide+Tmr1Offset)) //Tmr1Unit=1Us
#define Tmr1On()	(TMR1ON=1)
#define Tmr1Off()	(TMR1ON=0)
#define AssertTmr1INT()			(TMR1IE=1, PEIE=1, GIE=1)
#define DeassertTmr1INT()		(TMR1IE=0, PEIE=0, GIE=1)

#endif // !_ssdInitial_H

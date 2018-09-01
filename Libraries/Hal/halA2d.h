//*************************************************************
//************************************************************* 

#ifndef _halA2d_H
#define _halA2d_H

//======================================
//(0) Macro DEBUGGING defined
//(1) define constant parameter
//(2) file register defined
//======================================
		UCHAR adSaveSecond;
	bank2	UCHAR adBatBuf[5];
		UCHAR adBatteryValue;

//======================================
//(3) system flag
//======================================
// -sys- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//======================================
//(4) hardware defination
//======================================
//------------------------------------------------
//-4.5- A2d control
//------------------------------------------------
//-->Reference voltage assert
#define IsHwRefVoltASSERT		(RB5)
#define _HwRefVoltDEASSERT()	(RB5=0)
#define _HwRefVoltASSERT()		(RB5=1)


// Pic16F886
// Define Macro Analog channel selection
// =====================================
//ADCON0 >> ADCS1(0) ADCS0(1)  CHS3  CHS2  CHS1 CHS0 GO/DONE ADON
//ADCON1 >> ADFM(0) - VCFG1(0) VCFG0(0) — — — —
// =====================================
// Marco defined
// =====================================
//#define ADC_CFG_NEG_REFERENCE_PIN -- COMMENT MEAN GND NEG REFERENCE VOLTAGE
//#define ADC_CFG_POS_REFERENCE_PIN -- COMMENT MEAN VCC POS REFERENCE VOLTAGE

// ------------------------------------
// DEFINE LEFT_ADJUSTIFY / RIGHT_ADJUSTIFY
//#define ADFM_RIGHT_ADJUSTIFY -- COMMENT MEAN AD RESULT LEFT ADJUSTIFY, MAXIMUM IS FFC0
#define ADFM_LEFT_ADJUSTIFY -- COMMENT MEAN AD RESULT LEFT ADJUSTIFY, MAXIMUM IS FFC0
// End of DEFINE
// ------------------------------------

// =====================================
// ADCON1 SETTING
// =====================================
// ADC result format
#if defined(ADFM_RIGHT_ADJUSTIFY)
	#define ADFM_Adjustify		(0x80) // AD RESULT MAX = (03FF)
#elif defined (ADFM_LEFT_ADJUSTIFY)
	#define ADFM_Adjustify		(0x00) // AD RESULT MAX = (FFC0)
#else // Is left adjustify
	#error "no define ADFM_Adjustify"
#endif // !ADFM_RIGHT_ADJUSTIFY

// ADC configuration of positive voltage reference
#if defined(ADC_CFG_NEG_REFERENCE_PIN)
	#define VCFG_NegRefPIN			(0x20)
#else
	#define VCFG_NegRefPIN			(0x00)
#endif // !ADC_NEG_REFERENCE_PIN
// ADC configuration of positive voltage reference
#if defined(ADC_POS_REFERENCE_PIN)
	#define VCFG_PosRefPIN			(0x10)
#else
	#define VCFG_PosRefPIN			(0x00)
#endif // !ADC_NEG_REFERENCE_PIN

// =====================================
// ADCON0 SETTING
// =====================================
#define ADCS_FoscDivBy2			(0x00)
#define ADCS_FoscDivBy8			(0x40)
#define ADCS_FoscDivBy32		(0x80)
#define ADCS_F_RC				(0xC0)
#define initA2d()\
	ANSEL  = 0B00000001;	/*0x01*/ \
	ANSELH = 0B00000000;	/*0x00*/ \
	ADCON0 = ADCS_FoscDivBy8;	/* FOSC/8, ####, 0, AdOff */ \
	ADCON1 = ADFM_Adjustify | VCFG_NegRefPIN | VCFG_PosRefPIN ;

// =====================================
//(1)AN0 --  0K2E Battery Measurement
//(2)AN1 --  0K2E Reference voltage Measurement
//(3)AN2 --  
//(4)AN3 --
//(5)AN4 --  
//(6)AN8 -- 
//(7)AN9 -- 
//(8)AN10 -- 
//(9)AN11 -- 
//(10)AN12 --
//(11)AN13 -- 
//-----------------
//FEDCBA98 76543210
//-----------------
// -Ad channel- // see above "initA2d" ADCON0 defined
//#define _selAN13()			ADCON0=ADCS_FoscDivBy8 | 0b00110101		// ##11 01## No need ad_On ()
//#define _selAN11() 			ADCON0=ADCS_FoscDivBy8 | 0b00101101		// ##10 11## No need ad_On ()
//#define _selAN10()			ADCON0=ADCS_FoscDivBy8 | 0b00101001		// ##10 10## No need ad_On ()
//#define _selAN8()			ADCON0=ADCS_FoscDivBy8 | 0b00100001		// ##10 00## No need ad_On ()
//#define _selAN4()			ADCON0=ADCS_FoscDivBy8 | 0b00010001		// ##01 00## No need ad_On ()
//#define _selAN3()			ADCON0=ADCS_FoscDivBy8 | 0b00001101		// ##00 11## No need ad_On ()
//#define _selAN2()			ADCON0=ADCS_FoscDivBy8 | 0b00001001		// ##00 10## No need ad_On ()
//#define _selAN1()			ADCON0=ADCS_FoscDivBy8 | 0b00000101		// ##00 01## No need ad_On ()
#define _selAN0()			ADCON0=ADCS_FoscDivBy8 | 0b00000001		// ##00 00## No need ad_On ()

// -Ad standard macro- //
#define ad_On()				ADON=1
#define ad_Off()			ADON=0
#define ad_Go()				ADGO=1 //GODONE=1;
#define ad_Done()			do{}while(ADGO); //(GODONE);

//======================================
//(5) Macro defined
//======================================
// sampler >> #define __isrAdtmrUsCountdown() if(adtmr) adtmr --;

//======================================
//(6) Function defination
//======================================

	void aHalA2d_BatVoltage(void);

#if defined (A2D_BAT_LEVEL_OFFICIAL_DATA)
	void bHalA2dBatREADING_asDebug(void);
#endif // !A2D_BAT_LEVEL_OFFICIAL_DATA


//======================================
// (7) Initial Process
//======================================
#endif // !_halA2d_H

//*************************************************************
//       Timing processing GUIDELINE
//*************************************************************
#ifndef _halA2d_H_isr
#define _halA2d_H_isr
#endif //!_halI2cm_H_isr

//************************************************************* 
// (2) Timing process in osSysClock, e.g.: #define SciSysclkTmr1() __clkSciPcMsgHmsCountdown();
//************************************************************* 
#ifndef _halA2d_H_sysClk
#define _halA2d_H_sysClk
#endif //!_halA2d_H_sysClk


//*************************************************************
//************************************************************* 

#ifndef osSkeleton_H
#define osSkeleton_H 

//======================================
//(1) define constant parameter
//(2) file register defined
//(3) system flag
//======================================
// -sys- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


//======================================
//(4) hardware defination
//======================================
//------------------------------------------------
// Module Power CONTROL
//------------------------------------------------
//--> Module Power control
#define IsHwModuleVCC		(!RB1) // REPLACE TO:IsHwAntVCC
#define _HwModuleVCCon()	(RB1=0) // REPLACE TO:_HwAntVCCon()
#define _HwModuleVCCoff()	(RB1=1) // REPLACE TO:_HwAntVCCoff()
//------------------------------------------------
//-4.1- Test Pin
//------------------------------------------------
//--> SPARE Pin as timer1 output check internal clock
#define IsHwTestFREQ		(RA3)
#define _HwHwTestFREQon()	(RA3=1)
#define _HwHwTestFREQoff()	(RA3=0)
#define __checkFreq() 	(IsHwTestFREQ)?(_HwHwTestFREQoff()):(_HwHwTestFREQon());
//--> DC/DC Power control
#define IsHwPwrVCC			(!RB3)
#define _HwPwrVCCon()		(RB3=1)
#define _HwPwrVCCoff()		(RB3=0)

//------------------------------------------------
//-4.2- DEV MODULE control
//------------------------------------------------

//------------------------------------------------
//-4.4- DEV1 MODULE control, REFER TO HalDEV1.h
//------------------------------------------------
//--> Data READY (from DEV1)
#define _IsHwDev1DR			(RA5)
//--> Wakeup DEV1 
#define IsHwDev1INT			(!RC5)
#define _HwDev1INTon()		(RC5=0)
#define _HwDev1INToff()		(RC5=1)

//------------------------------------------------
//-4.5- A2d control, REFER TO HalA2d.h
//------------------------------------------------
//>>shift to A2d.h>>Reference voltage assert 
//#define IsHwRefVoltASSERT		(RB5)
//#define _HwRefVoltDEASSERT()	(RB5=0)
//#define _HwRefVoltASSERT()		(RB5=1)

//------------------------------------------------
//-4.6- UART control, REFER TO HalSci.h
//------------------------------------------------
// --Uart selection IC control
//#define IsHwUartSelUSB			RB4 // High Link to Pc (Low Link to Ant)
//#define _HwUartSELusb()			RB4=1, __uartseltmr10MsSETTING(); // (default)
//#define _HwUartSELant()			RB4=0, __uartseltmr10MsSETTING();

//======================================
//(5) Macro defined
//======================================
#define __SciTraceNUMBER(Word8Char)\
	TXREG = Word8Char; do{}while(!TRMT); //__TraceNUMBER


//======================================
// (6) Function defination
// (7) Initial Process
//======================================
 

#endif // !osSkeleton_H

//*************************************************************
//       Timing processing GUIDELINE
//*************************************************************
#ifndef osSkeleton_H_isr
#define osSkeleton_H_isr
#endif //!osSkeleton_H_isr


#ifndef osSkeleton_H_sysClk
#define osSkeleton_H_sysClk
#endif //!osSkeleton_H_sysClk



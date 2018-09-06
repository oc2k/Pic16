//*************************************************************            
// halAnt.h
//************************************************************* 
#ifndef _halAnt_H
#define _halAnt_H

//======================================
//(1) define constant parameter
//======================================
// ==========================
// ANT SERIAL PORT TYPE: Async / Sync
// -- 3 SELECT 1 in below choices (according to ANT hardware)
// ==========================
#define SERIAL_UART_ASYNC
//#define SERIAL_BIT_SYNCHRONOUS 1      
//#define SERIAL_BYTE_SYNCHRONOUS

//======================================
//(2) file register defined
//(3) system flag
//======================================
// -sys- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// -sav- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// -ssd- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#if 0
#define ssdExitStartupBLK		ssd.cb.zer//xxx defined in halAnt.h
#define ssdExitStartupBLKon		ssdExitStartupBLK = 1 //Exit Main block
#define ssdExitStartupBLKoff	ssdExitStartupBLK = 0 //Exit Main block
#endif


//======================================
//(4) hardware defination
//======================================
// REFER TO: HalAntAsync.h (or HalAntSync.h)

//======================================
//(5) Macro defined
//======================================
// -- ANT Transaction --------
#if defined(SERIAL_UART_ASYNC) || defined (SERIAL_UART_ASYNC)
#define aHalAnt_Transaction()	aHalAntAsync_Transaction()
//#elif (SERIAL_BIT_SYNCHRONOUS) || (SERIAL_BYTE_SYNCHRONOUS)
//#define aHalAnt_Transaction()		aHalAntSync_Transaction()
#endif

// -- ANT Receive process --------
#if defined(SERIAL_UART_ASYNC) || defined (SERIAL_UART_ASYNC)
#define aHalAnt_ProcessByte() 	aHalAntAsync_ProcessByte()
//#elif (SERIAL_BIT_SYNCHRONOUS) || (SERIAL_BYTE_SYNCHRONOUS)
//#define aAntProcessByte() 	aAntSyncProcessByte()
#endif

#endif // !_halAnt_H

//======================================
//(6) Function defination
//======================================
	void init_HwAntSerial();

//*************************************************************
// Timing isr Processing GUIDELINE
//*************************************************************
#ifndef _halAnt_H_isr
#define _halAnt_H_isr
#endif
//************************************************************* 
// Timing process in osSysClock, e.g.: #define SciSysclkTmr1() __clkSciPcMsgHmsCountdown();
//************************************************************* 
#ifndef _halAnt_H_sysClk
#define _halAnt_H_sysClk
#endif


//*************************************************************
// halAntAsync.h
//************************************************************* 
#ifndef _halAntAsync_H
#define _halAntAsync_H

//======================================
//(1) define constant parameter
//(2) file register defined
//======================================
	UCHAR _antMs; // as share ANT ms countdown interrupt timer
	UCHAR antSleepHms; // sleep Hundred ms clock

//======================================
//(3) system flag
//======================================
// -fe- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#if 0 //define (sysFaultError)
#define feAntHiRtsChkERR		fe.cb.zer
#define feAntHiRtsChkERRon			feAntHiRtsChkERR = 1 // Ant Hardward checking done
#define feAntLoRtsChkERR		fe.cb.one
#define feAntLoRtsChkERRon			feAntLoRtsChkERR = 1 // Ant Hardward checking done
#endif

//======================================
//(4) hardware defination
//======================================
//--> ANT Reset control
#define IsHwAntRESET			(RB2) //In Old version
#define _HwAntResetASSERT()		(RB2=1)
#define _HwAntResetDEASSERT()	(RB2=0)
//--> ANT Suspend control
#define IsAntSuspendASSERTED		(!RC0) // OUTPUT
#define _HwAntSuspendASSERT()		(RC0=0) // Assert -- Initial
#define _HwAntSuspendDEASSERT()		(RC0=1) // (default) deassert
//--> ANT Sleep control
#define IsAntSleepDEASSERTED		(!RC1) // OUTPUT
#define _HwAntSleepASSERT()			(RC1=1) // Assert -- Initial
#define _HwAntSleepDEASSERT()		(RC1=0) // (default) deassert
// --> Ant RTS signal
#define _IsHwAntRtsAGREE		(!RC2) // INPUT, When ANT Rts Low mean: Host can transmit message to ANT

//======================================
//(5) Macro defined
//======================================
// -- _antHms --
#define IsAntSleepHMS					(antSleepHms != 0)
#define IsZeroAntSleepHMS				(antSleepHms == 0)
#define __clearAntSleepHMS()			(antSleepHms = 0)
#define __clkantSleepHmsCountdown()		if(antSleepHms ) antSleepHms--;
#define __antSleepHms8SETTING()			(antSleepHms = 8) // 800ms
// -- _antMs --
#define IsZeroOfAntMS					(_antMs == 0)
#define __isrAntMsCountdown()			if(_antMs) _antMs --;
#define __antMs100SETTING()			(_antMs = 100) // 100ms
// -- Uart Receiver --
#define __sciRxtmr_12MsSETTING()	     (rxtmr = 12)
#define __sciRxtmr_50MsSETTING()	     (rxtmr = 50)
#define __sciRxtmr_25MsSETTING()		 (rxtmr = 25)
//-> Receive ANT Message and Process
#define __isrMainUartAntRxBuf()\
	if(RCIF){ \
		__SetLBank(); \
		FSR=(UCHAR)&rcbuf.data[0]+rcbuf.cnt.value; \
		INDF=RCREG; \
		rcbuf.cnt.value++; if(rcbuf.cnt.cb.fiv) rcbuf.cnt.value--; \
		/**                                                        ^^^contraint value is "0b0010 0000" (32)*/ \
		__sciRxtmr_12MsSETTING(); /* Rxtmr timer extension */ \
		antProcWaitmrClear(); /* I got response, so clear response time*/ \
		RCIF=0; /* Clear Uart Receive flag */\
	} \

// -- Uart Transmitter --
// -- ANT+ Sleep / wakeup --

//======================================
//(6) Function defination
//======================================
	void init_HwAntAsync(void);
	void aHalAntAsync_Transaction(void);
	void aHalAntAsync_ProcessByte(void);
	void bHwAntSleepAssertRtsCHK();
	void bHwAntSleepDeassertRtsCHK();
	void bHalAntAsync_AntMesgCHECK(void);

#endif // !_halAntAsync_H

//*************************************************************
//  Timing isr Processing GUIDELINE
//*************************************************************
#ifndef _halAntAsync_H_isr
#define _halAntAsync_H_isr
	#define antAsyncIsrRxINT()		__isrMainUartAntRxBuf();
	#define antAsyncIsrMs()			__isrAntMsCountdown();
#endif
//************************************************************* 
// Timing process in osSysClock, e.g.: #define SciSysclkTmr1() __clkSciPcMsgHmsCountdown();
//************************************************************* 
#ifndef _halAntAsync_H_sysClk
#define _halAntAsync_H_sysClk
#endif


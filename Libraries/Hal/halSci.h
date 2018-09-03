//*************************************************************
//************************************************************* 

#ifndef _halSci_H
#define _halSci_H

//======================================
//(1) define constant parameter
//======================================
#define __constSciRxBufSizeLIMIT            32 //32
#define __constSciTxBufSizeLIMIT            80 //64
#define __constSwCodingSize                 10
#define __constSciOErrTmr                   10 //10 Seconds >>> Processing Uart Overrun Error
#define __constSciOErrResetTmr              5  //10 Seconds >>> Overrun Reset Uart Function 

//======================================
//(2) file register defined
//======================================
typedef  struct RcBufferStruct{
    CUN cnt;
    UCHAR data[__constSciRxBufSizeLIMIT];
}RCBUF;
    bank1 RCBUF rcbuf;
typedef  struct TxBufferStruct{
    UCHAR cnt;
    UCHAR size;
    UCHAR buffer[__constSciTxBufSizeLIMIT];
}TXBUF;
    bank2 TXBUF txBuf;
    UCHAR rxtmr;
    UCHAR sciStatusTmr, sciOErrTmr;
	UCHAR sciPcMsgHms; 
	UCHAR uartseltmr;

//======================================
//(3) system flag
//======================================
// -sys- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// -- "sysPCMsgDONE" superseded by "sysAntMsgEVT"
//======================================
//(4) hardware defination
//======================================
// --Uart selection IC control
#define IsHwUartSelUSB			RB4 // High Link to Pc (Low Link to Ant)
#define _HwUartSELusb()			RB4=1, __uartseltmr10MsSETTING(); // (default)
#define _HwUartSELant()			RB4=0, __uartseltmr10MsSETTING();
// --Toggle switch timing
#define IsUartSelecting					(uartseltmr != 0)
#define __isrUartseltmrMsCountdown()	if(uartseltmr) uartseltmr --;
#define __uartseltmr10MsSETTING()		(uartseltmr = 10) // 10 ms as trigger timer

//======================================
//(5) Macro defined
//======================================
// -- Uart Receiver --
#define IsEmptyOfRxBuf                   (rcbuf.cnt.value == 0)
#define __emptyUartRcBuf()               (rcbuf.cnt.value = 0)
//-->
#define IsZeroOfRxtmr                    (rxtmr == 0)
#define __isrRxtmrMsCountdown()          if(rxtmr) rxtmr --;
//-->
#define IsZeroOfOErrTmr                  (sciOErrTmr == 0)
#define __clkSciErrTmrSecCountdown()     if(sciOErrTmr) sciOErrTmr--;
#define __sciRxtmr_N_MsSETTING()	     (rxtmr = 12)
//-->
#define __isrMainUartStandardProcess()\
	if(RCIF){ \
		__SetLBank(); \
		FSR=(UCHAR)&rcbuf.data[0]+rcbuf.cnt.value; \
		INDF=RCREG; \
		rcbuf.cnt.value++; if(rcbuf.cnt.cb.fiv) rcbuf.cnt.value--; \
		/**                                                        ^^^contraint value is "0b0010 0000" (32)*/ \
		__sciRxtmr_N_MsSETTING(); /* Rxtmr timer extension */ \
		RCIF=0; /* Clear Uart Receive flag */\
	} \

// -- Uart Transmitter --
#define IsEmptyOfTxBuf                   (txBuf.size == 0)
#define __uartTransferDone()             (txBuf.cnt = txBuf.size = 0) 

// -- "sciPcMsgHmsTmr" //PC Message TIMER control
#define IsZeroOfPcMsgHMS				(sciPcMsgHms == 0) // Pc MSG HMS TIMEOUT
#define __clkSciPcMsgHmsCountdown()		if(sciPcMsgHms) sciPcMsgHms --;
#define __sciPcMsgHms5SETTING()		(sciPcMsgHms = 5) //uart timing call, To send Uart message per 0.5second

//======================================
//(6) Function defination
//======================================
    void aHalSci_SentDataToUart();
    void aHalSci_ClearOErr(); 

//======================================
// (7) Initial Process
//======================================
#define BAUD                9600
#define UART_ADJUST_UNIT    -1 // SELECT={-4,*-3,*-2,-1,0,1,2,3,4}

//--> Below 2 select 1
#define     NINE_FALSE        // (Default) Use 8bit communication
//#define     NINE_TRUE        // Use 9bit communication 

//--> Below 2 select 1
#define HIGH_SPEED_TRUE        //(default) SPBRG & SPBRG16 calculation for baudrate
//#define HIGH_SPEED_FALSE     // SPBRG&SPBRG16 calculation 

//--> Below 2 select 1
#define BRG16_TRUE            //(default) SPBRG&SPBRG16 calculation 
//#define BRG16_FALSE         // SPBRG&SPBRG16 calculation 

// -----------------------------------------
// NINE_BIT communication selection, 2 select 1
// -----------------------------------------
// -->
#if    defined(NINE_FALSE)
    #define NINE_BITS             (0x00)        // (Default) When "NINE_FALSE"
//#elif (NINE_TRUE)
//    #define NINE_BITS           (0x40)        // When "NINE_TRUE"
#endif 

// -----------------------------------------
// Baudrate Calculation
// -----------------------------------------
#if defined (HIGH_SPEED_TRUE) && defined (BRG16_TRUE)
    #define SPEED                 (0x04)
    #define BRG16Setting()        (BRG16=1)
    #define DIVIDER16 \
           ((UINT)(FOSC/(4UL * BAUD)-1+UART_ADJUST_UNIT))
    #define DIVIDER16HighByte \
           ((UCHAR)(DIVIDER16 >> 8))
    #define DIVIDER16LowByte  \
           ((UCHAR)(DIVIDER16 & 0x00FF))


//#elif define (HIGH_SPEED_FALSE) && (BRG16_FALSE)
//    #define SPEED = (0x00)
//    #define BRG16Setting()    (BRG16=0)
//    #define DIVIDER16       \
//         ((UINT)(FOSC/(16UL * BAUD)-1+UART_ADJUST_UNIT))
//    #define DIVIDER16HighByte    ((UCHAR)(DIVIDER16 >> 8))
//    #define DIVIDER16LowByte     ((UCHAR)(DIVIDER16 & 0x00FF))


//#elif define (HIGH_SPEED_TRUE) && (BRG16_FALSE)
//    #define SPEED = (0x04)
//    #define BRG16Setting()    (BRG16=0)
//    #define DIVIDER16       \
//          ((UINT)(FOSC/(16UL * BAUD)-1+UART_ADJUST_UNIT))
//    #define DIVIDER16HighByte    ((UCHAR)(DIVIDER16 >> 8))
//    #define DIVIDER16LowByte     ((UCHAR)(DIVIDER16 & 0x00FF)) 


//#elif define (HIGH_SPEED_FALSE) && (BRG16_TRUE)
//    #define SPEED = (0x00)
//    #define BRG16Setting()    (BRG16=1)
//    #define DIVIDER16       \
//         ((UINT)(FOSC/(64UL * BAUD)-1+UART_ADJUST_UNIT))
//    #define DIVIDER16HighByte    ((UCHAR)(DIVIDER16 >> 8))
//    #define DIVIDER16LowByte    ((UCHAR)(DIVIDER16 & 0x00FF)) 


#endif 



#define initE16Uart() \
    /* __NOP(); /**/ \
    BRG16Setting(); \
    TXSTA = (SPEED | NINE_BITS);\
    /* __NOP(); /**/ \
    RCSTA = (NINE_BITS|0x80); /* 0x80 Mean: SPEN=1 */\
    /* __NOP(); /**/ \
    SPBRG = DIVIDER16LowByte; /* Adjust with "UART_ADJUST_UNIT" */ \
    /* __NOP(); /**/ \
    SPBRGH = DIVIDER16HighByte; \
    /* __NOP(); /**/ \
    TXEN=0; CREN=0; \
    /* __NOP(); /**/ \



#define enableE16Uart() \
    TXEN=1; CREN=1; RCIE=1; // SPEN = 1;

#define disableE16Uart() \
    TXEN=0; CREN=0; RCIE=0; // SPEN = 0;

#endif // !_halSci_H 

//*************************************************************
//       Timing Processing GUIDELINE
//*************************************************************
#ifndef _halSci_H_isr
#define _halSci_H_isr
	#define sciIsrRxINT()	__isrMainUartStandardProcess();
#endif //!_halSci_H_isr
//************************************************************* 
// (2) Timing process in osSysClock, e.g.: #define SciSysclkTmr1() __clkSciPcMsgHmsCountdown();
//************************************************************* 
#ifndef _halSci_H_sysClk
#define _halSci_H_sysClk
	#define SciSysclkHms1() __clkSciPcMsgHmsCountdown(); //In Hms
	#define SciSysclkSec1() __clkSciErrTmrSecCountdown(); // In Sec

#endif //!_halSci_H_sysClk


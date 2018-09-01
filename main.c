//*************************************************************
//************************************************************* 
// --------------
// Base Head
// --------------
#include "./libraries/os/osConstantesDefs.h"
#include "./ht-pic/include/oc2k.h"
#include "./ht-pic/include/pic16f88x.h"
#include "./libraries/os/osPublic.h"
#include "./libraries/os/osSkeleton.h"

// --------------
// System Header
// --------------
#include "./libraries/ssd/ssdInit.h"
#include "./libraries/per/perPicee.h"
#include "./libraries/hal/halA2d.h"
#include "./libraries/hal/halSci.h"

// --------------
// Driver Header
// --------------

// --------------
// Interface Header
// --------------
#include "./libraries/if/sciINTERFACE.h"

// --------------
// Internal clock Header File
// --------------
#include "./libraries/os/osSysClock.h"

// --------------
// System Implement File
// --------------
#include "./libraries/os/osTools.c"
#include "./libraries/os/osSkeleton.c"
#include "./libraries/ssd/ssdInit.c"
#include "./libraries/per/perPicee.c"
#include "./libraries/hal/halSci.c"
#include "./libraries/hal/halA2d.c"

// --------------
// Driver Implement File
// --------------

// --------------
// Interface Implement File
// --------------
#include "./libraries/if/sciINTERFACE.c"

// --------------
// ANT+ Application Implement File
// --------------

// --------------
// System clock File
// --------------
#include "./libraries/os/osSysClock.c"

// =====================================
void main()
{

	/*********************************************************************/
	//	Initial block : Port, A2d, Uart, ...
	/*********************************************************************/
	//Mcu Register initial
	initMcu();
	initE16Uart();
	enableE16Uart();
	initNoticeSwVersionToUart();

	// Parameter of PIC EEPROM loading
	initPerPicEe_LoadingPara();

	// Library initial

	//(Last)Enable interrupt
	TMR1IE=1; PEIE=1; INTE=0; GIE=1;

	/*********************************************************************/
	//	Block I : To read device parameters (or ParaM & ParaC)
	//	.. 
	//	.. To turn off DeviceVCC ( and To assert ANT RESET Pin )
	//	.. To turn on DeviceVCC ( and To deassert ANT RESET Pin)
	//	.. 
	/*********************************************************************/
	do{

		__CLRWDT();

		// --------------------------
		// (A) Hal Base Functions
		// --------------------------
		// (1) Sci
		aHalSci_SentDataToUart();
		aHalSci_ClearOErr(); // when no use Uart receive function, can consider to comment the line

		// --------------------------
		// (B)Interface Functions
		// --------------------------
		// (1) sci interface to PC as debugging software
		__NOP();

		// --------------------------
		// (C)Application Functions
		// --------------------------
		// --------------------------
		// (D)System internal clock
		// --------------------------
		aHalSystemClock();
		
		// --------------------------
		// (E) Exit process
		// --------------------------
	}while(1);

}

// =====================================
// =====================================
static UCHAR isrSaveFSR;
static void interrupt isr(void) 
{
  //-0-> isr PROTECT  //-1-> watch dog
	isrSaveFSR = FSR;

//----------------------------------------------------------------
	if(TMR1IF){		// 1 Ms timer overflow

		Tmr1Resetting();
		__isrRxtmrMsCountdown();
		__isrUartseltmrMsCountdown();

#if defined (CLKFREQ_DEBUGGING_PROCESSING)
		__NOP();
		__checkFreq();
#endif //!CLKFREQ_DEBUGGING_PROCESSING

		if(++isrMs > 99)
		{
			isrMs = 0;
			//Per 100ms
			isrHms ++;
		}

		// ----
		// Exit
		// ----
		TMR1IF = 0;

	}
	/* END OF INTERRUPT CODE */

	FSR = isrSaveFSR;

}

/*********************/
/* end of the file   */
/*********************/


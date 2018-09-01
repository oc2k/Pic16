//*************************************************************

//************************************************************* 

#ifndef _osSysClock_H
#define _osSysClock_H

//======================================
//(1) define constant parameter
//(2) file register defined
//======================================
	UCHAR savMs, savExtHmsecond;
	CUN	hmSecond; //Per Hundred millimsecond >>>remove>>mSecond
	CUN oSecond,oMinute; //oneSecond, oneMinute
	//UCHAR shutdownTmr; //Reset: anyKey Press, Countdown: every second
//======================================
//(3) system flag
//======================================
// -sys- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//======================================
//(4) hardware defination
//(5) Macro defined
//(6) Function defination
	void aHalSystemClock();

// (7) Initial Process
//======================================
 

#endif // !osSysClock_H


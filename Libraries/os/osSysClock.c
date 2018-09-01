//*************************************************************

//************************************************************* 

// =====================================
// =====================================
void aHalSystemClock()
{
	while(isrMs == savMs) __NOP(); // __SLEEP();
	savMs = isrMs;
	if(savExtHmsecond == isrHms) 
return;

	savExtHmsecond = isrHms;
	//////////////////////////////////////////////////
	//Per 100millisecond (Ms)                       //
	//////////////////////////////////////////////////
	__clkSciPcMsgHmsCountdown();

	if(++hmSecond.value > 9){
		hmSecond.value = 0;

		//////////////////////////////////////////
		//Per 1 Second (Sec)                    //
		//////////////////////////////////////////
		__clkSciErrTmrSecCountdown();
		
		if( ++oSecond.value >59){
			oSecond.value=0;

			//////////////////////////////////
			//Per 1 minute (Mnt)            //
			//////////////////////////////////

			if(++oMinute.value >59){
				oMinute.value=0;

				//////////////////////
				//Per 1 Hour (Hr)   //
				//////////////////////

			}
		}
	}
}

/*********************/
/* end of the file   */
/*********************/


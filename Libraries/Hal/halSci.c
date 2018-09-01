//*************************************************************
//************************************************************* 
// =====================================
// =====================================
void aHalSci_SentDataToUart()
{
	// -----------------------------
	// Base condition
	// -----------------------------
	if(IsUartSelecting) return; // When Uart selection IC working, wait for it
	if(IsEmptyOfTxBuf) // Is Empty of Tx's buffer, exit
return;

	__SetHBank();
	FSR = (UCHAR)&txBuf.buffer[0];
	FSR += txBuf.cnt;
	TXREG = INDF; do{}while(!TRMT);
	__SetLBank();
	if(++txBuf.cnt >= txBuf.size) goto _sciSendingDone;
return;

_sciSendingDone:
	__uartTransferDone();
}

// =====================================
void aHalSci_ClearOErr()
{
	// -----------------------------------------------------------
	// condition 1: (IsZeroOfOErrTmr)--> Check OERR
	// -----------------------------------------------------------
	if(IsZeroOfOErrTmr){
		if(!OERR)
			return; //The Uart Status is normal

		// Detect "Overrun" issue, Disable the Uart and set alarm timer
		disableE16Uart();
		sciOErrTmr = __constSciOErrTmr;
	}

	// -----------------------------------------------------------
	// condition 2: (sciOErrTmr > __constSciOErrResetTmr) --> Period of Disable Uart
	// -----------------------------------------------------------
	else if(sciOErrTmr > __constSciOErrResetTmr){
		__NOP(); // waiting for alarm timer
	}
	
	// -----------------------------------------------------------
	// condition 3: (otherwise)--> Enable Uart
	// -----------------------------------------------------------
	else{
		initE16Uart();
		sciOErrTmr = 0;
		enableE16Uart(); // To be reset the UART -- second step: TURN ON
	}

}


/*********************/
/* end of the file   */
/*********************/

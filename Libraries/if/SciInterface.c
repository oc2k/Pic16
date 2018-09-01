//*************************************************************
//************************************************************* 
// =====================================
// =====================================
void initNoticeSwVersionToUart()
{
	// --------------------------------------
	// Rev1001_ (0d0a)
	// --------------------------------------
	__SetHBank();
	FSR = (UCHAR)&txBuf.buffer[0]; INDF = 'R'; //[0]
	FSR++; INDF = 'e'; //[1]
	FSR++; INDF = 'v'; //[2]
	FSR++; INDF = '1'; //[3]
	FSR++; INDF = '0'; //[4]
	FSR++; INDF = '0'; //[5]
	FSR++; INDF = '1'; //[6]
	FSR++; INDF = VersionNo; //[7]
	FSR++; INDF = 0xD; //[8]
	FSR++; INDF = 0xA; //[9]
	txBuf.size = __constSwCodingSize;

	_HwUartSELusb(); // Uart select USB for software coding

}


// ##################################################################
// ##   OPTIONAL CODE  ###################################################
// ##################################################################

#if defined (UART_DEBUGGING_PROCESSING)

// =====================================
// =====================================
void aIfSci_DebuggingUART()
{
	// -----------------------------
	// Extra condition
	// -----------------------------
	if(IsUartSelecting) return; // When Uart selection IC working, wait for it

	// -----------------------------
	// Base condition
	// -----------------------------
	if(!IsZeroOfPcMsgHMS) return; // Base condition1
	if(!IsEmptyOfTxBuf) // Base condition2: the txbuf isnotEmpty, mean PrevMessage no clean, don't process
return;

	__sciPcMsgHms5SETTING(); // Set alarm timer for next Pc message
	// test UART with "oSecond": >HTO
	__UWord8ToHTO(oSecond.value);
	__SetHBank();
	FSR = (UCHAR)&txBuf.buffer[0]; INDF = '>'; // [0]
	FSR ++; INDF = sub_j+'0'; // [1]
	FSR ++; INDF = sub_i+'0'; // [2]
	txBuf.size = 5; // [0d][0a]

	FSR ++; INDF = 0xD; // [3]
	FSR ++; INDF = 0xA; // [4]

	_HwUartSELusb(); // Uart Tx selection IC

}
/* END OF UART INTERFACE FUNCTION */

#endif //!UART_DEBUGGING_PROCESSING

/*********************/
/* end of the file   */
/*********************/

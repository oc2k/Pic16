//*************************************************************
// halAnt.c
//************************************************************* 

// =====================================
// =====================================
void init_HwAntSerial()
{
#if defined(SERIAL_UART_ASYNC) || defined (SERIAL_UART_ASYNC)

		init_HwAntAsync();

#elif defined(SERIAL_BIT_SYNCHRONOUS) || defined(SERIAL_BYTE_SYNCHRONOUS)
#error
		init_HwAntSync();

#endif

	// -------------------------------------------
	// The Ant Message initialization
	// -------------------------------------------
	// (1) Clear stmAnt and to set UartMsgDONEon for listen ANT have other message
	// (2) Clear AntMsgProcess's Process Message ID
	// (3) Init AntMsgResponse's Event code
	// -------------------------------------------
	#if defined (antDEVn)
	//
		__tool_ClearCurrentAntCMD();
		antMsgPROC.RdyMsgID = MESG_CLEAN_ID;
	// antTxbuf clear
		antTxBufClear();
	//
	#endif

}
/*eof*/

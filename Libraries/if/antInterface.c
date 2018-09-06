//*************************************************************
// antInterface.c
//************************************************************* 

// =====================================
// ===================================== 
void aAntIf_Transaction()
{
	// -----------------------------
	// Key flag
	// ----------------------------- 
	if(!IsStmAntMSG)//It's not state machine of "AntMSG", exit
return;

	// -----------------------------
	// Base condition
	// ----------------------------- 
#if defined (TRACE_NUMBER_PROCESS)
	__SciTraceNUMBER('2');//	TXREG = '2'; do{}while(!TRMT); // __TraceNUMBER
#endif // !TRACE_NUMBER_PROCESS
	
	// -----------------------
	// Detect RTC signal
	// (1) ANT sleep deassert
	// (2) EvtCode: INITIAL
	// (3) Set stmAnt to READY
	// -----------------------
	antMsgPROC.EvtCode = EVENT_RESPONSE_INITIAL_E5; //Initial response event code
	stmAntRDYon(); // Message ready, to pass to HAL layer processing
}

// =====================================
// ===================================== 
void aAntIf_ProcessByte()
{
	// -----------------------------
	// Key flag
	// ----------------------------- 
	if(!IsStmAntRX) //It's not state machine of "AntRX", exit
return;

	// -----------------------------
	// Base condition
	// ----------------------------- 
#if defined (TRACE_NUMBER_PROCESS)
		__SciTraceNUMBER('5');
#endif // !TRACE_NUMBER_PROCESS

	// -----------------------------
	// Core code
	// ----------------------------- 
	// ===============
	// To process the ANT RECEIVED MESSAGES
	// ===============
	// e.g. RESPONSE, STARTUP MESSAGE, etc.
	// THE ANS PROJECT NO PROCESSING

	__NOP();

	// ===============
	// To set STATE MACHINE
	// ===============
	stmAntRepTXon(); // change state machine to "Report TxBuf"

}

// =====================================
// ===================================== 
void aAntIf_ReportTx()
{
	// -----------------------------
	// Key flag
	// ----------------------------- 
	if(!IsStmAntRepTX)  //It's not state machine of "AntRepTX", exit
return;

	// -----------------------------
	// Base condition
	// ----------------------------- 
	if(!IsEmptyOfTxBuf) // When txbuf no clean, waiting ..
return;

// ### DEBUGGING CODE #####################
#if defined (ANTPLUS_DEBUGGING_CODE)

	// -----------------------------
	// Core code
	// ----------------------------- 
	// CHANGE ANT TO SLEEP
	bHwAntSleepAssertRtsCHK();
	_HwUartSELusb(); // CHANGE UART for PC

	// Uart report "antTxBuf"
	__SetHBank(); FSR = (UCHAR)&txBuf.buffer[0]; INDF = 'T'; // [0]
	FSR ++; INDF = 'x'; // [1]
	FSR ++; INDF = '>'; // [2]
	FSR ++; INDF = '>'; // [3]
	txBuf.size = __constUartReportBaseSIZE;

	// [empty antTxBuf] T>: NIL(0d0a)
	if(IsEmptyOfAntTxBUF){
		FSR ++; INDF = 'N'; // [4]
		FSR ++; INDF = 'I'; // [5]
		FSR ++; INDF = 'L'; // [6]
		FSR ++; INDF = 0xD; // [7]
		FSR ++; INDF = 0xA; // [8]
		txBuf.size += __constUartReportNilAddSIZE;
	}

	// [Send antTxBuf] T>: A4,LEN,ID,D0,D1,D2,D3,D4,D5,D6,D7,D8,CS(0d0a)
	// -------------- 1     2    3    4   5   6    7   8   9   10 11 12  13  14-- Size = 14x3+1=43
	else{

		// Push Sync byte into tx's buffer
		//FSR ++; INDF = 'A'; // [4]
		//FSR ++; INDF = '4'; // [5]
		//FSR ++; INDF = ','; // [6]
		__HiHalfByteConvertAscii(MESG_TX_SYNC);// [4]
		__SetHBank(); FSR++; INDF = sub_i;
		__LoHalfByteConvertAscii(MESG_TX_SYNC); // [5]
		__SetHBank(); FSR++; INDF = sub_i;
		FSR ++; INDF = ','; // [6]

		txBuf.size += __constUartReportTxSyncAddSIZE;

		// Convert AntMessge to Ascii and save into tx's buffer
		sysFsrHiBANKon;
		__Tools_convertBufAndSendToPC \
					((antTxBuf.LEN+MESG_SAVED_FRAME_SIZE+MESG_CHECKSUM_SIZE),\
					 (UCHAR)&antTxBuf.LEN,\
					 (UCHAR)&txBuf.buffer[7]);

		// Clear AntTxbuf data length
		antTxBufClear();

	}
/****************************************************/

#endif // !ANTPLUS_DEBUGGING_CODE

#if defined (TRACE_NUMBER_PROCESS)
		 __SciTraceNUMBER('6');
#endif // !TRACE_NUMBER_PROCESS

	// shift to report antRxBuf
	stmAntRepRXon();

}

// =====================================
// ===================================== 
void aAntIf_ReportRx()
{
	// -----------------------------
	// Key flag
	// ----------------------------- 
	if(!IsStmAntRepRX)  //It's not state machine of "AntRepRX", exit
return;

	// -----------------------------
	// Base condition
	// ----------------------------- 
	if(!IsEmptyOfTxBuf) // When txbuf no clean, waiting ..
return;

// ### DEBUGGING CODE #####################
#if defined (ANTPLUS_DEBUGGING_CODE)

#if defined (TRACE_NUMBER_PROCESS)
			 __SciTraceNUMBER('7');
#endif // !TRACE_NUMBER_PROCESS
	// -----------------------------
	// Uart report "rcBuf"
	// ----------------------------- 
	if(!IsEmptyOfRxBuf){
		__SetHBank(); FSR = (UCHAR)&txBuf.buffer[0]; INDF = 'R'; // [0]
		FSR ++; INDF = 'x'; // [1]
		FSR ++; INDF = '<'; // [2]
		FSR ++; INDF = '<'; // [3]
		txBuf.size = __constUartReportBaseSIZE;

		// Turn off Interrupte
		GIE=0;

		// Load rcbuf's data convert to Ascii and send to PC
		 __Tools_convertBufAndSendToPC \
					(rcbuf.cnt.value,\
					 (UCHAR)&rcbuf.data[0],\
					 (UCHAR)&txBuf.buffer[4]);
		
		// To empty the uart Rc's buffer
		__emptyUartRcBuf();

		// Turn on interrupte
		GIE=1;

	}

#endif // !ANTPLUS_DEBUGGING_CODE

	// shift to report Event
	stmAntRepEVTon();

}

// =====================================
// ===================================== 
void aAntIf_ReportEvent()
{
	// -----------------------------
	// Key flag
	// ----------------------------- 
	if(!IsStmAntRepEVT)  //It's not state machine of "AntRepEVT", exit
return;

	// -----------------------------
	// Base condition
	// ----------------------------- 
	if(!IsEmptyOfTxBuf) // When txbuf no clean, waiting ..
return;

// ### DEBUGGING CODE #####################
#if defined (ANTPLUS_DEBUGGING_CODE)

	#if defined (TRACE_NUMBER_PROCESS)
		 __SciTraceNUMBER('8');
	#endif // !TRACE_NUMBER_PROCESS
	// -----------------------------
	// Uart report "antMsgRESP"
	// ----------------------------- 
	// EVT:ProcMsgID, RdyMsgID, waitHms, respID, EvtCode, (0d0a)(0d0a)
	//   4     4         4              4       4           4             4    Size=4x7=28
	// EVT: 
	__SetHBank(); FSR = (UCHAR)&txBuf.buffer[0]; INDF = 'E'; // [0]
	FSR ++; INDF = 'V'; // [1]
	FSR ++; INDF = 'T'; // [2]
	FSR ++; INDF = ','; // [3]
	txBuf.size = __constUartReportBaseSIZE;

	// Load antMsgProc's data convert to Ascii and send to PC
	 __Tools_convertBufAndSendToPC \
					(__constAntMsgProcDataSIZE,\
				 (UCHAR)&antMsgPROC.ProcMsgID,\
				 (UCHAR)&txBuf.buffer[4]);

	// Extra (0d0a) as paragraph
	FSR ++; INDF = 0xD; // [a1]
	FSR ++; INDF = 0xA; // [a2]
	
	txBuf.size += __constUartReportExtraOdoaSIZE;

#endif // !ANTPLUS_DEBUGGING_CODE

	// -------------------------------------------
	// The Ant Message communication have done
	// -------------------------------------------
	// The Ant Message communication have done
	// (1) Clear stmAnt and to set UartMsgDONEon for listen ANT have other message
	// (2) Clear AntMsgProcess's Process Message ID
	// (3) Init AntMsgResponse's Event code
	// -------------------------------------------

	// Check ANT channel status
	//if(antMsgPROC.ProcMsgID == MESG_OPEN_CHANNEL_ID)
	//	sysAntChOPENon;
	//if(antMsgPROC.ProcMsgID == MESG_CLOSE_CHANNEL_ID) // double conform
	//	sysAntChOPENoff;

	// Clean ANT command ID
	__tool_ClearCurrentAntCMD();

	//  ANT SLEEP 800ms
	__antSleepHms8SETTING();

	// When EMPTY of ANT+ READY COMMAND, SEND UART MESSAGE
	if(IsEmptyOfAntRdyMsg){
		sysAntUartMsgEVTon; // Set to Event call for Pc Message
	}

}


// =====================================
// ===================================== 
void aAntIf_AntListenRTS()
{
	// -----------------------------
	// Key flag
	// ----------------------------- 
	if(IsAntSleepHMS) // Ant sleep, exit
return;
	
	// -----------------------------
	// Base condition
	// ----------------------------- 
	if(IsStmAnt) return; // stmAnt noZero, exit
	if(!sysAntChOpenDONE) // Ant channel has not opened, exit
return;

#if defined (TRACE_NUMBER_PROCESS)
			 __SciTraceNUMBER('9');
#endif // !TRACE_NUMBER_PROCESS

	stmAntLISTENon();
	antMsgPROC.RespID = MESG_RESPONSE_EVENT_ID;

}

// =====================================
// ===================================== 
void aAntIf_AntWAKEUP()
{
	// -----------------------------
	// Key flag
	// ----------------------------- 
	if(!IsStmAntLISTEN) // no Ant sleep, exit
return;
	
	// -----------------------------
	// Base condition
	// ----------------------------- 
	if(IsAntSleepDEASSERTED) return; // ANT is SLEEP Deassert (i.e.: SLEEP low), exit
	if(_IsHwAntRtsAGREE) // no Detect ANT RTS Low (i.e.: RTS high), exit
return;

	// To wake up ANT
	bHwAntSleepDeassertRtsCHK(); // Ant sleep deassert, block to call the function again
	__sciRxtmr_50MsSETTING();

#if defined (TRACE_NUMBER_PROCESS)
			 __SciTraceNUMBER('0');
#endif // !TRACE_NUMBER_PROCESS


}

// =====================================
// ===================================== 
void aAntIf_ExecuteAntCOMMAND()
{
	// -----------------------------
	// Key flag
	// ----------------------------- 
	if(!IsNotEmptyOfAntRdyMsg)  // Ant Ready Message space EMPTY, exit
return;

	// -----------------------------
	// Base condition
	// -----------------------------
	if(IsStmAnt) return; // In ant of state machine, exit
	if(!IsZeroOfantMsgProcWaitHms) return; // waiting for "ANTMSGPROC'Hms" timeout
	if(!IsEmptyOfTxBuf) return; // the uart buffer is empty
	if(IsAntMsgPROCESSING) // the ant message processing, exit
return;

	// -----------------------------
	// Ant READY COMMEND: 
	// ----------------------------- 
#if defined (TRACE_NUMBER_PROCESS)
			 __SciTraceNUMBER('1');
#endif // !TRACE_NUMBER_PROCESS
	__clearAntSleepHMS();
	switch(antMsgPROC.RdyMsgID){
		case MESG_NETWORK_KEY_ID:

			antIfCmd_NetworkKey();
			antMsgPROC.RdyMsgID = MESG_ASSIGN_CHANNEL_ID; // Next to set assigned channel
			break;

		case MESG_ASSIGN_CHANNEL_ID:

			antIfCmd_AssignChannel();
			antMsgPROC.RdyMsgID = MESG_CHANNEL_ID_ID;
			break;

		case MESG_CHANNEL_ID_ID:

			//antMsgPROC.devNumber.value = ANS_CHANNEL_DEVICE_NUMBER;
			//antMsgPROC.devType = ANS_CHANNEL_DEVICE_TYPE;
			//antMsgPROC.devTransType = ANS_CHANNEL_TRANS_TYPE;
			antIfCmd_ChannelId();
			antMsgPROC.RdyMsgID = MESG_CHANNEL_MESG_PERIOD_ID;
			break;

		case MESG_CHANNEL_MESG_PERIOD_ID:
		
			//antMsgPROC.msgPeriod.value = ANS_CHANNEL_MESG_PERIOD;
			antIfCmd_ChannelPeriod();
			antMsgPROC.RdyMsgID = MESG_CHANNEL_RADIO_FREQ_ID;
			break;

		case MESG_CHANNEL_RADIO_FREQ_ID:
		
			//antMsgPROC.RfFreq = ANS_CHANNEL_RF_FREQ;
			antIfCmd_ChannelRFFreq();
			antMsgPROC.RdyMsgID = MESG_OPEN_CHANNEL_ID;
			break;

		case MESG_OPEN_CHANNEL_ID:
		
			antIfCmd_OpenChannel();
			antMsgPROC.RdyMsgID = MESG_CLEAN_ID;
			sysAntChOpenCOMMon;
			break;
			
		case MESG_CLOSE_CHANNEL_ID:
		
			antIfCmd_CloseChannel();
			antMsgPROC.RdyMsgID = MESG_CLEAN_ID; //MESG_DEEP_SLEEP_ID;
			sysAntChOpenCOMMoff; sysAntChOpenDONEoff;
			break;

		case MESG_BROADCAST_DATA_ID:
		
			antIfCmd_Broadcast();
			antMsgPROC.RdyMsgID = MESG_CLEAN_ID;
			break;

		case MESG_DEEP_SLEEP_ID:
		
			antIfCmd_DeepSLEEP();
			antMsgPROC.RdyMsgID = MESG_CLEAN_ID;
			sysAntChOpenCOMMoff; sysAntChOpenDONEoff;
			break;

		// ---------------------------------------------
		// Add the new ANT Command ID here
		// ---------------------------------------------
		// case MESG_###_ID:
		// break;

		default:
			antMsgPROC.RdyMsgID = MESG_CLEAN_ID;
			return;

	}

	// ---------------------------
	// Start Ant state machine
	// ---------------------------
	stmAntMSGon();
	
}

////////////////////////////////////////////////////////////////////////////////
// Below is ANT Messages                                                                                                  //
//                                                                                                                                    //
//                                                                                                                                    //
////////////////////////////////////////////////////////////////////////////////

// =====================================
// ===================================== 
void antIfCmd_NetworkKey()
{

	// ---------------------------
	// (1) Create the ANT message
	// ---------------------------
	antMsgPROC.ProcMsgID =\
		antTxBuf.ID = MESG_NETWORK_KEY_ID; // Set <> as ANT message response MsgID
	antTxBuf.LEN = MESG_NETWORK_KEY_SIZE; // push ANT message data into buffer
	antTxBuf.data[0] = ANS_NETWORK_NUMBER;
	antTxBuf.data[1] = aucNetworkKey[0];
	antTxBuf.data[2] = aucNetworkKey[1];
	antTxBuf.data[3] = aucNetworkKey[2];
	antTxBuf.data[4] = aucNetworkKey[3];
	antTxBuf.data[5] = aucNetworkKey[4];
	antTxBuf.data[6] = aucNetworkKey[5];
	antTxBuf.data[7] = aucNetworkKey[6];
	antTxBuf.data[8] = aucNetworkKey[7];

	// ---------------------------
	// (2) Calculation antTxBuf checksum
	// ---------------------------
	sysFsrHiBANKon; __antTools_CALnSAVEAntMsgCS((UCHAR)&antTxBuf);

	// ---------------------------
	// (3) Set ant command process information
	// ---------------------------
	antMsgProcWaitHms200Ms(); // Set < 200ms > as ANT message response MsgWaitmr
	antMsgPROC.RespID = MESG_RESPONSE_EVENT_ID; // Set <> as message response MsgRespID, need to waiting response


}

// =====================================
// ===================================== 
void antIfCmd_AssignChannel()
{

	// ---------------------------
	// (1) Create the ANT message
	// ---------------------------
	antMsgPROC.ProcMsgID =\
		antTxBuf.ID = MESG_ASSIGN_CHANNEL_ID; // Set <> as ANT message response MsgID
	antTxBuf.LEN = MESG_ASSIGN_CHANNEL_SIZE; // push ANT message data into buffer
	antTxBuf.data[0] = ANS_CHANNEL_NUMBER; // [D0] CHANNEL NUMBER
	antTxBuf.data[1] = ANS_CHANNEL_TYPE; // [D1] CHANNEL TYPE
	antTxBuf.data[2] = ANS_NETWORK_NUMBER; // [D2] NETWORK NUMBER

	// ---------------------------
	// (2) Calculation antTxBuf checksum
	// ---------------------------
	sysFsrHiBANKon; __antTools_CALnSAVEAntMsgCS((UCHAR)&antTxBuf);

	// ---------------------------
	// (3) Set ant command process information
	// ---------------------------
	antMsgProcWaitHms200Ms(); // Set < 200ms > as ANT message response MsgWaitmr
	antMsgPROC.RespID = MESG_RESPONSE_EVENT_ID; // Set <> as message response MsgRespID

}

// =====================================
// Input: NA
// Output: antTxBuf[], antMsgProc[]
// Reg: NA
// e.g.: NA
// ===================================== 
void antIfCmd_ChannelId()
{
	// ---------------------------
	// (1) Create **message
	// ---------------------------
	antMsgPROC.ProcMsgID =\
		antTxBuf.ID = MESG_CHANNEL_ID_ID; // Set <> as ANT message response MsgID
	antTxBuf.LEN = MESG_CHANNEL_ID_SIZE; // push ANT message data into buffer
	antTxBuf.data[0] = ANS_CHANNEL_NUMBER; // [D0] CHANNEL NUMBER
	//antTxBuf.data[1] = antMsgPROC.devNumber.icun[0].value; // [D1] DEVICE NUMBER Low byte
	antTxBuf.data[1] = (UCHAR) ANS_CHANNEL_DEVICE_NUMBER;
	//antTxBuf.data[2] = antMsgPROC.devNumber.icun[1].value; // [D2] DEVICE NUMBER High Byte
	antTxBuf.data[2] = (UCHAR) (ANS_CHANNEL_DEVICE_NUMBER >> 8);
	//antTxBuf.data[3] = antMsgPROC.devType; // [D3] NETWORK NUMBER
	antTxBuf.data[3] = ANS_CHANNEL_DEVICE_TYPE;
	//antTxBuf.data[4] = antMsgPROC.devTransType; // [D4] device transmission type
	antTxBuf.data[4] = ANS_CHANNEL_TRANS_TYPE;
	
	// ---------------------------
	// (2) Calculation **Tx‘s buffer checksum
	// ---------------------------
	sysFsrHiBANKon; __antTools_CALnSAVEAntMsgCS((UCHAR)&antTxBuf);
	
	// ---------------------------
	// (3) Set **command process information
	// ---------------------------
	antMsgProcWaitHms200Ms(); // Set < 200ms > as ANT message response MsgWaitmr
	antMsgPROC.RespID = MESG_RESPONSE_EVENT_ID; // Set <> as message response MsgRespID
	
}

// =====================================
// ===================================== 
void antIfCmd_ChannelPeriod()
{
	// ---------------------------
	// (1) Create **message
	// ---------------------------
	antMsgPROC.ProcMsgID =\
		antTxBuf.ID = MESG_CHANNEL_MESG_PERIOD_ID; // Set <> as ANT message response MsgID
	antTxBuf.LEN = MESG_CHANNEL_MESG_PERIOD_SIZE; // push ANT message data into buffer
	antTxBuf.data[0] = ANS_CHANNEL_NUMBER; // [D0] CHANNEL NUMBER
	//antTxBuf.data[1] = antMsgPROC.msgPeriod.icun[0].value; // [D1] MESSAGING PERIOD Low byte
	antTxBuf.data[1] = (UCHAR)(ANS_CHANNEL_MESG_PERIOD & 0x00FF);
	//antTxBuf.data[2] = antMsgPROC.msgPeriod.icun[1].value; // [D2] MESSAGING PERIOD High Byte
	antTxBuf.data[2] = (UCHAR)(ANS_CHANNEL_MESG_PERIOD >> 8);

	// ---------------------------
	// (2) Calculation **Tx‘s buffer checksum
	// ---------------------------
	sysFsrHiBANKon; __antTools_CALnSAVEAntMsgCS((UCHAR)&antTxBuf);
	
	// ---------------------------
	// (3) Set **command process information
	// ---------------------------
	antMsgProcWaitHms200Ms(); // Set < 200ms > as ANT message response MsgWaitmr
	antMsgPROC.RespID = MESG_RESPONSE_EVENT_ID; // Set <> as message response MsgRespID
	
}

// =====================================
// [antInterface] | [Function description] | [Function code] | [run time] 
// -------------------------------------
// Design Record: 1204662412_ant message protocol and usage.pdf
// -------------------------------------
// Provide Sample Function name:
// BOOL ANT_ChannelRFFreq(UCHAR ucANTChannel_,UCHAR ucFreq_)
// -------------------------------------
// Access core code condition: NA
// -------------------------------------
// Input: NA
// Output: antTxBuf[], antMsgProc[]
// Reg: NA
// e.g.: NA
// ===================================== 
void antIfCmd_ChannelRFFreq()
{
	// ---------------------------
	// (1) Create **message
	// ---------------------------
	antMsgPROC.ProcMsgID =\
		antTxBuf.ID = MESG_CHANNEL_RADIO_FREQ_ID; // Set <> as ANT message response MsgID
	antTxBuf.LEN = MESG_CHANNEL_RADIO_FREQ_SIZE; // push ANT message data into buffer
	antTxBuf.data[0] = ANS_CHANNEL_NUMBER; // [D0] CHANNEL NUMBER
	//antTxBuf.data[1] = antMsgPROC.RfFreq; // [D1] RF Freqency
	antTxBuf.data[1] = (UCHAR)ANS_CHANNEL_RF_FREQ;
	
	// ---------------------------
	// (2) Calculation **Tx‘s buffer checksum
	// ---------------------------
	sysFsrHiBANKon; __antTools_CALnSAVEAntMsgCS((UCHAR)&antTxBuf);
	
	// ---------------------------
	// (3) Set **command process information
	// ---------------------------
	antMsgProcWaitHms200Ms(); // Set < 200ms > as ANT message response MsgWaitmr
	antMsgPROC.RespID = MESG_RESPONSE_EVENT_ID; // Set <> as message response MsgRespID
	
}

// =====================================
// ===================================== 
void antIfCmd_OpenChannel()
{
	// ---------------------------
	// (1) Create **message
	// ---------------------------
	antMsgPROC.ProcMsgID =\
		antTxBuf.ID = MESG_OPEN_CHANNEL_ID; // Set <> as ANT message response MsgID
	antTxBuf.LEN = MESG_OPEN_CHANNEL_SIZE; // push ANT message data into buffer
	antTxBuf.data[0] = ANS_CHANNEL_NUMBER; // [D0] CHANNEL NUMBER

	// ---------------------------
	// (2) Calculation **Tx‘s buffer checksum
	// ---------------------------
	sysFsrHiBANKon; __antTools_CALnSAVEAntMsgCS((UCHAR)&antTxBuf);
	
	// ---------------------------
	// (3) Set **command process information
	// ---------------------------
	antMsgProcWaitHms200Ms(); // Set < 200ms > as ANT message response MsgWaitmr
	antMsgPROC.RespID = MESG_RESPONSE_EVENT_ID; // Set <> as message response MsgRespID
	
}

// =====================================
// ===================================== 
void antIfCmd_CloseChannel()
{
	// ---------------------------
	// (1) Create **message
	// ---------------------------
	antMsgPROC.ProcMsgID =\
		antTxBuf.ID = MESG_CLOSE_CHANNEL_ID; // Set <> as ANT message response MsgID
	antTxBuf.LEN = MESG_CLOSE_CHANNEL_SIZE; // push ANT message data into buffer
	antTxBuf.data[0] = ANS_CHANNEL_NUMBER; // [D0] CHANNEL NUMBER

	// ---------------------------
	// (2) Calculation **Tx‘s buffer checksum
	// ---------------------------
	sysFsrHiBANKon; __antTools_CALnSAVEAntMsgCS((UCHAR)&antTxBuf);
	
	// ---------------------------
	// (3) Set **command process information
	// ---------------------------
	antMsgProcWaitHms200Ms(); // Set < 200ms > as ANT message response MsgWaitmr
	antMsgPROC.RespID = MESG_RESPONSE_EVENT_ID; // Set <> as message response MsgRespID
	
}

// =====================================
// ===================================== 
void antIfCmd_Broadcast()
{
	// ---------------------------
	// (1) Create **message
	// ---------------------------
	antMsgPROC.ProcMsgID =\
		antTxBuf.ID = MESG_BROADCAST_DATA_ID; // Set <> as ANT message response MsgID
	antTxBuf.LEN = MESG_DATA_SIZE; // push ANT message data into buffer
	antTxBuf.data[0] = ANS_CHANNEL_NUMBER; // [D0] CHANNEL NUMBER
	// Copy "Bike Power Sensor" data to antTxBuf's data
	sysFsrHiBANKon;
	#if defined (ANT_BPS_PROJECTCODE)
	__tools_sourceCopyToTarget \
		(ANT_DATA_SIZE , \
		 (UCHAR)&antBpsData.dataPageNum , \
		 (UCHAR)&antTxBuf.data[1]);
	#endif
	// ---------------------------
	// (2) Calculation **Tx‘s buffer checksum
	// ---------------------------
	sysFsrHiBANKon; __antTools_CALnSAVEAntMsgCS((UCHAR)&antTxBuf);
	
	// ---------------------------
	// (3) Set **command process information
	// ---------------------------
	//antMsgProcWaitHms200Ms(); // Set < 200ms > as ANT message response MsgWaitmr
	antMsgPROC.RespID = MESG_NO_RESPONSE_ID_E5; // Set <> as message response MsgRespID
	
}

// =====================================
// ===================================== 
void antIfCmd_DeepSLEEP()
{
	// ---------------------------
	// (1) Create **message
	// ---------------------------
	antMsgPROC.ProcMsgID =\
		antTxBuf.ID = MESG_DEEP_SLEEP_ID; // Set <> as ANT message response MsgID
	antTxBuf.LEN = MESG_DEEP_SLEEP_SIZE; // push ANT message data into buffer
	antTxBuf.data[0] = 0; // [D0] FIXED NUMBER "0"

	// ---------------------------
	// (2) Calculation **Tx‘s buffer checksum
	// ---------------------------
	sysFsrHiBANKon; __antTools_CALnSAVEAntMsgCS((UCHAR)&antTxBuf);
	
	// ---------------------------
	// (3) Set **command process information
	// ---------------------------
	//antMsgProcWaitHms200Ms(); // Set < 200ms > as ANT message response MsgWaitmr
	antMsgPROC.RespID = MESG_NO_RESPONSE_ID_E5; // Set <> as message response MsgRespID
	
}

/*eof*/

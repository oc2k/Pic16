//*************************************************************
// halAntAsync.c
//************************************************************* 

// =====================================
// =====================================
void init_HwAntAsync()
{

	// -------------------------
	// D-SUSPEND -> DELAY -> D-SLEEP
	// -------------------------
	//(1) conformation of "Suspend & Sleep" initial
	_HwAntSuspendASSERT();
	bHwAntSleepAssertRtsCHK();
	__NOP(); // BREAK POINT, SLEEP AND SUSPEND NO CHANGE

	//(2) Deassert  "ANT+SUSPEND"
	_HwAntSuspendDEASSERT();
	__DelayUWord8Countdown(0x05);

	//(3) Deassert  "ANT+SLEEP"
	bHwAntSleepDeassertRtsCHK();

}

// =====================================
// Description:
// .. (1) UartSELECT> USB -- ShortDELAY
// .. (2) ASSERT> ANT+SUSPEND  --- LongDELAY
// .. (3) ASSERT> ANT+SLEEP -- ShortDELAY
// .. (4) ASSERT> ANT+RESET -- LongDELAY
// .. (5) DEASSERT> ANT+SLEEP -- ShortDELAY
// .. (6) Cutdown> ANT+VCC -- LongDELAY
// =====================================
void shutdown_HwAntAsync()
{

	// -------------------------
	// .. (1) UartSELECT> USB -- ShortDELAY
	_HwUartSELusb();
	// .. (2) ASSERT> ANT+SUSPEND  --- LongDELAY
	_HwAntSuspendASSERT();
	__DelayUWord8Countdown(0x00);
	// .. (3) ASSERT> ANT+SLEEP -- ShortDELAY
	_HwAntSleepASSERT();
	__DelayUWord8Countdown(0x05);
	// .. (4) ASSERT> ANT+RESET -- LongDELAY
	_HwAntResetASSERT();
	__DelayUWord8Countdown(0x00);
	// .. (5) DEASSERT> ANT+SLEEP -- ShortDELAY
	_HwAntSleepDEASSERT();
	__DelayUWord8Countdown(0x05);
	// .. (6) Cutdown> ANT+VCC -- LongDELAY
	_HwModuleVCCoff(); // power circuit change, replace to >>_HwAntVCCoff();
	__DelayUWord8Countdown(0x00);

	// -------------------------
	// The ANT state change to IDLE state
	// -------------------------
	// CLOSE ALL DOWN
	// (1) ANT+SLEEP=0
	// (2) ANT+RESET=0
	// (3) ANT+VCC=0
	// -------------------------

}

#if 0
// =====================================
// Description:
// Macro, register and return informations
// (1) antMsgBuf -> txBuf
// (2) Calculation Checksum
// (3) 
// =====================================
void aHalAntAsync_Transaction()
{
	// -------
	// Key flag
	// -------
	if(!IsStmAntRDY) return; // Isnot antStmREADY, no process

	// -----------------------------
	// Base condition
	// -----------------------------
	if(IsUartSelecting) return; // When Uart selection IC working, wait for it
	if(!IsEmptyOfTxBuf) return; // When the txbuf isnotEmpty, mean PrevMessage no clean, don't process

#if defined (TRACE_NUMBER_PROCESS)
			 __SciTraceNUMBER('3');
#endif // !TRACE_NUMBER_PROCESS
	bHwAntSleepDeassertRtsCHK();
	if(IsFaultERROR) // ANT module is fault error
return;

	// Create Ant Transmit message
	bCreateAntMessage();

	// UART Select to ANT
	_HwUartSELant(); // Uart select ANT as wireless operation
	__emptyUartRcBuf(); // empty Uart rcbuf for ANT response

	// The ANT message no need response
	if(IsNotAntMsgRespCODE){
		stmAntRepTXon(); // Set the state machine of "AntReportTx"
	}
	
	// The ANT message need to response
	else{
		stmAntTXon(); // Set the state machine of "AntTx"
		__sciRxtmr_50MsSETTING(); // set 50ms as the transmit time
	}

}

// =====================================
// ===================================== 
void aHalAntAsync_ProcessByte()
{
	// -----------------------------
	// Base condition
	// -----------------------------
	if(!IsZeroOfRxtmr) return;
	if(!IsZeroOfantMsgProcWaitHms) return;

	// -----------------------------
	// BRANCH PROCESS
	// -----------------------------
	if(IsStmAntTX) goto _antProcByte1RESPONSE; // PRIORITY HIGHER
	if(IsStmAntLISTEN) goto _antProcByte2LISTEN; // PRIORITY LOWER
return;

// -------------------------------------
// condition 1: (IsStmAntTX) -> Set state machine of "StmAntRX"
// -------------------------------------
_antProcByte1RESPONSE: //ANT PASSIVE MESSAGE

	// No received ANT MESSAGES
	if(IsEmptyOfRxBuf){
		__sciRxtmr_25MsSETTING(); //After 25Ms try again
return;
	}

	// TO CHECK RECEIVED ANT MESSAGE
	bHalAntAsync_AntMesgCHECK();

	// SKIP TO INTERFACE LAYER TO CHECK MESSAGE
	_HwUartSELusb(); // CHANGE UART for PC
	stmAntRXon(); // pass to interface analysis ANT MESSAGES

	// CHANGE ANT TO SLEEP
	bHwAntSleepAssertRtsCHK();
#if defined (TRACE_NUMBER_PROCESS)
			 __SciTraceNUMBER('4');
#endif // !TRACE_NUMBER_PROCESS

return;

// -------------------------------------
// condition 2: (IsStmAntLISTEN) -> Set state machine of "StmAntRepRX"
// -------------------------------------
_antProcByte2LISTEN: // ANT ACTIVE MESSAGE

	// No received ANT MESSAGES
	if(IsEmptyOfRxBuf){
		__sciRxtmr_25MsSETTING(); //After 25Ms try again
return;
	}

	// TO CHECK RECEIVED ANT MESSAGE
	bHalAntAsync_AntMesgCHECK();

	// TO CREATE BURST DATA
	if(sysAntChOpenDONE){
		if(sysAntRespEvtTX){
				
			sysAntRespEvtTXoff; // if Host listen correct "EVENT TX" ANT MESSAGE, MARK IT
			antMsgPROC.RdyMsgID = MESG_BROADCAST_DATA_ID;

		}
	}

	// SKIP TO INTERFACE LAYER TO CHECK MESSAGE
	_HwUartSELusb(); // CHANGE UART for PC
	stmAntRepRXon();

	// CHANGE ANT TO SLEEP
	bHwAntSleepAssertRtsCHK();
#if defined (TRACE_NUMBER_PROCESS)
			 __SciTraceNUMBER('4');
#endif // !TRACE_NUMBER_PROCESS

}
#endif

// =====================================
// =====================================
void bHwAntSleepAssertRtsCHK()
{

	/*****************************/
	
	_HwAntSleepASSERT(); // Assert SLEEP is HIGH LEVEL, the RTS current response is HIGH LEVEL
	__antMs100SETTING();
	do{
		if(IsZeroOfAntMS)
		{
			#if 0
			feAntHiRtsChkERRon; // time over, skip out and mark fault
			#endif
			break;
		}
		if(!_IsHwAntRtsAGREE) break; // the "RTS" Level is high, skip out

	}while(1);

	/***************************** /// Below code is ignore the RTS&SLEEP fault for debugging

	_HwAntSleepDEASSERT(); // When Simulation, don't waste time for SLEEP and RTS Toggle ON/OFF
	__antMs100SETTING();
	do{
		if(IsZeroOfAntMS){
			feAntLoRtsChkERRon; // time over, skip out and mark fault
			break;
		}
		if(_IsHwAntRtsAGREE) break; // the "RTS" Level is low, skip out

	}while(1);

	/*****************************/
}

// =====================================
//
// =====================================
void bHwAntSleepDeassertRtsCHK()
{
	_HwAntSleepDEASSERT(); // Deassert SLEEP is LOW LEVEL, the RTS current response is LOW LEVEL
	__antMs100SETTING();
	do{
		if(IsZeroOfAntMS){
			#if 0
				feAntLoRtsChkERRon; // time over, skip out and mark fault
			#endif
			break;
		}
		if(_IsHwAntRtsAGREE) break; // the "RTS" Level is low, skip out

	}while(1);
}


// =====================================
// DESCRIPTION: 
// .. To ANT RECEIVED MESSAGE STRUCTURE: 
// .... [0],    [1],  [2],     [3],    [4] 
// .... SYNC,LEN, MsgID,  CHn, DATA0..N,CHECKSUM
// .... [A4] , [03],[40],     [00], [ID],[CODE]
// (1) CHECK ANT MSG HEADER
// (2) CHECK ANT EXPECTED MSG ID
// ===================================== 
void bHalAntAsync_AntMesgCHECK()
{

	// ----------------------------
	// To Check Received Message STRUCTURE: SYNC,LEN,MSG ID,CHn,DATA0..N,CHECKSUM
	// ----------------------------
	// (1) To check SYNC HEADER
	if(rcbuf.data[0] != 0xA4){
		antMsgPROC.EvtCode = EVENT_INVALID_HEADER_E5; // ERROR 1
	}
	// (2) To check MESSAGE EXPECTED ID
	else if(rcbuf.data[2] != antMsgPROC.RespID){
		antMsgPROC.EvtCode = EVENT_NO_EXPECTED_ID_E5; // ERROR 2
	}
	// ----------------------------
	// CORRECT MESSAGE DONE PROCESSING
	// ----------------------------
	else{

		// ----------------------------
		// RESPONSE Message STRUCTURE: __0_, _1_,_*2__,_3__,__*4___,___*5____,CS
		// RESPONSE Message STRUCTURE: SYNC,LEN,MsgID,CHn,*CmdID,*MsgCODE,CS
		// RESPONSE Message STRUCTURE:  [A4],[03],*[40] ,CHn,*CmdID,*MsgCODE,CS
		// ----------------------------
		if(rcbuf.data[2] == MESG_RESPONSE_EVENT_ID){
			//if(rcbuf.cnt.value == 0x07){
				// To set "ANT CHANNEL OPEN" Mark
				if(rcbuf.data[4] == MESG_OPEN_CHANNEL_ID){
						antMsgPROC.EvtCode = EVENT_CHANNAL_OPEN_E5; // CORRECT MSG RESPONSE
						sysAntChOpenDONEon;
				}
				// To set "BURST DATA" Mark
				if(rcbuf.data[5] == EVENT_TX ){
					sysAntRespEvtTXon;
				}
			//}
		}
	}

	// ----------------------------
	// END OF CHECKING MESSAGE STRUCTURE
	// ----------------------------
	__NOP();

}
/*eof*/

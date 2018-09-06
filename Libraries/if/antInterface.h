//*************************************************************
//         oc2k - 2011 - All right reserved                 
//*************************************************************
//                                                             
//  Project      :       
//  Type         :       
//  Name         :       
//  Instance     :       
//  Created by   :    08/07/2011   
//  Creation date:       
//  Description  :                                         
//                                                  
//*************************************************************
//  Trace 2nd Number: 3##
//*************************************************************
//       HISTORICAL       
//*************************************************************
//           
// Date         :   
// Changed by   :       
// Description  :                 
//
//************************************************************* 

#ifndef _antInterface_H
#define _antInterface_H

//======================================
//(1) define constant parameter
//======================================
// ANTPLUS_DEBUGGING_CODE <OR> ANTPLUS_OFFICIAL_CODE , to DEFINED IN osConstantesDEFs.h
#if defined(ANTPLUS_OFFICIAL_CODE) || defined(ANTPLUS_DEBUGGING_CODE)
#else
#error " To defined "ANTPLUS_OFFICIAL_CODE" or "ANTPLUS_OFFICIAL_CODE" in osConstantesDEFs.h "
#warning	"No Sci Interface"
#endif // !(defined(ANTPLUS_OFFICIAL_CODE) || defined(ANTPLUS_DEBUGGING_CODE))

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// -- END OF SELECTION ---
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define __constUartReportBaseSIZE		4
#define __constUartReportNilAddSIZE		5
#define __constUartReportTxSyncAddSIZE	3
#define __constUartReportEachDataSIZE	3
#define __constUartReportEndingAddSIZE	1
#define __constUartReportExtraOdoaSIZE	2
#define __constUartReportLimitSIZE		78
#define __constAntMsgProcDataSIZE		5 // 1[ProcMsgID] 2[RdyMsgID] 3[RespID] 4[RFU] 5[EvtCode]
#define __constUartReportOfficialSIZE	2  // include Tx, Rx and Evt

//======================================
//(2) Define file register
//======================================
typedef  struct AntMsgBUFStruct{
	UCHAR LEN;
	UCHAR ID;
	UCHAR data[ANT_MAX_DATA_SIZE];
}AntMsgBUF;
typedef  struct AntMsgResponseStruct{
	UCHAR waitHms; // TO BE SETTING THE RESPONSE TIME
	UCHAR ProcMsgID; // PROCESSING MESSAGE ID
	UCHAR RdyMsgID; // READY TO SEND MESSAGE ID
	UCHAR RespID; // EXPECTED RESPONSE ID -- NEED TO SETTING
	UCHAR RFU; //RESERVE FOR FUTURE USE
	UCHAR EvtCode; // EVENT CODE -- E5 IS INITIAL CODE
//	IUN devNumber; // DEVICE NUMBER 
//	UCHAR devType; // DEVICE TYPE
//	UCHAR devTransType; // DEVICE TRANSFER TYPE
//	IUN msgPeriod; //
//	UCHAR RfFreq;
}AntMsgPROCESS;

	bank3 AntMsgBUF antTxBuf;
	bank1 AntMsgBUF antRxBuf;
	bank1 AntMsgPROCESS antMsgPROC;
	
	CUN stmAnt;
	CUN cmd;
	CUN sysAnt;

static const UCHAR aucNetworkKey[] = ANTPLUS_NETWORK_KEY;

//======================================
//(3) system flag
//======================================
#define IsEmptyOfAntTxBUF		(antTxBuf.LEN == 0)
#define IsAntMsgPROCESSING		(antMsgPROC.ProcMsgID != 0)
#define IsNotEmptyOfAntRdyMsg	(antMsgPROC.RdyMsgID != 0)
#define IsEmptyOfAntRdyMsg		(antMsgPROC.RdyMsgID == 0)
#define IsNotAntMsgRespCODE		(antMsgPROC.RespID == 0)
// --> Macro
#define antTxBufClear()			antTxBuf.LEN = 0; // After Report Tx to activate
#define antProcMsgIdClear()		antMsgPROC.ProcMsgID = 0; // To finish to process current Ant message
#define antProcWaitmrClear()	antMsgPROC.waitHms= 0; // To finish AntSTM
#define __isrAntProcWaitHmsCountdown() 	if(antMsgPROC.waitHms) antMsgPROC.waitHms --; // Per 100ms countdown in isr
//#define antMsgProcWaitHms500Ms()		(antMsgPROC.waitHms = 5) // 500ms
#define antMsgProcWaitHms200Ms()		(antMsgPROC.waitHms = 2) // 200ms
#define IsZeroOfantMsgProcWaitHms		(antMsgPROC.waitHms == 0)
// -stm- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#define IsStmAnt			(stmAnt.value != 0)
//#define IsZeroOfStmAnt		(stmAnt.value == 0)
#define stmAntCLEAR()		stmAnt.value = 0
#define stmAntMSGon()		stmAnt.value = 0b00000001
#define stmAntRDYon()		stmAnt.value = 0b00000010
#define stmAntTXon()		stmAnt.value = 0b00000100
#define stmAntRXon()		stmAnt.value = 0b00001000
#define stmAntRepTXon()		stmAnt.value = 0b00010000
#define stmAntRepRXon()		stmAnt.value = 0b00100000
#define stmAntRepEVTon()	stmAnt.value = 0b01000000
//#define stmAntHwCHKon()		stmAnt.value = 0b10000000
#define stmAntLISTENon()	stmAnt.value = 0b10000000
//-->
#define IsStmAntMSG		stmAnt.cb.zer
#define IsStmAntRDY		stmAnt.cb.one
#define IsStmAntTX		stmAnt.cb.two
#define IsStmAntRX		stmAnt.cb.thr
#define IsStmAntRepTX	stmAnt.cb.fou
#define IsStmAntRepRX	stmAnt.cb.fiv
#define IsStmAntRepEVT	stmAnt.cb.six
//#define IsStmAntHwCHK	stmAnt.cb.sev
#define IsStmAntLISTEN	stmAnt.cb.sev
// -cmd- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//#define IsNotCmdEXECUTED	(cmd.value == 0)
//#define cmdAntCmdCLEAR()	(cmd.value = 0)
//#define cmdSetAntCmdONE		cmd.cb.zer //xxx	Set Network ID
//#define cmdSetAntCmdONEon		cmdSetAntCmdONE = 1
//#define cmdSetAntCmdTWO		cmd.cb.two//xxx	Assign channel
//#define cmdSetAntCmdTWOon		cmdSetAntCmdTWO = 1
//#define cmdSetAntCmdTHR		cmd.cb.thr//xxx	
//#define cmdSetAntCmdTHRon		cmdSetAntCmdTHR = 1
//#define cmdSetAntCmdTHRoff		cmdSetAntCmdTHR = 0
// -sysAnt- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#define sysAntChOpenDONE		sysAnt.cb.zer
#define sysAntChOpenDONEon			sysAntChOpenDONE = 1 // open channel command reply
#define sysAntChOpenDONEoff			sysAntChOpenDONE = 0 // Init & close channel commend( or deep sleep)
#define sysAntChOpenCOMM		sysAnt.cb.one
#define sysAntChOpenCOMMon			sysAntChOpenCOMM = 1 // open channel command
#define sysAntChOpenCOMMoff			sysAntChOpenCOMM = 0 // Init & close channel commend( or deep sleep)
#define sysAntRespEvtTX			sysAnt.cb.two
#define sysAntRespEvtTXon			sysAntRespEvtTX = 1 // Response process in bHalAntAsync_AntMesgCHECK
#define sysAntRespEvtTXoff			sysAntRespEvtTX = 0 // when send burst data clear in aHalAntAsync_ProcessByte
#define sysAntBurstDataNEW		sysAnt.cb.thr
#define sysAntBurstDataNEWon		sysAntBurstDataNEW = 1 // burst data READY: (1) calculation done, (2) burst data prepare
#define sysAntBurstDataNEWoff		sysAntBurstDataNEW = 0 // AFTER Send to ANT, CLEAR IT
// -->
#define sysAntUartMsgEVT		sysAnt.cb.fou//xxx
#define sysAntUartMsgEVTon			sysAntUartMsgEVT = 1 // Event call set in "antReportEVT"
#define sysAntUartMsgEVToff			sysAntUartMsgEVT = 0 // Event call clear in "TransactionPC"
//EndOf constant parameter


//======================================
//(4) hardware defination
//======================================
 

//======================================
//(5) Macro defined
//======================================
// The macro would be replace to "initAnt_resetAntPreProcess"
#define initAnt_ReforeAntResetProcess() \
	__emptyUartRcBuf();
 
// The macro would be replace to "initAnt_resetAntPostProcess"
#define initAnt_AfterAntResetProcess() \
	init_HwAntSerial(); /*Initial ANT Hardware*/ 

//======================================
//(6) Function defination
//======================================

	void aAntIf_Transaction();
	void aAntIf_ProcessByte();
	void aAntIf_ReportTx();
	void aAntIf_ReportRx();
	void aAntIf_ReportEvent();
	void aAntIf_AntListenRTS();
	void aAntIf_AntWAKEUP();
	void aAntIf_ExecuteAntCOMMAND();
	//-->
	void antIfCmd_NetworkKey();
	void antIfCmd_AssignChannel();
	void antIfCmd_ChannelId();
	void antIfCmd_ChannelPeriod();
	void antIfCmd_ChannelRFFreq();
	void antIfCmd_OpenChannel();
	void antIfCmd_CloseChannel();
	void antIfCmd_Broadcast();
	void antIfCmd_DeepSLEEP();
	//void antIf_UnAssignChannel();
	//void antIf_SearchTimeout();
	//void antIf_ChannelPower();
	//void antIf_AcknowledgedTimeout();
	//void antIf_Acknowledged();
	//void antIf_BurstPacket();
	//void antIf_SendBurstTransfer();
	//void antIf_RequestMessage();
	//void antIf_RunScript();
	//void antIf_WaitForResponse();

	//void antIf_ClearWait();
	//void antIf_CommandTimeout();
	//void antIf_CommandAckTimeout();

#endif // !_antInterface_H

//*************************************************************
//       Timing processing GUIDELINE
//*************************************************************
#ifndef _antInterface_H_isr
#define _antInterface_H_isr
	#define antIsrHms1() __isrAntProcWaitHmsCountdown(); //In Isr Hms
#endif //!_antInterface_H_isr

//************************************************************* 
// (2) Timing process in osSysClock, e.g.: #define SciSysclkTmr1() __clkSciPcMsgHmsCountdown();
//************************************************************* 
#ifndef _antInterface_H_sysClk
#define _antInterface_H_sysClk
#endif //!_antInterface_H_sysClk


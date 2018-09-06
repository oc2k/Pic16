//*************************************************************
//antTools.c
//************************************************************* 

// =====================================
// Input: [antMsgBuf's start pointer]
// Output: [calculate and save currect location]
// Reg: [! FSR, i, j]
// e.g.: 	sysFsrHiBANK; __antTools_CALnSAVEAntMsgCS((UCHAR)&antTxBuf);
// -------------------------------------
// Description:
// =====================================
void jAntTools_CALnSAVEAntMsgCS()
{
	// ---------------------------------
	// FRAME1:  SYNC BYTE
	// ------ AntMsgBuf Structure ---------
	// UCHAR LEN;
	// UCHAR ID;
	// UCHAR data[ANT_MAX_DATA_SIZE];
	// ---------------------------------
	// FRAME2: CHECKSUM
	// ---------------------------------

	// (1) Adjust the pointer access correct bank
	__SetLBank(); if(sysFsrHiBANK) __SetHBank();

	// (2) Take the pointer pointer to Top of buffer and release sub_j
	FSR = sub_j; //release j as using

	// (3) To fill antTxBufTop of buffer is buffer data LEN, pass to sub_i as counter
	sub_i = INDF + MESG_FRAME_SIZE_E5;

	// ---------------------------------
	// Begin to calculate:
	// ---------------------------------
	// (1) Put first byte: TX_SYNC
	sub_j = MESG_TX_SYNC; // CASE 1: ANTTXBUF
	//sub_j = MESG_RX_SYNC; // CASE 2: ANTRXBUF

	// (2) XOR OTHER MESSAGE BYTE
	do{
		sub_j ^= INDF; FSR++; // Xor all buffer data
	}while(--sub_i);

	// (3) Put the calucation result into Ant*xBuf
	INDF = sub_j;

	 // back to default bank (bank0 and bank1) access
	sysFsrHiBANKoff;

}
#define __antTools_CALnSAVEAntMsgCS(U8PtrOfTopAntMsgBuf)\
			sub_j = U8PtrOfTopAntMsgBuf, jAntTools_CALnSAVEAntMsgCS();

// =====================================
// Macro, register and return informations
// Input: antMsgBuf
// Output: Uart txBuf
// Procedure: Add Header.. copy data and calculation checksum
// ---------------------------------
// Description:
// =====================================
void bCreateAntMessage()
{
	// (1) Add Message Header
	txBuf.buffer[0] = MESG_TX_SYNC;

	// (2) Transfer antMsgBuf to Txbuf (LEN, ID, DATA)

	sysFsrHiBANKon;
	__tools_sourceCopyToTarget \
		(( txBuf.size = antTxBuf.LEN + ANT_SIZE_SIZE + MESG_ID_SIZE + MESG_CHECKSUM_SIZE), \
		 (UCHAR)&antTxBuf.LEN, \
		 (UCHAR)&txBuf.buffer[1]);

	txBuf.size += (ANT_SYNC_SIZE ); // adjust buffer size

}

// =====================================
// parameters: size, sourcePointer, TargetPointer
// Input:  [Source: [03][E4]...]
// Output: [Target: "03,E4, ...]
// Reg: [20h - 25h] // i,j,k,m,n,o
// e.g.: 
// (sysFsrHiBANKoff;) 
// __AntTools_convertBufAndSendToPC \
//			(rcbuf.cnt.value,\
//			 (UCHAR)&rcbuf.data[0],\
//			 (UCHAR)&txBuf.buffer[4]);
// ---------------------------------
// Description:
// =====================================
void oTools_convertBufAndSendToPC()
{
	// (1) Load source data of pointer
	// (2) convert sourct data to ascii
	// (3) save the ascii byte into tx's buffer
	// .. Next pointer or exit
	do{
	
		// Load source data
		FSR = sub_o;
	
		// Convert source data
		__SetLBank(); if(sysFsrHiBANK) __SetHBank();
		__HiHalfByteConvertAscii(INDF); sub_m = sub_i;
		__SetLBank(); if(sysFsrHiBANK) __SetHBank();
		__LoHalfByteConvertAscii(INDF); sub_n = sub_i;
	
		// Save convert data to Tx's buffer (in bank2)
		__SetHBank();
		FSR = sub_k; INDF = sub_m; // [0]
		FSR ++; INDF = sub_n; // [1]
		FSR ++; INDF = ','; // [2]
	
		// Adjust pointer and etc.
		sub_o ++; // Adjust source pointer
		sub_k += __constUartReportEachDataSIZE; // Adjust target pointer
		txBuf.size += __constUartReportEachDataSIZE; // adjust tx's buffer size
		if(txBuf.size > __constUartReportLimitSIZE) // check tx's buffer limit
			break;
	
	}while(--sub_j);
	
	// Send "0D0A" as ending
	INDF = 0xD; // replace ","
	FSR ++; INDF = 0xA;
	txBuf.size += __constUartReportEndingAddSIZE;

	// resume default bank access
	sysFsrHiBANKoff;

}
#define __Tools_convertBufAndSendToPC(u8Size, u8SourceTopPtr, u8TargetTopPtr)\
			sub_j = u8Size;\
			sub_k = u8TargetTopPtr;\
			sub_o = u8SourceTopPtr;\
			oTools_convertBufAndSendToPC();

// =====================================
// e.g.: __tool_ClearCurrentAntCMD();
// -------------------------------------
// Description:
// =====================================
void tool_ClearCurrentAntCMD()
{
	// -------------------------------------------
	// The Ant Message communication have done
	// (1) Clear stmAnt and to set UartMsgDONEon for listen ANT have other message
	// (2) Clear AntMsgProcess's Process Message ID
	// (3) Init AntMsgResponse's Event code
	// -------------------------------------------
	stmAntCLEAR();
	antProcMsgIdClear();
	antMsgPROC.EvtCode = EVENT_RESPONSE_INITIAL_E5;
}
#define __tool_ClearCurrentAntCMD() tool_ClearCurrentAntCMD()

/* eof */


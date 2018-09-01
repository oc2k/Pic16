//*************************************************************
//************************************************************* 
// =====================================
// -------------------------------------
// Input: 
// Output: 
// Reg: 
// e.g.: 
// Description: Loading eeprom
// =====================================
void iTools_PicEepromOneByteRead()
{
	EEADR = sub_i;
	EECON1 &= 0x7F; //EEPGD=0
	RD = 1;
	//sub_i = EEDATA;
	return;
}
#define __tools_PicEepromOneByteRead(U8Addr)\
	(sub_i = U8Addr, iTools_PicEepromOneByteRead(), EEDATA)

// =====================================
// -------------------------------------
// Description:
// =====================================
void initPerPicEe_LoadingPara()
{

	for (sub_j=0;sub_j<__constEePicMemSizeLIMIT;sub_j++){
		
		eePicMem[sub_j] = __tools_PicEepromOneByteRead(sub_j);
		
	}

	__NOP(); // ToSetBreakPointer
}

/*End of picee.c */

//*************************************************************
//************************************************************* 
// =====================================
// =====================================
void aHalA2d_BatVoltage()
{
	// -----------------------------
	// Extra condition
	// -----------------------------

	// -----------------------------
	// Base condition
	// -----------------------------
	if(adSaveSecond == oSecond.value)
return;

	//adSaveMinute = oMinute.value;
	adSaveSecond = oSecond.value;
	_selAN0();
	ad_On();
	ad_Go();
	sub_i=100; do{}while(--sub_i);
	ad_Done();
	adBatBuf[2]=adBatBuf[1];
	adBatBuf[1]=adBatBuf[0];
	adBatBuf[3]=adBatBuf[4]=adBatBuf[0]=ADRESH;
	sub_i = 2; FSR=(UCHAR)&adBatBuf[1];
	do{
		if(INDF < adBatBuf[3]) adBatBuf[3]=INDF;
		if(INDF > adBatBuf[4]) adBatBuf[4]=INDF;
		FSR++;
	}while(--sub_i);//release i
	//Put HiPassFilter and LowPassFilter
	inti_.value = adBatBuf[0] \
				+ adBatBuf[1] \
				- adBatBuf[3] \
				+ adBatBuf[2] \
				- adBatBuf[4];
	adBatteryValue = sub_i; //Get the Filter result

}

/*********************/
/* end of the file   */
/*********************/


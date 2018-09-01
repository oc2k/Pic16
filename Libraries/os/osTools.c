//*************************************************************
//************************************************************* 
// =====================================
// =====================================
void kUWord8ToHTO()
{
	sub_k=sub_j=0;
	while(sub_i>99){
		sub_k++;
		sub_i-=100;
	};
	while(sub_i>9){
		sub_j++;
		sub_i-=10;
	};
}
#define __UWord8ToHTO(U8Byte) sub_i=U8Byte; kUWord8ToHTO();

//======================================
// Tool | UWord16 convert to Wan,Kilo,hundred,ten,one|
// =====================================
//>>>> -->In>> (HHLL)
//>>>>(0x24),(0x23),  (0x22),(0x21),(0x20);
//>>>>   Wan,  Kilo, Hundred,   Ten,   One;
// -------------------------------------
// e.g.	__wUWord16ToWKHTO(0xFFF0);
// =====================================
void wUWord16ToWKHTO()
{
	_wan=_kilo=_hundred=0;
	while(inti_.value>9999){
		_wan++;
		inti_.value-=10000;
	};
	while(inti_.value>999){
		_kilo++;
		inti_.value-=1000;
	};
	while(inti_.value>99){
		_hundred++;
		inti_.value-=100;
	};
	while(sub_i>9){
		sub_j++;
		sub_i-=10;
	};
}
#define __UWord16ToWKHTO(inUWord16) (inti_.value=inUWord16, wUWord16ToWKHTO())

// =====================================
// Access core code condition: NA
// -------------------------------------
// Input: 
// Output: 
// Reg: (0x20-0x23) & FSR
// e.g.: __tools_sourceCopyToTarget(13,(UCHAR)&paraUserTopRep[0], (UCHAR)&eePicMem[0]);
// Description: SourceBlock copyTo TargetBlock
// =====================================
void mTools_SourceCopyToTarget()
{
	//Copy Source and Target Area in High Bank (bank2,3)
	__SetLBank(); //Access Low bank (bank0 & bank1) is default
	if(sysFsrHiBANK) __SetHBank();
	do{
		FSR = sub_j; sub_m=INDF;
		FSR = sub_k; INDF = sub_m;
		sub_j++; sub_k++;
	}while(--sub_i);
	sysFsrHiBANKoff; //resume default setting
}
#define __tools_sourceCopyToTarget(U8Size, U8SourcePtr, TargetPtr) \
					sub_i=U8Size; \
					sub_j=U8SourcePtr;\
					sub_k=TargetPtr;\
					mTools_SourceCopyToTarget();

// =====================================
// -------------------------------------
// Input: sub_i(20h)
// Output: sub_i(20h)
// Reg: i
// e.g.: __HiHalfByteConvertAscii(0xF1);
// Description: Convert 1Byte HiPart convert to Ascii
// =====================================
void iHiHalfByteConvertAscii()
{
	sub_i >>= 4;
	//Input less than 10
	if(sub_i > 9){
		sub_i += 0x37; //0Ah -> 41h ; the constant is 41h-0Ah=37h
	}
	//Input great than 9
	else{
		sub_i += '0'; //0 -> '0'
	}
}
#define __HiHalfByteConvertAscii(U8Byte) sub_i = U8Byte, iHiHalfByteConvertAscii();

// =====================================
// -------------------------------------
// Input: sub_i(20h)
// Output: sub_i(20h)
// Reg: i
// e.g.: __LoHalfByteConvertAscii(0xF1);
// Description: Convert 1Byte LoPart convert to Ascii
// =====================================
void iLoHalfByteConvertAscii()
{
	sub_i &= 0x0F;
	//Input less than 10
	if(sub_i > 9){
		sub_i += 0x37; //0Ah -> 41h ; the constant is 41h-0Ah=37h
	}
	//Input great than 9
	else{
		sub_i += '0'; //0 -> '0'
	}
}
#define __LoHalfByteConvertAscii(U8Byte) sub_i = U8Byte, iLoHalfByteConvertAscii();

// =====================================
// -------------------------------------
// Input: sub_i(20h)
// Output: NA
// Reg: i
// e.g.: __DelayUWord8Countdown(0x00); //This is maximum delay
// Description: Convert 1Byte LoPart convert to Ascii
// =====================================
void iDelayUWord8Countdown()
{
	do{}while(--sub_i);
}
#define __DelayUWord8Countdown(U8Byte) sub_i = U8Byte, iDelayUWord8Countdown();

//======================================
// -------------------------------------
// Input: i(20h), j(21h) and FSR
// Output: sub_k(22h) that is oldest data
// Reg: i,j,k,m(23h)
// e.g.: __UWord8PushIntoFifoBuffer(0x50, 0xAA, &USERBANK3);
// Description: 
// .. To push newData into Fifo's buffer
// .. The Fifo's buffer in bank2 or bank3
// =====================================
void mUWord8PushIntoFifoBuffer()
{
	__SetHBank(); // Fifo's buffer in bank2 or bank3
	FSR += sub_m = sub_i;
	sub_k = INDF;
	FSR --;
	do{
		__FSRW(); FSR ++;
		__WFSR(); FSR --; FSR --;
	} while (--sub_m);
	FSR ++;
	INDF = sub_j;
	//__SetLBank(); //Default Bank0,1
}
#define __UWord8PushIntoFifoBuffer(U8BufSize, U8NewData, U8Pointer) \
					sub_i = (U8BufSize-1); sub_j = U8NewData; FSR = U8Pointer;\
					mUWord8PushIntoFifoBuffer();

//======================================
// -------------------------------------
// Input: FSR
// Output: longi_ (20h..23h)
// Reg: u16n_ (24h..25) and sub_p (26h)
// e.g.: __UWord16SumOfBuffer(10
// Description: 
// .. sum of u16 buffer
// .. The Fifo's buffer in bank2 or bank3
// ** output longi_ (20h..23h)
// =====================================
void pUWord16SumOfBuffer()
{
	__SetHBank();
	longi_.value = 0;
	do{
		u16n_.icun[0].value = INDF; FSR ++; --sub_p;
		u16n_.icun[1].value = INDF; FSR ++;
		longi_.value += u16n_.value;
	}while(--sub_p);
}
#define __UWord16SumOfBuffer(U8BufSize, U8Pointer) \
					sub_p = U8BufSize; FSR = U8Pointer;\
					pUWord16SumOfBuffer();

/***************/
/* end of file */
/***************/

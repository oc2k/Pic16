//*************************************************************
//************************************************************* 

#ifndef _osPublic_H
#define _osPublic_H

	UCHAR sub_i  @0x20;
	UCHAR sub_j  @0x21;
	UCHAR sub_k  @0x22;
	UCHAR sub_m  @0x23;
	UCHAR sub_n  @0x24;
	UCHAR sub_o  @0x25;
	UCHAR sub_p  @0x26;
	UCHAR sub_q  @0x27;
	//>--
	UCHAR _one		@0x20;
	UCHAR _ten		@0x21;
	UCHAR _hundred	@0x22;
	UCHAR _kilo		@0x23;
	UCHAR _wan		@0x24;
	//>--
	CUN subi_    @0x20;
	CUN subj_    @0x21;
	CUN subk_    @0x22;
	CUN subm_    @0x23;
	CUN subn_    @0x24;
	CUN subo_    @0x25;
	CUN subp_    @0x26;
	CUN subq_    @0x27;
	//>--
	CUN u8O_    @0x20;
	CUN u8T_    @0x21;
	CUN u8H_    @0x22;
	CUN u8K_    @0x23;
	CUN u8W_    @0x24;
	//>--
	IUN u16i_    @0x20; //0x21,0x20
	IUN u16j_    @0x21; //0x22,0x21
	IUN u16k_    @0x22; //0x23,0x22
	IUN u16m_    @0x23; //0x24,0x23
	IUN u16n_    @0x24; //0x25,0x24
	IUN u16o_    @0x25; //0x26,0x25
	IUN u16p_    @0x26; //0x27,0x26
	//>--
	IUN inti_	 @0x20; //0x21,0x20
	FUN longi_	 @0x20; //0x23,0x22,0x21,0x20

////Be careful 0x71, C compiler(HiTech) Using save WREG in Interrupt
////Be careful 0x72, I Using Save FSR in Interrupt routine
	UCHAR temp_i @0x73;
	UCHAR temp_j @0x74;
	UCHAR temp_k @0x75;

	UCHAR temp_e @0x7e;
	UCHAR temp_f @0x7f;
	//>--
	CUN tempi_   @0x73;
	CUN tempj_   @0x74;
	CUN tempk_   @0x75;
	//>--
	IUN tempij_	 @0x73; //74,73

//======================================
//(2) file register defined
//======================================
	CUN sys; //,sys2,sys3;//, sav;
	UCHAR isrMs, isrHms; //Hms mean hundred msecond

//======================================
//(3) system flag
//======================================
// -sys- %%%%%%%%%%%Main Loop%%%%%%%%%%%%%
#define sysFsrHiBANK		sys.cb.zer //xxx
#define sysFsrHiBANKon			sysFsrHiBANK = 1
#define sysFsrHiBANKoff			sysFsrHiBANK = 0

// -sys- %%%%%%%%%%%Main Loop%%%%%%%%%%%%%
//efine sysFsrHiBANK		sys.cb.zer //xxx
// -sys2- %%%%%%%%%%%Main Loop%%%%%%%%%%%%%
// -sys3- %%%%%%%%%%%Main Loop%%%%%%%%%%%%%
// -para- %%%%%%%%%% save in eeprom %%%%%%%%%%%%%
#endif // !_osPublic_H


//*************************************************************

//************************************************************* 

#ifndef _perPicEE_H
#define _perPicEE_H

//======================================
//(1) define constant parameter
#define __constEePicMemSizeLIMIT            6 //15

//======================================
//(2) file register defined
	bank1	UCHAR eePicMem[__constEePicMemSizeLIMIT];


//======================================
//(3) system flag
// -para- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//(4) hardware defination
//(5) Macro defined
//(6) Function defination
//======================================
	void initPerPicEe_LoadingPara();

#endif // !_perPicEE_H

//======================================
// Persistence Pic eeprom block internal definations
//======================================
#define EEPROM_SIZE	256
// macro versions of EEPROM write and read
//#define	EEPROM_WRITE(addr, value) EEADRH=0; while(WR)continue;EEADR=(addr);EEDATA=(value); \
//					EECON1&=0x7F;CARRY=0;if(GIE)CARRY=1;GIE=0; \
//					WREN=1;EECON2=0x55;EECON2=0xAA;WR=1;WREN=0; \
//					if(CARRY)GIE=1;
//#define	EEPROM_READ(addr) ((EEADR=(addr)),(EECON1&=0x7F),(RD=1),EEDATA)

/********************************
void UserDefinedInChipEEprom()/**/

#define PROFILE 5	//[user change]
/* 5 type eeprom defination
//0 for profile 0
//1 for EEPROM counting 0 to 0xFF
//2 for EEPROM filled with zeros
//3 for EEPROM filled with user design.
//4 default status, all 0xFF
//5 project eeprom default value
/**/
#if (PROFILE!=0) && (PROFILE!=1) && (PROFILE!=2) && (PROFILE!=3) && (PROFILE!=4) && (PROFILE!=5)
	#error defined profile in eep_init.c must be 0-5
#endif

//[do not alter]
#asm
psect eedata,delta=2,abs,ovrld
	org 2100h
#endasm

#if (PROFILE==5)	//profile 5>> project eeprom
/**************************************************************
Parameter of iMotor
1) [00H]	para
2) [01H]	para1 Mean: Insert comment (default)
/**/
  //db 0x00,0x01; 0x02,0x03; 0x04,0x05; 0x06,0x07; 0x08,0x09; 0x0A,0x0B; 0x0C,0x0D; 0x0E,0x0F
#asm
	db 0x08
	db 0x06
	db 0x00
	db 0x30
	db 0x02
	db 0x00

	db 0x00

	db 0x00

	db 0x00
	db 0x00
	db 0x00
	db 0x00
	db 0x00
	db 0x00
	db 0x00

	db 0xFF
	db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
#endasm
#endif

#if (PROFILE==0)	//profile 0 --- debug "Simulator Trace"
	//db 0x00,0x01; 0x02,0x03; 0x04,0x05; 0x06,0x07; 0x08,0x09; 0x0A,0x0B; 0x0C,0x0D; 0x0E,0x0F
#asm
	  db 0x0C
	  db 0x06
	  db 0x05
	  db 0x04
	  db 0x03
	  db 0x02
  
	  db 0x01
  
	  db 0x07
  
	  db 0x08
	  db 0x09
	  db 0x0A
	  db 0x0B
	  db 0x0C
	  db 0x0D
	  db 0x0E
  
	  db 0x0F
	  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
	  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
#endasm
#endif

#if (PROFILE==1)	//profile 1
#asm
  db 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F 
  db 0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F 
  db 0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F 
  db 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F 
  db 0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F 
  db 0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F 
  db 0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F 
  db 0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F 
  db 0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F 
  db 0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F 
  db 0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF 
  db 0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF 
  db 0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF 
  db 0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF 
  db 0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF 
  db 0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF
#endasm
#endif

#if (PROFILE==2)	//fonttable backup.
#asm
  db ' ',' ','B','1',' ','1',' ','2',' ','3',' ','4',' ','5',' ','6'
  db ' ','7',' ','8',' ','9','1','0','1','1','1','2','1','3','1','4'
  db '1','5','1','6','1','7','1','8','1','9','2','0','2','1','2','2'
  db '2','3','2','4','2','5','2','6','2','7','2','8','2','9','3','0'
  db '3','1','3','2','3','3','3','4','3','5','3','6','3','7','3','8'
  db '3','9','4','0','4','1','4','2','4','3','4','4','4','5','4','6'
  db '4','7','4','8','4','9','5','0','5','1','5','2','5','3','5','4'
  db '5','5','5','6','5','7','5','8','5','9','6','0','6','1','6','2'
  db 0x40,0x0,'B','1',' ','1',' ','2',' ','3',' ','4',' ','5',' ','6'
  db ' ','7',' ','8',' ','9','1','0','1','1','1','2','1','3','1','4'
  db '1','5','1','6','1','7','1','8','1','9','2','0','2','1','2','2'
  db '2','3','2','4','2','5','2','6','2','7','2','8','2','9','3','0'
  db '3','1','3','2','3','3','3','4','3','5','3','6','3','7','3','8'
  db '3','9','4','0','4','1','4','2','4','3','4','4','4','5','4','6'
  db '4','7','4','8','4','9','5','0','5','1','5','2','5','3','5','4'
  db '5','5','5','6','5','7','5','8','5','9','6','0','6','1','6','2'
#endasm
#endif

#if (PROFILE==3)	//profile 3
#asm
;;;->|  00  |<-01->|   02   |<-03->|   04   |<-05->|   06   |<-07->|
  db ' ',' ','B',' ',' ','1',' ','2',' ','3',' ','4',' ','5',' ','6'
  db ' ','7',' ','8',' ','9','1','0','1','1','1','2','1','3','1','4'
  db '1','5','1','6','@','@','@','@','@','@','@','@','@','@','@','@'
  db '@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@'
  db '@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@'
  db '@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@'
  db '@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@'
  db '@','@','@','@','@','@','@','@','@','@','@','@','@','@','@','@'
;->| faultbit, 0   |<-01->|   02   |<-03->|   04   |<-05->|   06   |<-07->|
  db 0x40,0x0,'B',' ',' ','1',' ','2',' ','3',' ','4',' ','5',' ','6'
  db ' ','7',' ','8',' ','9','1','0','1','1','1','2','1','3','1','4'
  db '1','5','1','6','1','7','1','8','1','9','2','0','2','1','2','2'
  db '2','3','2','4','2','5','2','6','2','7','2','8','2','9','3','0'
  db '3','1','3','2','3','3','3','4','3','5','3','6','3','7','3','8'
  db '3','9','4','0','4','1','4','2','4','3','4','4','4','5','4','6'
  db '4','7','4','8','4','9','5','0','5','1','5','2','5','3','5','4'
  db '5','5','5','6','5','7','5','8','5','9','6','0','6','1','6','2'
#endasm
#endif

#if (PROFILE==4)	//profile 4 >>all 0xFF default status
#asm
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF 
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF 
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF 
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF 
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF 
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF 
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF 
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF 
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF 
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF 
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF 
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF 
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF 
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF 
  db 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
#endasm
#endif

/*End of picee.h */

//*************************************************************
//       Timing processing GUIDELINE
//*************************************************************
#ifndef _perPicEE_H_isr
#define _perPicEE_H_isr
#endif //!_perPicEE_H_isr

//************************************************************* 
// (2) Timing process in osSysClock, e.g.: #define SciSysclkTmr1() __clkSciPcMsgHmsCountdown();
//************************************************************* 
#ifndef _perPicEE_H_sysClk
#define _perPicEE_H_sysClk
#endif //!_perPicEE_H_sysClk

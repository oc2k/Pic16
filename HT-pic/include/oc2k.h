//----------------------------------------------------------------------//
//	HiTech head file(H2oc2k.LIB) 	Version: 23 April 2004				//
//	HiTech head file(H1oc2k.LIB) 	Version: 19 Aug.  2002				//
//	Come from H2oc2k.h		>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//  Store position:                                                     //
//                 \!C16-icd2\                                          //
//                 \Cdrom(2)\_1_installation\9)Microchip-PIC            //
//                 \Pic\HT-PIC\include                                  //
//----------------------------------------------------------------------//
#ifndef oc2k_H
#define oc2k_H
#endif
/* =====================================================================*
 *	Revision History													*
 *	Rev   Date         Reason											*
 *	----  -----------  -----------------								*
 *	1.00  20/02/2002   Initial Creation									*
 *	1.01  04/05/2002   assemble	express									*
 *	1.02  24/05/2002   additional temp register for hitech function.	*
 *	1.03  05/06/2002   additional __SWAPF(x,f)							*
 *	1.04  01/07/2002   additional __IF & __IFN							*
 *	1.05  14/07/2002   additional bit control(__BITSET, __BITCLR), GOTO	*
 *	1.06  14/07/2002   additional define control (RETURNCOM)			*
 *	1.07  06/08/2002   join to common struct and union					*
 *	1.08  05/09/2002   __CALL ADDITIONAL								*
 *	1.09  29/11/2002   addtional temp bit define is "tempx_"			*
 *	1.10  26/12/2002   addtional INDF bit define is "indf_"				*
 *	2.01  23/04/2004   remove sub and temp register,                    *
 *                     modify CUN,IUN,TUN,FUN define                    *
 *                     Add> PORTBIT(adr,bit)                            *
 *	3.01  05/09/2004
 *	5.01  10/08/2007
 * ==================================================================== *
 *	oc2k Revision History													*
 *	Rev   Date         Reason											*
 * ==================================================================== *
void __Assembler()
/**/
static volatile	unsigned char bank1	USERBANK1	@ 0xA0;//Version 1.01...
static volatile	unsigned char bank2	USERBANK2	@ 0x110;
static volatile	unsigned char bank3	USERBANK3	@ 0x190;
//===== Assembler Macros =================================================
#define	__SLEEP()			asm(" sleep")
#define	__CLRWDT()			asm(" clrwdt")
#define	__NOP()				asm(" nop")
#define __CLRW()			asm(" clrw")
/////==> can use <<<<<"INDF">>>>>
#define __WFSR()			asm(" movwf 0")
#define __FSRW()			asm(" movf 0,W")

#define	___mkstr1(x)		#x
#define	___mkstr(x)			___mkstr1(x)

/////////////////////////////////////////////////// ==> #define __ORG(k)	asm(" org " ___mkstr(k))
/////////////////////////////////////////////////// ==> #define __GOTO(k)	asm(" goto "___mkstr(k))
#ifndef RETURNCOM
	#error	define above.
#elif	RETURNCOM == 1
	#define __GOTO(k)			asm(" goto "___mkstr(k))
	#define __RETURN()			asm(" return ")
	#define __RETFIE()			asm(" retfie ")
#endif
#define __RETLW(k)			asm(" retlw "___mkstr(k))

//#define __LABEL(k)			asm(___mkstr(k)"_:")
//#define __WHILEINC(f,d,k)	asm(" incfsz " ___mkstr(f)"," ___mkstr(d));\
//							goto (k);
//#define __WHILEDEC(f,d,k)	asm(" decfsz " ___mkstr(f)"," ___mkstr(d));\
//							goto (k);

#define __CALL(k)			asm(" call "___mkstr(k))
#define __CLRF(f)			asm(" clrf "___mkstr(f))

#define __SWAPF(f,d)     	asm(" swapf "___mkstr(f)","___mkstr(d))
#define __MOVF(f,d)     	asm(" movf "___mkstr(f)","___mkstr(d))
#define __MOVLW(k)			asm(" movlw "___mkstr(k))
#define __MOVWF(f)			asm(" movwf "___mkstr(f))

#define __INCF(f,d)     	asm(" incf "___mkstr(f)","___mkstr(d))
#define __DECF(f,d)     	asm(" decf "___mkstr(f)","___mkstr(d))

#define __INCFSZ(f,d)   	asm(" incfsz "___mkstr(f)","___mkstr(d))
#define __DECFSZ(f,d)   	asm(" decfsz "___mkstr(f)","___mkstr(d))

#define __ADDLW(k)			asm(" addlw "___mkstr(k))
#define __SUBLW(k)			asm(" sublw "___mkstr(k))

#define __ADDWF(f,d)    	asm(" addwf "___mkstr(f)","___mkstr(d))
#define __SUBWF(f,d)    	asm(" subwf "___mkstr(f)","___mkstr(d))

#define __COMF(f,d)     	asm(" comf  "___mkstr(f)","___mkstr(d))
#define __IORWF(f,d)    	asm(" iorwf "___mkstr(f)","___mkstr(d))
#define __IORLW(k)			asm(" iorlw "___mkstr(k))
#define __XORWF(f,d)	    asm(" xorwf "___mkstr(f)","___mkstr(d))
#define __XORLW(k)			asm(" xorlw "___mkstr(k))
#define __ANDWF(f,d)    	asm(" andwf "___mkstr(f)","___mkstr(d))
#define __ANDLW(k)			asm(" andlw "___mkstr(k))

#define __RLF(f,d)			asm(" rlf "___mkstr(f)","___mkstr(d))
#define __RRF(f,d)			asm(" rrf "___mkstr(f)","___mkstr(d))

#define __BCF(f,b)			asm(" bcf "___mkstr(f)","___mkstr(b))
#define __BSF(f,b)			asm(" bsf "___mkstr(f)","___mkstr(b))
#define __BTFSC(f,b)		asm(" btfsc " ___mkstr(f)","___mkstr(b))
#define __BTFSS(f,b)		asm(" btfss " ___mkstr(f)","___mkstr(b))

#define __SetHBank()		asm(" bsf 0x3, 7 ")
/////==> IRP = 1;
#define __SetLBank()		asm(" bcf 0x3, 7 ")
/////==> IRP = 0;
#define __IF_CARRY()		__BTFSC(_STATUS, 0)
#define __IFN_CARRY()		__BTFSS(_STATUS, 0)
#define __IF_DC()			__BTFSC(_STATUS, 1)
#define __IFN_DC()			__BTFSS(_STATUS, 1)
#define __IF_ZERO()			__BTFSC(_STATUS, 2)
#define __IFN_ZERO()		__BTFSS(_STATUS, 2)

//Version: 1.06 additional here.
#define __BITSET(var,bitno) ((var) |= 1 << (bitno))
#define __BITCLR(var,bitno) ((var) &= ~(1 << (bitno)))
//#define	max(a,b)		(((a) > (b)) ? (a) : (b))
//#define	min(a,b)		(((a) < (b)) ? (a) : (b))

//Version: 2.01 additional below
#define	PORTBIT(adr, bit)	((unsigned)(&adr)*8+(bit)) //Ver2.01
typedef	unsigned char	UCHAR;
typedef	unsigned int	UINT;

/* ===================================================================== *
 *  UCHAR, UINT                                                          *
 *  CBIT, CUN, IUN, TUN, FUN,                                            *
 * ===================================================================== *
//h1oc2k.h>>>Version: 1.01 join to here.
//h2oc2k.h>>>Version: 1.01 join to here.
void Union_Struct()
/**///CBIT, CUN, IUN, TUN, FUN,
typedef	struct cbittag{
        char zer:   1;
        char one:   1;
        char two:   1;
        char thr:   1;
        char fou:   1;
        char fiv:   1;
        char six:   1;
        char sev:   1;
}CBIT;

typedef	union cuntag{
		UCHAR	value;
        CBIT cb;
}CUN;

typedef	union iuntag{
		UINT	value;
		CUN		icun[2];
}IUN;

typedef	union tuntag{
		unsigned short int value;
		IUN tiun[1];
		CUN tcun[3];
}TUN;

typedef	union funtag{
		unsigned long int value;
		TUN ftun[1];
		IUN fiun[2];
		CUN fcun[4];
}FUN;

// -- Add "oc2k (Rev1.01)"
typedef	union duntag{
		double value;
		unsigned long hexVal;
		CUN dcun[4];
}DUN;



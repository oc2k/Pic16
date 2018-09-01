 /*
  * #ifndef	_HTC_H_
  * #warning Header file pic16f887.h included directly. Use #include <htc.h> instead.
  * #endif

  * header file for the MICROCHIP PIC microcontroller
  *	16F882
  * 16F883
  * 16F884
  * 16F886
  * 16F887
  */
/////////////////////////////////////////////////////////////////////////////////////
////History//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
// -2008 July31-  Copy from new HitechC and Reference Pic1687x.h ////////////////////
// -2008 Aug12-  ErrCode for WDTCON-CM2CON1  ////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#if defined(_16F882)	|| defined(_16F883)	|| defined(_16F884)	||\
    defined(_16F886)	|| defined(_16F887)
#else
#error "Wrong Pic"
#endif
#ifndef	__PIC16F88x_H
#define	__PIC16F88x_H

// Special function register definitions

static volatile unsigned char	INDF	@ 0x00;
static volatile unsigned char	TMR0	@ 0x01;
static volatile unsigned char	PCL	@ 0x02;
static volatile unsigned char	STATUS	@ 0x03;
static          unsigned char	FSR	@ 0x04;
static volatile unsigned char	PORTA	@ 0x05;
static volatile unsigned char	PORTB	@ 0x06;
static volatile unsigned char	PORTC	@ 0x07;
#if defined(_16F884) || defined(_16F887)
static volatile unsigned char	PORTD	@ 0x08;
#endif
static volatile unsigned char		PORTE	@ 0x09;
static          unsigned char	PCLATH	@ 0x0A;
static volatile unsigned char	INTCON	@ 0x0B;
static volatile unsigned char	PIR1	@ 0x0C;
static volatile unsigned char	PIR2	@ 0x0D;
static volatile unsigned char	TMR1L	@ 0x0E;
static volatile unsigned char	TMR1H	@ 0x0F;
static volatile unsigned char	T1CON	@ 0x10;
static volatile unsigned char	TMR2	@ 0x11;
static volatile unsigned char	T2CON	@ 0x12;
static volatile unsigned char	SSPBUF	@ 0x13;
static volatile unsigned char	SSPCON	@ 0x14;
static volatile unsigned char	CCPR1L	@ 0x15;
static volatile unsigned char	CCPR1H	@ 0x16;
static volatile unsigned char	CCP1CON	@ 0x17;
static volatile unsigned char	RCSTA	@ 0x18;
static volatile unsigned char	TXREG	@ 0x19;
static volatile unsigned char	RCREG	@ 0x1A;
static volatile unsigned char	CCPR2L	@ 0x1B;
static volatile unsigned char	CCPR2H	@ 0x1C;
static volatile unsigned char	CCP2CON	@ 0x1D;
static volatile unsigned char	ADRESH	@ 0x1E;
static volatile unsigned char	ADCON0	@ 0x1F;

/*	bank 1 registers */
static          unsigned char bank1	OPTION	@ 0x81;
static volatile	unsigned char bank1	TRISA	@ 0x85;
static volatile	unsigned char bank1	TRISB	@ 0x86;
static volatile	unsigned char bank1	TRISC	@ 0x87;
#if defined(_16F884) || defined(_16F887)
static volatile unsigned char bank1	TRISD	@ 0x88;
#endif
static volatile unsigned char bank1	TRISE	@ 0x89;
static volatile unsigned char bank1	PIE1	@ 0x8C;
static volatile unsigned char bank1	PIE2	@ 0x8D;
static volatile unsigned char bank1	PCON	@ 0x8E;
static volatile unsigned char bank1 OSCCON		@ 0x08F; //88x
static volatile unsigned char bank1 OSCTUNE		@ 0x090; //88x
static volatile unsigned char bank1	SSPCON2	@ 0x91;
static volatile unsigned char bank1	PR2	@ 0x92;
static volatile unsigned char bank1	SSPADD	@ 0x93;
//static volatile unsigned char bank1 SSPMSK	@ 0x093; //88x
static volatile unsigned char bank1	SSPSTAT	@ 0x94;
static volatile unsigned char bank1 WPUB		@ 0x095; //88x
static volatile unsigned char bank1 IOCB		@ 0x096; //88x
static volatile unsigned char bank1	VRCON		@ 0x097; //88x
static volatile unsigned char bank1	TXSTA	@ 0x98;
static volatile unsigned char bank1	SPBRG	@ 0x99;
static volatile unsigned char bank1	SPBRGH		@ 0x09A; //88x
static volatile unsigned char bank1	PWM1CON		@ 0x09B; //88x
static volatile unsigned char bank1	ECCPAS		@ 0x09C; //88x
static volatile unsigned char bank1	PSTRCON		@ 0x09D; //88x
static volatile unsigned char bank1	ADRESL	@ 0x9E;
static volatile unsigned char bank1	ADCON1	@ 0x9F;
/*	bank 2 registers */
static volatile unsigned char bank2	WDTCON		@ 0x105; //88x
static volatile unsigned char bank2	CM1CON0		@ 0x107; //88x
static volatile unsigned char bank2	CM2CON0		@ 0x108; //88x
static volatile unsigned char bank2	CM2CON1		@ 0x109; //88x
static volatile unsigned char bank2	EEDAT		@ 0x10C; //88x
/* Alternate definition */
static volatile unsigned char bank2	EEDATA	@ 0x10C;
static volatile unsigned char bank2	EEADR	@ 0x10D;
/* Alternate definition */
static volatile unsigned char bank2	EEADRL		@ 0x10D; //88x
static volatile unsigned char bank2	EEDATH	@ 0x10E;
static volatile unsigned char bank2	EEADRH	@ 0x10F;

/*	bank 3 registers */
static volatile unsigned char bank3	SRCON		@ 0x185; //88x
static volatile unsigned char bank3	BAUDCTL		@ 0x187; //88x
static volatile unsigned char bank3	ANSEL		@ 0x188; //88x
static volatile unsigned char bank3	ANSELH		@ 0x189; //88x
static volatile unsigned char bank3	EECON1	@ 0x18C;
static volatile unsigned char bank3	EECON2	@ 0x18D;

/*	STATUS bits	*/
/* Definitions for STATUS register */
static volatile bit	IRP     @ (unsigned)&STATUS*8+7;
static volatile bit	RP1     @ (unsigned)&STATUS*8+6;
static volatile bit	RP0     @ (unsigned)&STATUS*8+5;
static volatile bit	TO	@ (unsigned)&STATUS*8+4;
static volatile bit	PD	@ (unsigned)&STATUS*8+3;
static volatile bit	ZERO    @ (unsigned)&STATUS*8+2;
static volatile bit	DC      @ (unsigned)&STATUS*8+1;
static volatile bit	CARRY   @ (unsigned)&STATUS*8+0;

/*      PORTA bits      */
/* Definitions for PORTA register */
static volatile bit	RA7				@ ((unsigned)&PORTA*8)+7; //88x
static volatile bit	RA6				@ ((unsigned)&PORTA*8)+6; //88x
static volatile bit	RA5	@ (unsigned)&PORTA*8+5;
static volatile bit	RA4	@ (unsigned)&PORTA*8+4;
static volatile bit	RA3	@ (unsigned)&PORTA*8+3;
static volatile bit	RA2	@ (unsigned)&PORTA*8+2;
static volatile bit	RA1	@ (unsigned)&PORTA*8+1;
static volatile bit	RA0	@ (unsigned)&PORTA*8+0;

/*      PORTB bits      */
/* Definitions for PORTB register */
static volatile bit	RB7	@ (unsigned)&PORTB*8+7;
static volatile bit	RB6	@ (unsigned)&PORTB*8+6;
static volatile bit	RB5	@ (unsigned)&PORTB*8+5;
static volatile bit	RB4	@ (unsigned)&PORTB*8+4;
static volatile bit	RB3	@ (unsigned)&PORTB*8+3;
static volatile bit	RB2	@ (unsigned)&PORTB*8+2;
static volatile bit	RB1	@ (unsigned)&PORTB*8+1;
static volatile bit	RB0	@ (unsigned)&PORTB*8+0;

/*      PORTC bits      */
/* Definitions for PORTC register */
static volatile bit	RC7	@ (unsigned)&PORTC*8+7;
static volatile bit	RC6	@ (unsigned)&PORTC*8+6;
static volatile bit	RC5	@ (unsigned)&PORTC*8+5;
static volatile bit	RC4	@ (unsigned)&PORTC*8+4;
static volatile bit	RC3	@ (unsigned)&PORTC*8+3;
static volatile bit	RC2	@ (unsigned)&PORTC*8+2;
static volatile bit	RC1	@ (unsigned)&PORTC*8+1;
static volatile bit	RC0	@ (unsigned)&PORTC*8+0;

/*      PORTD bits      */
#if defined(_16F884) || defined(_16F887)
/* Definitions for PORTD register */
static volatile bit	RD7	@ (unsigned)&PORTD*8+7;
static volatile bit	RD6	@ (unsigned)&PORTD*8+6;
static volatile bit	RD5	@ (unsigned)&PORTD*8+5;
static volatile bit	RD4	@ (unsigned)&PORTD*8+4;
static volatile bit	RD3	@ (unsigned)&PORTD*8+3;
static volatile bit	RD2	@ (unsigned)&PORTD*8+2;
static volatile bit	RD1	@ (unsigned)&PORTD*8+1;
static volatile bit	RD0	@ (unsigned)&PORTD*8+0;

/*      PORTE bits      */
/* Definitions for PORTE register */
static volatile bit	RE2	@ (unsigned)&PORTE*8+2;
static volatile bit	RE1	@ (unsigned)&PORTE*8+1;
static volatile bit	RE0	@ (unsigned)&PORTE*8+0;
#endif
static volatile bit	RE3			@ ((unsigned)&PORTE*8)+3; //88x

/*	INTCON bits	*/
/* Definitions for INTCON register */
static volatile bit	GIE	@ (unsigned)&INTCON*8+7;
static volatile bit	PEIE	@ (unsigned)&INTCON*8+6;
static volatile bit	T0IE	@ (unsigned)&INTCON*8+5;
static volatile bit	INTE	@ (unsigned)&INTCON*8+4;
// Alternate definition for backward compatibility
//static volatile bit	RABIE		@ ((unsigned)&INTCON*8)+3; //88x
static volatile bit	RBIE	@ (unsigned)&INTCON*8+3;
static volatile bit	T0IF	@ (unsigned)&INTCON*8+2;
static volatile bit	INTF	@ (unsigned)&INTCON*8+1;
static volatile bit	RBIF	@ (unsigned)&INTCON*8+0;
// alternate definitions
static volatile bit	TMR0IE	@ (unsigned)&INTCON*8+5;
static volatile bit	TMR0IF	@ (unsigned)&INTCON*8+2;
// Alternate definition for backward compatibility
//static volatile bit	RABIF		@ ((unsigned)&INTCON*8)+0; //88x

/*	PIR1 bits	*/
/* Definitions for PIR1 register */
//static volatile bit	PSPIF	@ (unsigned)&PIR1*8+7; //87x
static volatile bit	ADIF	@ (unsigned)&PIR1*8+6;
static volatile bit	RCIF	@ (unsigned)&PIR1*8+5;
static volatile bit	TXIF	@ (unsigned)&PIR1*8+4;
static volatile bit	SSPIF	@ (unsigned)&PIR1*8+3;
static volatile bit	CCP1IF	@ (unsigned)&PIR1*8+2;
static volatile bit	TMR2IF	@ (unsigned)&PIR1*8+1;
static volatile bit	TMR1IF	@ (unsigned)&PIR1*8+0;

/*	PIR2 bits	*/
/* Definitions for PIR2 register */
static volatile bit	OSFIF			@ ((unsigned)&PIR2*8)+7; //88x
static volatile bit	C2IF			@ ((unsigned)&PIR2*8)+6; //88x
static volatile bit	C1IF			@ ((unsigned)&PIR2*8)+5; //88x
static volatile bit	EEIF	@ (unsigned)&PIR2*8+4;
static volatile bit	BCLIF	@ (unsigned)&PIR2*8+3;
static volatile bit	ULPWUIF			@ ((unsigned)&PIR2*8)+2; //88x
static volatile bit	CCP2IF	@ (unsigned)&PIR2*8+0;

/*	T1CON bits	*/
/* Definitions for T1CON register */
static			bit	T1GINV			@ ((unsigned)&T1CON*8)+7; //88x
static			bit	TMR1GE			@ ((unsigned)&T1CON*8)+6; //88x
static volatile bit	T1CKPS1	@ (unsigned)&T1CON*8+5;
static volatile bit	T1CKPS0	@ (unsigned)&T1CON*8+4;
static volatile bit	T1OSCEN	@ (unsigned)&T1CON*8+3;
static volatile bit	T1SYNC 	@ (unsigned)&T1CON*8+2;
static volatile bit	TMR1CS 	@ (unsigned)&T1CON*8+1;
static volatile bit	TMR1ON 	@ (unsigned)&T1CON*8+0;

/*	T2CON bits	*/
/* Definitions for T2CON register */
static volatile bit	TOUTPS3	@ (unsigned)&T2CON*8+6;
static volatile bit	TOUTPS2	@ (unsigned)&T2CON*8+5;
static volatile bit	TOUTPS1	@ (unsigned)&T2CON*8+4;
static volatile bit	TOUTPS0	@ (unsigned)&T2CON*8+3;
static volatile bit	TMR2ON 	@ (unsigned)&T2CON*8+2;
static volatile bit	T2CKPS1	@ (unsigned)&T2CON*8+1;
static volatile bit	T2CKPS0	@ (unsigned)&T2CON*8+0;

/*	SSPCON bits	*/
/* Definitions for SSPCON register */
static volatile bit	WCOL	@ (unsigned)&SSPCON*8+7;
static volatile bit	SSPOV	@ (unsigned)&SSPCON*8+6;
static volatile bit	SSPEN	@ (unsigned)&SSPCON*8+5;
static volatile bit	CKP	@ (unsigned)&SSPCON*8+4;
static volatile bit	SSPM3	@ (unsigned)&SSPCON*8+3;
static volatile bit	SSPM2	@ (unsigned)&SSPCON*8+2;
static volatile bit	SSPM1	@ (unsigned)&SSPCON*8+1;
static volatile bit	SSPM0	@ (unsigned)&SSPCON*8+0;

/*	CCP1CON bits	*/
/* Definitions for CCP1CON register */
static			bit	P1M1			@ ((unsigned)&CCP1CON*8)+7; //88x
static			bit	P1M0			@ ((unsigned)&CCP1CON*8)+6; //88x
static			bit	DC1B1			@ ((unsigned)&CCP1CON*8)+5; //88x
static			bit	DC1B0			@ ((unsigned)&CCP1CON*8)+4; //88x
//static volatile bit	CCP1X	@ (unsigned)&CCP1CON*8+5; //87x
//static volatile bit	CCP1Y	@ (unsigned)&CCP1CON*8+4; //87x
static volatile bit	CCP1M3	@ (unsigned)&CCP1CON*8+3;
static volatile bit	CCP1M2	@ (unsigned)&CCP1CON*8+2;
static volatile bit	CCP1M1	@ (unsigned)&CCP1CON*8+1;
static volatile bit	CCP1M0	@ (unsigned)&CCP1CON*8+0;

/*	RCSTA bits	*/
/* Definitions for RCSTA register */
static volatile bit	SPEN	@ (unsigned)&RCSTA*8+7;
static volatile bit	RX9 	@ (unsigned)&RCSTA*8+6;
static volatile bit	SREN	@ (unsigned)&RCSTA*8+5;
static volatile bit	CREN	@ (unsigned)&RCSTA*8+4;
static volatile bit	ADDEN	@ (unsigned)&RCSTA*8+3;
static volatile bit	FERR	@ (unsigned)&RCSTA*8+2;
static volatile bit	OERR	@ (unsigned)&RCSTA*8+1;
static volatile bit	RX9D	@ (unsigned)&RCSTA*8+0;

/*	CCP2CON bits	*/
/* Definitions for CCP2CON register */
static volatile bit	CCP2X	@ (unsigned)&CCP2CON*8+5;
static volatile bit	CCP2Y	@ (unsigned)&CCP2CON*8+4;
static volatile bit	CCP2M3	@ (unsigned)&CCP2CON*8+3;
static volatile bit	CCP2M2	@ (unsigned)&CCP2CON*8+2;
static volatile bit	CCP2M1	@ (unsigned)&CCP2CON*8+1;
static volatile bit	CCP2M0	@ (unsigned)&CCP2CON*8+0;

/*	 ADCON0 bits	*/
/* Definitions for ADCON0 register */
static volatile bit	ADCS1	@ (unsigned)&ADCON0*8+7;
static volatile bit	ADCS0 	@ (unsigned)&ADCON0*8+6;
static volatile bit	CHS3			@ (unsigned)&ADCON0*8+5; //88x
static volatile bit	CHS2			@ (unsigned)&ADCON0*8+4; //88x
static volatile bit	CHS1			@ (unsigned)&ADCON0*8+3; //88x
static volatile bit	CHS0			@ (unsigned)&ADCON0*8+2; //88x
static volatile bit	ADGO			@ (unsigned)&ADCON0*8+1; //88x
static volatile bit	ADON	@ (unsigned)&ADCON0*8+0;

/* 	OPTION bits	*/
/* Definitions for OPTION register */
//static bank1 bit	RABPU			@ ((unsigned)&OPTION*8)+7; //88x
// Alternate definition for backward compatibility
static bank1 bit	RBPU	@ (unsigned)&OPTION*8+7;
static bank1 bit	INTEDG	@ (unsigned)&OPTION*8+6;
static bank1 bit	T0CS	@ (unsigned)&OPTION*8+5;
static bank1 bit	T0SE	@ (unsigned)&OPTION*8+4;
static bank1 bit	PSA	@ (unsigned)&OPTION*8+3;
static bank1 bit	PS2	@ (unsigned)&OPTION*8+2;
static bank1 bit	PS1	@ (unsigned)&OPTION*8+1;
static bank1 bit	PS0	@ (unsigned)&OPTION*8+0;

/*      TRISA bits      */
/* Definitions for TRISA register */
static volatile bank1 bit	TRISA7		@ ((unsigned)&TRISA*8)+7; //88x
static volatile bank1 bit	TRISA6		@ ((unsigned)&TRISA*8)+6; //88x
static volatile bank1 bit	TRISA5	@ (unsigned)&TRISA*8+5;
static volatile bank1 bit	TRISA4	@ (unsigned)&TRISA*8+4;
static volatile bank1 bit	TRISA3	@ (unsigned)&TRISA*8+3;
static volatile bank1 bit	TRISA2	@ (unsigned)&TRISA*8+2;
static volatile bank1 bit	TRISA1	@ (unsigned)&TRISA*8+1;
static volatile bank1 bit	TRISA0	@ (unsigned)&TRISA*8+0;

/*      TRISB bits      */
/* Definitions for TRISB register */
static volatile bank1 bit	TRISB7	@ (unsigned)&TRISB*8+7;
static volatile bank1 bit	TRISB6	@ (unsigned)&TRISB*8+6;
static volatile bank1 bit	TRISB5	@ (unsigned)&TRISB*8+5;
static volatile bank1 bit	TRISB4	@ (unsigned)&TRISB*8+4;
static volatile bank1 bit	TRISB3	@ (unsigned)&TRISB*8+3;
static volatile bank1 bit	TRISB2	@ (unsigned)&TRISB*8+2;
static volatile bank1 bit	TRISB1	@ (unsigned)&TRISB*8+1;
static volatile bank1 bit	TRISB0	@ (unsigned)&TRISB*8+0;

/*      TRISC bits      */
/* Definitions for TRISC register */
static volatile bank1 bit	TRISC7	@ (unsigned)&TRISC*8+7;
static volatile bank1 bit	TRISC6	@ (unsigned)&TRISC*8+6;
static volatile bank1 bit	TRISC5	@ (unsigned)&TRISC*8+5;
static volatile bank1 bit	TRISC4	@ (unsigned)&TRISC*8+4;
static volatile bank1 bit	TRISC3	@ (unsigned)&TRISC*8+3;
static volatile bank1 bit	TRISC2	@ (unsigned)&TRISC*8+2;
static volatile bank1 bit	TRISC1	@ (unsigned)&TRISC*8+1;
static volatile bank1 bit	TRISC0	@ (unsigned)&TRISC*8+0;

#if defined(_16F884) || defined(_16F887)
/*      TRISD bits      */
/* Definitions for TRISD register */
static volatile bank1 bit	TRISD7	@ (unsigned)&TRISD*8+7;
static volatile bank1 bit	TRISD6	@ (unsigned)&TRISD*8+6;
static volatile bank1 bit	TRISD5	@ (unsigned)&TRISD*8+5;
static volatile bank1 bit	TRISD4	@ (unsigned)&TRISD*8+4;
static volatile bank1 bit	TRISD3	@ (unsigned)&TRISD*8+3;
static volatile bank1 bit	TRISD2	@ (unsigned)&TRISD*8+2;
static volatile bank1 bit	TRISD1	@ (unsigned)&TRISD*8+1;
static volatile bank1 bit	TRISD0	@ (unsigned)&TRISD*8+0;

/*      TRISE bits      */
/* Definitions for TRISE register */
//static volatile bank1 bit	IBF			@ (unsigned)&TRISE*8+7; //87x
//static volatile bank1 bit	OBF			@ (unsigned)&TRISE*8+6; //87x
//static volatile bank1 bit	IBOV		@ (unsigned)&TRISE*8+5; //87x
//static volatile bank1 bit	PSPMODE		@ (unsigned)&TRISE*8+4; //87x
static volatile bank1 bit	TRISE2  @ (unsigned)&TRISE*8+2;
static volatile bank1 bit	TRISE1  @ (unsigned)&TRISE*8+1;
static volatile bank1 bit	TRISE0  @ (unsigned)&TRISE*8+0;
#endif
static volatile bank1 bit	TRISE3	  @ (unsigned)&TRISE*8+3; //88x

/*	PIE1 bits	*/
/* Definitions for PIE1 register */
//static volatile bank1 bit	PSPIE		@ (unsigned)&PIE1*8+7; //87x
static volatile bank1 bit	ADIE	@ (unsigned)&PIE1*8+6;
static volatile bank1 bit	RCIE	@ (unsigned)&PIE1*8+5;
static volatile bank1 bit	TXIE	@ (unsigned)&PIE1*8+4;
static volatile bank1 bit	SSPIE	@ (unsigned)&PIE1*8+3;
static volatile bank1 bit	CCP1IE	@ (unsigned)&PIE1*8+2;
static volatile bank1 bit	TMR2IE	@ (unsigned)&PIE1*8+1;
static volatile bank1 bit	TMR1IE	@ (unsigned)&PIE1*8+0;

/*	PIE2 bits	*/
/* Definitions for PIE2 register */
static volatile bank1 bit	OSFIE		@ ((unsigned)&PIE2*8)+7; //88x
static volatile bank1 bit	C2IE		@ ((unsigned)&PIE2*8)+6; //88x
static volatile bank1 bit	C1IE		@ ((unsigned)&PIE2*8)+5; //88x
static volatile bank1 bit	EEIE	@ (unsigned)&PIE2*8+4;
static volatile bank1 bit	BCLIE	@ (unsigned)&PIE2*8+3;
static volatile bank1 bit	ULPWUIE		@ ((unsigned)&PIE2*8)+2; //88x
static volatile bank1 bit	CCP2IE	@ (unsigned)&PIE2*8+0;

/*	PCON bits	*/
/* Definitions for PCON register */
static volatile bank1 bit	ULPWUE		@ ((unsigned)&PCON*8)+5; //88x
static volatile bank1 bit	SBOREN		@ ((unsigned)&PCON*8)+4; //88x
static volatile bank1 bit	POR	@ (unsigned)&PCON*8+1;	
static volatile bank1 bit	BOR	@ (unsigned)&PCON*8+0;	

/* Definitions for OSCCON register */
static 			bank1 bit	IRCF2		@ ((unsigned)&OSCCON*8)+6;
static 			bank1 bit	IRCF1		@ ((unsigned)&OSCCON*8)+5;
static 			bank1 bit	IRCF0		@ ((unsigned)&OSCCON*8)+4;
static volatile bank1 bit	OSTS		@ ((unsigned)&OSCCON*8)+3; //88x
static volatile bank1 bit	HTS			@ ((unsigned)&OSCCON*8)+2; //88x
static volatile bank1 bit	LTS			@ ((unsigned)&OSCCON*8)+1; //88x
static 			bank1 bit	SCS		@ ((unsigned)&OSCCON*8)+0;

/* Definitions for OSCTUNE register */
static 			bank1 bit	TUN4		@ ((unsigned)&OSCTUNE*8)+4; //88x
static 			bank1 bit	TUN3		@ ((unsigned)&OSCTUNE*8)+3; //88x
static 			bank1 bit	TUN2		@ ((unsigned)&OSCTUNE*8)+2; //88x
static 			bank1 bit	TUN1		@ ((unsigned)&OSCTUNE*8)+1; //88x
static 			bank1 bit	TUN0		@ ((unsigned)&OSCTUNE*8)+0; //88x

/*	SSPCON2 bits */
/* Definitions for SSPCON2 register */
static volatile bank1 bit	GCEN	@ (unsigned)&SSPCON2*8+7;
static volatile bank1 bit	ACKSTAT	@ (unsigned)&SSPCON2*8+6;
static volatile bank1 bit	ACKDT	@ (unsigned)&SSPCON2*8+5;
static volatile bank1 bit	ACKEN	@ (unsigned)&SSPCON2*8+4;
static volatile bank1 bit	RCEN	@ (unsigned)&SSPCON2*8+3;
static volatile bank1 bit	PEN	@ (unsigned)&SSPCON2*8+2;
static volatile bank1 bit	RSEN	@ (unsigned)&SSPCON2*8+1;
static volatile bank1 bit	SEN	@ (unsigned)&SSPCON2*8+0;


/*      SSPSTAT bits    */
/* Definitions for SSPSTAT register */
static volatile bank1 bit	STAT_SMP	@ (unsigned)&SSPSTAT*8+7;
static volatile bank1 bit	STAT_CKE	@ (unsigned)&SSPSTAT*8+6;
static volatile bank1 bit	STAT_DA		@ (unsigned)&SSPSTAT*8+5;
static volatile bank1 bit	STAT_P		@ (unsigned)&SSPSTAT*8+4;
static volatile bank1 bit	STAT_S		@ (unsigned)&SSPSTAT*8+3;
static volatile bank1 bit	STAT_RW		@ (unsigned)&SSPSTAT*8+2;
static volatile bank1 bit	STAT_UA		@ (unsigned)&SSPSTAT*8+1;
static volatile bank1 bit	STAT_BF		@ (unsigned)&SSPSTAT*8+0;

/* Definitions for WPUB register */
static 			bank1 bit	WPUB0		@ ((unsigned)&WPUB*8)+0; //88x
static 			bank1 bit	WPUB1		@ ((unsigned)&WPUB*8)+1; //88x
static 			bank1 bit	WPUB2		@ ((unsigned)&WPUB*8)+2; //88x
static 			bank1 bit	WPUB3		@ ((unsigned)&WPUB*8)+3; //88x
static 			bank1 bit	WPUB4		@ ((unsigned)&WPUB*8)+4; //88x
static 			bank1 bit	WPUB5		@ ((unsigned)&WPUB*8)+5; //88x
static 			bank1 bit	WPUB6		@ ((unsigned)&WPUB*8)+6; //88x
static 			bank1 bit	WPUB7		@ ((unsigned)&WPUB*8)+7; //88x

/* Definitions for IOCB register */
static 			bank1 bit	IOCB0		@ ((unsigned)&IOCB*8)+0; //88x
static 			bank1 bit	IOCB1		@ ((unsigned)&IOCB*8)+1; //88x
static 			bank1 bit	IOCB2		@ ((unsigned)&IOCB*8)+2; //88x
static 			bank1 bit	IOCB3		@ ((unsigned)&IOCB*8)+3; //88x
static 			bank1 bit	IOCB4		@ ((unsigned)&IOCB*8)+4; //88x
static 			bank1 bit	IOCB5		@ ((unsigned)&IOCB*8)+5; //88x
static 			bank1 bit	IOCB6		@ ((unsigned)&IOCB*8)+6; //88x
static 			bank1 bit	IOCB7		@ ((unsigned)&IOCB*8)+7; //88x

/* Definitions for VRCON register */
static 			bank1 bit	VR0			@ ((unsigned)&VRCON*8)+0; //88x
static 			bank1 bit	VR1			@ ((unsigned)&VRCON*8)+1; //88x
static 			bank1 bit	VR2			@ ((unsigned)&VRCON*8)+2; //88x
static 			bank1 bit	VR3			@ ((unsigned)&VRCON*8)+3; //88x
static 			bank1 bit	VRSS		@ ((unsigned)&VRCON*8)+4; //88x
static 			bank1 bit	VRR			@ ((unsigned)&VRCON*8)+5; //88x
static 			bank1 bit	VROE		@ ((unsigned)&VRCON*8)+6; //88x
static 			bank1 bit	VREN		@ ((unsigned)&VRCON*8)+7; //88x

/*	TXSTA bits	*/
/* Definitions for TXSTA register */
static volatile bank1 bit	CSRC	@ (unsigned)&TXSTA*8+7;
static volatile bank1 bit	TX9	@ (unsigned)&TXSTA*8+6;
static volatile bank1 bit	TXEN	@ (unsigned)&TXSTA*8+5;
static volatile bank1 bit	SYNC	@ (unsigned)&TXSTA*8+4;
static 			bank1 bit	SENDB			@ ((unsigned)&TXSTA*8)+3; //88x
static volatile bank1 bit	BRGH	@ (unsigned)&TXSTA*8+2;
static volatile bank1 bit	TRMT	@ (unsigned)&TXSTA*8+1;
static volatile bank1 bit	TX9D	@ (unsigned)&TXSTA*8+0;

/* Definitions for SPBRG register */
static 			bank1 bit	BRG0		@ ((unsigned)&SPBRG*8)+0; //88x
static 			bank1 bit	BRG1		@ ((unsigned)&SPBRG*8)+1; //88x
static 			bank1 bit	BRG2		@ ((unsigned)&SPBRG*8)+2; //88x
static 			bank1 bit	BRG3		@ ((unsigned)&SPBRG*8)+3; //88x
static 			bank1 bit	BRG4		@ ((unsigned)&SPBRG*8)+4; //88x
static 			bank1 bit	BRG5		@ ((unsigned)&SPBRG*8)+5; //88x
static 			bank1 bit	BRG6		@ ((unsigned)&SPBRG*8)+6; //88x
static 			bank1 bit	BRG7		@ ((unsigned)&SPBRG*8)+7; //88x

/* Definitions for SPBRGH register */
static 			bank1 bit	BRG8		@ ((unsigned)&SPBRGH*8)+0; //88x
static 			bank1 bit	BRG9		@ ((unsigned)&SPBRGH*8)+1; //88x
static 			bank1 bit	BRG10		@ ((unsigned)&SPBRGH*8)+2; //88x
static 			bank1 bit	BRG11		@ ((unsigned)&SPBRGH*8)+3; //88x
static 			bank1 bit	BRG12		@ ((unsigned)&SPBRGH*8)+4; //88x
static 			bank1 bit	BRG13		@ ((unsigned)&SPBRGH*8)+5; //88x
static 			bank1 bit	BRG14		@ ((unsigned)&SPBRGH*8)+6; //88x
static 			bank1 bit	BRG15		@ ((unsigned)&SPBRGH*8)+7; //88x

/* Definitions for PWM1CON register */
static volatile bank1 bit	PDC0		@ ((unsigned)&PWM1CON*8)+0; //88x
static volatile bank1 bit	PDC1		@ ((unsigned)&PWM1CON*8)+1; //88x
static volatile bank1 bit	PDC2		@ ((unsigned)&PWM1CON*8)+2; //88x
static volatile bank1 bit	PDC3		@ ((unsigned)&PWM1CON*8)+3; //88x
static volatile bank1 bit	PDC4		@ ((unsigned)&PWM1CON*8)+4; //88x
static volatile bank1 bit	PDC5		@ ((unsigned)&PWM1CON*8)+5; //88x
static volatile bank1 bit	PDC6		@ ((unsigned)&PWM1CON*8)+6; //88x
static volatile bank1 bit	PRSEN		@ ((unsigned)&PWM1CON*8)+7; //88x

/* Definitions for ECCPAS register */
static 			bank1 bit	PSSBD0		@ ((unsigned)&ECCPAS*8)+0; //88x
static 			bank1 bit	PSSBD1		@ ((unsigned)&ECCPAS*8)+1; //88x
static 			bank1 bit	PSSAC0		@ ((unsigned)&ECCPAS*8)+2; //88x
static 			bank1 bit	PSSAC1		@ ((unsigned)&ECCPAS*8)+3; //88x
static 			bank1 bit	ECCPAS0		@ ((unsigned)&ECCPAS*8)+4; //88x
static 			bank1 bit	ECCPAS1		@ ((unsigned)&ECCPAS*8)+5; //88x
static 			bank1 bit	ECCPAS2		@ ((unsigned)&ECCPAS*8)+6; //88x
static volatile bank1 bit	ECCPASE		@ ((unsigned)&ECCPAS*8)+7; //88x

/* Definitions for PSTRCON register */
static 			bank1 bit	STRA		@ ((unsigned)&PSTRCON*8)+0; //88x
static 			bank1 bit	STRB		@ ((unsigned)&PSTRCON*8)+1; //88x
static 			bank1 bit	STRC		@ ((unsigned)&PSTRCON*8)+2; //88x
static 			bank1 bit	STRD		@ ((unsigned)&PSTRCON*8)+3; //88x
static 			bank1 bit	STRSYNC		@ ((unsigned)&PSTRCON*8)+4; //88x

/*	ADCON1 bits	*/
/* Definitions for ADCON1 register */
static volatile bank1 bit	ADFM	@ (unsigned)&ADCON1*8+7;
static 			bank1 bit	VCFG1		@ ((unsigned)&ADCON1*8)+5; //88x
static 			bank1 bit	VCFG0		@ ((unsigned)&ADCON1*8)+4; //88x
//static volatile bank1 bit	PCFG3		@ (unsigned)&ADCON1*8+3; //87x
//static volatile bank1 bit	PCFG2		@ (unsigned)&ADCON1*8+2; //87x
//static volatile bank1 bit	PCFG1		@ (unsigned)&ADCON1*8+1; //87x
//static volatile bank1 bit	PCFG0		@ (unsigned)&ADCON1*8+0; //87x

/* Definitions for WDTCON register */
static 			bank1 bit	SWDTEN		@ ((unsigned)&WDTCON*8)+0; //88x
static 			bank1 bit	WDTPS0		@ ((unsigned)&WDTCON*8)+1; //88x
static 			bank1 bit	WDTPS1		@ ((unsigned)&WDTCON*8)+2; //88x
static 			bank1 bit	WDTPS2		@ ((unsigned)&WDTCON*8)+3; //88x
static 			bank1 bit	WDTPS3		@ ((unsigned)&WDTCON*8)+4; //88x

/* Definitions for CM1CON0 register */
static 			bank1 bit	C1CH0		@ ((unsigned)&CM1CON0*8)+0; //88x
static 			bank1 bit	C1CH1		@ ((unsigned)&CM1CON0*8)+1; //88x
static 			bank1 bit	C1R			@ ((unsigned)&CM1CON0*8)+2; //88x
static 			bank1 bit	C1POL		@ ((unsigned)&CM1CON0*8)+4; //88x
static 			bank1 bit	C1OE		@ ((unsigned)&CM1CON0*8)+5; //88x
static volatile bank1 bit	C1OUT		@ ((unsigned)&CM1CON0*8)+6; //88x
static 			bank1 bit	C1ON		@ ((unsigned)&CM1CON0*8)+7; //88x

/* Definitions for CM2CON0 register */
static 			bank1 bit	C2CH0		@ ((unsigned)&CM2CON0*8)+0; //88x
static 			bank1 bit	C2CH1		@ ((unsigned)&CM2CON0*8)+1; //88x
static 			bank1 bit	C2R			@ ((unsigned)&CM2CON0*8)+2; //88x
static 			bank1 bit	C2POL		@ ((unsigned)&CM2CON0*8)+4; //88x
static 			bank1 bit	C2OE		@ ((unsigned)&CM2CON0*8)+5; //88x
static volatile bank1 bit	C2OUT		@ ((unsigned)&CM2CON0*8)+6; //88x
static 			bank1 bit	C2ON		@ ((unsigned)&CM2CON0*8)+7; //88x

/* Definitions for CM2CON1 register */
static 			bank1 bit	C2SYNC		@ ((unsigned)&CM2CON1*8)+0; //88x
static 			bank1 bit	T1GSS		@ ((unsigned)&CM2CON1*8)+1; //88x
static 			bank1 bit	C2RSEL		@ ((unsigned)&CM2CON1*8)+4; //88x
static 			bank1 bit	C1RSEL		@ ((unsigned)&CM2CON1*8)+5; //88x
static volatile bank1 bit	MC2OUT		@ ((unsigned)&CM2CON1*8)+6; //88x
static volatile bank1 bit	MC1OUT		@ ((unsigned)&CM2CON1*8)+7; //88x

/* Definitions for SRCON register */
static 			bank3 bit	FVREN		@ ((unsigned)&SRCON*8)+0; //88x
static volatile bank3 bit	PULSR		@ ((unsigned)&SRCON*8)+2; //88x
static volatile bank3 bit	PULSS		@ ((unsigned)&SRCON*8)+3; //88x
static 			bank3 bit	C2REN		@ ((unsigned)&SRCON*8)+4; //88x
static 			bank3 bit	C1SEN		@ ((unsigned)&SRCON*8)+5; //88x
static 			bank3 bit	SR0			@ ((unsigned)&SRCON*8)+6; //88x
static 			bank3 bit	SR1			@ ((unsigned)&SRCON*8)+7; //88x

/* Definitions for BAUDCTL register */
static volatile bank3 bit	ABDEN		@ ((unsigned)&BAUDCTL*8)+0; //88x
static volatile bank3 bit	WUE			@ ((unsigned)&BAUDCTL*8)+1; //88x
static 			bank3 bit	BRG16		@ ((unsigned)&BAUDCTL*8)+3; //88x
static volatile bank3 bit	SCKP		@ ((unsigned)&BAUDCTL*8)+4; //88x
static volatile bank3 bit	RCIDL		@ ((unsigned)&BAUDCTL*8)+6; //88x
static volatile bank3 bit	ABDOVF		@ ((unsigned)&BAUDCTL*8)+7; //88x

/* Definitions for ANSEL register */
static 			bank3 bit	ANS0		@ ((unsigned)&ANSEL*8)+0; //88x
static 			bank3 bit	ANS1		@ ((unsigned)&ANSEL*8)+1; //88x
static 			bank3 bit	ANS2		@ ((unsigned)&ANSEL*8)+2; //88x
static 			bank3 bit	ANS3		@ ((unsigned)&ANSEL*8)+3; //88x
static 			bank3 bit	ANS4		@ ((unsigned)&ANSEL*8)+4; //88x
#if defined(_16F884) || defined(_16F887)
static 			bank3 bit	ANS5		@ ((unsigned)&ANSEL*8)+5; //88x
static 			bank3 bit	ANS6		@ ((unsigned)&ANSEL*8)+6; //88x
static 			bank3 bit	ANS7		@ ((unsigned)&ANSEL*8)+7; //88x
#endif

/* Definitions for ANSELH register */
static 			bank3 bit	ANS8		@ ((unsigned)&ANSELH*8)+0; //88x
static 			bank3 bit	ANS9		@ ((unsigned)&ANSELH*8)+1; //88x
static 			bank3 bit	ANS10		@ ((unsigned)&ANSELH*8)+2; //88x
static 			bank3 bit	ANS11		@ ((unsigned)&ANSELH*8)+3; //88x
static 			bank3 bit	ANS12		@ ((unsigned)&ANSELH*8)+4; //88x
static 			bank3 bit	ANS13		@ ((unsigned)&ANSELH*8)+5; //88x

/*	EECON1 bits */
/* Definitions for EECON1 register */
static volatile bank3 bit	EEPGD	@ (unsigned)&EECON1*8+7;
static volatile bank3 bit	WRERR	@ (unsigned)&EECON1*8+3;
static volatile bank3 bit	WREN	@ (unsigned)&EECON1*8+2;
static volatile bank3 bit	WR	@ (unsigned)&EECON1*8+1;
static volatile bank3 bit	RD	@ (unsigned)&EECON1*8+0;

#define EEPROM_SIZE	256
/* macro versions of EEPROM write and read */
#define	EEPROM_WRITE(addr, value) while(WR)continue;EEADR=(addr);EEDATA=(value); \
					EECON1&=0x7F;CARRY=0;if(GIE)CARRY=1;GIE=0; \
					WREN=1;EECON2=0x55;EECON2=0xAA;WR=1;WREN=0; \
					if(CARRY)GIE=1

#define	EEPROM_READ(addr) ((EEADR=(addr)),(EECON1&=0x7F),(RD=1),EEDATA)
					
/* macro versions of Flash read and write */
#define FLASH_WRITE(addr, value)	EEADR=((addr)&0xff);	\
					EEADRH=((addr)>>8);	\
					EEDATH=((value)>>8);	\
					EEDATA=((value)&0xff);	\
					EEPGD = 1;		\
					WREN=1;			\
					EECON2 = 0x55;		\
					EECON2 = 0xaa;		\
					WR=1;			\
					asm("nop");		\
					asm("nop");		\
              				WREN=0

#define FLASH_READ(addr)		EEADR=((addr)&0xff);	\
					EEADRH=((addr)>>8);	\
					WREN=0;			\
					EEPGD = 1;		\
					RD=1;			\
					asm("nop");		\
					asm("nop");		\
					((EEDATH << 8) | EEDATA)

/* library function versions */
					
extern void eeprom_write(unsigned char addr, unsigned char value);
extern unsigned char eeprom_read(unsigned char addr);
					
// Configuration Mask Definitions
#define CONFIG_ADDR	0x2007
//...

#endif

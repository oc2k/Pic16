//*************************************************************
//************************************************************* 
// =====================================
#ifndef _osConstantesDefs_NAME
#define _osConstantesDefs_NAME

//======================================
//(1) define constant parameter
//======================================
// ===================
// Common fields
// ===================
#define TRUE                           1
#define FALSE                          0
#define RETURNCOM		0
#define SCI			_TRUE
#define INTERRUPT	_TRUE

// ===================
// Change Frequency affect to
// (1) T1RATE in "ssdinit.h"
// (2) T2 PWM initial routine
// ===================
#define FOSC			4000000		// PIC frequency use
#define VersionNo		'a'

// ===================
// Optional Debugging DEFINED
// ===================
// Debugging UART Function, After debug comment line
//#define TRACE_NUMBER_PROCESS
//#define CLKFREQ_DEBUGGING_PROCESSING
//#define UART_DEBUGGING_PROCESSING
//#define A2D_BAT_DEBUGGING_PROCESSING
//->Library debugging defined
//#define I2CM_DEBUGGING_PROCESSING
// Condition: the "UART_DEBUGGING_PROCESSING" disable
// ===================
// Baseline period: SklBL->BaseBL->DrvBL
// ===================
// SklBL: skeleton Baseline with sci&a2d
// BaseBL: Baseline with base function (e.g.: i2cm, PWM, etc.)
// DrvBL: Baseline with drive function (e.g.: ANT, DEV, GS, ..etc.)
// Done, called Project Baseline code
// ===================
// After that Add HMI, STM, Application code
// Done, called Project full function code
// ===================


#endif // !_osConstantesDefs_NAME


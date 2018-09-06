//*************************************************************
// antTypes.h
//************************************************************* 
#ifndef AntType_H
#define AntType_H

#define LITTLE_ENDIAN
#define NULL                           ((void *) 0)

#define MAX_UCHAR                      0xFF
#define MAX_SCHAR                      0x7F
#define MIN_SCHAR                      0x80

#define MAX_SHORT                      0x7FFF
#define MIN_SHORT                      0x8000
#define MAX_USHORT                     0xFFFF
#define MAX_SSHORT                     0x7FFF
#define MIN_SSHORT                     0x8000

#define MAX_LONG                       0x7FFFFFFF
#define MIN_LONG                       0x80000000
#define MAX_ULONG                      0xFFFFFFFF
#define MAX_SLONG                      0x7FFFFFFF
#define MIN_SLONG                      0x80000000

typedef unsigned char                  BOOL;
typedef unsigned char                  UCHAR;
typedef signed char                    SCHAR;

typedef short                          SHORT;
typedef unsigned short                 USHORT;
typedef signed short                   SSHORT;

typedef long                           LONG;
typedef unsigned long                  ULONG;
typedef signed long                    SLONG;

typedef float                          FLOAT;
typedef double                         DOUBLE;

typedef union
{
   USHORT usData;
   struct
   {
      #if defined(LITTLE_ENDIAN)
         UCHAR ucLow;
         UCHAR ucHigh;
      #elif defined(BIG_ENDIAN)
         UCHAR ucHigh;
         UCHAR ucLow;
      #else
         #error
      #endif
   } stBytes;
} USHORT_UNION;

typedef union
{
   ULONG ulData;
   UCHAR aucBytes[4];
   struct
   {
      // The least significant byte of the ULONG in this structure is
      // referenced by ucByte0.
      UCHAR ucByte0;
      UCHAR ucByte1;
      UCHAR ucByte2;
      UCHAR ucByte3;
   } stBytes;
} ULONG_UNION;

#endif

//*************************************************************
//  Timing isr processing GUIDELINE
//*************************************************************
#ifndef AntType_H_isr
#define AntType_H_isr
#endif

//************************************************************* 
// Timing process in osSysClock, e.g.: #define SciSysclkTmr1() __clkSciPcMsgHmsCountdown();
//************************************************************* 
#ifndef AntType_H_sysClk
#define AntType_H_sysClk
#endif


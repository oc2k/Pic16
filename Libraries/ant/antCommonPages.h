//*************************************************************
// antCommonPages.h
//************************************************************* 
#ifndef __AntCommonPages_H
#define __AntCommonPages_H                       

// Page structs
#define COMMON_PAGE_RESERVE_BYTE                           ((UCHAR) 0xFF)

typedef struct
{
   UCHAR ucPg80ReserveByte1;
   UCHAR ucPg80ReserveByte2;
   UCHAR  ucHwVersion;                               // Page 80
   USHORT usManId;                                   // Page 80
   USHORT usModelNumber;                             // Page 80
} CommonPage80_Data;

typedef struct
{
   UCHAR ucPg81ReserveByte1;
   UCHAR ucPg81ReserveByte2;
   UCHAR  ucSwVersion;                               // Page 81
   ULONG  ulSerialNumber;                            // Page 81
} CommonPage81_Data;

typedef struct
{
   UCHAR ucPg82ReserveByte1;
   UCHAR ucPg82ReserveByte2;
   ULONG  ulCumOperatingTime;                        // Page 82
   UCHAR  ucBattVoltage256;                          // Page 82
   UCHAR  ucBattVoltage;                             // Page 82
   UCHAR  ucBattStatus;                              // Page 82
   UCHAR  ucCumOperatingTimeRes;                     // Page 82
} CommonPage82_Data;


#endif

//*************************************************************
//       Timing processing GUIDELINE
//*************************************************************
#ifndef __AntCommonPages_H_isr
#define __AntCommonPages_H_isr
#endif

//************************************************************* 
// (2) Timing process in osSysClock, e.g.: #define SciSysclkTmr1() __clkSciPcMsgHmsCountdown();
//************************************************************* 
#ifndef __AntCommonPages_H_sysClk
#define __AntCommonPages_H_sysClk
#endif


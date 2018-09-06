//*************************************************************      
// antPlus.h
//************************************************************* 
#ifndef AntPlus_H
#define AntPlus_H

// -------------------------------------------------------------------------------------
// ANS Project configuration setting
// -------------------------------------------------------------------------------------
// Transmit or master channel 0x10 // Page17,19 of "ANT+ Device Profile - Bicycle Power_Rev 2.0.pdf"
// 0x50 -- Transmit only channel //Page45,46 of "1204662412_ant message protocol and usage.pdf"
// 0x10 -- Transmit channel //Page45,46 of "1204662412_ant message protocol and usage.pdf"
// -------------------------------------------------------------------------------------
#define ANS_CHANNEL_TYPE					 ((UCHAR) 0x10) 
#define ANS_NETWORK_NUMBER					 ((UCHAR) 0)
#define ANS_CHANNEL_NUMBER					 ((UCHAR) 0)
#define ANS_CHANNEL_DEVICE_NUMBER			 ((UINT)  0x0001) // Page16 of "ANT+ Device Profile - Bicycle Power_Rev 2.0.pdf"
#define ANS_CHANNEL_DEVICE_TYPE				 ((UCHAR) 0x0B) // Page16 of "ANT+ Device Profile - Bicycle Power_Rev 2.0.pdf"
#define ANS_CHANNEL_TRANS_TYPE				 ((UCHAR) 0x05) // Page16 of "ANT+ Device Profile - Bicycle Power_Rev 2.0.pdf"
#define ANS_CHANNEL_MESG_PERIOD				 DEFAULT_CHANNEL_MESSAGE_PERIOD //((UINT)  0x8000) // (32768) Page16 of "ANT+ Device Profile - Bicycle Power_Rev 2.0.pdf"
#define ANS_CHANNEL_RF_FREQ					 ((UCHAR) 0x39) // Page16 of "ANT+ Device Profile - Bicycle Power_Rev 2.0.pdf"

// Global ANT parameters
//#define ANTPLUS_NETWORK_NUMBER               ((UCHAR) 0)
//#error "MUST INSERt ANT+ KEY HERE !!!!!!!!!!!!!!!!!!!!!!!!"
//#define ANTPLUS_NETWORK_KEY                  { 0x__,0x__,0x__,0x__,0x__,0x__,0x__,0x__ }     // INSERT ANT+ NETWORK KEY HERE (ignore germin ID)
#define ANTPLUS_NETWORK_KEY                  { 0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01 }     // This is Sample ID
#define ANTPLUS_RF_FREQ                      ((UCHAR) 0x39)     // decimal 57 (2457 MHz) 

// SDM
#define SDM_PAGE_1                           ((UCHAR) 1)
#define SDM_PAGE_2                           ((UCHAR) 2)
#define SDM_PAGE_3                           ((UCHAR) 3)
#define SDM_PAGE_4                           ((UCHAR) 4)
#define SDM_PAGE_5                           ((UCHAR) 5)
#define SDM_PAGE_6                           ((UCHAR) 6)
#define SDM_PAGE_7                           ((UCHAR) 7)
#define SDM_PAGE_8                           ((UCHAR) 8)
#define SDM_PAGE_9                           ((UCHAR) 9)
#define SDM_PAGE_10                          ((UCHAR) 10)
#define SDM_PAGE_11                          ((UCHAR) 11)
#define SDM_PAGE_12                          ((UCHAR) 12)
#define SDM_PAGE_13                          ((UCHAR) 13)

// HRM
#define HRM_PAGE_0                           ((UCHAR) 0)
#define HRM_PAGE_1                           ((UCHAR) 1)
#define HRM_PAGE_2                           ((UCHAR) 2)
#define HRM_PAGE_3                           ((UCHAR) 3)
#define HRM_PAGE_4                           ((UCHAR) 4)

// COMBINED BIKE SPEED AND CADENCE
#define CBSCRX_PAGE_0                        ((UCHAR) 0)

// SEPARATE BIKE SPEED AND CADENCE
#define BSC_PAGE_0                           ((UCHAR) 0)
#define BSC_PAGE_1                           ((UCHAR) 1)
#define BSC_PAGE_2                           ((UCHAR) 2)
#define BSC_PAGE_3                           ((UCHAR) 3)

// BIKE POWER SENSOR
#define BPS_PAGE_1                           ((UCHAR) 1)
#define BPS_PAGE_16                          ((UCHAR) 16)
#define BPS_PAGE_17                          ((UCHAR) 17)
#define BPS_PAGE_18                          ((UCHAR) 18)
#define BPS_PAGE_32                          ((UCHAR) 32)

// GLOBAL
#define GLOBAL_PAGE_80                       ((UCHAR) 80)
#define GLOBAL_PAGE_81                       ((UCHAR) 81)
#define GLOBAL_PAGE_82                       ((UCHAR) 82)

//Page 82 flags
#define GBL82_COARSE_BATT_INVALID_VOLTAGE          ((UCHAR) 0x0F)
#define GBL82_BATT_STATUS_NEW                      ((UCHAR) 1)
#define GBL82_BATT_STATUS_GOOD                     ((UCHAR) 2)
#define GBL82_BATT_STATUS_OK                       ((UCHAR) 3)
#define GBL82_BATT_STATUS_LOW                      ((UCHAR) 4)
#define GBL82_BATT_STATUS_CRITICAL                 ((UCHAR) 5)
#define GBL82_BATT_STATUS_INVALID                  ((UCHAR) 7)
#define GBL82_CUM_TIME_16_SECOND_RES               ((UCHAR) 0)
#define GBL82_CUM_TIME_2_SECOND_RES                ((UCHAR) 1)

typedef enum
{
   ANTPLUS_EVENT_NONE,              // No Event
   ANTPLUS_EVENT_INIT_COMPLETE,     // Initialization of channel complete
   ANTPLUS_EVENT_COMMAND_FAIL,      // A command has failed
   ANTPLUS_EVENT_CHANNEL_CLOSED,    // Closing of channel complete
   ANTPLUS_EVENT_CHANNEL_ID,        // Recieved channel ID information
   ANTPLUS_EVENT_PAGE,              // Got a page
   ANTPLUS_EVENT_UNKNOWN_PAGE,      // Got unknown page (could not decode
   ANTPLUS_EVENT_TRANSMIT,           // Transmitted a page
   ANTPLUS_EVENT_CALIBRATION_TIMEOUT // Calibration request timed out
}ANTPLUS_Events;

typedef struct
{
   ANTPLUS_Events eEvent;           // Event
   USHORT usParam1;                 // Generic parameter 1
   USHORT usParam2;                 // Generic parameter 2
} ANTPLUS_EVENT_RETURN;

#endif //!AntPlus_H

//*************************************************************
// Timing isr processing GUIDELINE
//*************************************************************
#ifndef AntPlus_H_isr
#define AntPlus_H_isr
#endif

//************************************************************* 
// Timing process in osSysClock, e.g.: #define SciSysclkTmr1() __clkSciPcMsgHmsCountdown();
//************************************************************* 
#ifndef AntPlus_H_sysClk
#define AntPlus_H_sysClk
#endif


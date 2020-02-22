#ifndef RTW_HEADER_Racing_2019_private_h_
#define RTW_HEADER_Racing_2019_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "Racing_2019.h"

#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

extern can_tp1_canChannel* can_type1_channel_M1_C1;
extern can_tp1_canService* can_type1_service_M1_C1[13];
extern can_tp1_canChannel* can_type1_channel_M1_C2;
extern can_tp1_canService* can_type1_service_M1_C2[13];

#define CANTP1_M1_NUMMSG               4

extern can_tp1_canMsg* can_type1_msg_M1[CANTP1_M1_NUMMSG];
extern Int32 rtican_type1_tq_error[CAN_TYPE1_NUM_MODULES]
  [CAN_TYPE1_NUM_TASKQUEUES];
extern can_tp1_canChannel* can_type1_channel_M2_C2;
extern can_tp1_canService* can_type1_service_M2_C2[13];
extern can_tp1_canChannel* can_type1_channel_M2_C1;
extern can_tp1_canService* can_type1_service_M2_C1[13];

#define CANTP1_M2_NUMMSG               40

extern can_tp1_canMsg* can_type1_msg_M2[CANTP1_M2_NUMMSG];
extern Int32 rtican_type1_tq_error[CAN_TYPE1_NUM_MODULES]
  [CAN_TYPE1_NUM_TASKQUEUES];

#define CANTP1_M1_C1_TX_STD_0X161      0
#define TX_C1_STD_0X161                0
#undef TX_C1_STD_0X161
#define CANTP1_M1_C1_RX_STD_0X181      1
#define RX_C1_STD_0X181                1
#undef RX_C1_STD_0X181
#define CANTP1_M1_C1_Status            0
#define Status_C1                      0
#undef Status_C1
#define CANTP1_M1_C1_StuffErrors       1
#define StuffErrors_C1                 1
#undef StuffErrors_C1
#define CANTP1_M1_C1_FormatErrors      2
#define FormatErrors_C1                2
#undef FormatErrors_C1
#define CANTP1_M1_C1_AckErrors         3
#define AckErrors_C1                   3
#undef AckErrors_C1
#define CANTP1_M1_C1_Bit0Errors        4
#define Bit0Errors_C1                  4
#undef Bit0Errors_C1
#define CANTP1_M1_C1_Bit1Errors        5
#define Bit1Errors_C1                  5
#undef Bit1Errors_C1
#define CANTP1_M1_C1_CRCErrors         6
#define CRCErrors_C1                   6
#undef CRCErrors_C1
#define CANTP1_M1_C1_RXLost            7
#define RXLost_C1                      7
#undef RXLost_C1
#define CANTP1_M1_C1_DataLost          12
#define CANTP1_M1_C1_RXOK              8
#define RXOK_C1                        8
#undef RXOK_C1
#define CANTP1_M1_C1_TXOK              9
#define TXOK_C1                        9
#undef TXOK_C1
#define CANTP1_M1_C2_TX_STD_0X162      2
#define TX_C2_STD_0X162                2
#undef TX_C2_STD_0X162
#define CANTP1_M1_C2_RX_STD_0X182      3
#define RX_C2_STD_0X182                3
#undef RX_C2_STD_0X182
#define CANTP1_M1_C2_Status            0
#define Status_C2                      0
#undef Status_C2
#define CANTP1_M1_C2_StuffErrors       1
#define StuffErrors_C2                 1
#undef StuffErrors_C2
#define CANTP1_M1_C2_FormatErrors      2
#define FormatErrors_C2                2
#undef FormatErrors_C2
#define CANTP1_M1_C2_AckErrors         3
#define AckErrors_C2                   3
#undef AckErrors_C2
#define CANTP1_M1_C2_Bit0Errors        4
#define Bit0Errors_C2                  4
#undef Bit0Errors_C2
#define CANTP1_M1_C2_Bit1Errors        5
#define Bit1Errors_C2                  5
#undef Bit1Errors_C2
#define CANTP1_M1_C2_CRCErrors         6
#define CRCErrors_C2                   6
#undef CRCErrors_C2
#define CANTP1_M1_C2_RXLost            7
#define RXLost_C2                      7
#undef RXLost_C2
#define CANTP1_M1_C2_DataLost          12
#define CANTP1_M1_C2_RXOK              8
#define RXOK_C2                        8
#undef RXOK_C2
#define CANTP1_M1_C2_TXOK              9
#define TXOK_C2                        9
#undef TXOK_C2

extern can_tp1_canMsg* CANTP1_TX_SPMSG_M1_C1_STD;
extern can_tp1_canMsg* CANTP1_TX_SPMSG_M1_C1_XTD;
extern can_tp1_canMsg* CANTP1_TX_SPMSG_M1_C2_STD;
extern can_tp1_canMsg* CANTP1_TX_SPMSG_M1_C2_XTD;

#define CANTP1_M2_C2_TX_STD_0X19C      0
#define TX_C2_STD_0X19C                0
#undef TX_C2_STD_0X19C
#define CANTP1_M2_C2_TX_STD_0XA6       1
#define TX_C2_STD_0XA6                 1
#undef TX_C2_STD_0XA6
#define CANTP1_M2_C2_TX_STD_0XCC       2
#define TX_C2_STD_0XCC                 2
#undef TX_C2_STD_0XCC
#define CANTP1_M2_C2_RX_STD_0X65       3
#define RX_C2_STD_0X65                 3
#undef RX_C2_STD_0X65
#define CANTP1_M2_C2_RX_STD_0XC6       4
#define RX_C2_STD_0XC6                 4
#undef RX_C2_STD_0XC6
#define CANTP1_M2_C2_RX_STD_0X13A      5
#define RX_C2_STD_0X13A                5
#undef RX_C2_STD_0X13A
#define CANTP1_M2_C2_RX_STD_0X165      6
#define RX_C2_STD_0X165                6
#undef RX_C2_STD_0X165
#define CANTP1_M2_C2_RX_STD_0X180      7
#define RX_C2_STD_0X180                7
#undef RX_C2_STD_0X180
#define CANTP1_M2_C2_RX_STD_0X117      8
#define RX_C2_STD_0X117                8
#undef RX_C2_STD_0X117
#define CANTP1_M2_C2_RX_STD_0XF6       9
#define RX_C2_STD_0XF6                 9
#undef RX_C2_STD_0XF6
#define CANTP1_M2_C2_Status            0
#define Status_C2                      0
#undef Status_C2
#define CANTP1_M2_C2_StuffErrors       1
#define StuffErrors_C2                 1
#undef StuffErrors_C2
#define CANTP1_M2_C2_FormatErrors      2
#define FormatErrors_C2                2
#undef FormatErrors_C2
#define CANTP1_M2_C2_AckErrors         3
#define AckErrors_C2                   3
#undef AckErrors_C2
#define CANTP1_M2_C2_Bit0Errors        4
#define Bit0Errors_C2                  4
#undef Bit0Errors_C2
#define CANTP1_M2_C2_Bit1Errors        5
#define Bit1Errors_C2                  5
#undef Bit1Errors_C2
#define CANTP1_M2_C2_CRCErrors         6
#define CRCErrors_C2                   6
#undef CRCErrors_C2
#define CANTP1_M2_C2_RXLost            7
#define RXLost_C2                      7
#undef RXLost_C2
#define CANTP1_M2_C2_DataLost          12
#define CANTP1_M2_C2_RXOK              8
#define RXOK_C2                        8
#undef RXOK_C2
#define CANTP1_M2_C2_TXOK              9
#define TXOK_C2                        9
#undef TXOK_C2
#define CANTP1_M2_C1_TX_STD_0XC9       10
#define TX_C1_STD_0XC9                 10
#undef TX_C1_STD_0XC9
#define CANTP1_M2_C1_RX_STD_0XC8       11
#define RX_C1_STD_0XC8                 11
#undef RX_C1_STD_0XC8
#define CANTP1_M2_C1_RX_STD_0XCE       12
#define RX_C1_STD_0XCE                 12
#undef RX_C1_STD_0XCE
#define CANTP1_M2_C1_RX_STD_0XCD       13
#define RX_C1_STD_0XCD                 13
#undef RX_C1_STD_0XCD
#define CANTP1_M2_C1_RX_STD_0XCC       14
#define RX_C1_STD_0XCC                 14
#undef RX_C1_STD_0XCC
#define CANTP1_M2_C1_RX_STD_0XD1       15
#define RX_C1_STD_0XD1                 15
#undef RX_C1_STD_0XD1
#define CANTP1_M2_C1_RX_STD_0XD0       16
#define RX_C1_STD_0XD0                 16
#undef RX_C1_STD_0XD0
#define CANTP1_M2_C1_RX_STD_0XCF       17
#define RX_C1_STD_0XCF                 17
#undef RX_C1_STD_0XCF
#define CANTP1_M2_C1_RX_STD_0XD4       18
#define RX_C1_STD_0XD4                 18
#undef RX_C1_STD_0XD4
#define CANTP1_M2_C1_RX_STD_0XD3       19
#define RX_C1_STD_0XD3                 19
#undef RX_C1_STD_0XD3
#define CANTP1_M2_C1_RX_STD_0XD2       20
#define RX_C1_STD_0XD2                 20
#undef RX_C1_STD_0XD2
#define CANTP1_M2_C1_RX_STD_0XD7       21
#define RX_C1_STD_0XD7                 21
#undef RX_C1_STD_0XD7
#define CANTP1_M2_C1_RX_STD_0XD6       22
#define RX_C1_STD_0XD6                 22
#undef RX_C1_STD_0XD6
#define CANTP1_M2_C1_RX_STD_0XD5       23
#define RX_C1_STD_0XD5                 23
#undef RX_C1_STD_0XD5
#define CANTP1_M2_C1_RX_STD_0XDA       24
#define RX_C1_STD_0XDA                 24
#undef RX_C1_STD_0XDA
#define CANTP1_M2_C1_RX_STD_0XD9       25
#define RX_C1_STD_0XD9                 25
#undef RX_C1_STD_0XD9
#define CANTP1_M2_C1_RX_STD_0XD8       26
#define RX_C1_STD_0XD8                 26
#undef RX_C1_STD_0XD8
#define CANTP1_M2_C1_RX_STD_0XDD       27
#define RX_C1_STD_0XDD                 27
#undef RX_C1_STD_0XDD
#define CANTP1_M2_C1_RX_STD_0XDC       28
#define RX_C1_STD_0XDC                 28
#undef RX_C1_STD_0XDC
#define CANTP1_M2_C1_RX_STD_0XDB       29
#define RX_C1_STD_0XDB                 29
#undef RX_C1_STD_0XDB
#define CANTP1_M2_C1_RX_STD_0XE0       30
#define RX_C1_STD_0XE0                 30
#undef RX_C1_STD_0XE0
#define CANTP1_M2_C1_RX_STD_0XDF       31
#define RX_C1_STD_0XDF                 31
#undef RX_C1_STD_0XDF
#define CANTP1_M2_C1_RX_STD_0XDE       32
#define RX_C1_STD_0XDE                 32
#undef RX_C1_STD_0XDE
#define CANTP1_M2_C1_RX_STD_0XE2       33
#define RX_C1_STD_0XE2                 33
#undef RX_C1_STD_0XE2
#define CANTP1_M2_C1_RX_STD_0XE3       34
#define RX_C1_STD_0XE3                 34
#undef RX_C1_STD_0XE3
#define CANTP1_M2_C1_RX_STD_0XE4       35
#define RX_C1_STD_0XE4                 35
#undef RX_C1_STD_0XE4
#define CANTP1_M2_C1_RX_STD_0XE5       36
#define RX_C1_STD_0XE5                 36
#undef RX_C1_STD_0XE5
#define CANTP1_M2_C1_RX_STD_0XE6       37
#define RX_C1_STD_0XE6                 37
#undef RX_C1_STD_0XE6
#define CANTP1_M2_C1_RX_STD_0XE7       38
#define RX_C1_STD_0XE7                 38
#undef RX_C1_STD_0XE7
#define CANTP1_M2_C1_RX_STD_0XE1       39
#define RX_C1_STD_0XE1                 39
#undef RX_C1_STD_0XE1
#define CANTP1_M2_C1_Status            0
#define Status_C1                      0
#undef Status_C1
#define CANTP1_M2_C1_StuffErrors       1
#define StuffErrors_C1                 1
#undef StuffErrors_C1
#define CANTP1_M2_C1_FormatErrors      2
#define FormatErrors_C1                2
#undef FormatErrors_C1
#define CANTP1_M2_C1_AckErrors         3
#define AckErrors_C1                   3
#undef AckErrors_C1
#define CANTP1_M2_C1_Bit0Errors        4
#define Bit0Errors_C1                  4
#undef Bit0Errors_C1
#define CANTP1_M2_C1_Bit1Errors        5
#define Bit1Errors_C1                  5
#undef Bit1Errors_C1
#define CANTP1_M2_C1_CRCErrors         6
#define CRCErrors_C1                   6
#undef CRCErrors_C1
#define CANTP1_M2_C1_RXLost            7
#define RXLost_C1                      7
#undef RXLost_C1
#define CANTP1_M2_C1_DataLost          12
#define CANTP1_M2_C1_RXOK              8
#define RXOK_C1                        8
#undef RXOK_C1
#define CANTP1_M2_C1_TXOK              9
#define TXOK_C1                        9
#undef TXOK_C1

extern can_tp1_canMsg* CANTP1_TX_SPMSG_M2_C2_STD;
extern can_tp1_canMsg* CANTP1_TX_SPMSG_M2_C2_XTD;
extern can_tp1_canMsg* CANTP1_TX_SPMSG_M2_C1_STD;
extern can_tp1_canMsg* CANTP1_TX_SPMSG_M2_C1_XTD;
extern UInt16 ENABLE_Index_UsbFlRec;
extern UInt16 Car_Reset_Index_UsbFlRec;
extern UInt16 BMS_Reset_Index_UsbFlRec;
extern UInt16 BMS_Status_Index_UsbFlRec;
extern UInt16 Idc_Accu_x10_Index_UsbFlRec;
extern UInt16 VDC_BMS_Index_UsbFlRec;
extern UInt16 s1c1_Index_UsbFlRec;
extern UInt16 s1c10_Index_UsbFlRec;
extern UInt16 s1c11_Index_UsbFlRec;
extern UInt16 s1c12_Index_UsbFlRec;
extern UInt16 s1c2_Index_UsbFlRec;
extern UInt16 s1c3_Index_UsbFlRec;
extern UInt16 s1c4_Index_UsbFlRec;
extern UInt16 s1c5_Index_UsbFlRec;
extern UInt16 s1c6_Index_UsbFlRec;
extern UInt16 s1c7_Index_UsbFlRec;
extern UInt16 s1c8_Index_UsbFlRec;
extern UInt16 s1c9_Index_UsbFlRec;
extern UInt16 s1t1_Index_UsbFlRec;
extern UInt16 s1t2_Index_UsbFlRec;
extern UInt16 s1t3_Index_UsbFlRec;
extern UInt16 s1t4_Index_UsbFlRec;
extern UInt16 s2c1_Index_UsbFlRec;
extern UInt16 s2c10_Index_UsbFlRec;
extern UInt16 s2c11_Index_UsbFlRec;
extern UInt16 s2c12_Index_UsbFlRec;
extern UInt16 s2c2_Index_UsbFlRec;
extern UInt16 s2c3_Index_UsbFlRec;
extern UInt16 s2c4_Index_UsbFlRec;
extern UInt16 s2c5_Index_UsbFlRec;
extern UInt16 s2c6_Index_UsbFlRec;
extern UInt16 s2c7_Index_UsbFlRec;
extern UInt16 s2c8_Index_UsbFlRec;
extern UInt16 s2c9_Index_UsbFlRec;
extern UInt16 s2t1_Index_UsbFlRec;
extern UInt16 s2t2_Index_UsbFlRec;
extern UInt16 s2t3_Index_UsbFlRec;
extern UInt16 s2t4_Index_UsbFlRec;
extern UInt16 s3c1_Index_UsbFlRec;
extern UInt16 s3c10_Index_UsbFlRec;
extern UInt16 s3c11_Index_UsbFlRec;
extern UInt16 s3c12_Index_UsbFlRec;
extern UInt16 s3c2_Index_UsbFlRec;
extern UInt16 s3c3_Index_UsbFlRec;
extern UInt16 s3c4_Index_UsbFlRec;
extern UInt16 s3c5_Index_UsbFlRec;
extern UInt16 s3c6_Index_UsbFlRec;
extern UInt16 s3c7_Index_UsbFlRec;
extern UInt16 s3c8_Index_UsbFlRec;
extern UInt16 s3c9_Index_UsbFlRec;
extern UInt16 s3t1_Index_UsbFlRec;
extern UInt16 s3t2_Index_UsbFlRec;
extern UInt16 s3t3_Index_UsbFlRec;
extern UInt16 s3t4_Index_UsbFlRec;
extern UInt16 s4c1_Index_UsbFlRec;
extern UInt16 s4c10_Index_UsbFlRec;
extern UInt16 s4c11_Index_UsbFlRec;
extern UInt16 s4c12_Index_UsbFlRec;
extern UInt16 s4c2_Index_UsbFlRec;
extern UInt16 s4c3_Index_UsbFlRec;
extern UInt16 s4c4_Index_UsbFlRec;
extern UInt16 s4c5_Index_UsbFlRec;
extern UInt16 s4c6_Index_UsbFlRec;
extern UInt16 s4c7_Index_UsbFlRec;
extern UInt16 s4c8_Index_UsbFlRec;
extern UInt16 s4c9_Index_UsbFlRec;
extern UInt16 s4t1_Index_UsbFlRec;
extern UInt16 s4t2_Index_UsbFlRec;
extern UInt16 s4t3_Index_UsbFlRec;
extern UInt16 s4t4_Index_UsbFlRec;
extern UInt16 s5c1_Index_UsbFlRec;
extern UInt16 s5c10_Index_UsbFlRec;
extern UInt16 s5c11_Index_UsbFlRec;
extern UInt16 s5c12_Index_UsbFlRec;
extern UInt16 s5c2_Index_UsbFlRec;
extern UInt16 s5c3_Index_UsbFlRec;
extern UInt16 s5c4_Index_UsbFlRec;
extern UInt16 s5c5_Index_UsbFlRec;
extern UInt16 s5c6_Index_UsbFlRec;
extern UInt16 s5c7_Index_UsbFlRec;
extern UInt16 s5c8_Index_UsbFlRec;
extern UInt16 s5c9_Index_UsbFlRec;
extern UInt16 s5t1_Index_UsbFlRec;
extern UInt16 s5t2_Index_UsbFlRec;
extern UInt16 s5t3_Index_UsbFlRec;
extern UInt16 s5t4_Index_UsbFlRec;
extern UInt16 s6c1_Index_UsbFlRec;
extern UInt16 s6c10_Index_UsbFlRec;
extern UInt16 s6c11_Index_UsbFlRec;
extern UInt16 s6c12_Index_UsbFlRec;
extern UInt16 s6c2_Index_UsbFlRec;
extern UInt16 s6c3_Index_UsbFlRec;
extern UInt16 s6c4_Index_UsbFlRec;
extern UInt16 s6c5_Index_UsbFlRec;
extern UInt16 s6c6_Index_UsbFlRec;
extern UInt16 s6c7_Index_UsbFlRec;
extern UInt16 s6c8_Index_UsbFlRec;
extern UInt16 s6c9_Index_UsbFlRec;
extern UInt16 s6t1_Index_UsbFlRec;
extern UInt16 s6t2_Index_UsbFlRec;
extern UInt16 s6t3_Index_UsbFlRec;
extern UInt16 s6t4_Index_UsbFlRec;
extern UInt16 s7c1_Index_UsbFlRec;
extern UInt16 s7c10_Index_UsbFlRec;
extern UInt16 s7c11_Index_UsbFlRec;
extern UInt16 s7c12_Index_UsbFlRec;
extern UInt16 s7c2_Index_UsbFlRec;
extern UInt16 s7c3_Index_UsbFlRec;
extern UInt16 s7c4_Index_UsbFlRec;
extern UInt16 s7c5_Index_UsbFlRec;
extern UInt16 s7c6_Index_UsbFlRec;
extern UInt16 s7c7_Index_UsbFlRec;
extern UInt16 s7c8_Index_UsbFlRec;
extern UInt16 s7c9_Index_UsbFlRec;
extern UInt16 s7t1_Index_UsbFlRec;
extern UInt16 s7t2_Index_UsbFlRec;
extern UInt16 s7t3_Index_UsbFlRec;
extern UInt16 s7t4_Index_UsbFlRec;
extern UInt16 Aux_CAN_314_Index_UsbFlRec;
extern UInt16 Aux_CAN_357_Index_UsbFlRec;
extern UInt16 Aux_CAN_412_Index_UsbFlRec;
extern UInt16 Aux_Thermistor_Index_UsbFlRec;
extern UInt16 BSPD_Status_Index_UsbFlRec;
extern UInt16 Core_Aux_Thermistor_Index_UsbFlRec;
extern UInt16 DCDC_Thermistor_Index_UsbFlRec;
extern UInt16 Flow_Meter_Left_Index_UsbFlRec;
extern UInt16 Flow_Meter_Right_Index_UsbFlRec;
extern UInt16 Safe_State_Index_UsbFlRec;
extern UInt16 Susp_RL_Index_UsbFlRec;
extern UInt16 Susp_RR_Index_UsbFlRec;
extern UInt16 Baudrate_Rx_Accu_Index_UsbFlRec;
extern UInt16 Baudrate_Rx_Inverter_RIGHT_Index_UsbFlRec;
extern UInt16 Baudrate_Rx_Inverter_LEFT_Index_UsbFlRec;
extern UInt16 Baudrate_Rx_Dash_Aux_Index_UsbFlRec;
extern UInt16 APPS1_Raw_Index_UsbFlRec;
extern UInt16 APPS2_Raw_Index_UsbFlRec;
extern UInt16 APPS_Value_Index_UsbFlRec;
extern UInt16 Brake_Index_UsbFlRec;
extern UInt16 Brake_Voltage_Index_UsbFlRec;
extern UInt16 DCDC_5V_APPS_Index_UsbFlRec;
extern UInt16 DASH_CAN_198_Counter_Index_UsbFlRec;
extern UInt16 RPM_FR_Index_UsbFlRec;
extern UInt16 Steering_Index_UsbFlRec;
extern UInt16 Core_Thermistor_Index_UsbFlRec;
extern UInt16 TSMS_Previous_Index_UsbFlRec;
extern UInt16 TSMS_After_Index_UsbFlRec;
extern UInt16 SC_State_Index_UsbFlRec;
extern UInt16 SC_Enable_Index_UsbFlRec;
extern UInt16 ENABLE_Accu_CAN_Rx_Index_UsbFlRec;
extern UInt16 ENABLE_Inv_LEFT_CAN_Rx_Index_UsbFlRec;
extern UInt16 ENABLE_Inv_RIGHT_CAN_Rx_Index_UsbFlRec;
extern UInt16 ENABLE_Sensor_Error_Index_UsbFlRec;
extern UInt16 ENABLE_Plausibility_Index_UsbFlRec;
extern UInt16 ENABLE_BSPD_State_Index_UsbFlRec;
extern UInt16 ENABLE_TSAL_Safe_State_Index_UsbFlRec;
extern UInt16 ENABLE_BMS_Status_Index_UsbFlRec;
extern UInt16 ENABLE_Dash_CAN_Tx_Index_UsbFlRec;
extern UInt16 ENABLE_Aux_CAN_Tx_Index_UsbFlRec;
extern UInt16 ENABLE_Accu_CAN_Tx_Index_UsbFlRec;
extern UInt16 ENABLE_Torque_CAN_Tx_Index_UsbFlRec;
extern UInt16 ENABLE_CAN_Status_Index_UsbFlRec;
extern UInt16 ENABLE_Dash_CAN_Rx_Index_UsbFlRec;
extern UInt16 ENABLE_Aux_CAN_Rx_Index_UsbFlRec;
extern UInt16 VDC_Datalogger_Index_UsbFlRec;
extern UInt16 IDC_Datalogger_Index_UsbFlRec;
extern UInt16 IAC_Left_Index_UsbFlRec;
extern UInt16 IAC_Right_Index_UsbFlRec;
extern UInt16 KWh_Index_UsbFlRec;
extern UInt16 KWh_Consumed_Index_UsbFlRec;
extern UInt16 KWh_Regen_Index_UsbFlRec;
extern UInt16 Kph_Index_UsbFlRec;
extern UInt16 Kph_Min_Index_UsbFlRec;
extern UInt16 Kw_Index_UsbFlRec;
extern UInt16 Meters_Max_Index_UsbFlRec;
extern UInt16 Meters_Min_Index_UsbFlRec;
extern UInt16 Accel_X_Index_UsbFlRec;
extern UInt16 Accel_Y_Index_UsbFlRec;
extern UInt16 Accel_Z_Index_UsbFlRec;
extern UInt16 Irms_LEFT_Index_UsbFlRec;
extern UInt16 Vout_LEFT_Index_UsbFlRec;
extern UInt16 Motor_Temp_LEFT_Index_UsbFlRec;
extern UInt16 IGBT_Temp_LEFT_Index_UsbFlRec;
extern UInt16 Inverter_Air_Temp_LEFT_Index_UsbFlRec;
extern UInt16 Inverter_Error_LEFT_Index_UsbFlRec;
extern UInt16 Inverter_btb_LEFT_Index_UsbFlRec;
extern UInt16 Motor_Power_LEFT_Index_UsbFlRec;
extern UInt16 RPM_LEFT_Index_UsbFlRec;
extern UInt16 Commanded_Torque_Left_Index_UsbFlRec;
extern UInt16 Irms_RIGHT_Index_UsbFlRec;
extern UInt16 Vout_RIGHT_Index_UsbFlRec;
extern UInt16 Motor_Temp_RIGHT_Index_UsbFlRec;
extern UInt16 IGBT_Temp_RIGHT_Index_UsbFlRec;
extern UInt16 Inverter_Air_Temp_RIGHT_Index_UsbFlRec;
extern UInt16 Inverter_Error_RIGHT_Index_UsbFlRec;
extern UInt16 Inverter_BTB_RIGHT_Index_UsbFlRec;
extern UInt16 Motor_Power_RIGHT_Index_UsbFlRec;
extern UInt16 RPM_RIGHT_Index_UsbFlRec;
extern UInt16 Commanded_Torque_Right_Index_UsbFlRec;
extern UInt16 Torque_Left_Index_UsbFlRec;
extern UInt16 Torque_Right_Index_UsbFlRec;
extern UInt16 Regen_AND_Index_UsbFlRec;
extern UInt16 Sensor_Error_Index_UsbFlRec;
extern UInt16 ED_Enable_Index_UsbFlRec;
extern UInt16 PL_Torque_Limiter_Percentage_Index_UsbFlRec;
extern UInt16 Braking_Torque_Index_UsbFlRec;
extern UInt16 Torue_before_mul_Index_UsbFlRec;
extern real_T rt_powd_snf(real_T u0, real_T u1);
extern real32_T rt_powf_snf(real32_T u0, real32_T u1);
extern real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);
extern real32_T look1_iflf_pbinlxpw(real32_T u0, const real32_T bp0[], const
  real32_T table[], uint32_T prevIndex[], uint32_T maxIndex);
extern void uMultiWordMul(const uint32_T u1[], int32_T n1, const uint32_T u2[],
  int32_T n2, uint32_T y[], int32_T n);
extern uint32_T MultiWord2uLong(const uint32_T u[]);
extern void uMultiWordShr(const uint32_T u1[], int32_T n1, uint32_T n2, uint32_T
  y[], int32_T n);
extern void mul_wide_s32(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi,
  uint32_T *ptrOutBitsLo);
extern int32_T mul_s32_hiSR(int32_T a, int32_T b, uint32_T aShift);
extern void Racing_20_NEGATIVEEdge_Init(B_NEGATIVEEdge_Racing_2019_T *localB,
  P_NEGATIVEEdge_Racing_2019_T *localP);
extern void Racing_2019_NEGATIVEEdge(real_T rtu_Enable, boolean_T rtu_IN,
  boolean_T rtu_INprevious, B_NEGATIVEEdge_Racing_2019_T *localB);
extern void Racing_20_POSITIVEEdge_Init(B_POSITIVEEdge_Racing_2019_T *localB,
  P_POSITIVEEdge_Racing_2019_T *localP);
extern void Racing_2019_POSITIVEEdge(real_T rtu_Enable, boolean_T rtu_IN,
  boolean_T rtu_INprevious, B_POSITIVEEdge_Racing_2019_T *localB);
extern void Racing_2019_s1t1(real32_T rtu_x, B_s1t1_Racing_2019_T *localB);
extern void Racing_2019_s1t4(real32_T rtu_x, B_s1t4_Racing_2019_T *localB);
extern void Racing_2019_s7t1(real32_T rtu_x, B_s7t1_Racing_2019_T *localB);
extern void Racing_201_IrmsLEFTRaw_Init(B_IrmsLEFTRaw_Racing_2019_T *localB,
  P_IrmsLEFTRaw_Racing_2019_T *localP);
extern void Racing_2019_IrmsLEFTRaw(real_T rtu_In1, B_IrmsLEFTRaw_Racing_2019_T *
  localB);
void Racing_2019_output0(void);
void Racing_2019_update0(void);
void Racing_2019_output2(void);
void Racing_2019_update2(void);
void Racing_2019_output3(void);
void Racing_2019_update3(void);
void Racing_2019_output4(void);
void Racing_2019_update4(void);
void Racing_2019_output5(void);
void Racing_2019_update5(void);

#endif

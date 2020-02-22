/*********************** dSPACE target specific file *************************

   Include file Racing_2019_rti.c:

   Definition of functions and variables for the system I/O and for
   the hardware and software interrupts used.

   RTI1401 7.8 (02-May-2017)
   Sun Aug 11 09:33:09 2019

   Copyright 2019, dSPACE GmbH. All rights reserved.

 *****************************************************************************/

#if !(defined(__RTI_SIMENGINE__) || defined(RTIMP_FRAME))
# error This file may be included only by the RTI(-MP) simulation engine.
#endif

/* Include the model header file. */
#include "Racing_2019.h"
#include "Racing_2019_private.h"

/* Defines for block output and parameter structure existence */
#define RTI_rtB_STRUCTURE_EXISTS       1
#define RTI_rtP_STRUCTURE_EXISTS       1
#define RTB_STRUCTURE_NAME             Racing_2019_B
#define RTP_STRUCTURE_NAME             Racing_2019_P

/* dSPACE generated includes for header files */
#include <brtenv.h>
#include <rtkernel.h>
#include <rti_assert.h>
#include <rtidefineddatatypes.h>
#include <dsflrecusb.h>
#include <rti_msg_access.h>
#include <rtiusbflightrec_msg.h>
#include <rtican_ds1401.h>
#ifndef dsRtmGetNumSampleTimes
# define dsRtmGetNumSampleTimes(rtm)   6
#endif

#ifndef dsRtmGetTPtr
# define dsRtmGetTPtr(rtm)             ((rtm)->Timing.t)
#endif

#ifndef dsRtmSetTaskTime
# define dsRtmSetTaskTime(rtm, sti, val) (dsRtmGetTPtr((rtm))[sti] = (val))
#endif

/****** Definitions: task functions for timer tasks *********************/

/* Timer Task 1. (Base rate). */
static void rti_TIMERA(rtk_p_task_control_block task)
{
  /* Task entry code BEGIN */
  /* -- None. -- */
  /* Task entry code END */

  /* Task code. */
  baseRateService(task);

  /* Task exit code BEGIN */
  /* -- None. -- */
  /* Task exit code END */
}

/* Timer Task 2. (Sample rate). */
static void rti_TIMERA2(rtk_p_task_control_block task)
{
  /* Task code. */
  sampleRateService(task);
}

/* Timer Task 3. (Sample rate). */
static void rti_TIMERA3(rtk_p_task_control_block task)
{
  /* Task code. */
  sampleRateService(task);
}

/* Timer Task 4. (Sample rate). */
static void rti_TIMERA4(rtk_p_task_control_block task)
{
  /* Task code. */
  sampleRateService(task);
}

/* Timer Task 5. (Sample rate). */
static void rti_TIMERA5(rtk_p_task_control_block task)
{
  /* Task code. */
  sampleRateService(task);
}

/* ===== Declarations of RTI blocks ======================================== */

/* dSPACE I/O Board DSUSBFLIGHTREC #1 */
UInt16 ENABLE_Index_UsbFlRec;
UInt16 Car_Reset_Index_UsbFlRec;
UInt16 BMS_Reset_Index_UsbFlRec;
UInt16 BMS_Status_Index_UsbFlRec;
UInt16 Idc_Accu_x10_Index_UsbFlRec;
UInt16 VDC_BMS_Index_UsbFlRec;
UInt16 s1c1_Index_UsbFlRec;
UInt16 s1c10_Index_UsbFlRec;
UInt16 s1c11_Index_UsbFlRec;
UInt16 s1c12_Index_UsbFlRec;
UInt16 s1c2_Index_UsbFlRec;
UInt16 s1c3_Index_UsbFlRec;
UInt16 s1c4_Index_UsbFlRec;
UInt16 s1c5_Index_UsbFlRec;
UInt16 s1c6_Index_UsbFlRec;
UInt16 s1c7_Index_UsbFlRec;
UInt16 s1c8_Index_UsbFlRec;
UInt16 s1c9_Index_UsbFlRec;
UInt16 s1t1_Index_UsbFlRec;
UInt16 s1t2_Index_UsbFlRec;
UInt16 s1t3_Index_UsbFlRec;
UInt16 s1t4_Index_UsbFlRec;
UInt16 s2c1_Index_UsbFlRec;
UInt16 s2c10_Index_UsbFlRec;
UInt16 s2c11_Index_UsbFlRec;
UInt16 s2c12_Index_UsbFlRec;
UInt16 s2c2_Index_UsbFlRec;
UInt16 s2c3_Index_UsbFlRec;
UInt16 s2c4_Index_UsbFlRec;
UInt16 s2c5_Index_UsbFlRec;
UInt16 s2c6_Index_UsbFlRec;
UInt16 s2c7_Index_UsbFlRec;
UInt16 s2c8_Index_UsbFlRec;
UInt16 s2c9_Index_UsbFlRec;
UInt16 s2t1_Index_UsbFlRec;
UInt16 s2t2_Index_UsbFlRec;
UInt16 s2t3_Index_UsbFlRec;
UInt16 s2t4_Index_UsbFlRec;
UInt16 s3c1_Index_UsbFlRec;
UInt16 s3c10_Index_UsbFlRec;
UInt16 s3c11_Index_UsbFlRec;
UInt16 s3c12_Index_UsbFlRec;
UInt16 s3c2_Index_UsbFlRec;
UInt16 s3c3_Index_UsbFlRec;
UInt16 s3c4_Index_UsbFlRec;
UInt16 s3c5_Index_UsbFlRec;
UInt16 s3c6_Index_UsbFlRec;
UInt16 s3c7_Index_UsbFlRec;
UInt16 s3c8_Index_UsbFlRec;
UInt16 s3c9_Index_UsbFlRec;
UInt16 s3t1_Index_UsbFlRec;
UInt16 s3t2_Index_UsbFlRec;
UInt16 s3t3_Index_UsbFlRec;
UInt16 s3t4_Index_UsbFlRec;
UInt16 s4c1_Index_UsbFlRec;
UInt16 s4c10_Index_UsbFlRec;
UInt16 s4c11_Index_UsbFlRec;
UInt16 s4c12_Index_UsbFlRec;
UInt16 s4c2_Index_UsbFlRec;
UInt16 s4c3_Index_UsbFlRec;
UInt16 s4c4_Index_UsbFlRec;
UInt16 s4c5_Index_UsbFlRec;
UInt16 s4c6_Index_UsbFlRec;
UInt16 s4c7_Index_UsbFlRec;
UInt16 s4c8_Index_UsbFlRec;
UInt16 s4c9_Index_UsbFlRec;
UInt16 s4t1_Index_UsbFlRec;
UInt16 s4t2_Index_UsbFlRec;
UInt16 s4t3_Index_UsbFlRec;
UInt16 s4t4_Index_UsbFlRec;
UInt16 s5c1_Index_UsbFlRec;
UInt16 s5c10_Index_UsbFlRec;
UInt16 s5c11_Index_UsbFlRec;
UInt16 s5c12_Index_UsbFlRec;
UInt16 s5c2_Index_UsbFlRec;
UInt16 s5c3_Index_UsbFlRec;
UInt16 s5c4_Index_UsbFlRec;
UInt16 s5c5_Index_UsbFlRec;
UInt16 s5c6_Index_UsbFlRec;
UInt16 s5c7_Index_UsbFlRec;
UInt16 s5c8_Index_UsbFlRec;
UInt16 s5c9_Index_UsbFlRec;
UInt16 s5t1_Index_UsbFlRec;
UInt16 s5t2_Index_UsbFlRec;
UInt16 s5t3_Index_UsbFlRec;
UInt16 s5t4_Index_UsbFlRec;
UInt16 s6c1_Index_UsbFlRec;
UInt16 s6c10_Index_UsbFlRec;
UInt16 s6c11_Index_UsbFlRec;
UInt16 s6c12_Index_UsbFlRec;
UInt16 s6c2_Index_UsbFlRec;
UInt16 s6c3_Index_UsbFlRec;
UInt16 s6c4_Index_UsbFlRec;
UInt16 s6c5_Index_UsbFlRec;
UInt16 s6c6_Index_UsbFlRec;
UInt16 s6c7_Index_UsbFlRec;
UInt16 s6c8_Index_UsbFlRec;
UInt16 s6c9_Index_UsbFlRec;
UInt16 s6t1_Index_UsbFlRec;
UInt16 s6t2_Index_UsbFlRec;
UInt16 s6t3_Index_UsbFlRec;
UInt16 s6t4_Index_UsbFlRec;
UInt16 s7c1_Index_UsbFlRec;
UInt16 s7c10_Index_UsbFlRec;
UInt16 s7c11_Index_UsbFlRec;
UInt16 s7c12_Index_UsbFlRec;
UInt16 s7c2_Index_UsbFlRec;
UInt16 s7c3_Index_UsbFlRec;
UInt16 s7c4_Index_UsbFlRec;
UInt16 s7c5_Index_UsbFlRec;
UInt16 s7c6_Index_UsbFlRec;
UInt16 s7c7_Index_UsbFlRec;
UInt16 s7c8_Index_UsbFlRec;
UInt16 s7c9_Index_UsbFlRec;
UInt16 s7t1_Index_UsbFlRec;
UInt16 s7t2_Index_UsbFlRec;
UInt16 s7t3_Index_UsbFlRec;
UInt16 s7t4_Index_UsbFlRec;
UInt16 Aux_CAN_314_Index_UsbFlRec;
UInt16 Aux_CAN_357_Index_UsbFlRec;
UInt16 Aux_CAN_412_Index_UsbFlRec;
UInt16 Aux_Thermistor_Index_UsbFlRec;
UInt16 BSPD_Status_Index_UsbFlRec;
UInt16 Core_Aux_Thermistor_Index_UsbFlRec;
UInt16 DCDC_Thermistor_Index_UsbFlRec;
UInt16 Flow_Meter_Left_Index_UsbFlRec;
UInt16 Flow_Meter_Right_Index_UsbFlRec;
UInt16 Safe_State_Index_UsbFlRec;
UInt16 Susp_RL_Index_UsbFlRec;
UInt16 Susp_RR_Index_UsbFlRec;
UInt16 Baudrate_Rx_Accu_Index_UsbFlRec;
UInt16 Baudrate_Rx_Inverter_RIGHT_Index_UsbFlRec;
UInt16 Baudrate_Rx_Inverter_LEFT_Index_UsbFlRec;
UInt16 Baudrate_Rx_Dash_Aux_Index_UsbFlRec;
UInt16 APPS1_Raw_Index_UsbFlRec;
UInt16 APPS2_Raw_Index_UsbFlRec;
UInt16 APPS_Value_Index_UsbFlRec;
UInt16 Brake_Index_UsbFlRec;
UInt16 Brake_Voltage_Index_UsbFlRec;
UInt16 DCDC_5V_APPS_Index_UsbFlRec;
UInt16 DASH_CAN_198_Counter_Index_UsbFlRec;
UInt16 RPM_FR_Index_UsbFlRec;
UInt16 Steering_Index_UsbFlRec;
UInt16 Core_Thermistor_Index_UsbFlRec;
UInt16 TSMS_Previous_Index_UsbFlRec;
UInt16 TSMS_After_Index_UsbFlRec;
UInt16 SC_State_Index_UsbFlRec;
UInt16 SC_Enable_Index_UsbFlRec;
UInt16 ENABLE_Accu_CAN_Rx_Index_UsbFlRec;
UInt16 ENABLE_Inv_LEFT_CAN_Rx_Index_UsbFlRec;
UInt16 ENABLE_Inv_RIGHT_CAN_Rx_Index_UsbFlRec;
UInt16 ENABLE_Sensor_Error_Index_UsbFlRec;
UInt16 ENABLE_Plausibility_Index_UsbFlRec;
UInt16 ENABLE_BSPD_State_Index_UsbFlRec;
UInt16 ENABLE_TSAL_Safe_State_Index_UsbFlRec;
UInt16 ENABLE_BMS_Status_Index_UsbFlRec;
UInt16 ENABLE_Dash_CAN_Tx_Index_UsbFlRec;
UInt16 ENABLE_Aux_CAN_Tx_Index_UsbFlRec;
UInt16 ENABLE_Accu_CAN_Tx_Index_UsbFlRec;
UInt16 ENABLE_Torque_CAN_Tx_Index_UsbFlRec;
UInt16 ENABLE_CAN_Status_Index_UsbFlRec;
UInt16 ENABLE_Dash_CAN_Rx_Index_UsbFlRec;
UInt16 ENABLE_Aux_CAN_Rx_Index_UsbFlRec;
UInt16 VDC_Datalogger_Index_UsbFlRec;
UInt16 IDC_Datalogger_Index_UsbFlRec;
UInt16 IAC_Left_Index_UsbFlRec;
UInt16 IAC_Right_Index_UsbFlRec;
UInt16 KWh_Index_UsbFlRec;
UInt16 KWh_Consumed_Index_UsbFlRec;
UInt16 KWh_Regen_Index_UsbFlRec;
UInt16 Kph_Index_UsbFlRec;
UInt16 Kph_Min_Index_UsbFlRec;
UInt16 Kw_Index_UsbFlRec;
UInt16 Meters_Max_Index_UsbFlRec;
UInt16 Meters_Min_Index_UsbFlRec;
UInt16 Accel_X_Index_UsbFlRec;
UInt16 Accel_Y_Index_UsbFlRec;
UInt16 Accel_Z_Index_UsbFlRec;
UInt16 Irms_LEFT_Index_UsbFlRec;
UInt16 Vout_LEFT_Index_UsbFlRec;
UInt16 Motor_Temp_LEFT_Index_UsbFlRec;
UInt16 IGBT_Temp_LEFT_Index_UsbFlRec;
UInt16 Inverter_Air_Temp_LEFT_Index_UsbFlRec;
UInt16 Inverter_Error_LEFT_Index_UsbFlRec;
UInt16 Inverter_btb_LEFT_Index_UsbFlRec;
UInt16 Motor_Power_LEFT_Index_UsbFlRec;
UInt16 RPM_LEFT_Index_UsbFlRec;
UInt16 Commanded_Torque_Left_Index_UsbFlRec;
UInt16 Irms_RIGHT_Index_UsbFlRec;
UInt16 Vout_RIGHT_Index_UsbFlRec;
UInt16 Motor_Temp_RIGHT_Index_UsbFlRec;
UInt16 IGBT_Temp_RIGHT_Index_UsbFlRec;
UInt16 Inverter_Air_Temp_RIGHT_Index_UsbFlRec;
UInt16 Inverter_Error_RIGHT_Index_UsbFlRec;
UInt16 Inverter_BTB_RIGHT_Index_UsbFlRec;
UInt16 Motor_Power_RIGHT_Index_UsbFlRec;
UInt16 RPM_RIGHT_Index_UsbFlRec;
UInt16 Commanded_Torque_Right_Index_UsbFlRec;
UInt16 Torque_Left_Index_UsbFlRec;
UInt16 Torque_Right_Index_UsbFlRec;
UInt16 Regen_AND_Index_UsbFlRec;
UInt16 Sensor_Error_Index_UsbFlRec;
UInt16 ED_Enable_Index_UsbFlRec;
UInt16 PL_Torque_Limiter_Percentage_Index_UsbFlRec;
UInt16 Braking_Torque_Index_UsbFlRec;
UInt16 Torue_before_mul_Index_UsbFlRec;

/* dSPACE I/O Board DS1_RTICAN #1 */

/* ...  definition of channel struct */
can_tp1_canChannel* can_type1_channel_M1_C1;

/* ...  service variables for the RTICAN status block */
can_tp1_canService* can_type1_service_M1_C1[13];

/* ...  definition of channel struct */
can_tp1_canChannel* can_type1_channel_M1_C2;

/* ...  service variables for the RTICAN status block */
can_tp1_canService* can_type1_service_M1_C2[13];

/* declare pointers to CAN message structures for support of TX-Custom code */
can_tp1_canMsg* CANTP1_TX_SPMSG_M1_C1_STD;
can_tp1_canMsg* CANTP1_TX_SPMSG_M1_C1_XTD;

/* declare pointers to CAN message structures for support of TX-Custom code */
can_tp1_canMsg* CANTP1_TX_SPMSG_M1_C2_STD;
can_tp1_canMsg* CANTP1_TX_SPMSG_M1_C2_XTD;

/* ... definition of message variable for the RTICAN blocks */
can_tp1_canMsg* can_type1_msg_M1[CANTP1_M1_NUMMSG];

/* dSPACE I/O Board DS1_RTICAN #2 */

/* ...  definition of channel struct */
can_tp1_canChannel* can_type1_channel_M2_C2;

/* ...  service variables for the RTICAN status block */
can_tp1_canService* can_type1_service_M2_C2[13];

/* ...  definition of channel struct */
can_tp1_canChannel* can_type1_channel_M2_C1;

/* ...  service variables for the RTICAN status block */
can_tp1_canService* can_type1_service_M2_C1[13];

/* declare pointers to CAN message structures for support of TX-Custom code */
can_tp1_canMsg* CANTP1_TX_SPMSG_M2_C2_STD;
can_tp1_canMsg* CANTP1_TX_SPMSG_M2_C2_XTD;

/* declare pointers to CAN message structures for support of TX-Custom code */
can_tp1_canMsg* CANTP1_TX_SPMSG_M2_C1_STD;
can_tp1_canMsg* CANTP1_TX_SPMSG_M2_C1_XTD;

/* ... definition of message variable for the RTICAN blocks */
can_tp1_canMsg* can_type1_msg_M2[CANTP1_M2_NUMMSG];

/* dSPACE I/O Board RTICAN_GLOBAL #0 */

/* ===== Definition of interface functions for simulation engine =========== */
#if GRTINTERFACE == 1
#ifdef MULTITASKING
# define dsIsSampleHit(RTM,sti)        rtmGetSampleHitPtr(RTM)[sti]
#else
# define dsIsSampleHit(RTM,sti)        rtmIsSampleHit(RTM,sti,0)
#endif

#else
#ifndef rtmStepTask
# define rtmStepTask(rtm, idx)         ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

# define dsIsSampleHit(RTM,sti)        rtmStepTask(RTM, sti)
#endif

#undef __INLINE
#if defined(_INLINE)
# define __INLINE                      static inline
#else
# define __INLINE                      static
#endif

/*Define additional variables*/
static time_T dsTFinal = -1.0;

#define dsGetTFinal(rtm)               (dsTFinal)

static time_T dsStepSize = 0.001;

# define dsGetStepSize(rtm)            (dsStepSize)

static void rti_mdl_initialize_host_services(void)
{
  ts_timestamp_type ts = { 0, 0 };

  host_service(1, &ts);
  DsDaq_Init(0, 32, 1);
}

static void rti_mdl_initialize_io_boards(void)
{
  /* Registering of RTI products and modules at VCM */
  {
    vcm_module_register(VCM_MID_RTI1401, (void *) 0,
                        VCM_TXT_RTI1401, 7, 8, 0,
                        VCM_VERSION_RELEASE, 0, 0, 0, VCM_CTRL_NO_ST);

    {
      vcm_module_descriptor_type* msg_mod_ptr;
      msg_mod_ptr = vcm_module_register(VCM_MID_MATLAB, (void *) 0,
        VCM_TXT_MATLAB, 9, 2, 0,
        VCM_VERSION_RELEASE, 0, 0, 0, VCM_CTRL_NO_ST);
      vcm_module_register(VCM_MID_SIMULINK, msg_mod_ptr,
                          VCM_TXT_SIMULINK, 8, 9, 0,
                          VCM_VERSION_RELEASE, 0, 0, 0, VCM_CTRL_NO_ST);
      vcm_module_register(VCM_MID_RTW, msg_mod_ptr,
                          VCM_TXT_RTW, 8, 12, 0,
                          VCM_VERSION_RELEASE, 0, 0, 0, VCM_CTRL_NO_ST);
      vcm_module_register(VCM_MID_STATEFLOW, msg_mod_ptr,
                          VCM_TXT_STATEFLOW, 8, 9, 0,
                          VCM_VERSION_RELEASE, 0, 0, 0, VCM_CTRL_NO_ST);
      vcm_module_register(VCM_MID_STATEFLOW_CODER, msg_mod_ptr,
                          VCM_TXT_STATEFLOW_CODER, 8, 12, 0,
                          VCM_VERSION_RELEASE, 0, 0, 0, VCM_CTRL_NO_ST);
    }

    vcm_module_register(VCM_MID_RTICAN, (void *) 0,
                        VCM_TXT_RTICAN, 3, 4, 4,
                        VCM_VERSION_RELEASE, 0, 0, 0, VCM_CTRL_NO_ST);
  }

  /* dSPACE I/O Board DS1401STDADCT4 #1 */
  adc_tp4_init(ADC_TP4_1_MODULE_ADDR);

  /* dSPACE I/O Board DS1401STDADCT4 #1 Unit:ADC */
  adc_tp4_single_init2(ADC_TP4_1_MODULE_ADDR,
                       ADC_TP4_CH6,
                       ADC_TP4_INPUT_VOLTAGE_RANGE_2,
                       ADC_TP4_TRIG_SW,
                       0.0);
  adc_tp4_single_init2(ADC_TP4_1_MODULE_ADDR,
                       ADC_TP4_CH5,
                       ADC_TP4_INPUT_VOLTAGE_RANGE_2,
                       ADC_TP4_TRIG_SW,
                       0.0);
  adc_tp4_single_init2(ADC_TP4_1_MODULE_ADDR,
                       ADC_TP4_CH7,
                       ADC_TP4_INPUT_VOLTAGE_RANGE_2,
                       ADC_TP4_TRIG_SW,
                       0.0);
  adc_tp4_single_init2(ADC_TP4_1_MODULE_ADDR,
                       ADC_TP4_CH3,
                       ADC_TP4_INPUT_VOLTAGE_RANGE_2,
                       ADC_TP4_TRIG_SW,
                       0.0);
  adc_tp4_single_init2(ADC_TP4_1_MODULE_ADDR,
                       ADC_TP4_CH1,
                       ADC_TP4_INPUT_VOLTAGE_RANGE_2,
                       ADC_TP4_TRIG_SW,
                       0.0);
  adc_tp4_single_init2(ADC_TP4_1_MODULE_ADDR,
                       ADC_TP4_CH2,
                       ADC_TP4_INPUT_VOLTAGE_RANGE_2,
                       ADC_TP4_TRIG_SW,
                       0.0);

  /* dSPACE I/O Board DS1401STDDIOT4 #1 */
  /* main init for DIO TP4 Module 1 */
  dio_tp4_init(DIO_TP4_1_MODULE_ADDR);

  /* dSPACE I/O Board DS1401STDDIOT4 #1 Unit:DIGOUT */
  /* setup digital output mode (supply rails) for channel 5 on port 1 */
  dio_tp4_digout_init(DIO_TP4_1_MODULE_ADDR, 1, DIO_TP4_MASK_CH5, 1, 1);

  /* setup digital output mode (supply rails) for channel 10 on port 1 */
  dio_tp4_digout_init(DIO_TP4_1_MODULE_ADDR, 1, DIO_TP4_MASK_CH10, 1, 1);

  /* setup digital output mode (supply rails) for channel 4 on port 1 */
  dio_tp4_digout_init(DIO_TP4_1_MODULE_ADDR, 1, DIO_TP4_MASK_CH4, 1, 1);

  /* dSPACE I/O Board DSUSBFLIGHTREC #1 */
  {
    /* dSPACE I/O Board DSUSBFLIGHTREC #1 Unit:SETUP */
    /* This part of code has been generated from the block: */
    /* USB device flight recorder initialization function */

    /* if not already done, initialize the USB device flight recorder */
    dsflrec_usb_initialize(1, RTI_USB_FLREC_DEFAULT_BLOCK_SIZE);
  }

  /* dSPACE I/O Board DSUSBFLIGHTREC #1 Unit:WRITE */
  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Car_Reset_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&Car_Reset_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "BMS_Reset_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&BMS_Reset_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "BMS_Status_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&BMS_Status_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Idc_Accu_x10_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&Idc_Accu_x10_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "VDC_BMS_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&VDC_BMS_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1c1_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s1c1_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1c10_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s1c10_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1c11_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s1c11_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1c12_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s1c12_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1c2_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s1c2_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1c3_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s1c3_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1c4_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s1c4_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1c5_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s1c5_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1c6_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s1c6_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1c7_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s1c7_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1c8_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s1c8_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1c9_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s1c9_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1t1_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s1t1_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1t2_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s1t2_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1t3_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s1t3_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s1t4_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s1t4_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2c1_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s2c1_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2c10_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s2c10_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2c11_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s2c11_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2c12_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s2c12_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2c2_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s2c2_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2c3_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s2c3_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2c4_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s2c4_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2c5_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s2c5_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2c6_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s2c6_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2c7_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s2c7_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2c8_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s2c8_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2c9_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s2c9_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2t1_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s2t1_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2t2_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s2t2_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2t3_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s2t3_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s2t4_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s2t4_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3c1_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s3c1_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3c10_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s3c10_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3c11_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s3c11_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3c12_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s3c12_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3c2_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s3c2_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3c3_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s3c3_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3c4_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s3c4_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3c5_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s3c5_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3c6_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s3c6_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3c7_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s3c7_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3c8_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s3c8_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3c9_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s3c9_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3t1_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s3t1_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3t2_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s3t2_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3t3_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s3t3_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s3t4_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s3t4_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4c1_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s4c1_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4c10_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s4c10_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4c11_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s4c11_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4c12_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s4c12_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4c2_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s4c2_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4c3_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s4c3_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4c4_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s4c4_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4c5_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s4c5_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4c6_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s4c6_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4c7_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s4c7_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4c8_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s4c8_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4c9_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s4c9_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4t1_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s4t1_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4t2_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s4t2_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4t3_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s4t3_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s4t4_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s4t4_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5c1_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s5c1_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5c10_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s5c10_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5c11_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s5c11_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5c12_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s5c12_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5c2_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s5c2_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5c3_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s5c3_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5c4_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s5c4_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5c5_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s5c5_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5c6_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s5c6_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5c7_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s5c7_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5c8_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s5c8_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5c9_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s5c9_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5t1_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s5t1_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5t2_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s5t2_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5t3_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s5t3_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s5t4_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s5t4_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6c1_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s6c1_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6c10_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s6c10_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6c11_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s6c11_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6c12_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s6c12_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6c2_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s6c2_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6c3_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s6c3_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6c4_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s6c4_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6c5_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s6c5_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6c6_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s6c6_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6c7_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s6c7_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6c8_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s6c8_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6c9_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s6c9_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6t1_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s6t1_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6t2_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s6t2_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6t3_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s6t3_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s6t4_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s6t4_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7c1_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s7c1_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7c10_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s7c10_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7c11_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s7c11_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7c12_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s7c12_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7c2_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s7c2_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7c3_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s7c3_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7c4_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s7c4_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7c5_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s7c5_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7c6_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s7c6_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7c7_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s7c7_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7c8_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s7c8_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7c9_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&s7c9_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7t1_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s7t1_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7t2_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s7t2_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7t3_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s7t3_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "s7t4_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&s7t4_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Aux_CAN_314_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&Aux_CAN_314_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Aux_CAN_357_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&Aux_CAN_357_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Aux_CAN_412_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&Aux_CAN_412_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Aux_Thermistor_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Aux_Thermistor_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "BSPD_Status_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&BSPD_Status_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Core_Aux_Thermistor_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Core_Aux_Thermistor_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "DCDC_Thermistor_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&DCDC_Thermistor_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Flow_Meter_Left_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Flow_Meter_Left_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Flow_Meter_Right_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Flow_Meter_Right_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Safe_State_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&Safe_State_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Susp_RL_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Susp_RL_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Susp_RR_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Susp_RR_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Baudrate_Rx_Accu_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&Baudrate_Rx_Accu_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Baudrate_Rx_Inverter_RIGHT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&Baudrate_Rx_Inverter_RIGHT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Baudrate_Rx_Inverter_LEFT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&Baudrate_Rx_Inverter_LEFT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Baudrate_Rx_Dash_Aux_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&Baudrate_Rx_Dash_Aux_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "APPS1_Raw_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&APPS1_Raw_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "APPS2_Raw_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&APPS2_Raw_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "APPS_Value_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&APPS_Value_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Brake_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Brake_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Brake_Voltage_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&Brake_Voltage_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "DCDC_5V_APPS_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&DCDC_5V_APPS_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "DASH_CAN_198_Counter_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&DASH_CAN_198_Counter_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "RPM_FR_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&RPM_FR_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Steering_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Steering_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Core_Thermistor_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Core_Thermistor_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "TSMS_Previous_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&TSMS_Previous_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "TSMS_After_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&TSMS_After_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "SC_State_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&SC_State_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "SC_Enable_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&SC_Enable_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_Accu_CAN_Rx_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_Accu_CAN_Rx_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_Inv_LEFT_CAN_Rx_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_Inv_LEFT_CAN_Rx_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_Inv_RIGHT_CAN_Rx_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_Inv_RIGHT_CAN_Rx_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_Sensor_Error_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_Sensor_Error_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_Plausibility_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_Plausibility_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_BSPD_State_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_BSPD_State_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_TSAL_Safe_State_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_TSAL_Safe_State_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_BMS_Status_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_BMS_Status_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_Dash_CAN_Tx_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_Dash_CAN_Tx_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_Aux_CAN_Tx_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_Aux_CAN_Tx_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_Accu_CAN_Tx_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_Accu_CAN_Tx_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_Torque_CAN_Tx_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_Torque_CAN_Tx_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_CAN_Status_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_CAN_Status_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_Dash_CAN_Rx_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_Dash_CAN_Rx_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ENABLE_Aux_CAN_Rx_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ENABLE_Aux_CAN_Rx_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "VDC_Datalogger_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&VDC_Datalogger_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "IDC_Datalogger_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&IDC_Datalogger_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "IAC_Left_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&IAC_Left_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "IAC_Right_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&IAC_Right_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "KWh_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&KWh_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "KWh_Consumed_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&KWh_Consumed_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "KWh_Regen_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&KWh_Regen_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Kph_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Kph_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Kph_Min_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Kph_Min_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Kw_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&Kw_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Meters_Max_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Meters_Max_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Meters_Min_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Meters_Min_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Accel_X_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&Accel_X_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Accel_Y_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&Accel_Y_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Accel_Z_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&Accel_Z_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Irms_LEFT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&Irms_LEFT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Vout_LEFT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&Vout_LEFT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Motor_Temp_LEFT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&Motor_Temp_LEFT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "IGBT_Temp_LEFT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&IGBT_Temp_LEFT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Inverter_Air_Temp_LEFT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&Inverter_Air_Temp_LEFT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Inverter_Error_LEFT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT8,&Inverter_Error_LEFT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Inverter_btb_LEFT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT8,&Inverter_btb_LEFT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Motor_Power_LEFT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&Motor_Power_LEFT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "RPM_LEFT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&RPM_LEFT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Commanded_Torque_Left_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&Commanded_Torque_Left_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Irms_RIGHT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&Irms_RIGHT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Vout_RIGHT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&Vout_RIGHT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Motor_Temp_RIGHT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&Motor_Temp_RIGHT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "IGBT_Temp_RIGHT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&IGBT_Temp_RIGHT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Inverter_Air_Temp_RIGHT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&Inverter_Air_Temp_RIGHT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Inverter_Error_RIGHT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT8,&Inverter_Error_RIGHT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Inverter_BTB_RIGHT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT8,&Inverter_BTB_RIGHT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Motor_Power_RIGHT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&Motor_Power_RIGHT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "RPM_RIGHT_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_INT16,&RPM_RIGHT_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Commanded_Torque_Right_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&Commanded_Torque_Right_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Torque_Left_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Torque_Left_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Torque_Right_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Torque_Right_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Regen_AND_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&Regen_AND_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Sensor_Error_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT16,&Sensor_Error_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "ED_Enable_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&ED_Enable_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "PL_Torque_Limiter_Percentage_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&PL_Torque_Limiter_Percentage_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Braking_Torque_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_UINT8,&Braking_Torque_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  {
    /* dSPACE USB FLIGHT RECORDER WRITE */
    Int16 errorCode = 0;

    /* ----------------------------------------------------------------------  */
    /* |  prototype function                                                 | */
    /* ----------------------------------------------------------------------  */
    /* | Int16  dsflrec_usb_add_variable (char       *VarName,               | */
    /* |                                  UInt16    DataTypeId,              | */
    /* |                                  UInt16    *VarIndex);              | */
    /* ----------------------------------------------------------------------- */
    /* ----------------------------------------------------------------------- */
    char variable_name[]= "Torue_before_mul_UsbFlRec";
    errorCode = dsflrec_usb_add_variable(&variable_name[0],
      DSFLREC_DATA_TYPE_FLOAT32,&Torue_before_mul_Index_UsbFlRec);

#ifdef DEBUG_INIT

    if (errorCode == DSFLREC_USB_VAR_ALREADY_EXIST)
      rti_msg_info_set(RTI_USB_FLREC_VARIABLE_ERROR);

#endif

    if (errorCode == DSFLREC_USB_INIT_TABLE_FULL)
      rti_msg_error_set(RTI_USB_FLREC_INIT_TABLE_ERROR);
  }

  /* dSPACE I/O Board DS1401BASEII #1 Unit:ACCELREAD */
  {
    /* IO initialization of the acceleration sensor */
    ds1401_accel_sensor_init(SYS1401_ACCEL_SENSOR_RANGE_4G,
      SYS1401_ACCEL_SENSOR_MOST_RECENT_READ,
      SYS1401_ACCEL_SENSOR_OUTPUT_DATA_RATE_2);
  }

  /* dSPACE I/O Board DS1_RTICAN #1 */
  /* Initialization of DS1501 board */
  can_tp1_communication_init(can_tp1_address_table[0].module_addr,
    CAN_TP1_INT_ENABLE);

  /* dSPACE RTICAN MASTER SETUP Block */
  /* ... Initialize the CAN communication: 1000 kbit/s */
  can_type1_channel_M1_C1 = can_tp1_channel_init(can_tp1_address_table[0].
    module_addr, 0, (1000 * 1000), CAN_TP1_STD, CAN_TP1_NO_SUBINT);
  can_tp1_channel_termination_set(can_type1_channel_M1_C1,
    CAN_TP1_TERMINATION_ON);

  /* ... Initialize TX message structs for custom code  */
  CANTP1_TX_SPMSG_M1_C1_STD = can_tp1_msg_tx_register(can_type1_channel_M1_C1, 3,
    1050, CAN_TP1_STD, CAN_TP1_TIMECOUNT_INFO | CAN_TP1_DELAYCOUNT_INFO |
    CAN_TP1_MSG_INFO, CAN_TP1_NO_SUBINT, 0, CAN_TP1_TRIGGER_MSG,
    CAN_TP1_TIMEOUT_NORMAL);
  CANTP1_TX_SPMSG_M1_C1_XTD = can_tp1_msg_tx_register(can_type1_channel_M1_C1, 3,
    1100, CAN_TP1_EXT, CAN_TP1_TIMECOUNT_INFO | CAN_TP1_DELAYCOUNT_INFO |
    CAN_TP1_MSG_INFO, CAN_TP1_NO_SUBINT, 0, CAN_TP1_TRIGGER_MSG,
    CAN_TP1_TIMEOUT_NORMAL);

  /* dSPACE RTICAN MASTER SETUP Block */
  /* ... Initialize the Partial Networking Settings */

  /* dSPACE RTICAN TX Message Block: "Inverter_Left_CAN_Tx" Id:353 */
  /* ... Register message */
  can_type1_msg_M1[CANTP1_M1_C1_TX_STD_0X161] = can_tp1_msg_tx_register
    (can_type1_channel_M1_C1, 0, 353, CAN_TP1_STD, (CAN_TP1_TIMECOUNT_INFO),
     CAN_TP1_NO_SUBINT, 0, CAN_TP1_TRIGGER_MSG, CAN_TP1_TIMEOUT_NORMAL);

  /* dSPACE RTICAN RX Message Block: "Inverter_LEFT_Rx" Id:385 */
  /* ... Register message */
  can_type1_msg_M1[CANTP1_M1_C1_RX_STD_0X181] = can_tp1_msg_rx_register
    (can_type1_channel_M1_C1, 2, 385, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN Status block */
  /* ... Register employed functions */
  can_type1_service_M1_C1[CANTP1_M1_C1_Status] = can_tp1_service_register
    (can_type1_channel_M1_C1,CAN_TP1_SERVICE_BUSSTATUS);
  can_type1_service_M1_C1[CANTP1_M1_C1_StuffErrors] = can_tp1_service_register
    (can_type1_channel_M1_C1,CAN_TP1_SERVICE_STUFFBIT_ERR);
  can_type1_service_M1_C1[CANTP1_M1_C1_FormatErrors] = can_tp1_service_register
    (can_type1_channel_M1_C1,CAN_TP1_SERVICE_FORM_ERR);
  can_type1_service_M1_C1[CANTP1_M1_C1_AckErrors] = can_tp1_service_register
    (can_type1_channel_M1_C1,CAN_TP1_SERVICE_ACK_ERR);
  can_type1_service_M1_C1[CANTP1_M1_C1_Bit0Errors] = can_tp1_service_register
    (can_type1_channel_M1_C1,CAN_TP1_SERVICE_BIT0_ERR);
  can_type1_service_M1_C1[CANTP1_M1_C1_Bit1Errors] = can_tp1_service_register
    (can_type1_channel_M1_C1,CAN_TP1_SERVICE_BIT1_ERR);
  can_type1_service_M1_C1[CANTP1_M1_C1_CRCErrors] = can_tp1_service_register
    (can_type1_channel_M1_C1,CAN_TP1_SERVICE_CRC_ERR);
  can_type1_service_M1_C1[CANTP1_M1_C1_RXLost] = can_tp1_service_register
    (can_type1_channel_M1_C1,CAN_TP1_SERVICE_RX_LOST);
  can_type1_service_M1_C1[CANTP1_M1_C1_DataLost] = can_tp1_service_register
    (can_type1_channel_M1_C1,CAN_TP1_SERVICE_DATA_LOST);
  can_type1_service_M1_C1[CANTP1_M1_C1_RXOK] = can_tp1_service_register
    (can_type1_channel_M1_C1,CAN_TP1_SERVICE_RX_OK);
  can_type1_service_M1_C1[CANTP1_M1_C1_TXOK] = can_tp1_service_register
    (can_type1_channel_M1_C1,CAN_TP1_SERVICE_TX_OK);

  /* dSPACE RTICAN MASTER SETUP Block */
  /* ... Initialize the CAN communication: 1000 kbit/s */
  can_type1_channel_M1_C2 = can_tp1_channel_init(can_tp1_address_table[0].
    module_addr, 1, (1000 * 1000), CAN_TP1_STD, CAN_TP1_NO_SUBINT);
  can_tp1_channel_termination_set(can_type1_channel_M1_C2,
    CAN_TP1_TERMINATION_ON);

  /* ... Initialize TX message structs for custom code  */
  CANTP1_TX_SPMSG_M1_C2_STD = can_tp1_msg_tx_register(can_type1_channel_M1_C2, 3,
    1050, CAN_TP1_STD, CAN_TP1_TIMECOUNT_INFO | CAN_TP1_DELAYCOUNT_INFO |
    CAN_TP1_MSG_INFO, CAN_TP1_NO_SUBINT, 0, CAN_TP1_TRIGGER_MSG,
    CAN_TP1_TIMEOUT_NORMAL);
  CANTP1_TX_SPMSG_M1_C2_XTD = can_tp1_msg_tx_register(can_type1_channel_M1_C2, 3,
    1100, CAN_TP1_EXT, CAN_TP1_TIMECOUNT_INFO | CAN_TP1_DELAYCOUNT_INFO |
    CAN_TP1_MSG_INFO, CAN_TP1_NO_SUBINT, 0, CAN_TP1_TRIGGER_MSG,
    CAN_TP1_TIMEOUT_NORMAL);

  /* dSPACE RTICAN MASTER SETUP Block */
  /* ... Initialize the Partial Networking Settings */

  /* dSPACE RTICAN TX Message Block: "Inverter_Right_CAN_Tx" Id:354 */
  /* ... Register message */
  can_type1_msg_M1[CANTP1_M1_C2_TX_STD_0X162] = can_tp1_msg_tx_register
    (can_type1_channel_M1_C2, 1, 354, CAN_TP1_STD, (CAN_TP1_TIMECOUNT_INFO),
     CAN_TP1_NO_SUBINT, 0, CAN_TP1_TRIGGER_MSG, CAN_TP1_TIMEOUT_NORMAL);

  /* dSPACE RTICAN RX Message Block: "Inverter_RIGHT_Rx" Id:386 */
  /* ... Register message */
  can_type1_msg_M1[CANTP1_M1_C2_RX_STD_0X182] = can_tp1_msg_rx_register
    (can_type1_channel_M1_C2, 3, 386, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN Status block */
  /* ... Register employed functions */
  can_type1_service_M1_C2[CANTP1_M1_C2_Status] = can_tp1_service_register
    (can_type1_channel_M1_C2,CAN_TP1_SERVICE_BUSSTATUS);
  can_type1_service_M1_C2[CANTP1_M1_C2_StuffErrors] = can_tp1_service_register
    (can_type1_channel_M1_C2,CAN_TP1_SERVICE_STUFFBIT_ERR);
  can_type1_service_M1_C2[CANTP1_M1_C2_FormatErrors] = can_tp1_service_register
    (can_type1_channel_M1_C2,CAN_TP1_SERVICE_FORM_ERR);
  can_type1_service_M1_C2[CANTP1_M1_C2_AckErrors] = can_tp1_service_register
    (can_type1_channel_M1_C2,CAN_TP1_SERVICE_ACK_ERR);
  can_type1_service_M1_C2[CANTP1_M1_C2_Bit0Errors] = can_tp1_service_register
    (can_type1_channel_M1_C2,CAN_TP1_SERVICE_BIT0_ERR);
  can_type1_service_M1_C2[CANTP1_M1_C2_Bit1Errors] = can_tp1_service_register
    (can_type1_channel_M1_C2,CAN_TP1_SERVICE_BIT1_ERR);
  can_type1_service_M1_C2[CANTP1_M1_C2_CRCErrors] = can_tp1_service_register
    (can_type1_channel_M1_C2,CAN_TP1_SERVICE_CRC_ERR);
  can_type1_service_M1_C2[CANTP1_M1_C2_RXLost] = can_tp1_service_register
    (can_type1_channel_M1_C2,CAN_TP1_SERVICE_RX_LOST);
  can_type1_service_M1_C2[CANTP1_M1_C2_DataLost] = can_tp1_service_register
    (can_type1_channel_M1_C2,CAN_TP1_SERVICE_DATA_LOST);
  can_type1_service_M1_C2[CANTP1_M1_C2_RXOK] = can_tp1_service_register
    (can_type1_channel_M1_C2,CAN_TP1_SERVICE_RX_OK);
  can_type1_service_M1_C2[CANTP1_M1_C2_TXOK] = can_tp1_service_register
    (can_type1_channel_M1_C2,CAN_TP1_SERVICE_TX_OK);

  /* dSPACE RTICAN RX Message Block: "Inverter_LEFT_Rx" Id:385 */
  Racing_2019_B.SFunction1_o3 = 0;     /* processed - flag */

  /* dSPACE RTICAN RX Message Block: "Inverter_RIGHT_Rx" Id:386 */
  Racing_2019_B.SFunction1_o3_h = 0;   /* processed - flag */

  /* dSPACE I/O Board DS1_RTICAN #2 */
  /* Initialization of DS1501 board */
  can_tp1_communication_init(can_tp1_address_table[1].module_addr,
    CAN_TP1_INT_ENABLE);

  /* dSPACE RTICAN MASTER SETUP Block */
  /* ... Initialize the CAN communication: 1000 kbit/s */
  can_type1_channel_M2_C2 = can_tp1_channel_init(can_tp1_address_table[1].
    module_addr, 1, (1000 * 1000), CAN_TP1_STD, CAN_TP1_NO_SUBINT);
  can_tp1_channel_termination_set(can_type1_channel_M2_C2,
    CAN_TP1_TERMINATION_OFF);

  /* ... Initialize TX message structs for custom code  */
  CANTP1_TX_SPMSG_M2_C2_STD = can_tp1_msg_tx_register(can_type1_channel_M2_C2, 3,
    1050, CAN_TP1_STD, CAN_TP1_TIMECOUNT_INFO | CAN_TP1_DELAYCOUNT_INFO |
    CAN_TP1_MSG_INFO, CAN_TP1_NO_SUBINT, 0, CAN_TP1_TRIGGER_MSG,
    CAN_TP1_TIMEOUT_NORMAL);
  CANTP1_TX_SPMSG_M2_C2_XTD = can_tp1_msg_tx_register(can_type1_channel_M2_C2, 3,
    1100, CAN_TP1_EXT, CAN_TP1_TIMECOUNT_INFO | CAN_TP1_DELAYCOUNT_INFO |
    CAN_TP1_MSG_INFO, CAN_TP1_NO_SUBINT, 0, CAN_TP1_TRIGGER_MSG,
    CAN_TP1_TIMEOUT_NORMAL);

  /* dSPACE RTICAN MASTER SETUP Block */
  /* ... Initialize the Partial Networking Settings */

  /* dSPACE RTICAN TX Message Block: "AUX_412" Id:412 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0X19C] = can_tp1_msg_tx_register
    (can_type1_channel_M2_C2, 5, 412, CAN_TP1_STD, (CAN_TP1_TIMECOUNT_INFO),
     CAN_TP1_NO_SUBINT, 0, CAN_TP1_TRIGGER_MSG, CAN_TP1_TIMEOUT_NORMAL);

  /* dSPACE RTICAN TX Message Block: "AUX_166" Id:166 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XA6] = can_tp1_msg_tx_register
    (can_type1_channel_M2_C2, 0, 166, CAN_TP1_STD, (CAN_TP1_TIMECOUNT_INFO|
      CAN_TP1_DELAYCOUNT_INFO), CAN_TP1_NO_SUBINT, 0, CAN_TP1_TRIGGER_MSG,
     CAN_TP1_TIMEOUT_NORMAL);

  /* dSPACE RTICAN TX Message Block: "DASH_204" Id:204 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XCC] = can_tp1_msg_tx_register
    (can_type1_channel_M2_C2, 0, 204, CAN_TP1_STD, (CAN_TP1_TIMECOUNT_INFO),
     CAN_TP1_NO_SUBINT, 0, CAN_TP1_TRIGGER_MSG, CAN_TP1_TIMEOUT_NORMAL);

  /* dSPACE RTICAN RX Message Block: "DASH_101" Id:101 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X65] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C2, 0, 101, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "DASH_198" Id:198 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XC6] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C2, 0, 198, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "AUX_314" Id:314 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X13A] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C2, 5, 314, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "AUX_357" Id:357 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X165] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C2, 5, 357, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "AUX_384" Id:384 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X180] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C2, 5, 384, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "DASH_279" Id:279 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X117] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C2, 5, 279, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "DASH_246" Id:246 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XF6] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C2, 5, 246, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN Status block */
  /* ... Register employed functions */
  can_type1_service_M2_C2[CANTP1_M2_C2_Status] = can_tp1_service_register
    (can_type1_channel_M2_C2,CAN_TP1_SERVICE_BUSSTATUS);
  can_type1_service_M2_C2[CANTP1_M2_C2_StuffErrors] = can_tp1_service_register
    (can_type1_channel_M2_C2,CAN_TP1_SERVICE_STUFFBIT_ERR);
  can_type1_service_M2_C2[CANTP1_M2_C2_FormatErrors] = can_tp1_service_register
    (can_type1_channel_M2_C2,CAN_TP1_SERVICE_FORM_ERR);
  can_type1_service_M2_C2[CANTP1_M2_C2_AckErrors] = can_tp1_service_register
    (can_type1_channel_M2_C2,CAN_TP1_SERVICE_ACK_ERR);
  can_type1_service_M2_C2[CANTP1_M2_C2_Bit0Errors] = can_tp1_service_register
    (can_type1_channel_M2_C2,CAN_TP1_SERVICE_BIT0_ERR);
  can_type1_service_M2_C2[CANTP1_M2_C2_Bit1Errors] = can_tp1_service_register
    (can_type1_channel_M2_C2,CAN_TP1_SERVICE_BIT1_ERR);
  can_type1_service_M2_C2[CANTP1_M2_C2_CRCErrors] = can_tp1_service_register
    (can_type1_channel_M2_C2,CAN_TP1_SERVICE_CRC_ERR);
  can_type1_service_M2_C2[CANTP1_M2_C2_RXLost] = can_tp1_service_register
    (can_type1_channel_M2_C2,CAN_TP1_SERVICE_RX_LOST);
  can_type1_service_M2_C2[CANTP1_M2_C2_DataLost] = can_tp1_service_register
    (can_type1_channel_M2_C2,CAN_TP1_SERVICE_DATA_LOST);
  can_type1_service_M2_C2[CANTP1_M2_C2_RXOK] = can_tp1_service_register
    (can_type1_channel_M2_C2,CAN_TP1_SERVICE_RX_OK);
  can_type1_service_M2_C2[CANTP1_M2_C2_TXOK] = can_tp1_service_register
    (can_type1_channel_M2_C2,CAN_TP1_SERVICE_TX_OK);

  /* dSPACE RTICAN MASTER SETUP Block */
  /* ... Initialize the CAN communication: 1000 kbit/s */
  can_type1_channel_M2_C1 = can_tp1_channel_init(can_tp1_address_table[1].
    module_addr, 0, (1000 * 1000), CAN_TP1_STD, CAN_TP1_NO_SUBINT);
  can_tp1_channel_termination_set(can_type1_channel_M2_C1,
    CAN_TP1_TERMINATION_ON);

  /* ... Initialize TX message structs for custom code  */
  CANTP1_TX_SPMSG_M2_C1_STD = can_tp1_msg_tx_register(can_type1_channel_M2_C1, 3,
    1050, CAN_TP1_STD, CAN_TP1_TIMECOUNT_INFO | CAN_TP1_DELAYCOUNT_INFO |
    CAN_TP1_MSG_INFO, CAN_TP1_NO_SUBINT, 0, CAN_TP1_TRIGGER_MSG,
    CAN_TP1_TIMEOUT_NORMAL);
  CANTP1_TX_SPMSG_M2_C1_XTD = can_tp1_msg_tx_register(can_type1_channel_M2_C1, 3,
    1100, CAN_TP1_EXT, CAN_TP1_TIMECOUNT_INFO | CAN_TP1_DELAYCOUNT_INFO |
    CAN_TP1_MSG_INFO, CAN_TP1_NO_SUBINT, 0, CAN_TP1_TRIGGER_MSG,
    CAN_TP1_TIMEOUT_NORMAL);

  /* dSPACE RTICAN MASTER SETUP Block */
  /* ... Initialize the Partial Networking Settings */

  /* dSPACE RTICAN TX Message Block: "BMS_201" Id:201 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_TX_STD_0XC9] = can_tp1_msg_tx_register
    (can_type1_channel_M2_C1, 0, 201, CAN_TP1_STD, (CAN_TP1_TIMECOUNT_INFO),
     CAN_TP1_NO_SUBINT, 0, CAN_TP1_TRIGGER_MSG, CAN_TP1_TIMEOUT_NORMAL);

  /* dSPACE RTICAN RX Message Block: "BMS_200" Id:200 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XC8] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 0, 200, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s1q3" Id:206 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCE] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 1, 206, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s1q2" Id:205 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCD] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 0, 205, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s1q1" Id:204 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCC] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 0, 204, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s2q3" Id:209 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD1] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 1, 209, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s2q2" Id:208 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD0] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 1, 208, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s2q1" Id:207 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCF] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 1, 207, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s3q3" Id:212 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD4] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 2, 212, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s3q2" Id:211 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD3] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 1, 211, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s3q1" Id:210 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD2] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 1, 210, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s4q3" Id:215 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD7] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 2, 215, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s4q2" Id:214 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD6] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 2, 214, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s4q1" Id:213 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD5] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 2, 213, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s5q3" Id:218 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDA] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 2, 218, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s5q2" Id:217 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD9] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 2, 217, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s5q1" Id:216 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD8] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 2, 216, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s6q3" Id:221 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDD] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 3, 221, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s6q2" Id:220 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDC] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 3, 220, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s6q1" Id:219 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDB] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 3, 219, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s7q3" Id:224 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE0] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 3, 224, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s7q2" Id:223 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDF] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 3, 223, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s7q1" Id:222 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDE] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 3, 222, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s2t" Id:226 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE2] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 4, 226, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s3t" Id:227 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE3] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 4, 227, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s4t" Id:228 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE4] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 4, 228, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s5t" Id:229 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE5] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 4, 229, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s6t" Id:230 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE6] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 4, 230, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s7t" Id:231 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE7] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 4, 231, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN RX Message Block: "BMS_s1t" Id:225 */
  /* ... Register message */
  can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE1] = can_tp1_msg_rx_register
    (can_type1_channel_M2_C1, 4, 225, CAN_TP1_STD, (CAN_TP1_DATA_INFO|
      CAN_TP1_DATA_INFO|CAN_TP1_TIMECOUNT_INFO), CAN_TP1_NO_SUBINT);

  /* dSPACE RTICAN Status block */
  /* ... Register employed functions */
  can_type1_service_M2_C1[CANTP1_M2_C1_Status] = can_tp1_service_register
    (can_type1_channel_M2_C1,CAN_TP1_SERVICE_BUSSTATUS);
  can_type1_service_M2_C1[CANTP1_M2_C1_StuffErrors] = can_tp1_service_register
    (can_type1_channel_M2_C1,CAN_TP1_SERVICE_STUFFBIT_ERR);
  can_type1_service_M2_C1[CANTP1_M2_C1_FormatErrors] = can_tp1_service_register
    (can_type1_channel_M2_C1,CAN_TP1_SERVICE_FORM_ERR);
  can_type1_service_M2_C1[CANTP1_M2_C1_AckErrors] = can_tp1_service_register
    (can_type1_channel_M2_C1,CAN_TP1_SERVICE_ACK_ERR);
  can_type1_service_M2_C1[CANTP1_M2_C1_Bit0Errors] = can_tp1_service_register
    (can_type1_channel_M2_C1,CAN_TP1_SERVICE_BIT0_ERR);
  can_type1_service_M2_C1[CANTP1_M2_C1_Bit1Errors] = can_tp1_service_register
    (can_type1_channel_M2_C1,CAN_TP1_SERVICE_BIT1_ERR);
  can_type1_service_M2_C1[CANTP1_M2_C1_CRCErrors] = can_tp1_service_register
    (can_type1_channel_M2_C1,CAN_TP1_SERVICE_CRC_ERR);
  can_type1_service_M2_C1[CANTP1_M2_C1_RXLost] = can_tp1_service_register
    (can_type1_channel_M2_C1,CAN_TP1_SERVICE_RX_LOST);
  can_type1_service_M2_C1[CANTP1_M2_C1_DataLost] = can_tp1_service_register
    (can_type1_channel_M2_C1,CAN_TP1_SERVICE_DATA_LOST);
  can_type1_service_M2_C1[CANTP1_M2_C1_RXOK] = can_tp1_service_register
    (can_type1_channel_M2_C1,CAN_TP1_SERVICE_RX_OK);
  can_type1_service_M2_C1[CANTP1_M2_C1_TXOK] = can_tp1_service_register
    (can_type1_channel_M2_C1,CAN_TP1_SERVICE_TX_OK);

  /* dSPACE RTICAN RX Message Block: "DASH_101" Id:101 */
  Racing_2019_B.SFunction1_o4 = 0;     /* processed - flag */

  /* dSPACE RTICAN RX Message Block: "DASH_198" Id:198 */
  Racing_2019_B.SFunction1_o3_a = 0;   /* processed - flag */

  /* dSPACE RTICAN RX Message Block: "AUX_314" Id:314 */
  Racing_2019_B.SFunction1_o3_bg = 0;  /* processed - flag */

  /* dSPACE RTICAN RX Message Block: "AUX_357" Id:357 */
  Racing_2019_B.SFunction1_o4_n = 0;   /* processed - flag */

  /* dSPACE RTICAN RX Message Block: "AUX_384" Id:384 */
  Racing_2019_B.SFunction1_o6_jk = 0;  /* processed - flag */

  /* dSPACE RTICAN RX Message Block: "DASH_279" Id:279 */
  Racing_2019_B.SFunction1_o8 = 0;     /* processed - flag */

  /* dSPACE RTICAN RX Message Block: "DASH_246" Id:246 */
  Racing_2019_B.SFunction1_o5_np = 0;  /* processed - flag */

  /* dSPACE RTICAN TX Message Block: "AUX_412" Id:412 */
  /* Messages with timestamp zero have been received in pause/stop state
     and must not be handled.
   */
  if (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0X19C]->timestamp > 0.0) {
    Racing_2019_B.SFunction1_ks = 0;   /* processed - flag */
  }

  /* dSPACE RTICAN TX Message Block: "AUX_166" Id:166 */
  /* Messages with timestamp zero have been received in pause/stop state
     and must not be handled.
   */
  if (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XA6]->timestamp > 0.0) {
    Racing_2019_B.SFunction1_o1_age = 0;/* processed - flag */
    Racing_2019_B.SFunction1_o2_b = 0; /* delaytime */
  }

  /* dSPACE RTICAN TX Message Block: "DASH_204" Id:204 */
  /* Messages with timestamp zero have been received in pause/stop state
     and must not be handled.
   */
  if (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XCC]->timestamp > 0.0) {
    Racing_2019_B.SFunction1_iu = 0;   /* processed - flag */
  }

  /* dSPACE RTICAN RX Message Block: "BMS_200" Id:200 */
  Racing_2019_B.SFunction1_o4_a = 0;   /* processed - flag */

  /* dSPACE RTICAN RX Message Block: "BMS_s1q3" Id:206 */
  Racing_2019_B.SFunction1_o5 = 0;     /* processed - flag */
  Racing_2019_B.SFunction1_o6 = 0;     /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s1q2" Id:205 */
  Racing_2019_B.SFunction1_o5_o = 0;   /* processed - flag */
  Racing_2019_B.SFunction1_o6_o = 0;   /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s1q1" Id:204 */
  Racing_2019_B.SFunction1_o5_c = 0;   /* processed - flag */

  /* dSPACE RTICAN RX Message Block: "BMS_s2q3" Id:209 */
  Racing_2019_B.SFunction1_o5_cj = 0;  /* processed - flag */
  Racing_2019_B.SFunction1_o6_e = 0;   /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s2q2" Id:208 */
  Racing_2019_B.SFunction1_o5_g = 0;   /* processed - flag */
  Racing_2019_B.SFunction1_o6_i = 0;   /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s2q1" Id:207 */
  Racing_2019_B.SFunction1_o5_m = 0;   /* processed - flag */
  Racing_2019_B.SFunction1_o6_h = 0;   /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s3q3" Id:212 */
  Racing_2019_B.SFunction1_o5_l = 0;   /* processed - flag */
  Racing_2019_B.SFunction1_o6_id = 0;  /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s3q2" Id:211 */
  Racing_2019_B.SFunction1_o5_gd = 0;  /* processed - flag */
  Racing_2019_B.SFunction1_o6_c = 0;   /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s3q1" Id:210 */
  Racing_2019_B.SFunction1_o5_n = 0;   /* processed - flag */
  Racing_2019_B.SFunction1_o6_j = 0;   /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s4q3" Id:215 */
  Racing_2019_B.SFunction1_o5_a = 0;   /* processed - flag */
  Racing_2019_B.SFunction1_o6_m = 0;   /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s4q2" Id:214 */
  Racing_2019_B.SFunction1_o5_b = 0;   /* processed - flag */
  Racing_2019_B.SFunction1_o6_p = 0;   /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s4q1" Id:213 */
  Racing_2019_B.SFunction1_o5_f = 0;   /* processed - flag */
  Racing_2019_B.SFunction1_o6_j0 = 0;  /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s5q3" Id:218 */
  Racing_2019_B.SFunction1_o5_k = 0;   /* processed - flag */
  Racing_2019_B.SFunction1_o6_n = 0;   /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s5q2" Id:217 */
  Racing_2019_B.SFunction1_o5_d = 0;   /* processed - flag */
  Racing_2019_B.SFunction1_o6_d = 0;   /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s5q1" Id:216 */
  Racing_2019_B.SFunction1_o5_ke = 0;  /* processed - flag */
  Racing_2019_B.SFunction1_o6_a = 0;   /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s6q3" Id:221 */
  Racing_2019_B.SFunction1_o5_bo = 0;  /* processed - flag */
  Racing_2019_B.SFunction1_o6_is = 0;  /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s6q2" Id:220 */
  Racing_2019_B.SFunction1_o5_cb = 0;  /* processed - flag */
  Racing_2019_B.SFunction1_o6_ii = 0;  /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s6q1" Id:219 */
  Racing_2019_B.SFunction1_o5_bu = 0;  /* processed - flag */
  Racing_2019_B.SFunction1_o6_k = 0;   /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s7q3" Id:224 */
  Racing_2019_B.SFunction1_o5_j = 0;   /* processed - flag */
  Racing_2019_B.SFunction1_o6_f = 0;   /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s7q2" Id:223 */
  Racing_2019_B.SFunction1_o5_be = 0;  /* processed - flag */
  Racing_2019_B.SFunction1_o6_hb = 0;  /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s7q1" Id:222 */
  Racing_2019_B.SFunction1_o5_nf = 0;  /* processed - flag */
  Racing_2019_B.SFunction1_o6_g = 0;   /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s2t" Id:226 */
  Racing_2019_B.SFunction1_o5_i = 0;   /* processed - flag */
  Racing_2019_B.SFunction1_o6_jd = 0;  /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s3t" Id:227 */
  Racing_2019_B.SFunction1_o5_ok = 0;  /* processed - flag */
  Racing_2019_B.SFunction1_o6_as = 0;  /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s4t" Id:228 */
  Racing_2019_B.SFunction1_o5_mk = 0;  /* processed - flag */
  Racing_2019_B.SFunction1_o6_dw = 0;  /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s5t" Id:229 */
  Racing_2019_B.SFunction1_o5_ja = 0;  /* processed - flag */
  Racing_2019_B.SFunction1_o6_hg = 0;  /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s6t" Id:230 */
  Racing_2019_B.SFunction1_o5_m0 = 0;  /* processed - flag */
  Racing_2019_B.SFunction1_o6_eb = 0;  /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s7t" Id:231 */
  Racing_2019_B.SFunction1_o5_iw = 0;  /* processed - flag */
  Racing_2019_B.SFunction1_o6_gh = 0;  /* deltatime */

  /* dSPACE RTICAN RX Message Block: "BMS_s1t" Id:225 */
  Racing_2019_B.SFunction1_o5_az = 0;  /* processed - flag */

  /* dSPACE RTICAN TX Message Block: "BMS_201" Id:201 */
  /* Messages with timestamp zero have been received in pause/stop state
     and must not be handled.
   */
  if (can_type1_msg_M2[CANTP1_M2_C1_TX_STD_0XC9]->timestamp > 0.0) {
    Racing_2019_B.SFunction1_k = 0;    /* processed - flag */
  }

  /* dSPACE I/O Board RTICAN_GLOBAL #0 */
}

/* Function rti_mdl_slave_load() is empty */
#define rti_mdl_slave_load()

/* Function rti_mdl_rtk_initialize() is empty */
#define rti_mdl_rtk_initialize()

static void rti_mdl_initialize_io_units(void)
{
  /* dSPACE I/O Board DS1401STDDIOT4 #1 Unit:DIGOUT */
  /* re-adjust the supply rails for channel 5 on port 1 */
  dio_tp4_digout_init(DIO_TP4_1_MODULE_ADDR, 1, DIO_TP4_MASK_CH5, 1, 1);

  /* write initialization value to digital output channel 5 on port 1 */
  dio_tp4_digout_write(DIO_TP4_1_MODULE_ADDR , 1, DIO_TP4_MASK_CH5, (UInt16) 0);

  /* re-adjust the supply rails for channel 10 on port 1 */
  dio_tp4_digout_init(DIO_TP4_1_MODULE_ADDR, 1, DIO_TP4_MASK_CH10, 1, 1);

  /* write initialization value to digital output channel 10 on port 1 */
  dio_tp4_digout_write(DIO_TP4_1_MODULE_ADDR , 1, DIO_TP4_MASK_CH10, (UInt16)
                       512);

  /* re-adjust the supply rails for channel 4 on port 1 */
  dio_tp4_digout_init(DIO_TP4_1_MODULE_ADDR, 1, DIO_TP4_MASK_CH4, 1, 1);

  /* write initialization value to digital output channel 4 on port 1 */
  dio_tp4_digout_write(DIO_TP4_1_MODULE_ADDR , 1, DIO_TP4_MASK_CH4, (UInt16) 8);

  /* dSPACE I/O Board DS1401STDDIOT4 #1 Unit:DIGOUT Group:BITOUTCH */
  /* enable all digital output ports (no port wise Dis-Enabling supported) */
  /* called once per module for all dig output ports */
  dio_tp4_digout_mode_set(DIO_TP4_1_MODULE_ADDR, DIO_TP4_DIGOUT_ENABLE);

  /* dSPACE I/O Board DS1_RTICAN #1 */
  /* Start CAN controller */
  can_tp1_channel_start(can_type1_channel_M1_C1, CAN_TP1_INT_ENABLE);

  /* Start CAN controller */
  can_tp1_channel_start(can_type1_channel_M1_C2, CAN_TP1_INT_ENABLE);

  /* Set the type1CAN error level */
  rtican_type1_error_level = 0;

  /* ... Reset all taskqueue-specific error variables */
  rtican_type1_tq_err_all_reset(0);

  /* ... Clear all message data buffers */
  can_tp1_all_data_clear(can_tp1_address_table[0].module_addr);

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[0][0] = can_tp1_msg_wakeup
              (can_type1_msg_M1[CANTP1_M1_C1_TX_STD_0X161])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[0][2] = can_tp1_msg_wakeup
              (can_type1_msg_M1[CANTP1_M1_C1_RX_STD_0X181])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[0][1] = can_tp1_msg_wakeup
              (can_type1_msg_M1[CANTP1_M1_C2_TX_STD_0X162])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[0][3] = can_tp1_msg_wakeup
              (can_type1_msg_M1[CANTP1_M1_C2_RX_STD_0X182])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  /* dSPACE I/O Board DS1_RTICAN #2 */
  /* Start CAN controller */
  can_tp1_channel_start(can_type1_channel_M2_C2, CAN_TP1_INT_ENABLE);

  /* Start CAN controller */
  can_tp1_channel_start(can_type1_channel_M2_C1, CAN_TP1_INT_ENABLE);

  /* Set the type1CAN error level */
  rtican_type1_error_level = 0;

  /* ... Reset all taskqueue-specific error variables */
  rtican_type1_tq_err_all_reset(1);

  /* ... Clear all message data buffers */
  can_tp1_all_data_clear(can_tp1_address_table[1].module_addr);

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][5] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0X19C])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][0] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XA6])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][0] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C2_TX_STD_0XCC])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][0] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X65])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][0] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XC6])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][5] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X13A])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][5] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X165])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][5] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X180])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][5] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0X117])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][5] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C2_RX_STD_0XF6])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][0] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_TX_STD_0XC9])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][0] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XC8])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][1] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCE])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][0] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCD])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][0] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCC])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][1] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD1])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][1] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD0])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][1] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XCF])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][2] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD4])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][1] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD3])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][1] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD2])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][2] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD7])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][2] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD6])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][2] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD5])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][2] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDA])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][2] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD9])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][2] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XD8])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][3] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDD])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][3] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDC])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][3] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDB])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][3] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE0])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][3] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDF])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][3] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XDE])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][4] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE2])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][4] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE3])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][4] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE4])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][4] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE5])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][4] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE6])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][4] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE7])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }

  {
    static UInt32 numInit = 0;
    if (numInit != 0) {
      /* ... Wake message up */
      while ((rtican_type1_tq_error[1][4] = can_tp1_msg_wakeup
              (can_type1_msg_M2[CANTP1_M2_C1_RX_STD_0XE1])) ==
             DSMCOM_BUFFER_OVERFLOW) ;
    }

    ++numInit;
  }
}

/* Function rti_mdl_acknowledge_interrupts() is empty */
#define rti_mdl_acknowledge_interrupts()

/* Function rti_mdl_timetables_register() is empty */
#define rti_mdl_timetables_register()

/* Function rti_mdl_timesync_simstate() is empty */
#define rti_mdl_timesync_simstate()

/* Function rti_mdl_timesync_baserate() is empty */
#define rti_mdl_timesync_baserate()

static void rti_mdl_background(void)
{
  /* DsDaq background call */
  DsDaq_Background(0);

  /* dSPACE I/O Board DS1_RTICAN #1 */
  {
    real_T bg_code_exec_time;
    static real_T bg_code_last_exec_time = 0.0;
    bg_code_exec_time = RTLIB_TIC_READ();
    if ((bg_code_exec_time - bg_code_last_exec_time) > 0.25 ||
        (bg_code_exec_time - bg_code_last_exec_time) < 0) {
      /* ... Check taskqueue-specific error variables */
      rtican_type1_tq_err_all_chk(can_tp1_address_table[0].module_addr, 0);
      bg_code_last_exec_time = bg_code_exec_time;
    }
  }

  /* copy DPMEM - buffers in background */
  {
    /* call update function for CAN Tp1 CAN interface (module number: 1) */
    can_tp1_msg_copy_all_to_mem(can_tp1_address_table[0].module_addr);
  }

  /* dSPACE I/O Board DS1_RTICAN #2 */
  {
    real_T bg_code_exec_time;
    static real_T bg_code_last_exec_time = 0.0;
    bg_code_exec_time = RTLIB_TIC_READ();
    if ((bg_code_exec_time - bg_code_last_exec_time) > 0.25 ||
        (bg_code_exec_time - bg_code_last_exec_time) < 0) {
      /* ... Check taskqueue-specific error variables */
      rtican_type1_tq_err_all_chk(can_tp1_address_table[1].module_addr, 1);
      bg_code_last_exec_time = bg_code_exec_time;
    }
  }

  /* copy DPMEM - buffers in background */
  {
    /* call update function for CAN Tp1 CAN interface (module number: 2) */
    can_tp1_msg_copy_all_to_mem(can_tp1_address_table[1].module_addr);
  }
}

__INLINE void rti_mdl_sample_input(void)
{
  /* Calls for base sample time: [0.001, 0] */
  /* dSPACE I/O Board DS1401STDADCT4 #1 Unit:ADC */

  /* dSPACE I/O Board DS1401STDADCT4 #1 Unit:ADC Group:ADC */
  adc_tp4_sw_trigger(ADC_TP4_1_MODULE_ADDR, ADC_TP4_CONV_START_6|
                     ADC_TP4_CONV_START_5|ADC_TP4_CONV_START_7|
                     ADC_TP4_CONV_START_3|ADC_TP4_CONV_START_1|
                     ADC_TP4_CONV_START_2);

  /* dSPACE I/O Board DS1401BASEII #1 Unit:ACCELREAD */
  {
    ds1401_accel_sensor_xyz_axis_read((real_T*) &Racing_2019_B.SFunction1_o2_p,
      (real_T*) &Racing_2019_B.SFunction1_o3_h0,
      (real_T*) &Racing_2019_B.SFunction1_o4_mo,
      (uint32_T*) &Racing_2019_B.SFunction1_o1_nn);
  }

  /* dSPACE I/O Board DS1_RTICAN #1 Unit:DEFAULT */
  /* call update function for CAN Tp1 CAN interface (module number: 1) */
  can_tp1_msg_copy_all_to_mem(can_tp1_address_table[0].module_addr);

  /* dSPACE I/O Board DS1_RTICAN #2 Unit:DEFAULT */
  /* call update function for CAN Tp1 CAN interface (module number: 2) */
  can_tp1_msg_copy_all_to_mem(can_tp1_address_table[1].module_addr);

  /* Calls for sample time: [0.1, 0.0] */
  if (dsIsSampleHit(Racing_2019_M, 3)) {
    /* dSPACE I/O Board DS1_RTICAN #2 Unit:DEFAULT */
    /* call update function for CAN Tp1 CAN interface (module number: 2) */
    can_tp1_msg_copy_all_to_mem(can_tp1_address_table[1].module_addr);
  }

  /* Calls for sample time: [0.2, 0.0] */
  if (dsIsSampleHit(Racing_2019_M, 4)) {
    /* dSPACE I/O Board DS1_RTICAN #2 Unit:DEFAULT */
    /* call update function for CAN Tp1 CAN interface (module number: 2) */
    can_tp1_msg_copy_all_to_mem(can_tp1_address_table[1].module_addr);
  }
}

static void rti_mdl_daq_service()
{
  /* dSPACE Host Service */
  host_service(1, rtk_current_task_absolute_time_ptr_get());
  DsDaq_Service(0, 0, 1, (DsDaqSTimestampStruct *)
                rtk_current_task_absolute_time_ptr_get());
}

#undef __INLINE

/****** [EOF] ****************************************************************/

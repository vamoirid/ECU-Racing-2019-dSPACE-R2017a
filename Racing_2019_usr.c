/******************************************************************************

   Include file Racing_2019_usr.c:

   Definition of functions for user-defined initialization,
   system I/O, and background process code.

   RTI1401 7.8 (02-May-2017)
   Thu May 16 01:33:58 2019

   Copyright 2017, dSPACE GmbH. All rights reserved. Brand names
   or product names are trademarks or registered trademarks of their
   respective companies or organizations.

 *****************************************************************************/

/* ========================================================================= */
/* =====  Define file version macro. Never change this value.  ============= */
/* ========================================================================= */
#define USER_CODE_FILE_VERSION 5
/* ========================================================================= */

/* Insert #include directives for header files here. */


#if defined(_INLINE)
# define __INLINE static inline
#else
# define __INLINE static
#endif

static void UsbFlightRecorder_SetRecordingSize(UInt32 FileSizeMB) 
{
    vcm_module_descriptor_type      *pVcmEntry;
    DsFlrecUsbAdmin_t               *pVcmInfo;

    pVcmEntry = vcm_module_find( VCM_MID_FLREC_USB_1401, NULL );
    if( pVcmEntry == NULL )
    {
        msg_warning_printf( 0, 0, "Error: Flight Recorder was not initialized (failed to locate VCM entry)");
        return;
    }
    pVcmInfo = (DsFlrecUsbAdmin_t*)vcm_memory_ptr_get(pVcmEntry);
    if( pVcmInfo == NULL )
    {
        msg_warning_printf( 0, 0, "Error: Flight Recorder was not initialized (failed to locate VCM data)");
        return;
    }
    pVcmInfo->maxRecordingSizeMB = FileSizeMB;
    msg_info_printf( 0, 0, "USB Flight Recorder: Successfully set recording size to %d MB", FileSizeMB );
}


static void usr_initialize(void)
{
	UsbFlightRecorder_SetRecordingSize(256);
}


__INLINE void usr_sample_input(void)
{
}


__INLINE void usr_input(void)
{
}


__INLINE void usr_output(void)
{
}


static void usr_terminate(void)
{
}


static void usr_background(void)
{
}


#undef __INLINE

/****** [EOF] ****************************************************************/

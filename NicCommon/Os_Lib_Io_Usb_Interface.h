#ifndef OS_LIB_IO_USB_INTERFACE
#define OS_LIB_IO_USB_INTERFACE

#include "Os_DataTypes.h"
#include "Os_Module_Interface.h"

#include "Os_Lib_Io_Usb_DataTypes.h"


//定义通用的、由操作系统实现的基本USB相关IO操作

/*
* Create and destory a USB pipe.
*/

PUsbPipe OsUsbPipeCreate(NicOsInterface* pDevice, 
                         U16             transferType,    /* Type of transfer: control, bulk... */
                         U16             direction,       /* Specifies IN or OUT endpoint */
                         U16             maxPayload,      /* Maximum data payload per packet */
                         U16             bandwidth,       /* Bandwidth required for pipe */
                         U16             serviceInterval  /* Required service interval */
                         );

U8 OsUsbPipeDestory(NicOsInterface* pDevice, 
                    PUsbPipe        pPipe);

U8 OsUsbIsInPipe(PUsbPipe pPipe);

U8 OsUsbIsOutPipe(PUsbPipe pPipe);

/*
* This structure identifies USB transfer requests.  URBs must be allocated by
* calling usb_alloc_urb() and freed with a call to usb_free_urb().
* Initialization may be done using various usb_fill_*_urb() functions.  URBs
* are submitted using usb_submit_urb(), and pending requests may be canceled
* using usb_unlink_urb() or usb_kill_urb().
*/

PUrb OsUrbAllocate();

U8 OsUrbFree(PUrb);

/*
* Methods to do different kinds of transactions async or sync.
*/

/* 
* Initializes a control urb with the proper information and 
* then send it async (only submit the to a device)
* or sned it sync.
*/
U8 OsUsbSendControlAsync(NicOsInterface* pDevice, 
                         PUsbPipe pPipe,
                         PUrb pUrb,
                         U8 request,
                         U8 requestType,
                         U16 value,
                         U16 index,
                         PVoid data,
                         U16 size,
                         UsbCallback completeFunc);

U8 OsUsbSendControlSync(NicOsInterface* pDevice, 
                        PUsbPipe pPipe,
                        PUrb pUrb,
                        U8 request,
                        U8 requestType,
                        U16 value,
                        U16 index,
                        PVoid data,
                        U16 size,
                        UsbCallback completeFunc,
                        U32 timeout);

/* 
* Initializes an interrupt urb with the proper information and 
* then send it async (only submit the to a device)
* or sned it sync.
*/

U8 OsUsbSendInterruptAsync(NicOsInterface* pDevice, 
                           PUsbPipe pPipe,
                           PUrb pUrb,
                           PVoid data,
                           U32 len,
                           PU32 actualLen);

U8 OsUsbSendInterruptSync(NicOsInterface* pDevice, 
                          PUsbPipe pPipe,
                          PUrb pUrb,
                          PVoid data,
                          U32 len,
                          PU32 actualLen,
                          U32 timeout);

/* 
* Initializes a bulk urb with the proper information and 
* then send it async (only submit the to a device)
* or sned it sync.
*/

U8 OsUsbSendBulkAsync(NicOsInterface* pDevice, 
                      PUsbPipe pPipe,
                      PUrb pUrb,
                      PVoid data,
                      U32 len,
                      PU32 actualLen);

U8 OsUsbSendBulkSync(NicOsInterface* pDevice, 
                     PUsbPipe pPipe,
                     PUrb pUrb,
                     PVoid data,
                     U32 len,
                     PU32 actualLen,
                     U32 timeout);


#endif
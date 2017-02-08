#ifndef VXWORKS_USB_STUB_DEF
#define VXWORKS_USB_STUB_DEF

#include "OS_DataTypes.h"
#include "OS_IO_USB_Interface.h"

typedef int STATUS;

typedef int USBD_CLIENT_HANDLE;
typedef USBD_CLIENT_HANDLE *pUSBD_CLIENT_HANDLE;

typedef int USBD_PIPE_HANDLE;
typedef USBD_PIPE_HANDLE *pUSUSBD_PIPE_HANDLE;

typedef int USB_IRP;
typedef USB_IRP *pUSB_IRP;

//usbdPipeCreate( )
//
//NAME
//
//    usbdPipeCreate( ) - Creates a USB pipe for subsequent transfers
//
//SYNOPSIS
//
//    STATUS usbdPipeCreate
//        (
//        USBD_CLIENT_HANDLE clientHandle,    /* Client handle */
//        USBD_NODE_ID       nodeId,          /* Node Id of device/hub */
//        UINT16             endpoint,        /* Endpoint number */
//        UINT16             configuration,   /* config w/which pipe associated */
//        UINT16             interface,       /* interface w/which pipe associated */
//        UINT16             transferType,    /* Type of transfer: control, bulk... */
//        UINT16             direction,       /* Specifies IN or OUT endpoint */
//        UINT16             maxPayload,      /* Maximum data payload per packet */
//        UINT32             bandwidth,       /* Bandwidth required for pipe */
//        UINT16             serviceInterval, /* Required service interval */
//        pUSBD_PIPE_HANDLE  pPipeHandle      /* pipe handle returned by USBD */
//        )
//
//DESCRIPTION
//
//    This function establishes a pipe which can subsequently be used by a client to exchange data with a USB device endpoint.
//
//    nodeId and endpoint identify the device and device endpoint, respectively, to which the pipe should be "connected." configuration and interface specify the configuration and interface, respectively, with which the pipe is associated. (The USBD uses this information to keep track of "configuration events" associated with the pipe).
//
//    transferType specifies the type of data transfers for which this pipe will be used:
//
//    USB_XFRTYPE_CONTROL
//        Control transfer pipe (message). 
//    USB_XFRTYPE_ISOCH
//        Isochronous transfer pipe (stream). 
//    USB_XFRTYPE_INTERRUPT
//        Interrupt transfer pipe (stream). 
//    USB_XFRTYPE_BULK
//        Bulk transfer pipe (stream).
//
//        direction specifies the direction of the pipe as:
//
//    USB_DIR_IN
//        Data moves from device to host. 
//    USB_DIR_OUT
//        Data moves from host to device. 
//    USB_DIR_INOUT
//        Data moves bidirectionally (message pipes only).
//
//        If the direction is specified as USB_DIR_INOUT, the USBD assumes that both the IN and OUT endpoints identified by endpoint will be used by this pipe (see the discussion of message pipes in Chapter 5 of the USB Specification). USB_DIR_INOUT may be specified only for Control pipes.
//
//        maxPayload specifies the largest data payload supported by this endpoint. Normally a USB device will declare the maximum payload size it supports on each endpoint in its configuration descriptors. The client will typically read these descriptors using the USBD Configuration Functions and then parse the descriptors to retrieve the appropriate maximum payload value.
//
//        bandwidth specifies the bandwidth required for this pipe. For control and bulk pipes, this parameter should be 0. For interrupt pipes, this parameter should express the number of bytes per frame to be transferred. for isochronous pipes, this parameter should express the number of bytes per second to be transferred.
//
//        serviceInterval specifies the maximum latency for the pipe in milliseconds. So, if a pipe needs to be serviced, for example, at least every 20 milliseconds, then the serviceInterval value should be 20. The serviceInterval parameter is required only for interrupt pipes. For other types of pipes, serviceInterval should be 0.
//
//        If the USBD succeeds in creating the pipe it returns a pipe handle in pPipeHandle. The client must use the pipe handle to identify the pipe in subsequent calls to the USBD Transfer Functions. If there is insufficient bus bandwidth available to create the pipe (as might happen for an isochronous or interrupt pipe), then the USBD will return an error and a NULL handle in pPipeHandle. 
//
//RETURNS
//
//    OK, or ERROR if pipe could not be create 

inline STATUS usbdPipeCreate(
    PVoid           clientHandle,    /* Client handle */
    PVoid           nodeId,          /* Node Id of device/hub */
    U16             endpoint,        /* Endpoint number */
    U16             configuration,   /* config w/which pipe associated */
    U16             interface,       /* interface w/which pipe associated */
    U16             transferType,    /* Type of transfer: control, bulk... */
    U16             direction,       /* Specifies IN or OUT endpoint */
    U16             maxPayload,      /* Maximum data payload per packet */
    U16             bandwidth,       /* Bandwidth required for pipe */
    U16             serviceInterval, /* Required service interval */
    PVoid           pPipeHandle      /* pUSBD_PIPE_HANDLE , pipe handle returned by USBD */
    ){
        return 0;
    }

inline PUSBPipe USBPipeCreate(
    NICOSInterface* device, 
    U16             transferType,    /* Type of transfer: control, bulk... */
    U16             direction,       /* Specifies IN or OUT endpoint */
    U16             maxPayload,      /* Maximum data payload per packet */
    U16             bandwidth,       /* Bandwidth required for pipe */
    U16             serviceInterval /* Required service interval */
    ){
        pUSUSBD_PIPE_HANDLE handle = new USBD_PIPE_HANDLE();

        if (usbdPipeCreate (
            nullptr, //klsiHandle, 
            nullptr, //pNewDev->nodeId, 
            0, //pOutEp->endpointAddress, 
            0, //pCfgDescr->configurationValue, 
            pNewDev->interface, 
            transferType, 
            direction, 
            maxPayload, //FROM_LITTLEW (pOutEp->maxPacketSize), 
            bandwidth, 
            serviceInterval, 
            handle) 
            != 0 /*OK*/)	
            {
            return nullptr;
            }
        else{
            return handle;
            }

    }

//usbdPipeDestroy( )
//
//NAME
//
//    usbdPipeDestroy( ) - Destroys a USB data transfer pipe
//
//SYNOPSIS
//
//    STATUS usbdPipeDestroy
//        (
//        USBD_CLIENT_HANDLE clientHandle, /* Client handle */
//        USBD_PIPE_HANDLE   pipeHandle    /* pipe handle */
//        )

inline STATUS usbdPipeDestroy(
    USBD_CLIENT_HANDLE clientHandle, /* Client handle */
    USBD_PIPE_HANDLE   pipeHandle    /* pipe handle */
    ){
        return 0;
    }

inline U8 USBPipeDestory(
    PNICOSInterface pDevice, 
    PUSBPipe        pPipe)
    {
    if ( usbdPipeDestroy (0, 0) == 0 /* OK */){
        return 0;
        }
    else{
        return -1;
        }
    }

//usbdTransfer( )
//
//NAME
//
//    usbdTransfer( ) - Initiates a transfer on a USB pipe
//
//SYNOPSIS
//
//    STATUS usbdTransfer
//        (
//        USBD_CLIENT_HANDLE clientHandle, /* Client handle */
//        USBD_PIPE_HANDLE   pipeHandle,   /* Pipe handle */
//        pUSB_IRP           pIrp          /* ptr to I/O request packet */
//        )
//
//DESCRIPTION
//
//    A client uses this function to initiate an transfer on the pipe indicated by pipeHandle. The transfer is described by an IRP, or I/O request packet, which must be allocated and initialized by the caller prior to invoking usbdTransfer( ).
//
//    The USB_IRP structure is defined in usb.h as:
//
//    typedef struct usb_bfr_list
//        {
//        UINT16 pid;
//        pUINT8 pBfr;
//        UINT16 bfrLen;
//        UINT16 actLen;
//        } USB_BFR_LIST;
//
//    typedef struct usb_irp
//        {
//        LINK usbdLink;                // used by USBD
//        pVOID usbdPtr;                // used by USBD
//        LINK hcdLink;                 // used by HCD
//        pVOID hcdPtr;                 // used by HCD
//        pVOID userPtr;
//        UINT16 irpLen;
//        int result;                   // returned by USBD/HCD
//        IRP_CALLBACK usbdCallback;    // used by USBD
//        IRP_CALLBACK userCallback;
//        UINT16 dataToggle;            // filled in by USBD
//        UINT16 flags; 
//        UINT32 timeout;               // defaults to 5 seconds if zero
//        UINT16 startFrame;
//        UINT16 transferLen;
//        UINT16 dataBlockSize;
//        UINT16 bfrCount;
//        USB_BFR_LIST bfrList [1];
//        } USB_IRP, *pUSB_IRP;
//
//    The length of the USB_IRP structure must be stored in irpLen and varies depending on the number of bfrList elements allocated at the end of the structure. By default, the default structure contains a single bfrList element, but clients may allocate a longer structure to accommodate a larger number of bfrList elements.
//
//    flags define additional transfer options. The currently defined flags are:
//
//    USB_FLAG_SHORT_OK
//        Treats receive (IN) data underrun as OK. 
//    USB_FLAG_SHORT_FAIL
//        Treats receive (IN) data underrun as error. 
//    USB_FLAG_ISO_ASAP
//        Start an isochronous transfer immediately.
//
//        When the USB is transferring data from a device to the host the data may "underrun". That is, the device may transmit less data than anticipated by the host. This may or may not indicate an error condition depending on the design of the device. For many devices, the underrun is completely normal and indicates the end of data stream from the device. For other devices, the underrun indicates a transfer failure. By default, the USBD and underlying USB HCD (Host Controller Driver) treat underrun as the end-of-data indicator and do not declare an error. If the USB_FLAG_SHORT_FAIL flag is set, then the USBD/HCD will instead treat underrun as an error condition.
//
//        For isochronous transfers the USB_FLAG_ISO_ASAP specifies that the isochronous transfer should begin as soon as possible. If USB_FLAG_ISO_ASAP is not specified, then startFrame must specify the starting frame number for the transfer. The usbdCurrentFrameGet( ) function allows a client to retrieve the current frame number and a value called the frame scheduling window for the underlying USB host controller. The frame window specifies the maximum number of frames into the future (relative to the current frame number) which may be specified by startFrame. startFrame should be specified only for isochronous transfers.
//
//        dataBlockSize may also be specified for isochronous transfers. If non-0, the dataBlockSize defines the granularity of isochronous data being sent. When the underlying Host Controller Driver (HCD) breaks up the transfer into individual frames, it will ensure that the amount of data transferred in each frame is a multiple of this value.
//
//        timeout specifies the IRP timeout in milliseconds. If the caller passes a value of zero, then the USBD sets a default timeout of USB_TIMEOUT_DEFAULT. If no timeout is desired, then timeout should be set to USB_TIMEOUT_NONE. Timeouts apply only to control and bulk transfers. Isochronous and interrupt transfers do not time out.
//
//        bfrList is an array of buffer descriptors which describe data buffers to be associated with this IRP. If more than the one bfrList element is required then the caller must allocate the IRP by calculating the size as
//
//        irpLen = sizeof (USB_IRP) + (sizeof (USB_BFR_DESCR) * (bfrCount - 1))
//
//        transferLen must be the total length of data to be transferred. In other words, transferLen is the sum of all bfrLen entries in the bfrList.
//
//        pid specifies the packet type to use for the indicated buffer and is specified as USB_PID_xxxx.
//
//        The IRP userCallback routine must point to a client-supplied IRP_CALLBACK routine. The usbdTransfer( ) function returns as soon as the IRP has been successfully enqueued. If there is a failure in delivering the IRP to the HCD, then usbdTransfer( ) returns an error. The actual result of the IRP should be checked after the userCallback routine has been invoked. 
//
//RETURNS
//
//    OK, or ERROR if unable to submit IRP for transfer. 
//
//SEE ALSO
//
//    usbdLib 

inline STATUS usbdTransfer(
    USBD_CLIENT_HANDLE clientHandle, /* Client handle */
    USBD_PIPE_HANDLE   pipeHandle,   /* Pipe handle */
    pUSB_IRP           pIrp          /* ptr to I/O request packet */
    ){
        return 0;
    }

inline U8 USBSendBulkAsync(
    PNICOSInterface pDevice, 
    PUSBPipe pPipe,
    PUrb pUrb,
    PVoid data,
    U32 len,
    PU32 actualLen
    ){
        if (pDevice == NULL)
            return -1;

        //pUSB_IRP pIrp = &pDevCtrl->inIrp;	
        pUSB_IRP pIrp = new USB_IRP();

        /* Initialize IRP */

        //memset (pIrp, 0, sizeof (*pIrp));

        ////pIrp->userPtr = pDevCtrl;
        //pIrp->irpLen = sizeof (*pIrp);
        ////pIrp->userCallback = klsiRxCallback;
        //pIrp->timeout = USB_TIMEOUT_DEFAULT;
        //pIrp->transferLen = pDevCtrl->inBfrLen; 
        //pIrp->flags = USB_FLAG_SHORT_OK;

        //pIrp->bfrCount = 1;

        //pIrp->bfrList[0].pid = USB_PID_IN;
        //pIrp->bfrList[0].bfrLen = pDevCtrl->inBfrLen; 
        //pIrp->bfrList[0].pBfr = (pUINT8)pDevCtrl->pInBfrArray[pDevCtrl->rxIndex] - 2;  

        ///* Submit IRP */

        //if (usbdTransfer (klsiHandle, pDevCtrl->inPipeHandle, (pUSB_IRP)pIrp) != OK)
        //    return ERROR;

        //pDevCtrl->inIrpInUse = TRUE;

        //return OK;

        return 0
    }

#endif


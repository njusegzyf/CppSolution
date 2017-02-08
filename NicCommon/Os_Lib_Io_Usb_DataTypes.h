#ifndef OS_LIB_IO_USB_DATA_TYPES
#define OS_LIB_IO_USB_DATA_TYPES

#include "OS_DataTypes.h"

//定义USB相关的数据类型

typedef PVoid PUsbPipe;

typedef	PVoid PUrb;

// URB回调函数类型
typedef void(*UsbCallback)(PUrb);

// UsbTransferType specifies the type of data transfers for which this pipe will be used: 
typedef enum _UsbTransferType : U8 {

  // Control transfer pipe (message). 
  USB_XFRTYPE_ENUM_CONTROL = 0x01,

  // Isochronous transfer pipe (stream). 
  USB_XFRTYPE_ENUM_ISOCH = 0x02,

  // Interrupt transfer pipe (stream). 
  USB_XFRTYPE_ENUM_INTERRUPT = 0x04,

  // Bulk transfer pipe (stream).
  USB_XFRTYPE_ENUM_BULK = 0x08

  } UsbTransferType;

// UsbTransferDirection specifies the direction of the pipe as:
typedef enum _UsbTransferDirection : U8 {

  // Data moves from device to host. 
  USB_DIR_IN = 0x01,

  // Data moves from host to device. 
  USB_DIR_OUT = 0x02,

  // USB_DIR_ENUM_IN & USB_DIR_ENUM_OUT
  USB_DIR_INOUT = 0x03

  } UsbTransferDirection;

#endif
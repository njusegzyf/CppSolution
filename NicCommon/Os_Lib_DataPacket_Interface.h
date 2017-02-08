#ifndef OS_LIB_DATAPACKET_INTERFACE
#define OS_LIB_DATAPACKET_INTERFACE

#include "Os_DataTypes.h"

struct _NicOsInterface;
typedef struct _NicOsInterface NicOsInterface;

// 操作系统的无关的包缓存
typedef PVoid NicDataPacket;

// get pointer to internal data buffer
PVoid OsGetDataBufferPtr(_IN_ NicDataPacket* pDataPacket);

// 以下两个操作调整缓存的大小

// get internal data buffer size
size_t OsGetDataBufferSize(_IN_ NicDataPacket* pDataPacket);

// set internal data buffer size
OperationStatus OsSetDataBufferSize(
  _IN_ NicDataPacket* pDataPacket,
  _IN_ size_t newDataBufferSize);

// 以下两个操作读取、设置 实际数据大小（或者说数据包大小）

// get internal data length
size_t OsGetDataLength(_IN_ NicDataPacket* pDataPacket);

// set internal data length
OperationStatus OsSetDataLength(
  _IN_ NicDataPacket* pDataPacket,
  _IN_ size_t newDataLength);

// free data packet
void OsFreeDataPacket(
  _IN_ NicOsInterface* pOsInterface,
  _IN_ NicDataPacket* pDataPacket);

#endif
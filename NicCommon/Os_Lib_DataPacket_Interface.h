#ifndef OS_LIB_DATAPACKET_INTERFACE
#define OS_LIB_DATAPACKET_INTERFACE

#include "Os_DataTypes.h"

struct _NicOsInterface;
typedef struct _NicOsInterface NicOsInterface;

// ����ϵͳ���޹صİ�����
typedef PVoid NicDataPacket;

// get pointer to internal data buffer
PVoid OsGetDataBufferPtr(_IN_ NicDataPacket* pDataPacket);

// ��������������������Ĵ�С

// get internal data buffer size
size_t OsGetDataBufferSize(_IN_ NicDataPacket* pDataPacket);

// set internal data buffer size
OperationStatus OsSetDataBufferSize(
  _IN_ NicDataPacket* pDataPacket,
  _IN_ size_t newDataBufferSize);

// ��������������ȡ������ ʵ�����ݴ�С������˵���ݰ���С��

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
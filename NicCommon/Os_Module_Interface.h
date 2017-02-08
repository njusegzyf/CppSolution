#ifndef OS_MODULE_INTERFACE
#define OS_MODULE_INTERFACE

#include "Os_DataTypes.h"
#include "Os_Lib_DataPacket_Interface.h"

struct _NicDeviceInterface;
typedef struct _NicDeviceInterface NicDeviceInterface;

typedef struct _NicOsInterface{
    PVoid Content;
    NicDeviceInterface* pOsInterface;
    } NicOsInterface;

NicOsInterface* CreateOSInterface();

// free data packet
void NicOsTxDataPacketFree(_IN_ NicOsInterface* pOsInterface,
                           _IN_ NicDataPacket* pDataPacket);

void NicOsNotifyTxThrottleState(_IN_ NicOsInterface* pOsInterface,
                                _IN_ bool txThrottleState);


OperationStatus NicOsRequestTxClean(_IN_ NicOsInterface* pOsInterface);

#endif


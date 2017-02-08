#ifndef DEVICE_MODULE_INTERFACE
#define DEVICE_MODULE_INTERFACE

#include "Os_DataTypes.h"
#include "Os_Lib_DataPacket_Interface.h"

#include "Device_Module_Datatypes.h"

// This file includes device module's interface.

#pragma region Device life cycle manipulation

NicDeviceInterface* CreateDeviceInterface(_IN_ NicOsInterface* pOsInterface);

OperationStatus NicDeviceCheckChip(_IN_ NicDeviceInterface* pDeviceModule);

OperationStatus NicDeviceInitChip(_IN_ NicDeviceInterface* pDeviceModule,
                                  _IN_ NicDataPacket* pReceviceBuffers);

OperationStatus NicDeviceStart(_IN_ NicDeviceInterface* pDeviceModule);

OperationStatus NicDeviceClose(_IN_ NicDeviceInterface* pDeviceModule);

OperationStatus NicDeviceReset(_IN_ NicDeviceInterface* pDeviceModule);

OperationStatus NicDeviceCheckForHang(_IN_ NicDeviceInterface* pDeviceModule);

#pragma endregion

#pragma region Device interrupt manipulation

OperationStatus NicDeviceEnableInterrupt(_IN_ NicDeviceInterface* pDeviceModule);

OperationStatus NicDeviceDisableInterrupt(_IN_ NicDeviceInterface* pDeviceModule);

U32 NicDeviceGetInterruptStatus(_IN_ NicDeviceInterface* pDeviceModule);

OperationStatus NicDeviceSetInterruptStatus(_IN_ NicDeviceInterface* pDeviceModule,
  _IN_ U32 value);

OperationStatus NicDeviceHandleInterrupt(_IN_ NicDeviceInterface* pDeviceModule,
  _IN_ U32 interruptStatus);

bool NicDeviceIsRxInterrupt(_IN_ NicDeviceInterface* pDeviceModule,
  _IN_ U32 interruptStatus);

#pragma endregion

#pragma region Device attributes manipulation

OperationStatus NicDeviceSetDefaultAttributes(_IN_ NicDeviceInterface* pDeviceModule);

OperationStatus NicDeviceGetMacAddress(_IN_ NicDeviceInterface* pDeviceModule,
                                       _OUT_ PU8 pAddress);

OperationStatus NicDeviceSetMacAddress(_IN_ NicDeviceInterface* pDeviceModule,
                                       _IN_ PU8 pAddress);

OperationStatus NicDeviceSetMulticastList(NicDeviceInterface* pDeviceModule, EthernetAddress *pMulticastList, int multicastNumber);

OperationStatus NicDeviceGetMulticastList(NicDeviceInterface* pDeviceModule, 
                                          EthernetAddress** ppOutputMulticastList, 
                                          int* outputMulticastNumber);

OperationStatus NicDeviceSetPacketFilter(NicDeviceInterface* pDeviceModule,
                                         U32	filter);

#pragma endregion

#pragma region Device optional attributes

OperationStatus NicDeviceGetAttribute(_IN_ NicDeviceInterface* pDeviceModule,
  _IN_OUT_ SidQueryContent* pQueryContent);

OperationStatus NicDeviceSetAttribute(_IN_ NicDeviceInterface* pDeviceModule,
  _IN_OUT_ SidSetupContent* pSetupContent);

#pragma endregion

#pragma region Device optional services

OperationStatus DeviceSetOptionalService(_IN_ NicDeviceInterface* pDeviceInterface, // 代表设备模块
  _IN_  PVoid pServiceContent                // 代表可选服务的内容
  );

OperationStatus DeviceSetOptionalServiceHandlers(_IN_ NicDeviceInterface* pDeviceInterface, // 代表设备模块
  _IN_ PVoid pServiceHandlers       // 代表可选服务的Handlers
  );

#pragma endregion

OperationStatus NicDeviceGetStatistics(_IN_ NicDeviceInterface* pDeviceModule,
                                       _IN_OUT_ void* pQueryContent);

#pragma region Device interrupt manipulation

OperationStatus NicDeviceEnableInterrupt(_IN_ NicDeviceInterface* pDeviceModule);

OperationStatus NicDeviceDisableInterrupt(_IN_ NicDeviceInterface* pDeviceModule);

U32 NicDeviceGetInterruptStatus(_IN_ NicDeviceInterface* pDeviceModule);

OperationStatus NicDeviceSetInterruptStatus(_IN_ NicDeviceInterface* pDeviceModule, 
                                            _IN_ U32 value);

OperationStatus NicDeviceHandleInterrupt(_IN_ NicDeviceInterface* pDeviceModule, 
                                         _IN_ U32 interruptStatus);

bool NicDeviceIsRxInterrupt(_IN_ NicDeviceInterface* pDeviceModule, 
                            _IN_ U32 interruptStatus);

#pragma endregion

#pragma region Device data transmission and polling 

OperationStatus NicDeviceStartTransmitDataPacket(_IN_ NicDeviceInterface* pDeviceModule,
                                                 _IN_ NicDataPacket* pSendDataPacket);

OperationStatus NicDevicePollingDataPacket(_IN_ NicDeviceInterface* pDeviceModule,
                                           _OUT_ NicDataPacket** ppReciveDataPacket,
                                           _IN_ NicDataPacket* pNewDataPacketBuffer);

void NicDeviceTxClean(_IN_ NicDeviceInterface* pDeviceModule);

#pragma endregion

#endif

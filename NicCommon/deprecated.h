

//Help inline fuctions, not included in Device Interface
inline PVoid NicDeviceGetConfiguration(NicDeviceInterface* pDeviceModule, 
                                       NicDeviceCidType configurationType)
    {
    return pDeviceModule->attributes.configures[configurationType];
    }

inline int NicDeviceSetConfiguration(NicDeviceInterface* pDeviceModule, 
                                     NicDeviceCidType configurationType,
                                     U32 value)
    {
    pDeviceModule->attributes.configures[configurationType] = value;

    return TRUE;
    }

inline U32 NicDeviceGetCurrentSetting(NicDeviceInterface* pDeviceModule, int settingsType)
    {
    return pDeviceModule->attributes.settings[settingsType];
    }

inline int NicDeviceSetCurrentSetting(NicDeviceInterface* pDeviceModule, int settingsType, U32 value)
    {
    pDeviceModule->attributes.settings[settingsType] = value;

    return TRUE;
    }

// 设备Configure标识符
typedef	enum _NicDeviceCidType : int {
    CID_CONNECTION_TYPE=0,
    CID_SLOT_NUMBER,
    CID_BUFFER_PHYSICAL_ADDRESS,
    CID_TXBUFFER_NUMBER,
    CID_RXBUFFER_NUMBER,
    CID_ADAPTER_NUMBER,
    CID_IO_BASE_ADDRESS,
    CID_IO_RANGE,
    CID_IRQ_NUMBER,		// irq pin or line number
    CID_IRQ_LEVEL,		// to raise irql level
    CID_IRQ_GEN_TYPE,	// level sensitive(pci) or latched(isa)
    CID_IRQ_SHARED,		// shared or not
    CID_INTERFACE_TYPE,	// isa or pci device
    CID_BUS_MASTER,		// is a bus master or not
    CID_INTERMEDIATE,	// is a intermediate miniport
    CID_CHECK_FOR_HANG_PERIOD,	// in seconds
    CID_CHIP_STEPPING,
    CID_NEED_IO_SPACE,
    CID_NEED_INTERRUPT,

    /* wireless settings */
    CID_WLAN_NETWORK_TYPE,

    CID_SIZE
    } NicDeviceCidType;

int NicDeviceSetDefaultConfigurationsAndSettings(NicDeviceInterface* pDeviceModule);

int NicDeviceValidateConfigurationsAndSettings(NicDeviceInterface* pDeviceModule);

// int NicDeviceSetDefaultConfigurations(NicDeviceInterface* pDeviceModule);



// int NicDeviceValidateConfigurations(NicDeviceInterface* pDeviceModule);

//int NicDeviceValidateSettings(NicDeviceInterface* pDeviceModule);

//U32 NicDeviceGetConfiguration(NicDeviceInterface* pDeviceModule, int configurationType);

//int NicDeviceSetConfiguration(NicDeviceInterface* pDeviceModule, int configurationType, U32 value);

// #define NIC_SUPPORT_NDIS

#ifdef NIC_SUPPORT_NDIS

#include <ndis.h>
NDIS_OID NicSupportedOid[];

extern int NicSupportedOidSize;

//int NicDeviceRetriveNDISConfigurations(NicDeviceInterface* devicePtr, NDIS_HANDLE hconfig);

//NDIS_STATUS NicDeviceQueryNDISInformation(
//	NicDeviceInterface* devicePtr,
//	NDIS_OID		Oid,
//	PVOID		InfoBuffer, 
//	ULONG		InfoBufferLength, 
//	PULONG		BytesWritten,
//	PULONG		BytesNeeded);
//
//NDIS_STATUS NicDeviceSetNDISInformation(
//	NicDeviceInterface* devicePtr, 
//	NDIS_OID		Oid,
//	PVOID		InfoBuffer, 
//	ULONG		InfoBufferLength, 
//	PULONG		BytesRead,
//	PULONG		BytesNeeded);

#endif // end NIC_SUPPORT_NDIS

bool NicOsIsOutOfResource(_IN_ NicOsInterface* pOsInterface);

typedef	enum _NicIndicationType
    {
    NIC_IND_TX_IDLE=0,
    AID_ERROR=0x8000,
    AID_LARGE_INCOME_PACKET,
    } NicIndicationType;

OperationStatus NicOsReceiveIndication(_IN_ NicOsInterface* pOsInterface, 
                                       _IN_ PVoid data, 
                                       _IN_ int length);

OperationStatus NicOsIndication(_IN_ NicOsInterface* pOsInterface, 
                                _IN_ NicIndicationType uIndication);

OperationStatus NicOsReceiveIndication(_IN_ NicOsInterface* pOsInterface, 
                                       _IN_ NicDataPacket* pReceivedDataPacket);

PU8 NicDeviceRequestTxBuffer(_IN_ NicDeviceInterface* pDeviceModule);

OperationStatus NicDeviceStartTransmit(_IN_ NicDeviceInterface* pDeviceModule,
                                       _IN_ PU8 pTxBuffer,
                                       _IN_ size_t length);

void NicDeviceBeginPolling(_IN_ NicDeviceInterface* pDeviceModule);

void NicDeviceEndPolling(_IN_ NicDeviceInterface* pDeviceModule);

OperationStatus NicDeviceSetDefaultSettings(_IN_ NicDeviceInterface* pDeviceModule);
#ifndef PLATFORM_MODULE_INTERFACE
#define PLATFORM_MODULE_INTERFACE

#include "Os_DataTypes.h"

/**
* platform specification
*/

/**************************
*  CPU 
***************************/
typedef struct _CpuSpecification{
    char* cpuName;
    size_t cpuClockFrequency; // in HZ
    size_t cpuWordLength;
    enum {PLAT_ARM, PLAT_X86, PLAT_MIPS} cpuType;
    enum {PLAT_MEM_MAPPED, PLAT_IO_MAPPED} cpuDevAccessType;
    enum {PLAT_BIG, PLAT_LITTLE} cpuOrder;
    } CpuSpecification;

/*********************
*  BUS
**********************/

struct _DmaChannel;

typedef struct _BusSpecification{
    char* busName;
    size_t busClockFrequency; // in HZ
    size_t busDataWidth;
    enum {PLAT_PCI, PLAT_ISA, PLAT_USB, PLAT_MCA, PLAT_PCMCIA,PLAT_PLATFORM} busType;

    enum {PLAT_DMA, PLAT_NODMA} busDataTransfertype; //data transfer mode
    bool isBusSupportDma;
     struct _DmaChannel* busDmaChannels;

    } BusSpecification;

/**************************
*  IO_ADDR 
***************************/
typedef struct _IoSpecification{
    U32 ioAddress;
    U32 virtualAddress;
    size_t ioSize;
    } IoSpecification;

/*******************
*  IRQ
*******************/
typedef struct _IrqSpecification{
    size_t irqLevel;

    bool isIrqShared;
    // enum {PLAT_SHARED, PLAT_NO_SHARED} shared;

    enum {PLAT_EINT0, PLAT_EINT1, PLAT_EINT2, PLAT_EINT7, PLAT_EINT8, PLAT_EINT9, PLAT_INT_TIMER, PLAT_INT_ADC} irqNo;
    enum {PLAT_TRIGGER_NONE, PLAT_TRIGGER_RISING, PLAT_TRIGGER_FALLING, PLAT_TRIGGER_HIGH, PLAT_TRIGGER_LOW} irqType;
    } IrqSpecification;

typedef struct _DeviceModuleSpecification{
    bool isUsingPollingRx;
    bool isUsingPollingTx;

    size_t requiredReceiveBufferNumber;
    } DeviceModuleSpecification;

/* plarform specification init interface */
extern int NicPlatformSpecInit(void);

#endif	//end of PLATFORM_H
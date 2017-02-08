#ifndef OS_LIB_IO_DMA_INTERFACE
#define OS_LIB_IO_DMA_INTERFACE

#include "Os_DataTypes.h"
#include "Os_Module_Interface.h"

//typedef struct _DmaAddress {
//    } DmaAddress;

typedef int DmaAddress;

typedef enum _DmaDataDirection :char{
    DMA_TO_DEVICE, 
    DMA_FORM_DEVICE, 
    DMA_BIDIRECTIONAL,
    DMA_NONE
    } DmaDataDirection;

typedef int DmaChannel;

typedef PVoid DmaCallback;

typedef PVoid AsyncOperationCallback;

#pragma region DMA缓存API 

// 一致性DMA缓存

// 这个函数的返回值为申请到的DMA缓冲区的虚拟地址。此外，该函数还通过参数busAddress返回DMA缓冲区的总线地址。
PVoid OsDmaAllocCoherent(_IN_ NicOsInterface* pOsInterface,
                         _IN_ size_t size,
                         _IN_ U8 flag,
                         _OUT_ DmaAddress *busAddress);

// 与之 OsDmaAllocCoherent 对应的缓存释放函数
void OsDmaFreeCoherent(_IN_ NicOsInterface* osInterface,
                       _IN_ size_t size,
                       _IN_ U32 flag,
                       _IN_ PVoid cpuAddress,
                       _IN_ DmaAddress *busAddress);

// 流式DMA缓存,即将普通的CPU访问的buffer映射成DMA可以访问的buffer

// 做一次流式DMA映射，如果映射成功，返回的是总线地址，否则返回NULL。最后一个参数DMA的方向，可能取DMA_TO_DEVICE, DMA_FORM_DEVICE, DMA_BIDIRECTIONAL和DMA_NONE。
DmaAddress OsDmaMapSingle(_IN_ NicOsInterface* osInterface,
                          _IN_ PVoid buffer,
                          _IN_ size_t size,
                          _IN_ DmaDataDirection direction);

// 释放函数，释放后可以正常读写（CPU、或者设备）。
void OsDmaUnmapSingle(_IN_ NicOsInterface* osInterface,
                      _IN_ DmaAddress dmaAddress,
                      _IN_ size_t size,
                      _IN_ DmaDataDirection direction);

// 在Unmap前，如果需要读取数据，需要调用一下函数，手动同步以保证Chche一致性：

// 为主机端同步，同步后主机端可以访问主机内存读取同步后的数据
void OsDmaSyncSingleForCpu(_IN_ NicOsInterface* osInterface,
                           _IN_ DmaAddress dmaAddress,
                           _IN_ size_t size,
                           _IN_ DmaDataDirection direction);

// 为设备端同步，同步后设备端可以访问设备内存（设备寄存器）读取同步后的数据
void OsDmaSyncSingleForDevice(_IN_ NicOsInterface* osInterface,
                              _IN_ DmaAddress dmaAddress,
                              _IN_ size_t size,
                              _IN_ DmaDataDirection direction);

#pragma endregion

#pragma region DMA通道API

// 申请DMA通道。
// 输入参数：device_id DMA 设备名；channel 通道号（应该由平台模块提供，代表平台上固定的若干DMA通道）；
// 输出参数：若channel通道已使用，出错返回；否则，返回0
OperationStatus OSDmaChannelRequest(_IN_ NicOsInterface* osInterface,
                                    _IN_ DmaChannel channel);

// 停止DMA通道
OperationStatus OSDmaChannelStop(_IN_ DmaChannel channel);

// 同步刷新DMA通道，即等待所有已请求的DMA操作完成
OperationStatus OSDmaChannelFlush(_IN_ DmaChannel channel);

// 释放DMA通道
OperationStatus OSDmaChannelFree(_IN_ DmaChannel channel);

#pragma endregion

#pragma region 异步DMA读写操作API

// OsDmaRead，将DMA缓存地址（dmaAddress）上的数据，读取到主机缓存（bufferAddress）中，并在操作完成后调用回调函数。
OperationStatus OsDmaRead(_IN_ DmaChannel channel,
                          _IN_ PVoid bufferAddress, 
                          _IN_ DmaAddress dmaAddress,  
                          _IN_ size_t length,        // 以上为启动DMA读写操作的参数，包括DMA通道，源缓存地址，目标DMA地址，以及长度
                          _IN_ PVoid callbackParam,  // 传递给回调（DmaCallback）的参数
                          _IN_ DmaCallback callback);

// OsDmaWrite，将主机缓存（bufferAddress）上的数据，写入DMA缓存地址（dmaAddress）中，并在操作完成后调用回调函数。
OperationStatus OsDmaWrite(_IN_ DmaChannel channel,
                           _IN_ PVoid bufferAddress, 
                           _IN_ DmaAddress dmaAddress,  
                           _IN_ size_t length,        // 以上为启动DMA读写操作的参数，包括DMA通道，源缓存地址，目标DMA地址，以及长度
                           _IN_ PVoid callbackParam,  // 传递给回调（DmaCallback）的参数
                           _IN_ DmaCallback callback);

#pragma endregion

#pragma region 统一的异步读写（DMA读写操作，普通IO操作）

OperationStatus OsAsyncRead(_IN_ NicOsInterface* pOsInterface,
                            _IN_ PVoid sourceAddress, 
                            _IN_ PVoid targetAddress, 
                            _IN_ size_t length,        // 异步读写操作的源地址和目标地址，以及长度
                            _IN_ PVoid callbackParam,  
                            _IN_ AsyncOperationCallback callback);

OperationStatus OsAsyncWrite(_IN_ NicOsInterface* pOsInterface,
                             _IN_ PVoid sourceAddress, 
                             _IN_ PVoid targetAddress, 
                             _IN_ size_t length,        // 异步读写操作的源地址和目标地址，以及长度
                             _IN_ PVoid callbackParam,  
                             _IN_ AsyncOperationCallback callback);

#pragma endregion

#endif
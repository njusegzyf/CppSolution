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

#pragma region DMA����API 

// һ����DMA����

// ��������ķ���ֵΪ���뵽��DMA�������������ַ�����⣬�ú�����ͨ������busAddress����DMA�����������ߵ�ַ��
PVoid OsDmaAllocCoherent(_IN_ NicOsInterface* pOsInterface,
                         _IN_ size_t size,
                         _IN_ U8 flag,
                         _OUT_ DmaAddress *busAddress);

// ��֮ OsDmaAllocCoherent ��Ӧ�Ļ����ͷź���
void OsDmaFreeCoherent(_IN_ NicOsInterface* osInterface,
                       _IN_ size_t size,
                       _IN_ U32 flag,
                       _IN_ PVoid cpuAddress,
                       _IN_ DmaAddress *busAddress);

// ��ʽDMA����,������ͨ��CPU���ʵ�bufferӳ���DMA���Է��ʵ�buffer

// ��һ����ʽDMAӳ�䣬���ӳ��ɹ������ص������ߵ�ַ�����򷵻�NULL�����һ������DMA�ķ��򣬿���ȡDMA_TO_DEVICE, DMA_FORM_DEVICE, DMA_BIDIRECTIONAL��DMA_NONE��
DmaAddress OsDmaMapSingle(_IN_ NicOsInterface* osInterface,
                          _IN_ PVoid buffer,
                          _IN_ size_t size,
                          _IN_ DmaDataDirection direction);

// �ͷź������ͷź����������д��CPU�������豸����
void OsDmaUnmapSingle(_IN_ NicOsInterface* osInterface,
                      _IN_ DmaAddress dmaAddress,
                      _IN_ size_t size,
                      _IN_ DmaDataDirection direction);

// ��Unmapǰ�������Ҫ��ȡ���ݣ���Ҫ����һ�º������ֶ�ͬ���Ա�֤Chcheһ���ԣ�

// Ϊ������ͬ����ͬ���������˿��Է��������ڴ��ȡͬ���������
void OsDmaSyncSingleForCpu(_IN_ NicOsInterface* osInterface,
                           _IN_ DmaAddress dmaAddress,
                           _IN_ size_t size,
                           _IN_ DmaDataDirection direction);

// Ϊ�豸��ͬ����ͬ�����豸�˿��Է����豸�ڴ棨�豸�Ĵ�������ȡͬ���������
void OsDmaSyncSingleForDevice(_IN_ NicOsInterface* osInterface,
                              _IN_ DmaAddress dmaAddress,
                              _IN_ size_t size,
                              _IN_ DmaDataDirection direction);

#pragma endregion

#pragma region DMAͨ��API

// ����DMAͨ����
// ���������device_id DMA �豸����channel ͨ���ţ�Ӧ����ƽ̨ģ���ṩ������ƽ̨�Ϲ̶�������DMAͨ������
// �����������channelͨ����ʹ�ã������أ����򣬷���0
OperationStatus OSDmaChannelRequest(_IN_ NicOsInterface* osInterface,
                                    _IN_ DmaChannel channel);

// ֹͣDMAͨ��
OperationStatus OSDmaChannelStop(_IN_ DmaChannel channel);

// ͬ��ˢ��DMAͨ�������ȴ������������DMA�������
OperationStatus OSDmaChannelFlush(_IN_ DmaChannel channel);

// �ͷ�DMAͨ��
OperationStatus OSDmaChannelFree(_IN_ DmaChannel channel);

#pragma endregion

#pragma region �첽DMA��д����API

// OsDmaRead����DMA�����ַ��dmaAddress���ϵ����ݣ���ȡ���������棨bufferAddress���У����ڲ�����ɺ���ûص�������
OperationStatus OsDmaRead(_IN_ DmaChannel channel,
                          _IN_ PVoid bufferAddress, 
                          _IN_ DmaAddress dmaAddress,  
                          _IN_ size_t length,        // ����Ϊ����DMA��д�����Ĳ���������DMAͨ����Դ�����ַ��Ŀ��DMA��ַ���Լ�����
                          _IN_ PVoid callbackParam,  // ���ݸ��ص���DmaCallback���Ĳ���
                          _IN_ DmaCallback callback);

// OsDmaWrite�����������棨bufferAddress���ϵ����ݣ�д��DMA�����ַ��dmaAddress���У����ڲ�����ɺ���ûص�������
OperationStatus OsDmaWrite(_IN_ DmaChannel channel,
                           _IN_ PVoid bufferAddress, 
                           _IN_ DmaAddress dmaAddress,  
                           _IN_ size_t length,        // ����Ϊ����DMA��д�����Ĳ���������DMAͨ����Դ�����ַ��Ŀ��DMA��ַ���Լ�����
                           _IN_ PVoid callbackParam,  // ���ݸ��ص���DmaCallback���Ĳ���
                           _IN_ DmaCallback callback);

#pragma endregion

#pragma region ͳһ���첽��д��DMA��д��������ͨIO������

OperationStatus OsAsyncRead(_IN_ NicOsInterface* pOsInterface,
                            _IN_ PVoid sourceAddress, 
                            _IN_ PVoid targetAddress, 
                            _IN_ size_t length,        // �첽��д������Դ��ַ��Ŀ���ַ���Լ�����
                            _IN_ PVoid callbackParam,  
                            _IN_ AsyncOperationCallback callback);

OperationStatus OsAsyncWrite(_IN_ NicOsInterface* pOsInterface,
                             _IN_ PVoid sourceAddress, 
                             _IN_ PVoid targetAddress, 
                             _IN_ size_t length,        // �첽��д������Դ��ַ��Ŀ���ַ���Լ�����
                             _IN_ PVoid callbackParam,  
                             _IN_ AsyncOperationCallback callback);

#pragma endregion

#endif
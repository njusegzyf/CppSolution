#ifndef OS_LIB_IO_INTERFACE
#define OS_LIB_IO_INTERFACE

#include "Os_DataTypes.h"

//����ͨ�õġ��ɲ���ϵͳʵ�ֵĻ���IO����

//IO�˿ڶ�д����

#pragma region Read / Write single IO port

OperationStatus OSReadPort8(_IN_ U32 pAddr,     // ���������pAddrָ���˶�ȡ���ڴ��ַ
                            _OUT_ PVoid pData); // ������������ݽ���д�뵽pDataָ����ڴ�

OperationStatus OSWritePort8(_IN_ pAddr, 
                             _IN_ data);

OperationStatus OSReadPort16(_IN_ U32 pAddr,
                             _OUT_ PVoid pData);

OperationStatus OSWritePort16(_IN_ U32 pAddr, 
                              _IN_ U16 data);

OperationStatus OSReadPort32(_IN_ U32 pAddr, 
                             _OUT_ PVoid pData);

intOperationStatus OSWritePort32(_IN_ U32 pAddr, 
                                 _IN_ U32 data);

#pragma endregion

#pragma region Read / Write serveral continous IO ports

OperationStatus OSReadPortBuffer8(_IN_ U32 pAddr,
                                  _OUT_ PVoid pBuffer, 
                                  _IN_ size_t length);

OperationStatus OSReadPortBuffer16(_IN_ U32 pAddr,
                                   _OUT_ PVoid pBuffer, 
                                   _IN_ size_t length);

OperationStatus OSReadPortBuffer32(_IN_ U32 pAddr,
                                   _OUT_ PVoid pBuffer, 
                                   _IN_ size_t length);

#pragma endregion

#endif
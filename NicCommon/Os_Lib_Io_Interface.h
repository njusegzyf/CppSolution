#ifndef OS_LIB_IO_INTERFACE
#define OS_LIB_IO_INTERFACE

#include "Os_DataTypes.h"

//����ͨ�õġ��ɲ���ϵͳʵ�ֵĻ���IO����

//IO�˿ڶ�д����

#pragma region Read / Write single IO port

OperationStatus OsReadPort8(_IN_ U32 pAddr,     // ���������pAddrָ���˶�ȡ���ڴ��ַ
                            _OUT_ PVoid pData); // ������������ݽ���д�뵽pDataָ����ڴ�

OperationStatus OsWritePort8(_IN_ pAddr, 
                             _IN_ data);

OperationStatus OsReadPort16(_IN_ U32 pAddr,
                             _OUT_ PVoid pData);

OperationStatus OsWritePort16(_IN_ U32 pAddr, 
                              _IN_ U16 data);

OperationStatus OsReadPort32(_IN_ U32 pAddr, 
                             _OUT_ PVoid pData);

intOperationStatus OsWritePort32(_IN_ U32 pAddr, 
                                 _IN_ U32 data);

#pragma endregion

#pragma region Read / Write serveral continous IO ports

OperationStatus OsReadPortBuffer8(_IN_ U32 pAddr,
                                  _OUT_ PVoid pBuffer, 
                                  _IN_ size_t length);

OperationStatus OsReadPortBuffer16(_IN_ U32 pAddr,
                                   _OUT_ PVoid pBuffer, 
                                   _IN_ size_t length);

OperationStatus OsReadPortBuffer32(_IN_ U32 pAddr,
                                   _OUT_ PVoid pBuffer, 
                                   _IN_ size_t length);

#pragma endregion

#endif
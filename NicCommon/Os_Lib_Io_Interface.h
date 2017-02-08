#ifndef OS_LIB_IO_INTERFACE
#define OS_LIB_IO_INTERFACE

#include "Os_DataTypes.h"

//定义通用的、由操作系统实现的基本IO操作

//IO端口读写请求

#pragma region Read / Write single IO port

OperationStatus OSReadPort8(_IN_ U32 pAddr,     // 输入参数，pAddr指定了读取的内存地址
                            _OUT_ PVoid pData); // 输出参数，数据将被写入到pData指向的内存

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
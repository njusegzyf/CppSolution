#ifndef OS_DATA_TYPES_DEF
#define OS_DATA_TYPES_DEF

#include<cstdint>

//定义指定位数的数据类型
//typedef	unsigned long   U32;
//typedef	U32*            PU32;
//typedef	unsigned short	U16;
//typedef	U16*            PU16;
//typedef	unsigned char   U8;
//typedef	U8*             PU8;
//typedef void*           PVoid;

typedef uint32_t  U32;
typedef	U32*      PU32;
typedef	uint16_t	U16;
typedef	U16*      PU16;
typedef	uint8_t   U8;
typedef	U8*       PU8;

typedef int32_t   I32;
typedef	I32*      PI32;
typedef	int16_t 	I16;
typedef	I16*      PI16;
typedef	int8_t    I8;
typedef	I8*       PI8;

typedef void*     PVoid;


typedef enum _OperationStatus : U32 {
  STATUS_SUCCESS = 0,

  // 错误类型，无法执行操作

  STATUS_NOT_ACCEPTED,         // 当前不可响应
  STATUS_INVALID_OPERATION,    // 请求类型错误
  STATUS_NOT_SUPPORTED,        // 不支持该请求

  // 错误类型，执行过程出现错误

  STATUS_BUFFER_TOO_SHORT,
  STATUS_INVALID_LENGTH,
  STATUS_INVALID_DATA,

  // 异步操作返回结果

  STATUS_PENDING,

  // 发送（TX）结果，发送成功，但是不可再接受新数据

  STATUS_SUCCESS_TX_THROTTLE,
  STATUS_TX_READY,

  STATUS_RX_READY

  } OperationStatus;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#pragma region Parameter markups

#ifndef _IN_
#define _IN_
#endif

#ifndef _OUT_
#define _OUT_
#endif

#ifndef _IN_OUT_
#define _IN_OUT_
#endif

#pragma endregion

#endif
#ifndef OS_DATA_TYPES_DEF
#define OS_DATA_TYPES_DEF

#include<cstdint>

//����ָ��λ������������
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

  // �������ͣ��޷�ִ�в���

  STATUS_NOT_ACCEPTED,         // ��ǰ������Ӧ
  STATUS_INVALID_OPERATION,    // �������ʹ���
  STATUS_NOT_SUPPORTED,        // ��֧�ָ�����

  // �������ͣ�ִ�й��̳��ִ���

  STATUS_BUFFER_TOO_SHORT,
  STATUS_INVALID_LENGTH,
  STATUS_INVALID_DATA,

  // �첽�������ؽ��

  STATUS_PENDING,

  // ���ͣ�TX����������ͳɹ������ǲ����ٽ���������

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
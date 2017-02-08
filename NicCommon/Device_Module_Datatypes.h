#ifndef DEVICE_MODULE_DATATYPES
#define DEVICE_MODULE_DATATYPES

#include "Os_DataTypes.h"

// This file defines data structures of device module.

// Nic device attribute struct
typedef struct _NicDeviceAttributes{
    PU8				name;
    U32				id;	
    U8 				SA_prom[32];	/* mac address */
    U8 				mcastFilter[8]; /* multicast filter */
    U32				intr_serviced;	/* ISR loop-num */
    U32 			rx_serviced;	/* receive loop-num */
    U8				irqlock;

    //New Attribs
    PU32			configures;
    PU32			settings;

    U16				vendorID;
    U16				productID;
    const char *	vendorDescription;

    } NicDeviceAttributes;

// Nic device status struct
typedef struct _NicDeviceStatus{
    unsigned long	rx_packets;		/* total packets received	*/
    unsigned long	tx_packets;		/* total packets transmitted	*/
    unsigned long	rx_bytes;		/* total bytes received 	*/
    unsigned long	tx_bytes;		/* total bytes transmitted	*/
    unsigned long	rx_errors;		/* bad packets received		*/
    unsigned long	tx_errors;		/* packet transmit problems	*/
    unsigned long	rx_dropped;		/* no space in linux buffers	*/
    unsigned long	tx_dropped;		/* no space available in linux	*/
    unsigned long	multicast;		/* multicast packets received	*/
    unsigned long	collisions;

    /* detailed rx_errors: */
    unsigned long	rx_length_errors;
    unsigned long	rx_over_errors;		/* receiver ring buff overflow	*/
    unsigned long	rx_crc_errors;		/* recved pkt with crc error	*/
    unsigned long	rx_frame_errors;	/* recv'd frame alignment error */
    unsigned long	rx_fifo_errors;		/* recv'r fifo overrun		*/
    unsigned long	rx_missed_errors;	/* receiver missed packet	*/

    /* detailed tx_errors */
    unsigned long	tx_aborted_errors;
    unsigned long	tx_carrier_errors;
    unsigned long	tx_fifo_errors;
    unsigned long	tx_heartbeat_errors;
    unsigned long	tx_window_errors;
    } NicDeviceStatus;

// init device status structure
inline void NicDeviceStatusInit(NicDeviceStatus* dev_stat){
    dev_stat->rx_packets = 0;
    dev_stat->tx_packets = 0;
    dev_stat->rx_bytes = 0;
    dev_stat->tx_bytes = 0;
    dev_stat->rx_errors = 0;
    dev_stat->tx_errors = 0;
    dev_stat->rx_dropped = 0;
    dev_stat->tx_dropped = 0;
    dev_stat->multicast = 0;
    dev_stat->collisions = 0;

    dev_stat->rx_length_errors = 0;
    dev_stat->rx_over_errors = 0;
    dev_stat->rx_crc_errors = 0;
    dev_stat->rx_frame_errors = 0;
    dev_stat->rx_fifo_errors = 0;
    dev_stat->rx_missed_errors = 0;

    dev_stat->tx_aborted_errors = 0;
    dev_stat->tx_carrier_errors = 0;
    dev_stat->tx_fifo_errors = 0;

    dev_stat->tx_heartbeat_errors = 0;
    dev_stat->tx_window_errors = 0;
    }

// 设备Setting标识符
typedef	enum _NicDeviceSidType : int {
    SID_HW_STATUS = 0,
    SID_OP_MODE,
    SID_INT_MASK,
    SID_INT_GEN_MASK,
    SID_PORT_BASE_ADDRESS,
    SID_PHY_NUMBER,
    SID_MEDIA_SUPPORTED,
    SID_MEDIA_IN_USE,
    SID_MEDIA_CONNECTION_STATUS,

    SID_MAXIMUM_LOOKAHEAD,
    SID_MAXIMUM_FRAME_SIZE,
    SID_MAXIMUM_TOTAL_SIZE,
    SID_BUFFER_SIZE,
    SID_MAXIMUM_SEND_PACKETS,
    SID_LINK_SPEED,

    SID_GEN_MAC_OPTIONS,
    SID_802_3_PERMANENT_ADDRESS,
    SID_802_3_CURRENT_ADDRESS,
    SID_802_3_MAXIMUM_LIST_SIZE,
    SID_802_3_MULTICAST_LIST,
    SID_GEN_CURRENT_PACKET_FILTER,
    SID_GEN_TRANSMIT_BUFFER_SPACE,
    SID_GEN_RECEIVE_BUFFER_SPACE,
    SID_GEN_TRANSMIT_BLOCK_SIZE,
    SID_GEN_RECEIVE_BLOCK_SIZE,
    SID_GEN_VENDOR_ID,
    SID_GEN_VENDOR_DESCRIPTION,
    SID_GEN_CURRENT_LOOKAHEAD,
    SID_GEN_DRIVER_VERSION,
    SID_GEN_VENDOR_DRIVER_VERSION,
    SID_GEN_PROTOCOL_OPTIONS,
    } NicDeviceSidType;

typedef struct _SidQueryContent
    {
    NicDeviceSidType    sidType;       // The object identifier of the requested operation.
    PVoid               pBuffer;       // A pointer to a buffer into which the underlying driver returns the requested information for query-information requests.
    int                 bufferLength;  // The size, in bytes, of the buffer at pBuffer. 
    int                 bytesWritten;  // The number of bytes that the underlying driver transfers into the buffer at pBuffer for query-information requests. 
    int                 bytesNeeded;   // The number of bytes that are required to return query information requested by the given sidType.
    } SidQueryContent;

typedef struct _SidSetupContent
    {
    NicDeviceSidType    sidType;       // The object identifier of the requested operation.
    PVoid               pBuffer;       // A pointer to a buffer from which the underlying driver reads caller-supplied information for set-information requests.
    int                 bufferLength;  // The size, in bytes, of the buffer at pBuffer. 
    int                 bytesRead;     // The number of bytes that the underlying driver read from the buffer at pBuffer for set-information requests.
    int                 bytesNeeded;   // The number of bytes that are required to carry out the set operation requested by the given sidType.
    } SidSetupContent;

struct _NicOSInterface;

// Nic device module struct
typedef struct _NicDeviceInterface{
    NicDeviceAttributes attributes;
    NicDeviceStatus status;
    PVoid content;
    struct _NicOSInterface* pOsInterface;
    } NicDeviceInterface;

#pragma region Ethernet definitions

#define ETH_MAX_FRAME_SIZE  1514
#define ETH_HEADER_SIZE     14
#define ETH_CRC_SIZE     	4
#define ETH_ADDRESS_LENGTH  6

#define	MAX_MULTICAST_LIST	64

typedef U8 EthernetAddress[ETH_ADDRESS_LENGTH];

#pragma endregion

#endif
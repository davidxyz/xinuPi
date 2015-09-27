/**
 * @file mtags.h
 * Constants and declarations associated with the framebuffer system.
 */

#ifndef _MTAGS_H_
#define _MTAGS_H_
#include <device.h>
#include <stddef.h>
//unused space: might as well use it
#define BUFFER_ADDRESS 0x1000
#define RR_REQUEST 0x00000000
#define RR_RESPONSE_OK 0x80000000
#define RR_RESPONSE_ERROR 0x80000001
#define SLOT_OVERALL_LENGTH 0
#define SLOT_RR 1
#define SLOT_TAGSTART 2
#define SLOT_TAG_ID 0
#define SLOT_TAG_BUFLEN 1
#define SLOT_TAG_DATALEN 2
#define SLOT_TAG_DATA 3
#define MBOX_HEADER_LENGTH 2
#define TAG_HEADER_LENGTH 3
#define MBX_DEVICE_SDCARD 0x00000000
#define MBX_DEVICE_UART0 0x00000001
#define MBX_DEVICE_UART1 0x00000002
#define MBX_DEVICE_USBHCD 0x00000003
#define MBX_DEVICE_I2C0 0x00000004
#define MBX_DEVICE_I2C1 0x00000005
#define MBX_DEVICE_I2C2 0x00000006
#define MBX_DEVICE_SPI 0x00000007
#define MBX_DEVICE_CCP2TX 0x00000008
#define MBX_TAG_GET_FIRMWARE 0x00000001 /* in 0, out 4 */
#define MBX_TAG_GET_BOARD_MODEL 0x00010001 /* in 0, out 4 */
#define MBX_TAG_GET_BOARD_REVISION 0x00010002 /* in 0, out 4 */
#define MBX_TAG_GET_MAC_ADDRESS 0x00010003 /* in 0, out 6 */
#define MBX_TAG_GET_BOARD_SERIAL 0x00010004 /* in 0, out 8 */
#define MBX_TAG_GET_ARM_MEMORY 0x00010005 /* in 0, out 8 (4 -> base addr, 4 -> len in bytes) */
#define MBX_TAG_GET_VC_MEMORY 0x00010006 /* in 0, out 8 (4 -> base addr, 4 -> len in bytes) */
#define MBX_TAG_GET_COMMANDLINE 0x00050001 /* in 0, out variable */
#define MBX_TAG_GET_DMA_CHANNELS 0x00060001 /* in 0, out 4 */
#define MBX_TAG_GET_POWER_STATE 0x00020001 /* in 4 -> dev id, out 8 (4 -> device, 4 -> status) */
#define MBX_TAG_GET_TIMING 0x00020002 /* in 0, out 4 */
#define MBX_TAG_GET_FIRMWARE 0x00000001 /* in 0, out 4 */

#define ADDR_LEN 8
uchar* return_response(int);
uchar* get_parameter(ulong, int);
void add_mailbox_tag(volatile ulong* , ulong , ulong , ulong , ulong* );
void build_mailbox_request(volatile ulong* );
void print_parameter(const char*, ulong, int);
void dump_response(const char*, int);
ulong readmailbox(ulong);
void writemailbox(ulong, ulong);
#endif /* _MTAGS_H_*/

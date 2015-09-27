/**
 * @file mtags.c
 *
 * Provides communication channels between VC and ARM.
 */
/* Embedded Xinu, Copyright (C) 2013.  All rights reserved. */
/*
 *  * Access system mailboxes
 *   */

/* Mailbox memory addresses */
static volatile unsigned int *MAILBOX0READ = (unsigned int *) 0x2000b880;
static volatile unsigned int *MAILBOX0STATUS = (unsigned int *) 0x2000b898;
static volatile unsigned int *MAILBOX0WRITE = (unsigned int *) 0x2000b8a0;

/* Bit 31 set in status register if the write mailbox is full */
#define MAILBOX_FULL 0x80000000

/* Bit 30 set in status register if the read mailbox is empty */
#define MAILBOX_EMPTY 0x40000000
#include <stddef.h>
#include <stdio.h>
#include <mtags.h>
#include <barrier.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Read from mailbox one on channel one (GPU mailbox) */
/* Note: Data: first 28 bits. Channel: last 4 bits.   */
//index for loops
int i = 0;
//add multiple tags so we 
void add_mailbox_tag(volatile ulong* buffer, ulong tag, ulong buflen, ulong len, ulong* data) {
  volatile ulong* start = buffer + SLOT_TAGSTART;
  start[SLOT_TAG_ID] = tag;
  start[SLOT_TAG_BUFLEN] = buflen;
  start[SLOT_TAG_DATALEN] = len & 0x7FFFFFFF;
  ulong bufwords = buflen >> 2;
  if (0 == data) {
    for (i = 0; i < bufwords; ++i) {
      start[SLOT_TAG_DATA + i] = 0;
    }
  } else {
    for (i = 0; i < bufwords; ++i) {
      start[SLOT_TAG_DATA + i] = data[i];
    }
  }
  start[SLOT_TAG_DATA+bufwords] = 0; // end of tags, unless overwritten later
}
void build_mailbox_request(volatile ulong* buffer) {
  ulong tag_length = buffer[MBOX_HEADER_LENGTH + SLOT_TAG_BUFLEN];
  ulong end = (MBOX_HEADER_LENGTH*4) + (TAG_HEADER_LENGTH*4) + tag_length;
  ulong overall_length = end + 4;
  buffer[SLOT_OVERALL_LENGTH] = overall_length;
  buffer[SLOT_RR] = RR_REQUEST;
}
volatile ulong *mailbuffer = (ulong *) BUFFER_ADDRESS;
void dump_response(const char*name, int nwords){
	printf(name);
	printf(": ");
	for (i = 0; i < nwords; ++i) {
	    ulong value = mailbuffer[MBOX_HEADER_LENGTH + TAG_HEADER_LENGTH + i];
	    printf("%08x", (unsigned int)value);
	    printf(" ");
        }
	printf("\r\n");
}
uchar* return_response(int nwords){
	ulong value = 0;
	uchar *s = malloc(10*sizeof(uchar));
	bzero(s,10);
	uint offset = 0;
	uint binaryOffset = 3;
	uint x = 0;
	
	for(i=0;i < nwords; i++){
		value = mailbuffer[MBOX_HEADER_LENGTH + TAG_HEADER_LENGTH + i];
		//printf("\r\n\r\nulong MAC address: %d\r\n\r\n", value);
		for(x = 0;x < 4; x++){
			if( ((value >> (8*binaryOffset)) & 0b11111111) == 0){
				binaryOffset--;
				continue;
			} 
			s[offset++] = (unsigned char)( value >> (8*binaryOffset) & 0b11111111); 
			binaryOffset--;
		}
		binaryOffset = 3;
	}
	return s;
}
/*int main()
{
    char *hexstring = "deadbeef10203040b00b1e50";
    int i;
    unsigned int bytearray[12];
    uint8_t str_len = strlen(hexstring);

    for (i = 0; i < (str_len / 2); i++) {
        sscanf(hexstring + 2*i, "%02x", &bytearray[i]);
        printf("bytearray %d: %02x\n", i, bytearray[i]);
    }

    return 0;
}*/
void print_parameter(const char* name, ulong tag, int nwords) {
  add_mailbox_tag(mailbuffer, tag, nwords * 4, 0, 0);
  build_mailbox_request(mailbuffer);
  writemailbox(8, (ulong)mailbuffer);
  readmailbox(8);
  /* Valid response in data structure */
    if(mailbuffer[1] != 0x80000000) {
              printf("(error:");
                  //raspi_mini_uart_send_newline();
                     //dump_mailbox_to_uart();
                        } else {
                            dump_response(name, nwords);
		      }
}
uchar* get_parameter(ulong tag,int nwords){
  add_mailbox_tag(mailbuffer, tag, nwords * 4, 0, 0);
  build_mailbox_request(mailbuffer);
  writemailbox(8, (ulong)mailbuffer);
  readmailbox(8);
  /* Valid response in data structure */
    if(mailbuffer[1] != 0x80000000) {
             return 0;
	} else {
	 return return_response(nwords);
      }
}
ulong readmailbox(ulong channel) {
  ulong count = 0;
  ulong data;

	/* Loop until something is received from channel
 * 	 * If nothing recieved, it eventually give up and returns 0xffffffff
 * 	 	 */
	while(1) {
		while (*MAILBOX0STATUS & MAILBOX_EMPTY) {
			/* Need to check if this is the right thing to do */
			flushcache();

			/* This is an arbritarily large number */
			if(count++ >(1<<25)) {
				return 0xffffffff;
			}
		}

		/* Read the data
 * 		 * Data memory barriers as we've switched peripheral
 * 		 		 */
		dmb();
		data = *MAILBOX0READ;
		dmb();

		if ((data & 15) == channel)
			return data;
	}

	return 0;
}

void writemailbox(ulong channel, ulong data) {
	/* Wait for mailbox to be not full */
	while (*MAILBOX0STATUS & MAILBOX_FULL) 	{
		/* Need to check if this is the right thing to do */
		flushcache();
	}

	dmb();
	*MAILBOX0WRITE = (data | channel);
}


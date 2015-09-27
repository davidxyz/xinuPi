/*
 * @file     xsh_pistat.c
 *
 */
/* Embedded Xinu, Copyright (C) 2008.  All rights reserved. */

#include <stddef.h>
#include <stdio.h>
#include <mtags.h>

/**
 *
 * @ingroup shell
 * @ displays hardware stats of the pi
 * @return OK for success, SYSERR for syntax error
 */
shellcmd xsh_pistat(int nargs, char *args[])
{
	printf("pistat:\r\n");
        print_parameter("firmware", MBX_TAG_GET_FIRMWARE, 1);
        print_parameter("board model", MBX_TAG_GET_BOARD_MODEL, 1);
        print_parameter("board rev", MBX_TAG_GET_BOARD_REVISION, 1);
        print_parameter("mac address", MBX_TAG_GET_MAC_ADDRESS, 2);
        print_parameter("board serial", MBX_TAG_GET_BOARD_SERIAL, 2);
        print_parameter("arm mem", MBX_TAG_GET_ARM_MEMORY, 2);
        print_parameter("vc mem", MBX_TAG_GET_VC_MEMORY, 2); 

	
    return OK;
}

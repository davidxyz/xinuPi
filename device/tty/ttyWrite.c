/**
 * @file     ttyWrite.c
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <device.h>
#include <tty.h>

/**
 * @ingroup tty
 *
 * Write a buffer to a tty
 * @param devptr TTY device table entry
 * @param buf buffer of characters to output
 * @param len size of the buffer
 * @return count of characters output
 */
devcall ttyWrite(device *devptr, void *buf, uint len)
{
    uchar ch = 0;
    uint count = 0;
    uchar *buffer = buf;

    /* Write all characters in buffer */
    while (count < len)
    {
        ch = *buffer++;
        if (SYSERR == ttyPutc(devptr, ch))
        {
            return SYSERR;
        }
        count++;
    }

    return count;
}

/* @file snoopClose.c
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <interrupt.h>
#include <network.h>
#include <snoop.h>

/**
 * @ingroup snoop
 *
 * Closes a capture from a network device or file.
 * @param cap pointer to capture structure
 * @return OK if close was successful, otherwise SYSERR
 */
int snoopClose(struct snoop *cap)
{
    struct packet *pkt;
    int i;
    irqmask im;

    /* Error check pointers */
    if (NULL == cap)
    {
        return SYSERR;
    }

    /* Remove capture from all network interface */
    im = disable();
#if NNETIF
    for (i = 0; i < NNETIF; i++)
    {
        if (netiftab[i].capture == cap)
        {
            netiftab[i].capture = NULL;
        }
    }
#endif
    restore(im);

    /* Free queued packets */
    while (mailboxCount(cap->queue) > 0)
    {
        pkt = (struct packet *)mailboxReceive(cap->queue);
        if (SYSERR == netFreebuf(pkt))
        {
            return SYSERR;
        }
    }

    /* Free mailbox */
    if (SYSERR == mailboxFree(cap->queue))
    {
        return SYSERR;
    }

    return OK;
}

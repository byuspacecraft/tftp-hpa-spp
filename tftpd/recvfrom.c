/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2001-2006 H. Peter Anvin - All Rights Reserved
 *
 *   This program is free software available under the same license
 *   as the "OpenBSD" operating system, distributed at
 *   http://www.openbsd.org/.
 *
 * ----------------------------------------------------------------------- */

/*
 * recvfrom.c
 *
 * Emulate recvfrom() using recvmsg(), but try to capture the local address
 * since some TFTP clients consider it an error to get the reply from another
 * IP address than the request was sent to.
 *
 */

#include "config.h"             /* Must be included first! */
#include "common/tftpsubs.h"
#include "recvfrom.h"
#ifdef HAVE_MACHINE_PARAM_H
#include <machine/param.h>      /* Needed on some versions of FreeBSD */
#endif

#include <sys/uio.h>

    int
myrecvfrom(int s, void *buf, int len, unsigned int flags,
        struct sockaddr *from, socklen_t * fromlen,
        union sock_addr *myaddr)
{
    bzero(myaddr, sizeof(*myaddr));
    myaddr->sa.sa_family = from->sa_family;

    return recvfrom(s, buf, len, flags, from, fromlen);
}

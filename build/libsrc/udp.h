/**
 * socketproxy/src/library/udp.h
 * (c) 2010 Mike Doyle
 */

#ifndef __SP_UDP_H
#define __SP_UDP_H

#include <sys/socket.h>

ssize_t recvfrom( int sockfd, void *buff, size_t nbytes, int flags,
        struct sockaddr *from, socklen_t *addrlen );

ssize_t sendto( in sockfd, const void *buff, size_t nbytes, int flags,
        const struct sockaddr *to, socklen_t addrlen );

#endif

/**
 * socketproxy/src/library/socket.h
 * (c) 2010 Mike Doyle
 */

#ifndef __SP_SOCKET_H
#define __SP_SOCKET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/un.h>
#include "serialize.h"

#define DEBUG 0

int socket(int family, int type, int protocol);

int connect ( int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen);


#endif
